#pragma once
#include "IShareContexts.h"

class misShareContexts : public IShareContexts
{
public:
	misShareContexts();
	~misShareContexts();
	void ShareContexts(std::vector<std::shared_ptr<Iwindows>>&& windows) override;
};

