#pragma once
#include"ImageContainedProperties.h"

namespace parcast
{
	class ImageContainedPropertiesMatcher
	{
	public:
		explicit ImageContainedPropertiesMatcher(const ImageContainedProperties& data) : m_Data(data)
		{}

		static bool IsEqual(const ImageContainedProperties& a, const ImageContainedProperties& b)
		{
			return
				a.PolyDataUid == b.PolyDataUid &&
				a.ImageContainedPolyDataUid == b.ImageContainedPolyDataUid &&
				a.PolyDataName == b.PolyDataName &&
				a.ObjectVolume == b.ObjectVolume &&
				a.Extend == b.Extend &&
				a.ShowMargin == b.ShowMargin &&
				a.AlarmMargin == b.AlarmMargin &&
				a.MarginValue == b.MarginValue&&
				a.NumberOfMarginPixel == b.NumberOfMarginPixel &&
				a.MaxIndex == b.MaxIndex &&
				a.NumberOfIndex == b.NumberOfIndex &&
				a.SurfaceType == b.SurfaceType &&
				a.Color.Alpha == b.Color.Alpha &&
				a.Color.Red == b.Color.Red &&
				a.Color.Green == b.Color.Green &&
				a.Color.Blue == b.Color.Blue;
			
		}

		bool operator()(const ImageContainedProperties& other) const
		{
			return IsEqual(m_Data, other);
		}

		ImageContainedProperties m_Data;
	};


}

