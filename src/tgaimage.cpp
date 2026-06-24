#include "tgaimage.h"

#include <cmath>
#include <fstream>

// 创建一张 width * height 的图像。
// bytespp 表示每个像素占多少字节：RGB 是 3，RGBA 是 4。
TGAImage::TGAImage(int width, int height, int bytespp)
    : width_(width), height_(height), bytespp_(bytespp), data_(width * height * bytespp, 0) {}

// 设置某个像素的颜色。
// data_ 是一维数组，所以二维坐标 (x, y) 要映射成一维下标：
// index = (x + y * width) * bytespp。
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

// 使用 Bresenham 算法画直线。
// 目标：不用浮点插值，而是通过整数误差项决定 y 什么时候走一步。
void TGAImage::drawLine(Vec2i a, Vec2i b, const TGAColor &color) {
    bool steep = false;

    // 如果线更“陡”，也就是 y 方向变化比 x 方向更大，交换 x/y。
    // 这样主循环永远沿着变化更大的方向走，避免线条断裂。
    if (std::abs(a.x - b.x) < std::abs(a.y - b.y)) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
        steep = true;
    }

    // 保证从左往右画，简化后面的循环逻辑。
    if (a.x > b.x) {
        std::swap(a, b);
    }

    const int dx = b.x - a.x;
    const int dy = b.y - a.y;

    // error2 是放大 2 倍后的误差项，避免使用 0.5 这样的浮点数。
    const int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = a.y;

    for (int x = a.x; x <= b.x; x++) {
        // 如果前面交换过 x/y，这里写像素时要交换回来。
        if (steep) {
            set(y, x, color);
        } else {
            set(x, y, color);
        }

        // 误差累计到一定程度，说明真实直线已经更接近下一行像素了，y 就走一步。
        error2 += derror2;
        if (error2 > dx) {
            y += (b.y > a.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

// 把 framebuffer 写成未压缩 TGA 文件。
// 这里写的是最简单的 true-color TGA：文件头 + 像素数据 + footer。
bool TGAImage::write_tga_file(const std::string &filename, bool vflip) const {
    TGAHeader header;
    header.datatypecode = 2; // 2 表示未压缩 true-color 图像。
    header.width = static_cast<std::uint16_t>(width_);
    header.height = static_cast<std::uint16_t>(height_);
    header.bitsperpixel = static_cast<std::uint8_t>(bytespp_ << 3);
    header.imagedescriptor = vflip ? 0x00 : 0x20;

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // vflip 为 true 时，从最后一行往第一行写，让输出图像方向和屏幕坐标更一致。
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