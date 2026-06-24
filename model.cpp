#include "model.h"

#include <fstream>
#include <sstream>
#include <string>

// 读取一个 OBJ 模型文件。
// 当前只关心两类行：
// v x y z  表示一个三维顶点
// f a b c  表示一个三角面，由三个顶点索引组成
Model::Model(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        return;
    }

    std::string line;
    //getline 按行读取 ，读取到的内容保存到line里面
    while (std::getline(in, line)) {
        //将line里的内容拷贝一份
        std::istringstream iss(line);
        std::string prefix;
        //prefix读取第一个空格之前的内容
        iss >> prefix;

        if (prefix == "v") {
            // 顶点行：把 x、y、z 读进 vec3，然后存到 verts_。
            vec3 v;
            
            iss >> v.x >> v.y >> v.z;
            verts_.push_back(v);
        } else if (prefix == "f") {
            // 面行：OBJ 的面索引可能长这样：f 1 2 3，也可能长这样：f 1/1/1 2/2/2 3/3/3。
            // 这里用 token_stream >> int，只读取斜杠前面的顶点索引。
            std::vector<int> face;
            std::string token;
            while (iss >> token) {
                std::istringstream token_stream(token);
                int vertex_index = 0;
                token_stream >> vertex_index;

                // OBJ 文件里的顶点索引从 1 开始，C++ vector 下标从 0 开始，所以要减 1。
                face.push_back(vertex_index - 1);
            }
            if (face.size() >= 3) {
                faces_.push_back(face);
            }
        }
    }
}

int Model::nverts() const {
    return static_cast<int>(verts_.size());
}

int Model::nfaces() const {
    return static_cast<int>(faces_.size());
}

// 返回第 i 个顶点。
vec3 Model::vert(int i) const {
    return verts_[i];
}

// 返回第 iface 个面里的第 nthvert 个顶点。
// 例如 vert(i, 0)、vert(i, 1)、vert(i, 2) 就是第 i 个三角形的三个顶点。
vec3 Model::vert(int iface, int nthvert) const {
    return verts_[faces_[iface][nthvert]];
}