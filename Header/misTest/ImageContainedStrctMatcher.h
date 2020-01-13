#pragma once

#include "ChainBool.h"
#include "../misImageContainedPolyDataStructs.h"

namespace parcast
{
	class ImagePolyDataContenStrctMatcher
	{
	public:
		static bool IsEqual(const ImagePolyDataContenStrct& a, const ImagePolyDataContenStrct& b)
		{
			return ChainBool(std::cout, "ImagePolyDataContenStrctMatcher").
				Add(a.PolyDataUID == b.PolyDataUID).
				Add(a.marginValue == b.marginValue).
				Add(a.IndexRepresentObject == b.IndexRepresentObject).
				Add(a.GetShowMargin() == b.GetShowMargin()).
				Add(std::abs(a.ObjectVolume - b.ObjectVolume) < 1.e-4).
				Add(a.OpacityProp.GetVisibilityIn3DScene() == b.OpacityProp.GetVisibilityIn3DScene()).
				Add(a.OpacityProp.GetOpacityIn2DScene() == b.OpacityProp.GetOpacityIn2DScene()).
				Add(a.OpacityProp.OpacityIn3DScene == b.OpacityProp.OpacityIn3DScene).
				Add(a.OpacityProp.visibilityIn2DScene == b.OpacityProp.visibilityIn2DScene).
				Add(a.alarmMarging == b.alarmMarging).
				Add(a.maxIndex == b.maxIndex).
				Add(a.PolyDataColor == b.PolyDataColor).
				Add(a.PolyDataName == b.PolyDataName).
				Add(a.surfaceType == b.surfaceType).
				Add(a.numberOfIndex == b.numberOfIndex).
				Add(a.numberOfMarginPixel == b.numberOfMarginPixel);

		}


		
	};


}
