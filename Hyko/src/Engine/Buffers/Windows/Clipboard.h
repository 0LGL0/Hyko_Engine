#pragma once

#include <Windows.h>
#include <string>

class Clipboard {
public:
	static void inClipboard(const std::string data);
	static std::string outClipboard();
	
};