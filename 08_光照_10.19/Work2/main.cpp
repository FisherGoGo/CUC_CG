#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



Camera camera;

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        800, 600,
        "OpenGL Test",
        nullptr, nullptr
    );

    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD init failed\n";
        return -1;
    }

    std::cout << "OpenGL Version: "
        << glGetString(GL_VERSION)
        << std::endl;

    float vertices[] = {
        // 位置                 纹理坐标      法线

        // 正面：朝 +Z
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,

        // 背面：朝 -Z
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,

         // 右面：朝 +X
          0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
          0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f,

          // 左面：朝 -X
          -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

          // 上面：朝 +Y
          -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,

          // 下面：朝 -Y
          -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
           0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
    };

    unsigned int indices[] = {
        // 正面
        0, 1, 2,
        2, 3, 0,

        // 背面
        4, 5, 6,
        6, 7, 4,

		// 右面
        8, 9, 10,
        10, 11, 8,

        // 左面
        12, 13, 14,
        14, 15, 12,

        // 上面
        16, 17, 18,
        18, 19, 16,

        // 下面
        20, 21, 22,
        22, 23, 20,
    };

    //VBO , VAO, EBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);// 位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//纹理坐标
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));//法线
	glEnableVertexAttribArray(2);

    // -----------------

    //读入着色器

    Shader ourShader("vertex.txt", "fragment.txt");
	Shader lightShader("vertex.txt", "lightframe.txt");

    // ------


    // ----读入纹理----

    stbi_set_flip_vertically_on_load(true);
    //这里是因为默认读入将图片最上边一行放在了最下面一行，所以先反转

    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 3);

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);//选中纹理单元0
    glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理对象

    //超出坐标时，重复图片
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //图片缩小时使用多级渐远纹理，放大时使用线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //参数说明：纹理类型，纹理层级，纹理格式，宽，高，边界，数据格式，数据类型，数据

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);//释放内存


    // 现在多一个读笑脸

    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 4);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);//选中纹理单元1
    glBindTexture(GL_TEXTURE_2D, texture2);//绑定纹理对象

    // 同上
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //RGBA,A是透明度，多一个通道所以上边参数是 4

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    // -------

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);//手动设置纹理单元为0
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);//手动设置纹理单元为1


    // 查询模型矩阵和摄像机组合矩阵的 uniform 位置。
    
	int modelLoc = glGetUniformLocation(ourShader.ID, "model");

    int cameraLoc = glGetUniformLocation(ourShader.ID, "cameraMatrix");

    // ---------

    // 添加其他复制的立方体的偏移向量

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,   0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f,  -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f,  -3.5f),
        glm::vec3(-1.7f,  3.0f,  -7.5f),
        glm::vec3(1.3f, -2.0f,  -2.5f),
        glm::vec3(1.5f,  2.0f,  -2.5f),
        glm::vec3(1.5f,  0.2f,  -1.5f),
        glm::vec3(-1.3f,  1.0f,  -1.5f)
    };


    // 绘制光源
    glm::vec3 lightPos(2.0f, 1.0f, 0.5f);


	// 增加深度测试，避免立方体旋转时出现遮挡问题
    glEnable(GL_DEPTH_TEST);


	camera.Attach(window);

    while (!glfwWindowShouldClose(window))
    {
        // 先处理输入事件，再让摄像机更新位置和朝向
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        camera.Update(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除颜色缓冲和深度缓冲

        ourShader.use();

        glUniform3fv(glGetUniformLocation(ourShader.ID, "lightPos"), 1, glm::value_ptr(lightPos));

		float t = static_cast<float>(glfwGetTime());
		glm::vec3 lightColor(0.5f + 0.5f * std::sin(t), 0.5f + 0.5f * std::sin(t + 2.0944f), 0.5f + 0.5f * std::sin(t + 4.1888f));
        glUniform3fv(glGetUniformLocation(ourShader.ID, "lightColor"),1, glm::value_ptr(lightColor));
        

        glm::vec3 viewPos = camera.GetPosition();
        glUniform3fv(glGetUniformLocation(ourShader.ID, "viewPos"),1, glm::value_ptr(viewPos));
        
		// camera

        glm::mat4 cameraMatrix = camera.GetCameraMatrix(800.0f / 600.0f);
        glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

        // ---

        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO);

		float timeAngle = static_cast<float>(glfwGetTime()) * 50.0f;
        //timeAngle = 30.0f;

        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, cubePositions[i]);
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            float angle = timeAngle + 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(0.5f + 0.24f * i, 1.0f - 0.17 * i, 0.0f));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
        }

        // Light
        lightShader.use();
        glUniform3fv(glGetUniformLocation(lightShader.ID, "lightColor"),1, glm::value_ptr(lightColor));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

        // 先创建一个小立方体然后移动位置
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);


        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
