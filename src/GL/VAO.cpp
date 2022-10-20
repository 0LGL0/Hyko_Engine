#include "VAO.h"
#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>

unsigned int VAO::createVAO(std::vector<float> vertices, unsigned int VBO)
{
    vbo = VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}