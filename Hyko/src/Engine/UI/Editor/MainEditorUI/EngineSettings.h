#pragma once

#include "Engine/Scene/Scene.h"

#include <imgui.h>

// std
#include <memory>
#include <vector>
#include <string>
#include <functional>

namespace Hyko {
	class ESettings {
	private:
		using pointer = void(Hyko::ESettings::*)(void); // pointer to void function
	private:
		std::shared_ptr<Scene> m_scene;
	private: // Settings menus is opened?
		bool SystemDataOpened = false;

		//Hyko::ESettings::NameAndPointer m_SettingsHierarchyNames[1][1] = { {{"Data", &Data}}};

		const std::vector<std::vector<const char*>> m_HierarchySectionNames{ {"System", "Data"}};
		
		//std::vector<std::vector<Hyko::ESettings::NameAndPointer>> m_SettingsHierarchyNames = { { {"Data", &Data} } };

		//pointer m_SelectedFunc; // Selected function from hierarchy section

		char* m_selectedSectionName;

		float beginTime;
	private:
		//struct NameAndPointer {
		//	NameAndPointer(std::string _name, pointer _pointer)
		//		: name(_name), funcPointer(_pointer) {}

		//	pointer funcPointer;// Pointer to function
		//	std::string name; // Name of hierarchy section
		//};
	private:
		void Data();
	public:
		ESettings() = default;
		ESettings(std::shared_ptr<Scene> scene)
			: m_scene(scene){}
		void init();
	};
}