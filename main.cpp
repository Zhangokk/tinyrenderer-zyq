#include "geometry.h"
#include "tgaimage.h"

#include <cmath>

constexpr int width  = 800;
constexpr int height = 800;

const TGAColor white = {255, 255, 255, 255};
const TGAColor red   = {255,   0,   0, 255};

void line(Vec2i a, Vec2i b, TGAImage &framebuffer, const TGAColor &color) {
    bool steep = false;
    if (std::abs(a.x - b.x) < std::abs(a.y - b.y)) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
        steep = true;
    }
    if (a.x > b.x) {
        std::swap(a, b);
    }

    const int dx = b.x - a.x;
    const int dy = b.y - a.y;
    const int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = a.y;

    for (int x = a.x; x <= b.x; x++) {
        if (steep) {
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }

        error2 += derror2;
        if (error2 > dx) {
            y += (b.y > a.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

int main() {
    TGAImage framebuffer(width, height, TGAImage::RGB);

    line({13, 20}, {80, 40}, framebuffer, white);
    line({20, 13}, {40, 80}, framebuffer, red);
    line({80, 40}, {13, 20}, framebuffer, red);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}