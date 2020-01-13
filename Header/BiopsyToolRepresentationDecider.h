#pragma once

#include "misToolProperties.h"
#include "IToolRepresentationDecider.h"


class IVolume3DRenderer;

namespace parcast
{
	class BiopsyToolRepresentationDecider :public IToolRepresentationDecider
	{
	public:
		BiopsyToolRepresentationDecider();
		misToolRepresentationType GetToolRepType(std::shared_ptr<IVolumeRenderer> viewer) override;
	};
}