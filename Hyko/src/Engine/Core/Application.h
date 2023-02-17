#pragma once

#include "Engine/Meshes/Entity.h"
#include "GL/Window/window.h"
#include "Engine/System/FileSystem/shader.h"

// Editor camera
#include "Engine/Scene/Camera/EditorCamera.h"

// Editor UI
#include "Engine/UI/EngineUILayer.h"

#include "Engine/Renderer/Renderer.h"

// HK_GL
#include "GL/Framebuffer.h"

#include "entt.hpp"

// std
#include <memory>

class App {
private:
	std::shared_ptr<Hyko::Scene> m_scene{ std::make_shared<Hyko::Scene>() };
	std::shared_ptr<Shader> c_shader{new Shader};
	std::shared_ptr<Hyko::ECamera> eCamera{ new Hyko::ECamera };
	std::shared_ptr<FBO> fbo{std::make_shared<FBO>(1280.0f, 720.0f)};

	// UI
	Hyko::EUILayer eUILayer{ m_scene, fbo };
private:
	glm::mat4 projection;
	glm::mat4 view;
private:
	unsigned int shaderProgram;

	float m_LastFrameTime = 0.0f;
public:
	App() = default;

	void Init();
};