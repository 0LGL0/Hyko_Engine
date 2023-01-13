#include "EditorCamera.h"

#include "Engine/Core/KeyKodes.h"
#include "Engine/Core/MouseButtons.h"
#include "Engine/Events/InputEvents.h"

// GL / Maths
#include <glm/gtc/matrix_transform.hpp>

// std
#include <iostream>

Hyko::ECamera::ECamera(Hyko::OrthographicData data, glm::vec2 position)
{
	setData(data);
	m_position = position;

	m_type = projType::Orthographic;
}

Hyko::ECamera::ECamera(Hyko::PerspectiveData data, glm::vec2 position)
{
	setData(data);
	m_position = position;

	m_type = projType::Perspective;
}

void Hyko::ECamera::setPosition(glm::vec2 newPos)
{
	m_position = newPos;
}

void Hyko::ECamera::setPosition(float x, float y)
{
	m_position = { x, y };
}

void Hyko::ECamera::setData(Hyko::OrthographicData data)
{
	m_orthoData.m_bottom = data.m_bottom;
	m_orthoData.m_left = data.m_left;
	m_orthoData.m_right = data.m_right;
	m_orthoData.m_top = data.m_top;

	m_type = projType::Orthographic;
}

void Hyko::ECamera::setData(Hyko::PerspectiveData data)
{
	m_perspData.m_aspect = data.m_aspect;
	m_perspData.m_fovY = data.m_fovY;
	m_perspData.m_zFar = data.m_zFar;
	m_perspData.m_zNear = data.m_zNear;

	m_type = projType::Perspective;
}

void Hyko::ECamera::initProjection()
{
	switch (m_type) {
	case projType::Orthographic:
		m_projectionMat = glm::ortho(m_orthoData.m_left, m_orthoData.m_right, m_orthoData.m_bottom, m_orthoData.m_top, -1.0f, 1.0f);
		break;
	case projType::Perspective:
		m_projectionMat = glm::perspective(glm::radians(m_perspData.m_fovY), m_perspData.m_aspect, m_perspData.m_zNear, m_perspData.m_zFar);
		break;
	}

	m_viewMat = glm::lookAt(glm::vec3(m_position, 0.0f), glm::vec3(m_position, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Hyko::ECamera::updateInput(float dt, float camSpeed)
{
	// Movement
	if (Hyko::Input::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT)) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBORD_W))
			setPosition(getPosition().x, getPosition().y + camSpeed * dt);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBORD_S))
			setPosition(getPosition().x, getPosition().y - camSpeed * dt);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBORD_A))
			setPosition(getPosition().x - camSpeed * dt, getPosition().y);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBORD_D))
			setPosition(getPosition().x + camSpeed * dt, getPosition().y);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBORD_LEFT_CONTROL))
			setPosition(0.0f, 0.0f);
	}

	// Zoom
	if (Hyko::Input::getMouseYOffset() >= 1 || Hyko::Input::getMouseYOffset() <= -1) {
		switch (m_type) {
		case projType::Perspective: // Perspective
			if (m_perspData.m_fovY >= 1.0f && m_perspData.m_fovY <= 120.0f)
				m_perspData.m_fovY -= (Hyko::Input::getMouseYOffset() * 500) * dt;
			if (m_perspData.m_fovY > 120.0f)
				m_perspData.m_fovY = 120.0f;
			if (m_perspData.m_fovY < 1.0f)
				m_perspData.m_fovY = 1.0f;

			m_orthoData.m_bottom = -(m_perspData.m_fovY * 3.33f);
			m_orthoData.m_left = -(m_perspData.m_fovY * 3.33f);
			m_orthoData.m_top = m_perspData.m_fovY * 3.33f;
			m_orthoData.m_right = m_perspData.m_fovY * 3.33f;
			// 3.33 is a constant for 400 / 120
			// 400 is a max number for one side when ortho zoom
			// 120 is a max fov angle for perspective zoom

			break;

		case projType::Orthographic: //Orthographic
			if (Hyko::Input::getMouseYOffset() <= -1) { // Zoom -
				m_orthoData.m_bottom += Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_left += Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_top -= Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_right -= Hyko::Input::getMouseYOffset() * 1000 * dt;
			}
			else if (Hyko::Input::getMouseYOffset() >= 1) { // Zoom +
				m_orthoData.m_bottom += Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_left += Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_top -= Hyko::Input::getMouseYOffset() * 1000 * dt;
				m_orthoData.m_right -= Hyko::Input::getMouseYOffset() * 1000 * dt;
			}

			if ((m_orthoData.m_bottom < -400.0f && m_orthoData.m_left < -400.0f) && (m_orthoData.m_right > 400.0f && m_orthoData.m_top > 400.0f)) {
				m_orthoData.m_bottom = -400.0f;
				m_orthoData.m_left = -400.0f;
				m_orthoData.m_right = 400.0f;
				m_orthoData.m_top = 400.0f;
			}
			if ((m_orthoData.m_bottom > -1.0f && m_orthoData.m_left > -1.0f) && (m_orthoData.m_right < 1.0f && m_orthoData.m_top < 1.0f)) {
				m_orthoData.m_bottom = -1.0f;
				m_orthoData.m_left = -1.0f;
				m_orthoData.m_right = 1.0f;
				m_orthoData.m_top = 1.0f;
			}

			m_perspData.m_fovY = m_orthoData.m_top / 3.33f;
			// 3.33 is a constant for 400 / 120
			// 400 is a max number for one side when ortho zoom
			// 120 is a max fov angle for perspective zoom

			break;
		}
	}
}

glm::mat4 Hyko::ECamera::updateView()
{
	m_viewMat = glm::translate(glm::mat4(1.0f), { m_position, m_type == projType::Orthographic ? 0.0f : 100.0f });
	m_viewMat = glm::inverse(m_viewMat);
	
	return m_viewMat;
}

glm::mat4 Hyko::ECamera::updateProjection()
{
	switch (m_type) {
	case projType::Orthographic:
		m_projectionMat = glm::ortho(m_orthoData.m_left, m_orthoData.m_right, m_orthoData.m_bottom, m_orthoData.m_top, -1.0f, 1.0f);
		break;
	case projType::Perspective:
		m_projectionMat = glm::perspective(glm::radians(m_perspData.m_fovY), m_perspData.m_aspect, m_perspData.m_zNear, m_perspData.m_zFar);
		break;
	}

	return m_projectionMat;
}

void Hyko::ECamera::swapProjection(Hyko::projType type)
{
	m_type = type;
	updateProjection();
	updateView();
}
