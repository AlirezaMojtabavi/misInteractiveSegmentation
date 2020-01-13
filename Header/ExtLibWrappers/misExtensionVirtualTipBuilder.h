#pragma once
#include "IVirtualTipBuilder.h"
namespace parcast
{
	class misExtensionVirtualTipBuilder : public IVirtualTipBuilder
	{
	public:

		virtual vtkSmartPointer<vtkPolyData> CreateVirtualTip(double length) override;
	};

}