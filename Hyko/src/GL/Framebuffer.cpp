#include "Framebuffer.h"

#include "Engine/System/Debug/Assert.h"
#include "Engine/System/FileSystem/LogFiles.h"

#include <GLAD/glad.h>
#include <glfw3.h>


FBO::~FBO()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_RGB_Color);
	glDeleteTextures(1, &m_depth);
}

void FBO::init()
{
	glCreateFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RGB_Color);
	glBindTexture(GL_TEXTURE_2D, m_RGB_Color);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RGB_Color, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_depth);
	glBindTexture(GL_TEXTURE_2D, m_depth);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_width, m_height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);

	HK_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FRAMEBUFFER is not compile");
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) Hyko::LogF::addMsgToLog("Framebuffer is compiled");
	else Hyko::LogF::addErrorMsgToLog("Framebuffer is not compiled");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void FBO::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::setFramebufferWidth(const short int value)
{
	m_width = value;
}

void FBO::setFramebufferHeight(const short int value)
{
	m_height = value;
}
