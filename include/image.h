#pragma once

#include "color.h"

#include <string>
#include <vector>

class Image {
public:
    Image(int width, int height, Color clear_color = Color{});

    int width() const;
    int height() const;

    void clear(Color color);
    void setPixel(int x, int y, Color color);
    void drawLine(int x0, int y0, int x1, int y1, Color color);
    bool writePPM(const std::string& path) const;
    bool writeBMP(const std::string& path) const;

private:
    int width_ = 0;
    int height_ = 0;
    std::vector<Color> pixels_;
};