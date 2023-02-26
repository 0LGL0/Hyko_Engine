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