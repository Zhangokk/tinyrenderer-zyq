#pragma once

#include <cstdint>

struct Color {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;

    Color() = default;
    Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
        : r(red), g(green), b(blue) {}
};