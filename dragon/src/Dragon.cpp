#include "Dragon.h"
#include <cmath>
#include <string>

static std::vector<Point> buildDragon(int depth) {
    std::string seq = "F";
    for (int i = 0; i < depth; ++i) {
        std::string tmp;
        for (char c : seq) {
            if (c == 'F') tmp += "F+G";
            else if (c == 'G') tmp += "F-G";
            else tmp += c;
        }
        seq = std::move(tmp);
    }

    std::vector<Point> pts;
    int x = 0, y = 0, dx = 1, dy = 0;
    pts.push_back({x, y});

    for (char c : seq) {
        if (c == 'F' || c == 'G') {
            x += dx; y += dy;
            pts.push_back({x, y});
        } else if (c == '+') {
            // поворот на 90° влево
            int ndx = -dy, ndy = dx;
            dx = ndx; dy = ndy;
        } else if (c == '-') {
            // поворот на 90° вправо
            int ndx = dy,  ndy = -dx;
            dx = ndx; dy = ndy;
        }
    }
    return pts;
}

DragonWindow::DragonWindow(int w, int h, int depth)
    : Fl_Window(w, h, "Dragon Harter"), depth_(depth) {
    points_ = buildDragon(depth_);
    color(FL_WHITE);
    resizable(this);
}

void DragonWindow::draw() {
    Fl_Window::draw();
    fl_color(FL_BLACK);
    fl_line_style(FL_SOLID, 2);

    const int margin = 20;
    int minX = points_[0].x, maxX = minX, minY = points_[0].y, maxY = minY;
    for (auto &p : points_) {
        minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
    }
    double scale = std::min((w() - 2*margin) / double(maxX - minX),
                            (h() - 2*margin) / double(maxY - minY));
    int ox = (w() - int((maxX - minX)*scale)) / 2 - int(minX*scale);
    int oy = (h() - int((maxY - minY)*scale)) / 2 - int(minY*scale);

    for (size_t i = 1; i < points_.size(); ++i) {
        fl_line(ox + int(points_[i-1].x * scale),
                oy + int(points_[i-1].y * scale),
                ox + int(points_[i].x   * scale),
                oy + int(points_[i].y   * scale));
    }
}