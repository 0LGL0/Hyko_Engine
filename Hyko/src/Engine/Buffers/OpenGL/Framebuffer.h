#pragma once

#include <stdint.h>

class FBO {
private:
	uint32_t m_FBO;
	uint32_t m_RGB_Color;
	uint32_t m_depth;
private:
	short int m_width;
	short int m_height;
public:
	FBO(const float width, const float height)
		: m_width(width), m_height(height) {}
	~FBO();

	void init();

	void bind();
	void unBind();
public: // getters
	uint32_t getFBOTexture() { return m_RGB_Color; }
	uint32_t getFBO() { return m_FBO; }

	short int getFramebufferWidth() { return m_width; }
	short int getFramebufferHeight() { return m_height; }
public:
	void setFramebufferWidth(const short int value);
	void setFramebufferHeight(const short int value);
};