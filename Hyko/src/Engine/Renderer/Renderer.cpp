#include "Renderer.h"

// Macros
#include "Engine/Core/Macro.h"

// GL
#include <GLAD/glad.h>

Hyko::RendererData m_data;

void Hyko::Renderer::createTriangle()
{
	createTriangle({ 0.0f, 0.0f }, { 10.0f, 10.0f }, 0.0f, { 1.0f, 1.0f, 0.0f, 1.0f });
}

void Hyko::Renderer::createTriangle(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec4 color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos, 0.0f })
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale, 1.0f });

	createTriangle(transform, color);
}

void Hyko::Renderer::createTriangle(glm::mat4 transform, glm::vec4 color)
{
	for (int i = 0; i < 3; i++) {
		Vertex* vertexPtr = new Vertex;
		vertexPtr->position = transform * glm::vec4(m_data.triangleVertexPos[i], 1.0f);
		vertexPtr->color = color;

		m_data.vertices.push_back(vertexPtr->position.x);
		m_data.vertices.push_back(vertexPtr->position.y);
		m_data.vertices.push_back(vertexPtr->position.z);
			   
		m_data.vertices.push_back(vertexPtr->color.r);
		m_data.vertices.push_back(vertexPtr->color.g);
		m_data.vertices.push_back(vertexPtr->color.b);
		m_data.vertices.push_back(vertexPtr->color.a);

		delete vertexPtr;
	}

	addTriangleIndiceses();
	m_data.trianglesCount++;
	//m_data.m_rTools.createVO(m_data.rectangleVert, m_data.triangleIndices);
}

void Hyko::Renderer::createRectangle()
{
	createRectangle({ 0.0f, 0.0f }, { 10.0f, 10.0f }, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
}

void Hyko::Renderer::createRectangle(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec4 color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos, 0.0f })
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale, 1.0f });

	createRectangle(transform, color);
}

void Hyko::Renderer::createRectangle(glm::mat4 transform, glm::vec4 color)
{
	for (int i = 0; i < 4; i++) {
		Vertex* vertexPtr = new Vertex;
		vertexPtr->position = transform * glm::vec4(m_data.rectangleVertexPos[i], 1.0f);
		vertexPtr->color = color;

		m_data.vertices.push_back(vertexPtr->position.x);
		m_data.vertices.push_back(vertexPtr->position.y);
		m_data.vertices.push_back(vertexPtr->position.z);
			  
		m_data.vertices.push_back(vertexPtr->color.r);
		m_data.vertices.push_back(vertexPtr->color.g);
		m_data.vertices.push_back(vertexPtr->color.b);
		m_data.vertices.push_back(vertexPtr->color.a);

		delete vertexPtr;
	}
	addRectangleIndiceses();
	m_data.rectanglesCount++;
	//m_data.m_rTools.createVO(m_data.rectangleVert, m_data.rectangleIndices);
}

void Hyko::Renderer::createCircle()
{
	createCircle({ 0.0f, 0.0f }, { 10.0f, 10.0f }, 16, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
}

void Hyko::Renderer::createCircle(glm::vec2 pos, glm::vec2 scale, int segmentsCount, float angle, glm::vec4 color)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos, 0.0f })
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0.0f,0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale, 0.0f });

	createCircle(transform, color, segmentsCount);
}

void Hyko::Renderer::createCircle(glm::mat4 transform, glm::vec4 color, int segmentsCount)
{
	float pos;
	glm::vec3 ZPos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	m_data.circleVertices.push_back(ZPos.x);
	m_data.circleVertices.push_back(ZPos.y);
	m_data.circleVertices.push_back(ZPos.z);

	m_data.circleVertices.push_back(color.r);
	m_data.circleVertices.push_back(color.g);
	m_data.circleVertices.push_back(color.b);
	m_data.circleVertices.push_back(color.a);

	for (int i = 0; i < segmentsCount; i++) {
		pos = 3.141592f * 2.0f * (float)i / (float)segmentsCount;

		Vertex* vertexPtr = new Vertex;
		vertexPtr->position = transform * glm::vec4(cosf(pos), sinf(pos), 0.0f, 1.0f);
		vertexPtr->color = color;

		m_data.circleVertices.push_back(vertexPtr->position.x);
		m_data.circleVertices.push_back(vertexPtr->position.y);
		m_data.circleVertices.push_back(vertexPtr->position.z);

		m_data.circleVertices.push_back(vertexPtr->color.r);
		m_data.circleVertices.push_back(vertexPtr->color.g);
		m_data.circleVertices.push_back(vertexPtr->color.b);
		m_data.circleVertices.push_back(vertexPtr->color.a);

		delete vertexPtr;
	}

	addCircleIndiceses(segmentsCount);
	m_data.circlesCount++;

	/*for (int i = 0; i < 4; i++) {
		Vertex* vertexPtr = new Vertex;
		vertexPtr->position = transform * glm::vec4(m_data.rectangleVertexPos[i], 1.0f);
		vertexPtr->color = color;

		m_data.circleVertices.push_back(vertexPtr->position.x);
		m_data.circleVertices.push_back(vertexPtr->position.y);
		m_data.circleVertices.push_back(vertexPtr->position.z);
	
		m_data.circleVertices.push_back(vertexPtr->color.r);
		m_data.circleVertices.push_back(vertexPtr->color.g);
		m_data.circleVertices.push_back(vertexPtr->color.b);
		m_data.circleVertices.push_back(vertexPtr->color.a);

		delete vertexPtr;
	}
	addCircleIndiceses(segmentsCount);
	m_data.circlesCount++;*/
}

//void Hyko::Renderer::Init()
//{
//	m_data.basicProgram = m_data.m_scene->basicShader.createShaderProgram("Hyko//res//shaders//VBasicShader.glsl", "Hyko//res//shaders//FBasicShader.glsl");
//
//	m_data.m_scene->editCamera.initProjection();
//	m_data.projection = m_data.m_scene->editCamera.getProjectionMat();
//	m_data.view = m_data.m_scene->editCamera.getViewMat();
//}

//void Hyko::Renderer::Update()
//{
//	m_data.view = m_data.m_scene->editCamera.updateView();
//	m_data.projection = m_data.m_scene->editCamera.updateProjection();
//}

void Hyko::Renderer::BeginScene()
{
	//m_data.basicShader->use();
}

//void Hyko::Renderer::EndScene()
//{
//	m_data.m_scene->basicShader.unUse();
//}

void Hyko::Renderer::render()
{
	if (m_data.index.size() != 0) {
		m_data.m_rTools.createVO(m_data.vertices, m_data.index);
		m_data.m_rTools.renderIndxes(m_data.index);
		m_data.m_rTools.getVO().deleteVO();
	}

	if (m_data.circleIndices.size() != 0) {
		m_data.m_rTools.createVO(m_data.circleVertices, m_data.circleIndices);
		m_data.m_rTools.renderIndxes(m_data.circleIndices);
		m_data.m_rTools.getVO().deleteVO();
	}
	
	m_data.vertices.clear();
	m_data.index.clear();
	m_data.circleVertices.clear();
	m_data.circleIndices.clear();
}

void Hyko::Renderer::addTriangleIndiceses() 
{
	if (m_data.index.size() == 0) {
		m_data.index.push_back(0);

		for (int i = 0; i < 2; i++)
			m_data.index.push_back(m_data.index.back() + 1);
	}
	else {
		for (int i = 0; i < 3; i++)
			m_data.index.push_back(*std::max_element(m_data.index.begin(), m_data.index.end()) + 1);
	}
}

void Hyko::Renderer::addRectangleIndiceses()
{
	if (m_data.index.size() == 0) {
		m_data.index.push_back(0);
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index.back());
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index[m_data.index.size() - 5]);
	}		   
	else {	   
		m_data.index.push_back(*std::max_element(m_data.index.begin(), m_data.index.end()) + 1);
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index.back());
		m_data.index.push_back(m_data.index.back() + 1);
		m_data.index.push_back(m_data.index[m_data.index.size() - 5]);
	}
}

void Hyko::Renderer::addCircleIndiceses(const int segmentsCount)
{
	if (m_data.circleIndices.size() == 0) {
		m_data.circleIndices.push_back(1);
		m_data.circleIndices.push_back(0);
		m_data.circleIndices.push_back(2);

		for (int i = 0; i < segmentsCount - 2; i++) {
			m_data.circleIndices.push_back(m_data.circleIndices.back());
			m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3]);
			m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3] + 1);
		}

		m_data.circleIndices.push_back(m_data.circleIndices.back());
		m_data.circleIndices.push_back(0);
		m_data.circleIndices.push_back(1);
	}
	else {
		m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3] + 2);
		m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 4] + 1);
		m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 2] + 1);

		for (int i = 0; i < segmentsCount - 2; i++) {
			m_data.circleIndices.push_back(m_data.circleIndices.back());
			m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3]);
			m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3] + 1);
		}

		m_data.circleIndices.push_back(m_data.circleIndices.back());
		m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - 3]);
		m_data.circleIndices.push_back(m_data.circleIndices[m_data.circleIndices.size() - (segmentsCount * 3 - 1)]);
	}
}
