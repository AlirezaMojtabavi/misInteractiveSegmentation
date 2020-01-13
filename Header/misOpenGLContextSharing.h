#pragma once
#include "IWindows.h"
#include "IOpenGLContextSharing.h"

class misOpenGLContextSharing: public IOpenGLContextSharing
{
public:
	void ShareContexts(std::vector<std::shared_ptr<Iwindows>> source,
		std::vector<std::shared_ptr<Iwindows>> dest);
};
