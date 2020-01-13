#pragma once
class misScrewWidgetData;
struct misLandmarkInfoStruct;

class IBiopsyScrewWidgetUpdater
{
public:
	enum CHANGES
	{
		EntryPointHasChanged,
		TargetPointHasChaned,
		NothingHasChanged,
		EntryPointAndTargetPointHaveChanged
	};

	struct CHANGERESULT
	{
		CHANGES Changes = NothingHasChanged;

		misItkPointType EntryPointLastPosition;
		misItkPointType EntryPointCurrentPosition;

		misItkPointType TargetPointLastPosition;
		misItkPointType TargetPointCurrentPosition;
	};

public:
	virtual ~IBiopsyScrewWidgetUpdater() = default;

	virtual void Update(const misScrewWidgetData& screwWidgetVal, misLandmarkInfoStruct& targetLandmarkRelation,
	                    misLandmarkInfoStruct& entryLandmarkRelation) = 0;
};
