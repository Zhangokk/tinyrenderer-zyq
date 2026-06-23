#pragma once

struct Vec2i {
    int x = 0;
    int y = 0;

    Vec2i() = default;
    Vec2i(int x, int y) : x(x), y(y) {}

    int& operator[](const int i) {
        return i == 0 ? x : y;
    }

    const int& operator[](const int i) const {
        return i == 0 ? x : y;
    }
};