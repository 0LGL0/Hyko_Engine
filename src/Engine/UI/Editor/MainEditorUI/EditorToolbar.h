#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include "../Engine/System/Tools.h"

namespace Hyko {
	class EToolbar {
	private:
		//Hyko::Entity entity;
	private:
		bool createIsOpen = false;
	private:
		void sceneData_Menu();
		void create_Menu();
		void Christmas();
	public:
		bool meshIsCreting = false;
	public:
		void createEToolbar();
	};
}