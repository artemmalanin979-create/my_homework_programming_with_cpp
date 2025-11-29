#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// типы и токены //

struct Token {
    int kind;   // 0 = число, 1 = оператор, 2 = '(', 3 = ')', 4 = конец
    long value; // только для числа
    char op;    // символ оператора/скобки
};
Token curr_tok;     // текущий токен, который видит парсер
string expr_str;    // строка выражения
size_t pos;         // указатель на текущий символ в строке

// возможные операции с числами //

long bitwise_and(long a, long b) { return a & b; }
long bitwise_or (long a, long b) { return a | b; }
long bitwise_xor(long a, long b) { return a ^ b; }
long unary_minus(long a)         { return -a; }
long unary_plus (long a)         { return +a; }
long bitwise_not(long a)         { return ~a; }
long left_shift(long a, long b)  {
    if (b < 0) {
        cout << "Сдвиг на отрицательное число бит невозможен.\n";
        return 0;
    }
    return (a << b);
}
long right_shift(long a, long b) {
    if (b < 0) {
        cout << "Сдвиг на отрицательное число бит невозможен.\n";
        return 0;
    }
    return ((unsigned long)a >> b);
}

// считывание чисел //

long read_number() {
    // проверка что за сс //
    long val = 0;
    if (pos + 1 < expr_str.size() && expr_str[pos] == '0') { //0b
        char c = expr_str[pos + 1];
        if (c == 'b') {
            pos += 2;
            while (pos < expr_str.size() && (expr_str[pos] == '0' || expr_str[pos] == '1'))
                val = val * 2 + (expr_str[pos++] - '0');
        } else if (c == 'o') { //0o
            pos += 2;
            while (pos < expr_str.size() && expr_str[pos] >= '0' && expr_str[pos] <= '7')
                val = val * 8 + (expr_str[pos++] - '0');
        } else if (c == 'x') { //0x
            pos += 2;
            while (pos < expr_str.size() && isxdigit(expr_str[pos])) {
                char d = expr_str[pos++];
                int n = isdigit(d) ? d - '0' : 10 + tolower(d) - 'a';
                val = val * 16 + n;
            }
        } else { 
            while (pos < expr_str.size() && isdigit(expr_str[pos]))
                val = val * 10 + (expr_str[pos++] - '0');
        }
    } else { // обычное десятичное
        while (pos < expr_str.size() && isdigit(expr_str[pos]))
            val = val * 10 + (expr_str[pos++] - '0');
    }
    return val;
}

// лексер //

void next_token(){
    while (pos < expr_str.size() && isspace(expr_str[pos])) ++pos;
    if (pos >= expr_str.size()){ 
        curr_tok.kind = 4;
        return;
    } 
    char c = expr_str[pos];

    // скобки
    if (c == '(' || c == ')'){
        curr_tok.kind = (c == '(' ? 2 : 3);
        curr_tok.op   = c;
        ++pos;
        return;
    }
    // двухсимвольные <<  >>
    if (c == '<' && pos + 1 < expr_str.size() && expr_str[pos + 1] == '<'){
        curr_tok.kind = 1;
        curr_tok.op = '<'; 
        pos += 2; return;
    }
    if (c == '>' && pos + 1 < expr_str.size() && expr_str[pos + 1] == '>'){
        curr_tok.kind = 1; 
        curr_tok.op = '>'; 
        pos += 2; return;
    }
    // одиночные операторы
    if (c == '~' || c == '&' || c == '|' || c == '^' || c == '+' || c == '-') {
        curr_tok.kind = 1;
        curr_tok.op = c;
        ++pos;
        return;
    }
    // число
    if (isdigit(c) || c == '-' ||
        (c == '0' && pos + 1 < expr_str.size() &&
        (expr_str[pos + 1] == 'b' || expr_str[pos + 1] == 'o' || expr_str[pos + 1] == 'x'))){
        curr_tok.kind  = 0;
        curr_tok.value = read_number();
        return;
    }
}

// дерево //

struct Node {
    int  type;        // 0 = число, 1 = бинарная операция, 2 = унарная
    char op;          // символ операции 
    long val;
    Node *left, *right;
    Node(int t,char o,long v,Node *l=nullptr,Node *r=nullptr)
        : type(t), op(o), val(v), left(l), right(r) {}
    ~Node() { delete left; delete right; } // деструктор
};

// парсер //

Node* expr();
// расставляем приоритеты
Node* primary(){ // самый высокий: число, скобки, ~
    if (curr_tok.kind == 0){ // число
        Node *n = new Node(0, 0, curr_tok.value);
        next_token();
        return n;
    }
    if (curr_tok.kind == 2 && curr_tok.op == '('){ // скобки
        next_token();
        Node *e = expr();
        if (!(curr_tok.kind == 3 && curr_tok.op == ')')) cout << "Missing )\n";
        else next_token();
        return e;
    }
    if (curr_tok.kind == 1 && (curr_tok.op=='+' || curr_tok.op=='-' || curr_tok.op=='~')) {
        char op = curr_tok.op;
        next_token();
        return new Node(2, op, 0, primary(), nullptr);
    }
    cout << "Syntax error\n";
    next_token();
    return new Node(0, 0, 0);
}

Node* shift_expr(){ // << >>
    Node *left = primary();
    while (curr_tok.kind == 1 && (curr_tok.op == '<' || curr_tok.op == '>')){
        char op = curr_tok.op;
        next_token();
        left = new Node(1, op, 0, left, primary());
    }
    return left;
}

Node* and_expr(){ // &
    Node *left = shift_expr();
    while (curr_tok.kind == 1 && curr_tok.op == '&'){
        next_token();
        left = new Node(1, '&', 0, left, shift_expr());
    }
    return left;
}

Node* xor_expr(){ // ^
    Node *left = and_expr();
    while (curr_tok.kind == 1 && curr_tok.op == '^'){
        next_token();
        left = new Node(1, '^', 0, left, and_expr());
    }
    return left;
}

Node* expr(){ // самый низкий: |
    Node *left = xor_expr();
    while (curr_tok.kind == 1 && curr_tok.op == '|'){
        next_token();
        left = new Node(1, '|', 0, left, xor_expr());
    }
    return left;
}

// вычисления //

long eval(Node *n){
     // число
    if (n -> type == 0){
        return n -> val;
    }
    // унарная
    if (n -> type == 2){
        long v = eval(n -> left);
        if (n -> op == '~') return bitwise_not(v);
        if (n -> op == '-') return unary_minus(v);
        if (n -> op == '+') return unary_plus(v);
        return 0;
    }
    // бинарная
    long l = eval(n -> left);
    long r = eval(n -> right);
    switch (n -> op){
        case '&': return bitwise_and(l, r);
        case '|': return bitwise_or (l, r);
        case '^': return bitwise_xor(l, r);
        case '<': return left_shift (l, r);
        case '>': return right_shift(l, r);
    }
    return 0;
}

// вывод //

void print_result(long v){
    unsigned long u = (unsigned long)v;
    cout << "Answer:\n";
    cout << "0b";
    int lead = 1;
    for (int i = 31; i >= 0; --i){
        int b = (u >> i) & 1;
        if (lead && b == 0 && i) continue;
        lead = 0;
        cout << b;
    }
    if (lead) cout << '0';
    cout << "  " << v << "  0x" << hex << u << dec << '\n';
}

// наш main //

int main() {
    cout << "BitCalc. Empty line to quit.\n";
    for (;;) {
        cout << "Bitwise expression:\n";
        string line;
        if (!getline(cin, line) || line.empty()) break;

        expr_str = line;
        pos = 0;
        next_token();
        Node *root = expr();
        long res = eval(root);
        print_result(res);
        delete root;
    }
    return 0;
}