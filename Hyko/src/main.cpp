/********************************************
* 
* Hyko Engine (2D), ver: 0.1
* OpenGL 4.6, GLSL 4.60
* LICENSE: MPL 2.0
* 
* Good luck understanding my code)))
* 
********************************************/

#ifdef MEMORYLEAKS_SHOW
#include <vld.h>
#endif // MEMORYLEAKS_SHOW

#include "Engine/Core/Application.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/System/FileSystem/LogFiles.h"

int main() {
	App EApp;

	Hyko::Log::init();
	EApp.Init();
	Hyko::LogF::shutdown();

	return 0;
}