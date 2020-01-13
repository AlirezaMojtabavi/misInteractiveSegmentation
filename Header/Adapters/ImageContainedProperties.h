#pragma once

namespace parcast
{

	struct ImageContainedProperties
	{
		using ByteArrayPtr = std::shared_ptr<std::vector<uint8_t>>;

		std::string PolyDataUid;
		std::string	ImageContainedPolyDataUid;
		std::string	PolyDataName;
		int	IndexRepresentObject = 0;
		float ObjectVolume = 0.0;
		ByteArrayPtr Extend;
		bool ShowMargin = false;
		bool AlarmMargin = false;
		double MarginValue = 0;
		int NumberOfMarginPixel = 0;
		int MaxIndex =0;
		int NumberOfIndex = 0;
		int SurfaceType = 0;

		struct ColorType
		{
			double Alpha = 0.0;
			long long int Red = 0;
			long long int Green= 0;
			long long int Blue= 0;
		};
		ColorType Color;
	};
}