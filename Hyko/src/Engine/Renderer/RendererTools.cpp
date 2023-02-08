#include "RendererTools.h"

#include <GLAD/glad.h>

void Hyko::RendererTools::renderIndxes(std::vector<unsigned int> indxes)
{
	m_vo.bind();
	glDrawElements(GL_TRIANGLES, indxes.size(), GL_UNSIGNED_INT, nullptr);
	m_vo.unBind();
}

void Hyko::RendererTools::createVO(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	m_vo.createVertexObjects(vertices, 7, indices);
}
