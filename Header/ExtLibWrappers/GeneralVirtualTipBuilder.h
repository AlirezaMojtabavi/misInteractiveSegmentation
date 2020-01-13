#pragma once
#include "IVirtualTipBuilder.h"
namespace parcast
{
	class GeneralVirtualTipBuilder : public IVirtualTipBuilder
	{
	public:
		GeneralVirtualTipBuilder();
		vtkSmartPointer<vtkPolyData> CreateVirtualTip(double length) override;
	private:
 		static vtkSmartPointer<vtkPolyData> CreateStraightLinePolyData(double length);
 	};
}
