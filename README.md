# tinyrenderer-zyq

用 C++ 从零实现一个 CPU 软光栅渲染器

## 当前目标

- [x] 创建 Visual Studio C++ 项目
- [x] 定义 `Color` 和 `Image`
- [x] 实现 `setPixel(x, y, color)`
- [x] 输出第一张 `PPM` 图片
- [x] 实现画线算法
- [ ] 实现三角形线框
- [ ] 实现三角形填充
- [ ] 实现 Z-buffer
- [ ] 加载 OBJ 模型

## 如何运行

用 Visual Studio 打开：

```text
E:\github\tinyrenderer-zyq\tinyrenderer-zyq.sln
```

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

## 完成情况

- [x] Bresenham画线算法

  ![image-20260622103049601](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20260622103049601.png)