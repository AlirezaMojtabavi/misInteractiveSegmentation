#pragma once
#include "IWindows.h"

class IOpenGLContextSharing
{
public:
	virtual ~IOpenGLContextSharing() = default;
	virtual void ShareContexts(std::vector<std::shared_ptr<Iwindows>> source, std::vector<std::shared_ptr<Iwindows>> dest ) = 0;
};
