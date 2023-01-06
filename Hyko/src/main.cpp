#ifdef MEMORYLEAKS_SHOW
#include <vld.h>
#endif // MEMORYLEAKS_SHOW

#include "Engine/Core/Application.h"

int main() {
	App EApp;

	EApp.Init();

	return 0;
}