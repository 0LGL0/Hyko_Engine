#include <glad/glad.h>

#include "Entity.h"

// Hyko::Scene m_scene;

std::vector<std::vector<Hyko::vertex>> Hyko::Entity::vert;
std::vector<float> Hyko::Entity::triangleVertices;
std::vector<unsigned int> Hyko::Entity::triangleIndices;

Hyko::Triangle& Hyko::Entity::addToSceneTriangle()
{
	Hyko::Triangle* triangle = new Hyko::Triangle;

	triangle->m_position = { 0.0f, 0.0f };
	triangle->m_scale	 = { 1.0f, 1.0f };
	triangle->m_color	 = { 0.0f, 0.0f, 0.0f, 1.0f };
	triangle->m_rotation = 0.0f;
	triangle->type       = HK_TRIANGLE;

	Hyko::Triangle::count++;
	triangle->indx += (Hyko::Triangle::count - 1);

	m_scene->sceneTriangles.push_back(*triangle);

	ConverteToVertPos(HK_TRIANGLE, triangle->m_position, triangle->m_scale);

	addTriangleVertexes(getVertPosX(HK_TRIANGLE), getVertPosY(HK_TRIANGLE), { 1.0f,0.0f,0.0f,1.0f });
	addTriangleIndiceses();

	constVert = vert;

	triangleVertices.clear();

	ConvertVertexToVertices(vert);

	vo.deleteVO();
	vo.createVertexObjects(triangleVertices, 7, triangleIndices);

	return *triangle;
	delete triangle;
}

Hyko::Triangle& Hyko::Entity::addToSceneTriangle(glm::vec2 pos, float rot, glm::vec2 scale, glm::vec4 color)
{
	Hyko::Triangle* triangle = new Hyko::Triangle;

	triangle->m_position = pos;
	triangle->m_scale	 = scale;
	triangle->m_color	 = color;
	triangle->m_rotation = rot;
	triangle->type		 = HK_TRIANGLE;

	Hyko::Triangle::count++;
	triangle->indx += (Hyko::Triangle::count - 1);

	m_scene->sceneTriangles.push_back(*triangle);

	ConverteToVertPos(HK_TRIANGLE, pos, scale);

	addTriangleVertexes(getVertPosX(HK_TRIANGLE), getVertPosY(HK_TRIANGLE), color);
	addTriangleIndiceses();

	constVert = vert;

	triangleVertices.clear();

	ConvertVertexToVertices(vert);

	vo.deleteVO();
	vo.createVertexObjects(triangleVertices, 7, triangleIndices);

	return *triangle;
	delete triangle;
}

Hyko::Triangle& Hyko::Entity::addToSceneTriangle(float posX, float posY, float rot, float scaleX, float scaleY, float colorR, float colorG, float colorB, float colorA)
{
	Hyko::Triangle* triangle = new Hyko::Triangle;

	triangle->m_position = { posX, posY };
	triangle->m_scale	 = { scaleX, scaleY };
	triangle->m_color	 = { colorR, colorG, colorB, colorA };
	triangle->m_rotation = rot;
	triangle->type		 = HK_TRIANGLE;

	Hyko::Triangle::count++;
	triangle->indx += (Hyko::Triangle::count - 1);

	m_scene->sceneTriangles.push_back(*triangle);

	ConverteToVertPos(HK_TRIANGLE, { posX, posY }, {scaleX, scaleY});

	addTriangleVertexes(getVertPosX(HK_TRIANGLE), getVertPosY(HK_TRIANGLE), {colorR, colorG, colorB, colorA});
	addTriangleIndiceses();

	constVert = vert;

	triangleVertices.clear();

	ConvertVertexToVertices(vert);

	vo.deleteVO();
	vo.createVertexObjects(triangleVertices, 7, triangleIndices);

	return *triangle;
	delete triangle;
}

void Hyko::Entity::ConverteToVertPos(int8_t type, glm::vec2 pos, glm::vec2 meshScale)
{
	if (type == HK_TRIANGLE)
		triangleVertices = std::vector<float>{ pos.x - meshScale.x, pos.x + meshScale.x, pos.x, pos.y - meshScale.y, pos.y - meshScale.y, pos.y + meshScale.y, 0.0f, 0.0f, 0.0f };
}

glm::vec3 Hyko::Entity::ConverteToObjectPos(std::vector<vertex> vertexes)
{
	glm::mat4 posMat = glm::mat4(1.0f);

	for (int i = 0; i < vertexes.size(); i++)
		glm::translate(posMat, vertexes[i].position);

	return posMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Hyko::Entity::ConvertVertexToVertices(std::vector<std::vector<vertex>> vertexes)
{
	for (int i = 0; i < vertexes.size(); i++) {
		for (int j = 0; j < vertexes[i].size(); j++) {
			triangleVertices.push_back(vertexes[i][j].position.x);
			triangleVertices.push_back(vertexes[i][j].position.y);
			triangleVertices.push_back(0.0f);

			triangleVertices.push_back(vertexes[i][j].color.r);
			triangleVertices.push_back(vertexes[i][j].color.g);
			triangleVertices.push_back(vertexes[i][j].color.b);
			triangleVertices.push_back(vertexes[i][j].color.a);
		}
	}
}

glm::vec3 Hyko::Entity::getVertPosX(int8_t type)
{
	if (type == HK_TRIANGLE) {
		return {triangleVertices[0], triangleVertices[1], triangleVertices[2] };
	}
}

glm::vec3 Hyko::Entity::getVertPosY(int8_t type)
{
	if (type == HK_TRIANGLE) {
		return { triangleVertices[3], triangleVertices[4], triangleVertices[5] };
	}
}

glm::vec3 Hyko::Entity::getVertPosZ(int8_t type)
{
	if (type == HK_TRIANGLE) {
		return { triangleVertices[6], triangleVertices[7], triangleVertices[8] };
	}
}

void Hyko::Entity::render(int8_t type)
{
	if (type == HK_TRIANGLE) {
		vo.bind();

		glDrawElements(GL_TRIANGLES, triangleIndices.size(), GL_UNSIGNED_INT, nullptr);

		vo.unBind();
	}
}

void Hyko::Entity::addTriangleVertexes(glm::vec3 position_one, glm::vec3 position_two, glm::vec4 color)
{
	vertex vertex1{ {position_one.x, position_two.x, 0.0f}, color };
	vertex vertex2{ {position_one.y, position_two.y, 0.0f}, color };
	vertex vertex3{ {position_one.z, position_two.z, 0.0f}, color };

	vert.push_back(std::vector<vertex>{vertex1, vertex2, vertex3});
}

void Hyko::Entity::addTriangleIndiceses()
{
	if (triangleIndices.empty()) {
		triangleIndices.push_back(0);

		for (int i = 0; i < 2; i++) {
			triangleIndices.push_back(triangleIndices.back() + 1);
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			triangleIndices.push_back(triangleIndices.back() + 1);
		}
	}
}

void Hyko::Entity::setPosition(int indx, int8_t type, glm::vec2 newPos)
{
	Hyko::Triangle triangle;

	if (type == HK_TRIANGLE)
		triangle = m_scene->getSceneComponent<Hyko::Triangle>(indx, type);

	glm::mat4 transform;

	triangle.m_position = newPos;

	if(type == HK_TRIANGLE)
		transform = glm::scale(glm::mat4(1.0f), { triangle.m_scale, 0.0f }) * glm::rotate(glm::mat4(1.0f), triangle.m_rotation, {0.0f, 0.0f, 1.0f}) * glm::translate(glm::mat4(1.0f), {newPos, 0.0f});

	if (type == HK_TRIANGLE) {
		vert[indx][0].position = transform * glm::vec4(vert[indx][0].position, 1.0f);
		vert[indx][1].position = transform * glm::vec4(vert[indx][1].position, 1.0f);
		vert[indx][2].position = transform * glm::vec4(vert[indx][2].position, 1.0f);

		triangleVertices.clear();
		ConvertVertexToVertices(vert);

		vo.deleteVO();
		vo.createVertexObjects(triangleVertices, 7, triangleIndices);
	}
}

void Hyko::Entity::setScale(int indx, int8_t type, glm::vec2 newScale)
{
	Hyko::Triangle triangle;

	if (type == HK_TRIANGLE)
		triangle = m_scene->getSceneComponent<Hyko::Triangle>(indx, type);

	glm::mat4 transform;

	triangle.m_scale = newScale;

	if(type == HK_TRIANGLE)
		 transform = glm::scale(glm::mat4(1.0f), { newScale, 0.0f }) * glm::rotate(glm::mat4(1.0f), triangle.m_rotation, { 0.0f, 0.0f, 1.0f }) * glm::translate(glm::mat4(1.0f), { triangle.m_position, 0.0f });

	if (type == HK_TRIANGLE) {
		vert[indx][0].position = transform * glm::vec4(vert[indx][0].position, 1.0f);
		vert[indx][1].position = transform * glm::vec4(vert[indx][1].position, 1.0f);
		vert[indx][2].position = transform * glm::vec4(vert[indx][2].position, 1.0f);

		triangleVertices.clear();
		ConvertVertexToVertices(vert);

		vo.deleteVO();
		vo.createVertexObjects(triangleVertices, 7, triangleIndices);
	}
}

void Hyko::Entity::setRot(int indx, int8_t type, float angle)
{
	Hyko::Triangle triangle;

	if (type == HK_TRIANGLE)
		triangle = m_scene->getSceneComponent<Hyko::Triangle>(indx, type);

	glm::mat4 transform;

	triangle.m_rotation = angle;

	if (type == HK_TRIANGLE)
		transform = glm::translate(glm::mat4(1.0f), { triangle.m_position, 0.0f }) * glm::scale(glm::mat4(1.0f), { triangle.m_scale, 0.0f }) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f });

	if (type == HK_TRIANGLE) {
		vert[indx][0].position = transform * glm::vec4(vert[indx][0].position, 1.0f);
		vert[indx][1].position = transform * glm::vec4(vert[indx][1].position, 1.0f);
		vert[indx][2].position = transform * glm::vec4(vert[indx][2].position, 1.0f);

		triangleVertices.clear();
		ConvertVertexToVertices(vert);

		vo.deleteVO();
		vo.createVertexObjects(triangleVertices, 7, triangleIndices);
	}
}

void Hyko::Entity::setColor(int indx, int8_t type, glm::vec4 newColor)
{
	Hyko::Triangle triangle;

	if (type == HK_TRIANGLE)
		triangle = m_scene->getSceneComponent<Hyko::Triangle>(indx, type);

	triangle.m_color = newColor;

	if (type == HK_TRIANGLE) {
		vert[indx][0].color = newColor;
		vert[indx][1].color = newColor;
		vert[indx][2].color = newColor;

		triangle.m_color = newColor;

		triangleVertices.clear();
		ConvertVertexToVertices(vert);

		vo.deleteVO();
		vo.createVertexObjects(triangleVertices, 7, triangleIndices);
	}
}

void Hyko::Entity::EndDraw()
{
	vert = constVert;
}