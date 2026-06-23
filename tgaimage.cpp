#include "tgaimage.h"

#include <fstream>

TGAImage::TGAImage(int width, int height, int bytespp)
    : width_(width), height_(height), bytespp_(bytespp), data_(width * height * bytespp, 0) {}

bool TGAImage::set(int x, int y, const TGAColor &color) {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        return false;
    }

    const int index = (x + y * width_) * bytespp_;
    for (int i = 0; i < bytespp_; i++) {
        data_[index + i] = color[i];
    }
    return true;
}

bool TGAImage::write_tga_file(const std::string &filename, bool vflip) const {
    TGAHeader header;
    header.datatypecode = 2;
    header.width = static_cast<std::uint16_t>(width_);
    header.height = static_cast<std::uint16_t>(height_);
    header.bitsperpixel = static_cast<std::uint8_t>(bytespp_ << 3);
    header.imagedescriptor = vflip ? 0x00 : 0x20;

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&header), sizeof(header));

    if (vflip) {
        const int row_bytes = width_ * bytespp_;
        for (int y = height_ - 1; y >= 0; --y) {
            out.write(reinterpret_cast<const char*>(data_.data() + y * row_bytes), row_bytes);
        }
    } else {
        out.write(reinterpret_cast<const char*>(data_.data()), static_cast<std::streamsize>(data_.size()));
    }

    static constexpr char developer_area_ref[4] = {0, 0, 0, 0};
    static constexpr char extension_area_ref[4] = {0, 0, 0, 0};
    static constexpr char footer[18] = {'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0'};
    out.write(developer_area_ref, sizeof(developer_area_ref));
    out.write(extension_area_ref, sizeof(extension_area_ref));
    out.write(footer, sizeof(footer));

    return static_cast<bool>(out);
}

int TGAImage::get_width() const {
    return width_;
}

int TGAImage::get_height() const {
    return height_;
}