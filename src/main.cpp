//#define MEMORYLEAKS_SHOW

#ifdef MEMORYLEAKS_SHOW
#include <vld.h>
#endif // MEMORYLEAKS_SHOW

#include "window.h"

Window windowClass;

int main() {
	windowClass.WindowDraw(1280, 720);
	windowClass.WindowUpdate();
	windowClass.WindowShutDown();

	return 0;
}