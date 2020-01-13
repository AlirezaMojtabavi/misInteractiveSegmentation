#pragma once
namespace parcast
{
	class IVirtualTipBuilder
	{
	public:
		virtual ~IVirtualTipBuilder() = default;
		virtual vtkSmartPointer<vtkPolyData> CreateVirtualTip(double length) = 0;
	};
}