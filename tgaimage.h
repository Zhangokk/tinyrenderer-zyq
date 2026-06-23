#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#pragma pack(push, 1)
struct TGAHeader {
    std::uint8_t  idlength = 0;
    std::uint8_t  colormaptype = 0;
    std::uint8_t  datatypecode = 0;
    std::uint16_t colormaporigin = 0;
    std::uint16_t colormaplength = 0;
    std::uint8_t  colormapdepth = 0;
    std::uint16_t x_origin = 0;
    std::uint16_t y_origin = 0;
    std::uint16_t width = 0;
    std::uint16_t height = 0;
    std::uint8_t  bitsperpixel = 0;
    std::uint8_t  imagedescriptor = 0;
};
#pragma pack(pop)

struct TGAColor {
    std::uint8_t bgra[4] = {0, 0, 0, 0};
    std::uint8_t bytespp = 4;

    TGAColor() = default;
    TGAColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : bgra{b, g, r, a}, bytespp(4) {}

    std::uint8_t& operator[](const int i) { return bgra[i]; }
    const std::uint8_t& operator[](const int i) const { return bgra[i]; }
};

class TGAImage {
public:
    enum Format {
        GRAYSCALE = 1,
        RGB = 3,
        RGBA = 4,
    };

    TGAImage() = default;
    TGAImage(int width, int height, int bytespp);

    bool set(int x, int y, const TGAColor &color);
    bool write_tga_file(const std::string &filename, bool vflip = true) const;

    int get_width() const;
    int get_height() const;

private:
    int width_ = 0;
    int height_ = 0;
    int bytespp_ = 0;
    std::vector<std::uint8_t> data_;
};