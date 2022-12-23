#pragma once
#include <imgui.h>
#include <string>

namespace Hyko {
	class EHierarchy{
	private:
		void createNewTree(int8_t type, int indx);
	public:
		void createHierarchy();
	};
}