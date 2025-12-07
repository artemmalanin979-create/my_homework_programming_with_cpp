#include "Dragon.h"

constexpr int DEPTH = 20;  

int main() {
    DragonWindow win(800, 600, DEPTH);
    win.show();
    return Fl::run();
}