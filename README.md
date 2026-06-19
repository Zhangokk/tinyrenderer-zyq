# tinyrenderer-zyq

这是我的 TinyRenderer 造轮子项目。目标是用 C++ 从零实现一个 CPU 软光栅渲染器，把图形学基础真正写出来。

## 当前目标

- [x] 创建 Visual Studio C++ 项目
- [x] 定义 `Color` 和 `Image`
- [x] 实现 `setPixel(x, y, color)`
- [x] 输出第一张 `PPM` 图片
- [ ] 实现画线算法
- [ ] 实现三角形线框
- [ ] 实现三角形填充
- [ ] 实现 Z-buffer
- [ ] 加载 OBJ 模型

## 如何运行

用 Visual Studio 打开：

```text
E:\github\tinyrenderer-zyq\tinyrenderer-zyq.sln
```

选择 `Debug | x64`，点击“本地 Windows 调试器”。运行成功后生成：

```text
output\first.ppm
```

## 目录结构

```text
src/        源文件
include/    头文件
assets/     模型、纹理等资源
output/     渲染输出图片
notes/      每日学习日志
```

## 今日理解

当前程序没有调用 OpenGL。它直接在 CPU 内存里维护一张图片，通过 `setPixel` 写入像素，然后把像素数据保存成 PPM 图片。这就是软光栅渲染器的起点。