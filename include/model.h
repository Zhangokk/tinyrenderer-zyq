#pragma once

#include "geometry.h"

#include <string>
#include <vector>

// Model 只负责把 OBJ 文件解析成两部分数据：
// 1. verts_：所有顶点坐标
// 2. faces_：每个三角面引用了哪些顶点
class Model {
public:
    explicit Model(const std::string &filename);

    int nverts() const;
    int nfaces() const;

    vec3 vert(int i) const;
    vec3 vert(int iface, int nthvert) const;

private:
    std::vector<vec3> verts_;
    std::vector<std::vector<int>> faces_;
};