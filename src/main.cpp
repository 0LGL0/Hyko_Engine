#include "window.h"


Window windowClass;

int main() {
	windowClass.WindowDraw(1280, 720);
	windowClass.WindowUpdate();
	windowClass.WindowShutDown();

	return 0;
}