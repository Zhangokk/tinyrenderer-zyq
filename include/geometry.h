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

struct vec3 {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    vec3() = default;
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    float& operator[](const int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    const float& operator[](const int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
};