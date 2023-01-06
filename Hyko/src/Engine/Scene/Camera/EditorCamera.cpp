#include "EditorCamera.h"

#include <glm/gtc/matrix_transform.hpp>

Hyko::ECamera::ECamera(Hyko::OrthographicData data)
{
	orthoData.bottom = data.bottom;
	orthoData.left	 = data.left;
	orthoData.right  = data.right;
	orthoData.top	 = data.top;

	projType::Orthographic;

	orthoMat = glm::ortho(orthoData.left, orthoData.right, orthoData.bottom, orthoData.top);
}

Hyko::ECamera::ECamera(Hyko::PerspectiveData data)
{
	perspData.aspect = data.aspect;
	perspData.fovY	 = data.fovY;
	perspData.zFar	 = data.zFar;
	perspData.zNear	 = data.zNear;

	projType::Perspective;

	perspectiveMat = glm::perspective(perspData.fovY, perspData.aspect, perspData.zNear, perspData.zFar);
}

void Hyko::ECamera::setData(OrthographicData data)
{
	orthoData.bottom = data.bottom;
	orthoData.left = data.left;
	orthoData.right = data.right;
	orthoData.top = data.top;

	projType::Orthographic;

	orthoMat = glm::ortho(orthoData.left, orthoData.right, orthoData.bottom, orthoData.top);
}

void Hyko::ECamera::setData(PerspectiveData data)
{
	perspData.aspect = data.aspect;
	perspData.fovY = data.fovY;
	perspData.zFar = data.zFar;
	perspData.zNear = data.zNear;

	projType::Perspective;

	perspectiveMat = glm::perspective(perspData.fovY, perspData.aspect, perspData.zNear, perspData.zFar);
}
