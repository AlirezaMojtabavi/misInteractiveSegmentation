#pragma once

namespace parcast
{

	class IAutomaticCalibrationDetector
	{
	public:
		virtual void Update() = 0;
	};

}