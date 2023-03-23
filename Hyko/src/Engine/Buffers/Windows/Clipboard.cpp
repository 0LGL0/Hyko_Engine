#include "Clipboard.h"

#include "GL/Window/window.h"

#include "Engine/System/Debug/Assert.h"
#include "Engine/System/Debug/Log.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3.h>
#include <glfw3native.h>

void Clipboard::inClipboard(const std::string data) {
	const auto HWND = glfwGetWin32Window(Window::getNativeWindow());
	HK_ASSERT(HWND);

	if (OpenClipboard(HWND)) {
		if (!EmptyClipboard()) {
			HK_ERROR("Failed to clear clipboard");
			CloseClipboard();
			return;
		}
		const size_t strLen = data.length() + 1; // + null symbol
		const auto hMem = GlobalAlloc(GMEM_MOVEABLE, strLen);
		if (hMem) {
			void* buffer = GlobalLock(hMem);
			if (buffer == nullptr) {
				HK_ERROR("The clipboard is not locked (write)");
				CloseClipboard();
				return;
			}
			memcpy(buffer, data.c_str(), strLen);
			GlobalUnlock(hMem);
			if (!SetClipboardData(CF_TEXT, hMem)) {
				HK_ERROR("The data is not installed in the clipboard");
				GlobalFree(hMem);
				CloseClipboard();
				return;
			}
			CloseClipboard();
		}
		else {
			GlobalFree(hMem);
			CloseClipboard();
			return;
		}
	}
}

std::string Clipboard::outClipboard()
{
	const auto HWND = glfwGetWin32Window(Window::getNativeWindow());
	HK_ASSERT(HWND);

	if (OpenClipboard(HWND)) {
		const auto hData = GetClipboardData(CF_TEXT);
		if (hData) {
			char* buffer = static_cast<char*>(GlobalLock(hData));
			if (buffer == nullptr) {
				HK_ERROR("The clipboard is not locked (read)");
				CloseClipboard();
				return "";
			}
			GlobalUnlock(hData);
			CloseClipboard();

			return static_cast<std::string>(buffer);
		}
	}

	return "";
}
