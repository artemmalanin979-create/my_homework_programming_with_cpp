#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <vector>

struct Point { int x{}, y{}; };

class DragonWindow : public Fl_Window {
public:
    DragonWindow(int w, int h, int depth);
private:
    void draw() override;
    int  depth_;
    std::vector<Point> points_;
};