#pragma once
#include "IOpenGLContextSharing.h"

MOCK_BASE_CLASS(MockOpenGLContextSharing, IOpenGLContextSharing)
{
	
	MOCK_NON_CONST_METHOD(ShareContexts, 2, void(std::vector<std::shared_ptr<Iwindows>> , std::vector<std::shared_ptr<Iwindows>> ));

};

