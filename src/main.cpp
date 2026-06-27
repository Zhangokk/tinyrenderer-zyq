#include "geometry.h"
#include "model.h"
#include "tgaimage.h"

#include <iostream>

constexpr int width  = 800;
constexpr int height = 800;

// TGAColor 构造参数按 RGB 写，内部存储时会转成 TGA 需要的 BGRA 顺序。
const TGAColor white  = {255, 255, 255, 255};
const TGAColor red    = {255,   0,   0, 255};
const TGAColor green  = {  0, 255,   0, 255};
const TGAColor blue   = {  0,   0, 255, 255};
const TGAColor yellow = {255, 255,   0, 255};

// 把模型坐标投影到屏幕坐标。
// 当前先做最简单的正交投影：直接丢掉 z，只用 x、y。
// TinyRenderer 的示例模型大致在 [-1, 1] 范围内，所以：
// 1. v.x + 1 把范围从 [-1, 1] 平移到 [0, 2]
// 2. 再乘 width / 2，把它缩放到 [0, width]
Vec2i project(vec3 v) {
    return {
        static_cast<int>((v.x + 1.f) * width / 2.f),
        static_cast<int>((v.y + 1.f) * height / 2.f)
    };
}
void drawTriangle(Vec2i a,Vec2i b, Vec2i c,TGAImage& framebuffer) {
      framebuffer.drawLine(a, b, red);
      framebuffer.drawLine(b, c, red);
      framebuffer.drawLine(c, a, red);
}

int main() {
    // 运行程序时需要传入 obj 文件路径，例如：
    // .\x64\Debug\tinyrenderer-zyq.exe .\assets\diablo3_pose.obj
    //if (argc != 2) {
    //    std::cerr << "Usage: " << argv[0] << " obj/diablo3_pose.obj" << std::endl;
    //    return 1;
    //}

    // Model 负责读取 obj 文件里的顶点和面。
    // framebuffer 是我们自己的图像缓冲区，后面所有像素都会写到它里面。
    //Model model(argv[1]);
    TGAImage framebuffer(width, height, TGAImage::RGB);

    //**绘制三角形**
    Vec2i a = { 60,100 };
    Vec2i b = { 200,100 };
    Vec2i c = { 60,300 };
    drawTriangle(a, b, c, framebuffer);

    //**模型画线**
    // 遍历模型的每一个三角面。
    // 每个面有 3 个顶点，把 3 个顶点投影到屏幕后，用 drawLine 画三条边。
    // 这就是线框渲染：只画三角形边界，不填充三角形内部。
    //for (int i = 0; i < model.nfaces(); i++) {
    //    Vec2i a = project(model.vert(i, 0));
    //    Vec2i b = project(model.vert(i, 1));
    //    Vec2i c = project(model.vert(i, 2));

    //    // drawLine 是前面 Bresenham 直线算法实现好的基础能力。
    //    // 模型读取阶段不重新造画线逻辑，只复用这个接口。
    //    framebuffer.drawLine(a, b, red);
    //    framebuffer.drawLine(b, c, red);
    //    framebuffer.drawLine(c, a, red);
    //}
    // 把内存中的 framebuffer 写成 TGA 图片文件。
    framebuffer.write_tga_file("triangle.tga");
    return 0;
}