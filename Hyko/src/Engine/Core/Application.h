#pragma once

#include "Engine/Meshes/Entity.h"
#include "Engine/Projection/EditorProjection.h"
#include "GL/Window/window.h"
#include "Engine/System/Tools.h"
#include "Engine/System/FileSystem/shader.h"

// Editor camera
#include "Engine/Scene/Camera/EditorCamera.h"

// UI
#include "Engine/UI/EngineUILayer.h"

// std
#include <memory>

class App {
private:
	//EProjection EProj;
	std::shared_ptr<Hyko::Scene> m_scene{ new Hyko::Scene };
	Shader c_shader;
	std::shared_ptr<Hyko::ECamera> eCamera{ new Hyko::ECamera };

	// UI
	Hyko::EUILayer eUILayer{ m_scene, eCamera };
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