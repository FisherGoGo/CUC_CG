# CUC 计算机图形学实验

计算机图形学课程的 OpenGL 实验记录，按“编号_实验内容_日期”整理。主要使用 C++、OpenGL 和 Visual Studio，包含实验源码、着色器、纹理图片和环境配置资料。实验报告保留在本地，不上传 GitHub。

## 实验目录

| 日期 | 文件夹 | 内容 | 解决方案入口 |
| --- | --- | --- | --- |
| 9.7 | `01_OpenGL环境配置_9.7` | OpenGL 环境搭建与配置资料 | 配置说明 PDF |
| 9.7 | `02_窗口创建_9.7` | GLFW 窗口创建、GLAD 初始化与渲染循环 | `CG 9.7.slnx` |
| 9.14 | `03_基础图形绘制_9.14` | 纯色三角形、索引绘制矩形、顶点颜色插值 | `Work_2/9.14 EXP.slnx` |
| 9.21 | `04_纹理映射_9.21` | 单纹理映射与双纹理混合 | `9.21 EXP/9.21 EXP.slnx` |
| 9.28 | `05_几何变换_9.28` | 使用 GLM 实现旋转、缩放、平移和动态变换 | `9.28-Transform.slnx` |
| 10.10 | `06_坐标变换_10.10` | 模型、观察与投影矩阵，深度测试，旋转立方体和多个立方体 | `10.10.slnx` |

其他目录：

- `opengl/`：GLAD、GLFW 头文件与预编译库。
- `glm/`：GLM 数学库。
- `texture/`：纹理素材、Shader 类和 stb_image。
- `OpenGLTemplate/`、`New Temp/`：项目模板。
- `工作文件/`：报告排版等辅助脚本，需要配合本地报告使用。

本地的 `实验报告/` 目录和 Word 报告已加入忽略规则，克隆仓库时不会包含这些文件。

## 开发环境

- Windows 和 Visual Studio，安装“使用 C++ 的桌面开发”工作负载及 Windows SDK。
- 当前项目配置使用 MSVC `v145` 工具集；使用其他工具集时，需要在 VS 中重定向项目并选择兼容的 GLFW 库。
- OpenGL 3.3 Core Profile；显卡和驱动需要支持该版本。
- GLFW、GLAD、GLM、stb_image，所需文件已包含在仓库中。

解决方案使用 `.slnx` 格式，需要支持该格式的 Visual Studio。

## 打开和运行

1. 克隆仓库：

   ```bash
   git clone git@github.com:FisherGoGo/CUC_CG.git
   cd CUC_CG
   ```

2. 在对应实验文件夹中打开表格列出的 `.slnx` 文件。
3. 选择 `Debug | x64`，将要运行的 `Work` 项目设为启动项目。
4. 检查项目属性中的包含目录和库目录，然后编译运行。按 `Esc` 退出窗口。

### 首次克隆后的路径配置

部分 `.vcxproj` 仍使用原电脑上的绝对路径：

```text
D:\Project\University Session\Computer Graphics\
```

如果克隆位置不同，请在“项目属性”中修改对应配置的路径：

| 项目属性 | 仓库中的位置 |
| --- | --- |
| C/C++ → 常规 → 附加包含目录 | `opengl/glad/include`、`opengl/glfw-3.5.1.bin.WIN64/include`；涉及矩阵变换的项目还需要 `glm` |
| 链接器 → 常规 → 附加库目录 | `opengl/glfw-3.5.1.bin.WIN64/lib-vc2026`，或与当前工具集兼容的库目录 |
| 链接器 → 输入 → 附加依赖项 | `glfw3.lib`、`opengl32.lib` |

路径配置请保留 Visual Studio 的继承项。建议先使用已配置 GLFW 依赖的 `x64` 平台。

着色器和纹理通过相对路径加载，运行时的工作目录应为启动项目所在目录，可在“项目属性 → 调试 → 工作目录”中设置为 `$(ProjectDir)`。几何变换实验的纹理已放在各自的 `Work` 项目内；纹理映射实验的 `Work2`、`Work3` 从上两级目录读取图片。

## Git 管理

仓库保留源码、项目配置、环境配置资料和所需依赖。`.gitignore` 排除了实验报告、VS 缓存、编译产物、个人调试设置、重复压缩包及报告临时渲染文件；这些文件仍可保留在本地。

后续修改后提交并同步：

```bash
git add .
git commit -m "更新实验内容"
git push
```

第三方库的许可说明见各依赖目录中的许可证文件。
