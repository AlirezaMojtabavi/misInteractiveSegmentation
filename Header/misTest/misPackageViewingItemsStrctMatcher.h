#pragma once

#include "ChainBool.h"
#include "misPackageViewingItemsStrct.h"

namespace parcast
{

	class misPackageViewingItemsStrctMatcher
	{
	public:
		misPackageViewingItemsStrctMatcher(const misPackageViewingItemsStrct& data)
			: ThisData(data)
		{}

		bool operator()(const misPackageViewingItemsStrct& otherData)
		{
			return IsEqual(ThisData, otherData);
		}

		static bool IsEqual(const misPackageViewingItemsStrct& a, const misPackageViewingItemsStrct& b)
		{
			return ChainBool(std::cout, "misPackageViewingItemsStrctMatcher").
				Add(a.name == b.name).
				Add(a.packegeUID == b.packegeUID).
				Add(a.packageType == b.packageType).
				Add(IsShortImageEqual(a.imageProperties, b.imageProperties)).
				Add(IsShortImageContainedPolydataEqual(a.imageContainedProperties, b.imageContainedProperties)).
				Add(IsShort3DModelEqual(a.polyaDataProperties, b.polyaDataProperties)).
				Add(IsShort3DModelEqual(a.planningDataProperties, b.planningDataProperties)).
				Add(IsShort3DModelEqual(a.fmriDataProperties, b.fmriDataProperties));
		}

	private:
		const misPackageViewingItemsStrct& ThisData;

		static bool IsShortImageEqual(
			const std::vector<misShortImageViewingStrct>& l, const std::vector<misShortImageViewingStrct>& r)
		{
			ChainBool cb(std::cout, "IsShortImageEqual"); 
			cb.Add(l.size() == r.size());
			if (!cb)
				return false;
			if (l.empty())
				return true;
			for (auto i = l.size() - 1; i > 0; --i)
				cb.Add(l[i].name == r[i].name).
				Add(l[i].objectUID == r[i].objectUID).
				Add(l[i].opacity == r[i].opacity).
				Add(l[i].useable == r[i].useable).
				Add(l[i].visibility == r[i].visibility);
			return cb;
		}

		static bool IsShortImageContainedPolydataEqual(
			const std::vector<misShortImageContainedPolydataViewingStrct>& l, 
			const std::vector<misShortImageContainedPolydataViewingStrct>& r)
		{
			ChainBool cb(std::cout, "IsShortImageContainedPolydataEqual");
			cb.Add(l.size() == r.size());
			if (!cb)
				return false;
			if (l.empty())
				return true;
			for (auto i = l.size() - 1; i > 0; --i)
				cb.Add(l[i].objectUID == r[i].objectUID).
				Add(l[i].visibility == r[i].visibility);
			return cb;
		}

		static bool IsShort3DModelEqual(
			const std::vector<misShort3DModelViewingStrct>& l,
			const std::vector<misShort3DModelViewingStrct>& r)
		{
			ChainBool cb(std::cout, "IsShort3DModelEqual");
			cb.Add(l.size() == r.size());
			if (!cb)
				return false;
			if (l.empty())
				return true;
			for (auto i = l.size() - 1; i > 0; --i)
				cb.Add(l[i].name == r[i].name).
				Add(l[i].objectUID == r[i].objectUID).
				Add(l[i].objectContainerUID == r[i].objectContainerUID).
				Add(l[i].parentImageUID == r[i].parentImageUID).
				Add(l[i].opacity == r[i].opacity).
				Add(l[i].volume == r[i].volume).
				Add(l[i].type == r[i].type).
				Add(l[i].renderingType == r[i].renderingType).
				Add(l[i].color.alpha == r[i].color.alpha).
				Add(l[i].color.red == r[i].color.red).
				Add(l[i].color.green == r[i].color.green).
				Add(l[i].color.blue == r[i].color.blue).
				Add(l[i].useable == r[i].useable).
				Add(l[i].visibility3D == r[i].visibility3D).
				Add(l[i].segmentedObjectVisibility == r[i].segmentedObjectVisibility).
				Add(l[i].objectMarginAlarm == r[i].objectMarginAlarm).
				Add(l[i].objectShowMargin == r[i].objectShowMargin).
				Add(l[i].objectMarginValue == r[i].objectMarginValue);
			return cb;
		}
	};

}
