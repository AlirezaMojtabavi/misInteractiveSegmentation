#pragma once

#include "misToolProperties.h"
#include "IToolRepresentationDecider.h"

using namespace parcast;

namespace parcast
{
	class ToolRepresentationDecider :public IToolRepresentationDecider
	{
	public:
		ToolRepresentationDecider();
		misToolRepresentationType GetToolRepType(std::shared_ptr<IVolumeRenderer> viewer) override;
	};
}



