#pragma once
#include "IVirtualTipBuilder.h"

namespace parcast
{
	class BiopsyVirtualTipBuilder : public IVirtualTipBuilder
	{
	public:
		BiopsyVirtualTipBuilder();
		vtkSmartPointer<vtkPolyData> CreateVirtualTip(double length) override;
	};

}

