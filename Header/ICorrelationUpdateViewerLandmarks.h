#pragma once
namespace  parcast
{

	class ICorrelationUpdateViewerLandmarks
	{
	public:
		virtual ~ICorrelationUpdateViewerLandmarks() = default;
		virtual void UpdateViewerLandmarks() = 0;
	};
}
