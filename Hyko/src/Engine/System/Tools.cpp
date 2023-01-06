#include "Tools.h"

glm::vec2 Hyko::getWinSize(GLFWwindow* window)
{
    glfwGetWindowSize(window, &m_windowSizeX, &m_windowSizeY);

    return { m_windowSizeX, m_windowSizeY };
}
