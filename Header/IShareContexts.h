#pragma once
#include "IWindows.h"

class IShareContexts
{
public:
	virtual ~IShareContexts() = default;
	virtual void ShareContexts(std::vector<std::shared_ptr<Iwindows>>&& windows) = 0;
	
};

