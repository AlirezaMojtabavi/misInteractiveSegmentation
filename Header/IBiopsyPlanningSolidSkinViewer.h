#pragma once
#include "ISimpleDataPackage.h"
#include "misCroppingDirectionInVR.h"

namespace parcast
{
	class IBiopsyPlanningSolidSkinViewer
	{
	public:
		virtual  ~IBiopsyPlanningSolidSkinViewer() = default;

		virtual void Render(std::shared_ptr<ISimpleDataPackage> package, misCroppingDirectionInVR croppingDir = NoCut) = 0;
	};
}
