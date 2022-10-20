#include "EditorProjection.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 EProjection::createViewMatrix(glm::vec3 camPos)
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, camPos);

    return viewMatrix;
}

glm::mat4 EProjection::createOrthoProjection(float l, float r, float b, float t)
{
    glm::mat4 proj = glm::mat4(1.0f);

    proj = glm::ortho(l, r, b, t, -1.0f, 1.0f);

    return proj;
}

glm::mat4 EProjection::resizeOrthoProjection(float width, float height)
{
    glm::mat4 newProj = glm::mat4(1.0f);

    if (width > height) newProj = createOrthoProjection(-1.0f * (width / height), 1.0f * (width / height), -1.0f, 1.0f);
    else newProj = createOrthoProjection(-1.0f, 1.0f, -1.0f * (height / width), 1.0f * (height / width));

    return newProj;
}
