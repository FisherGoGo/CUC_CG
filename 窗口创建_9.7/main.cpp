#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 窗口大小改变时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 处理键盘输入
void processInput(GLFWwindow* window)
{
    // 按 ESC 关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // 1. 初始化 GLFW
    glfwInit();

    // 使用 OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // 使用 Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. 创建窗口
    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "LearnOpenGL",
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 3. 把这个窗口的 OpenGL Context 设置为当前 Context
    glfwMakeContextCurrent(window);

    // 设置窗口大小变化的回调函数
    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    // 4. 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 5. 设置 OpenGL 渲染区域
    glViewport(0, 0, 800, 600);

    // 6. 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        processInput(window);

        // 设置清屏颜色
        glClearColor(
            0.2f,
            0.3f,
            0.3f,
            1.0f
        );

        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换前后缓冲
        glfwSwapBuffers(window);

        // 处理键盘、鼠标、窗口等事件
        glfwPollEvents();
    }

    // 7. 清理 GLFW
    glfwTerminate();

    return 0;
}