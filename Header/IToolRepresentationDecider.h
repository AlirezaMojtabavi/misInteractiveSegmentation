#pragma once
#include "misToolProperties.h"
#include "IVolumeRenderer.h"

 
namespace parcast
{
	class IToolRepresentationDecider
	{
	public:
		virtual misToolRepresentationType GetToolRepType(std::shared_ptr<IVolumeRenderer> viewer) = 0;
	};
}