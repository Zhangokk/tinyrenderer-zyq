#include "image.h"

#include <iostream>

int main() {
    constexpr int width = 800;
    constexpr int height = 600;

    Image image(width, height, Color(18, 20, 28));

 
    image.drawLine(width / 2, height / 2 + 1, width-2, height-2, Color(255, 70, 70));
    image.drawLine(0, height / 2 + 1, width / 2, height - 2, Color(70, 70, 70));

    image.setPixel(width / 2, height / 2, Color(255, 70, 70));
    image.setPixel(width / 2 + 1, height / 2, Color(255, 70, 70));
    image.setPixel(width / 2, height / 2 + 1, Color(255, 70, 70));
    image.setPixel(width / 2 + 1, height / 2 + 1, Color(255, 70, 70));

    const std::string bmp_path = "output/first.bmp";
    const std::string ppm_path = "output/first.ppm";

    if (!image.writeBMP(bmp_path)) {
        std::cerr << "Failed to write " << bmp_path << std::endl;
        return 1;
    }

    // Keep PPM output as a simple debug format for later renderer tests.
    image.writePPM(ppm_path);

    std::cout << "Wrote " << bmp_path << std::endl;
    return 0;
}