#include "Scene.h"

int Hyko::Scene::getComponentCount(int8_t type)
{
    if (type == HK_TRIANGLE)
        return sceneTriangles.size();

    return 0;
}
