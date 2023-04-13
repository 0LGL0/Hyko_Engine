#include "EditorCamera.h"

#include "Engine/Core/KeyKodes.h"
#include "Engine/Core/MouseButtons.h"
#include "Engine/Events/InputEvents.h"

#include "Engine/System/FileSystem/LogFiles.h"

// GL / Maths
#include <glm/gtc/matrix_transform.hpp>

// std
#include <iostream>

void Hyko::Camera::updateInput(const float dt)
{
	if (Hyko::Input::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT)) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_W))
			setPos(getPos().x, getPos().y - m_camSpeed * dt);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_S))
			setPos(getPos().x, getPos().y + m_camSpeed * dt);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_A))
			setPos(getPos().x + m_camSpeed * dt, getPos().y);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_D))
			setPos(getPos().x - m_camSpeed * dt, getPos().y);
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL))
			setPos(0.0f, 0.0f);
	}

	if (Hyko::Input::getMouseYOffset() <= -1.0f || Hyko::Input::getMouseYOffset() >= 1.0f) {
		if (m_zoomValue <= 2.0f && m_zoomValue >= 0.01f)
			m_zoomValue -= (Hyko::Input::getMouseYOffset() * 5.0f) * dt;
		if (m_zoomValue > 2.0f)
			m_zoomValue = 2.0f;
		else if (m_zoomValue < 0.01f)
			m_zoomValue = 0.01f;
	}
}

void Hyko::Camera::updateView()
{
	m_viewMat = glm::translate(glm::mat4(1.0f), { m_pos, 0.0f });
}

void Hyko::Camera::updateProjection(std::shared_ptr<FBO> fbo)
{
	const float w = (float)fbo->getFramebufferWidth()  / 2.0f;
	const float h = (float)fbo->getFramebufferHeight() / 2.0f;

	m_left = -(w * m_zoomValue);
	m_right = w * m_zoomValue;
	m_bottom = -(h * m_zoomValue);
	m_top = h * m_zoomValue;

	m_projMat = glm::ortho(m_left, m_right, m_bottom, m_top);
}