#include "image.h"

#include <algorithm>
#include <fstream>

Image::Image(int width, int height, Color clear_color)
    : width_(width), height_(height), pixels_(width * height, clear_color) {}

int Image::width() const {
    return width_;
}

int Image::height() const {
    return height_;
}

void Image::clear(Color color) {
    std::fill(pixels_.begin(), pixels_.end(), color);
}

void Image::setPixel(int x, int y, Color color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    pixels_[y * width_ + x] = color;
}

bool Image::writePPM(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }

    out << "P6\n" << width_ << " " << height_ << "\n255\n";
    for (const Color& pixel : pixels_) {
        out.write(reinterpret_cast<const char*>(&pixel.r), 1);
        out.write(reinterpret_cast<const char*>(&pixel.g), 1);
        out.write(reinterpret_cast<const char*>(&pixel.b), 1);
    }
    return true;
}