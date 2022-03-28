# poorPBRT

本仓库从https://github.com/maijiaquan/ray-tracing-with-imgui.git fork而来。
在原仓库的基础上修改了代码的结构，使其更符合面向对象的规范。由于github并不会记录sln项目的结构，目前的`class`分为如下几类。可以自行clone仓库后查看。
![image](https://user-images.githubusercontent.com/46410388/159523805-fad6b98c-2f67-4bb7-a276-484d1dee9a90.png)


`BxDF`：材质类

`Camera`：相机类

`HitRecord`：单次光线命中的记录结构

`Light`：光源类

`Object`：物体类

`Ray`：光线

`Renderer`：渲染器类

`Spectrum`：光谱，尚未实现

`Texture`：纹理类

`utils`：原项目的所有全局变量，临时保存

`vec3`：点、向量和RGB颜色

每一个分类都有着各自的基类。根据以上的分类可以方便地对系统进行横向拓展。

在原仓库基础上的改进：
1. 面向对象的代码格式；
2. 智能指针的使用；
3. 实现了更多的几何形状；
4. 实现了更多的纹理；
5. 点、向量和颜色的分离。

计划完成：
1. principled BRDF；
2. Spectrum替代rgb3；done
3. CUDA加速；
4. 法线贴图；
5. BVH加速结构；
6. 全景相机；
7. 某个BSSRDF；
8. 某个BSDF；
9. EXR全景图作为背景光源；
10. json场景定义；
11. cmake构建；
12. 细化GUI。
