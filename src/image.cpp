#include "image.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>

namespace {

void writeU16(std::ofstream& out, std::uint16_t value) {
    out.put(static_cast<char>(value & 0xff));
    out.put(static_cast<char>((value >> 8) & 0xff));
}

void writeU32(std::ofstream& out, std::uint32_t value) {
    out.put(static_cast<char>(value & 0xff));
    out.put(static_cast<char>((value >> 8) & 0xff));
    out.put(static_cast<char>((value >> 16) & 0xff));
    out.put(static_cast<char>((value >> 24) & 0xff));
}

bool ensureParentDirectory(const std::string& path) {
    const std::filesystem::path file_path(path);
    const std::filesystem::path parent = file_path.parent_path();
    if (parent.empty()) {
        return true;
    }

    std::error_code error;
    std::filesystem::create_directories(parent, error);
    return !error;
}

} // namespace

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

void Image::drawLine(int x0, int y0, int x1, int y1, Color color) {
    const int dx = std::abs(x1 - x0);
    const int dy = std::abs(y1 - y0);
    const int steps = std::max(dx, dy);

    if (steps == 0) {
        setPixel(x0, y0, color);
        return;
    }

    for (int i = 0; i <= steps; ++i) {
        const float t = static_cast<float>(i) / static_cast<float>(steps);
        const int x = static_cast<int>(std::round(x0 + t * (x1 - x0)));
        const int y = static_cast<int>(std::round(y0 + t * (y1 - y0)));
        setPixel(x, y, color);
    }
}

bool Image::writePPM(const std::string& path) const {
    if (!ensureParentDirectory(path)) {
        return false;
    }

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

bool Image::writeBMP(const std::string& path) const {
    if (!ensureParentDirectory(path)) {
        return false;
    }

    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }

    constexpr std::uint32_t file_header_size = 14;
    constexpr std::uint32_t info_header_size = 40;
    constexpr std::uint16_t bits_per_pixel = 24;

    const std::uint32_t row_stride = static_cast<std::uint32_t>((width_ * 3 + 3) & ~3);
    const std::uint32_t pixel_data_size = row_stride * static_cast<std::uint32_t>(height_);
    const std::uint32_t pixel_data_offset = file_header_size + info_header_size;
    const std::uint32_t file_size = pixel_data_offset + pixel_data_size;

    // BMP file header.
    out.put('B');
    out.put('M');
    writeU32(out, file_size);
    writeU16(out, 0);
    writeU16(out, 0);
    writeU32(out, pixel_data_offset);

    // BITMAPINFOHEADER.
    writeU32(out, info_header_size);
    writeU32(out, static_cast<std::uint32_t>(width_));
    writeU32(out, static_cast<std::uint32_t>(height_));
    writeU16(out, 1);
    writeU16(out, bits_per_pixel);
    writeU32(out, 0);
    writeU32(out, pixel_data_size);
    writeU32(out, 2835);
    writeU32(out, 2835);
    writeU32(out, 0);
    writeU32(out, 0);

    const int padding = static_cast<int>(row_stride) - width_ * 3;
    const char padding_bytes[3] = {0, 0, 0};

    // Positive BMP height stores rows bottom-up.
    for (int y = height_ - 1; y >= 0; --y) {
        for (int x = 0; x < width_; ++x) {
            const Color& pixel = pixels_[y * width_ + x];
            out.put(static_cast<char>(pixel.b));
            out.put(static_cast<char>(pixel.g));
            out.put(static_cast<char>(pixel.r));
        }
        out.write(padding_bytes, padding);
    }

    return true;
}