#pragma once

#include "Input.h"
#include "Camera.h"
#include "glm/glm.hpp"

namespace Graphics
{


    camera processInput(GLFWwindow* window, camera c, double deltaTime, const Input::Mouse& mouse)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        c.speed = static_cast<float>(2.5 * deltaTime * c.multiplier);

        constexpr float m{ 1.001f };
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            c.multiplier *= m;
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            c.multiplier /= m;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            c.pos += c.speed * c.front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            c.pos -= c.speed * c.front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            c.pos -= glm::normalize(glm::cross(c.front, c.up)) * c.speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            c.pos += glm::normalize(glm::cross(c.front, c.up)) * c.speed;
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            c.pos += c.speed * c.up;
        if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            c.pos -= c.speed * c.up;

        /*glm::vec3 direction;
        direction.x = cos(glm::radians(mouse.yaw()) )* cos(glm::radians(mouse.pitch()));
        direction.y = sin(glm::radians(mouse.pitch()));
        direction.z = sin(glm::radians(mouse.yaw())) * cos(glm::radians(mouse.pitch()));
        c.front = glm::normalize(direction);*/

        return c;
    }
}
