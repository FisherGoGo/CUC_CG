#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f))
        : position(position)
    {
    }

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(position, position + front, worldUp);
    }

    glm::mat4 GetProjectionMatrix(float aspectRatio) const
    {
        // 本项目使用旧版 GLM，perspective 接收角度。
        return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    }

    glm::mat4 GetCameraMatrix(float aspectRatio) const
    {
        return GetProjectionMatrix(aspectRatio) * GetViewMatrix();
    }

    void Attach(GLFWwindow* window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(window, &lastX, &lastY);
        lastFrame = glfwGetTime();
    }

    void Update(GLFWwindow* window)
    {
        double currentFrame = glfwGetTime();
        float deltaTime = static_cast<float>(currentFrame - lastFrame);
        lastFrame = currentFrame;

        // 先转头，再沿新的朝向移动。
        ProcessMouseMovement(window);
        ProcessKeyboard(window, deltaTime);
    }

    glm::vec3 GetPosition() const
    {
        return position;
    }

private:
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 200.0f;

    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float moveSpeed = 2.5f;
    double lastFrame = 0.0;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;

    double lastX = 0.0;
    double lastY = 0.0;

    void ProcessKeyboard(GLFWwindow* window, float deltaTime)
    {
        float forwardInput = 0.0f;
        float rightInput = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            forwardInput += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            forwardInput -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            rightInput += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            rightInput -= 1.0f;

        glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
        glm::vec3 move = front * forwardInput + right * rightInput;
        if (glm::length(move) > 0.0f)
        {
            position += glm::normalize(move) * moveSpeed * deltaTime;
        }
    }

    void ProcessMouseMovement(GLFWwindow* window)
    {
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = static_cast<float>(xpos - lastX);
        float yoffset = static_cast<float>(lastY - ypos);
        lastX = xpos;
        lastY = ypos;

        yaw += xoffset * sensitivity;
        pitch += yoffset * sensitivity;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        float yawRadians = glm::radians(yaw);
        float pitchRadians = glm::radians(pitch);

        glm::vec3 direction;
        direction.x = std::cos(yawRadians) * std::cos(pitchRadians);
        direction.y = std::sin(pitchRadians);
        direction.z = std::sin(yawRadians) * std::cos(pitchRadians);
        front = glm::normalize(direction);
    }
};
