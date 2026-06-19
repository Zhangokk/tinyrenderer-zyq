#include "image.h"

#include <iostream>

int main() {
    constexpr int width = 800;
    constexpr int height = 600;

    Image image(width, height, Color(18, 20, 28));

    // First tiny renderer milestone: write pixels into an image buffer.
    image.setPixel(width / 2, height / 2, Color(255, 70, 70));
    image.setPixel(width / 2 + 1, height / 2, Color(255, 70, 70));
    image.setPixel(width / 2, height / 2 + 1, Color(255, 70, 70));
    image.setPixel(width / 2 + 1, height / 2 + 1, Color(255, 70, 70));

    const std::string output_path = "output/first.ppm";
    if (!image.writePPM(output_path)) {
        std::cerr << "Failed to write " << output_path << std::endl;
        return 1;
    }

    std::cout << "Wrote " << output_path << std::endl;
    return 0;
}