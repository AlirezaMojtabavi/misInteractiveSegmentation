#pragma once
#include "IImage.h"
#include "ITrackingToolQuery.h"

namespace parcast
{
	class IRegistrationCapturePoint
	{
	public:
		virtual int CaptureLastToolPositionAsLandmark(bool checkNewLandmarkMaxErrorForAcceptin,
			int currentSelectedLandmarkIndex, bool trackingEnabled, bool lastMustBeSelected) = 0;
		virtual void SetImage(std::shared_ptr<IImage> image) = 0;
		virtual void SetTrackingToolQueruy(std::shared_ptr<ITrackingToolQuery>) = 0;
		virtual ~IRegistrationCapturePoint()
		{

		}
	};
}