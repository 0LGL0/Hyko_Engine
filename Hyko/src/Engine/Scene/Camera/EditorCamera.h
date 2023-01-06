#pragma once
#include <glm/glm.hpp>

namespace Hyko {
	struct OrthographicData {
		int left	= 0;
		int right	= 0;
		int bottom	= 0;
		int top		= 0;
	};

	struct PerspectiveData {
		float fovY	= 0;
		float aspect	= 0;
		float zNear	= 0;
		float zFar	= 0;
	};

	enum projType {
		Orthographic, Perspective
	};

	class ECamera {
	private:
		OrthographicData orthoData;
		PerspectiveData  perspData;
	private:
		glm::mat4 perspectiveMat = glm::mat4(1.0f);
		glm::mat4 orthoMat		 = glm::mat4(1.0f);
	public:
		ECamera() = default;
		ECamera(Hyko::OrthographicData data);
		ECamera(Hyko::PerspectiveData data);
		~ECamera();
	public: // setters
		void setData(OrthographicData data);
		void setData(PerspectiveData data);
	};
}