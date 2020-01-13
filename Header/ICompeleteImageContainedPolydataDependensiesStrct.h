#pragma once
#include "mis3DModelViewingProperties.h"
#include "misSegmentedObjectTransferFunction.h"
#include "IImageContained.h"


struct misColorStruct;
class misImageContained;
struct misShort3DModelViewingStrct;
class  ICompeleteImageContainedPolydataDependensiesStrct
{
public:
	virtual ~ICompeleteImageContainedPolydataDependensiesStrct() = default;
	virtual void SetParentUID(const misUID& uid)  = 0;
	virtual misUID GetParentUID() const = 0;
	virtual void SetImageContained(const std::shared_ptr<IImageContained> imageCOntained) = 0;
	virtual std::shared_ptr<IImageContained> GetImageContained() const = 0;
	virtual void SetObjectUID(const misUID& uid) = 0;
	virtual misUID GetObjectUID() const = 0;
	virtual void SetAllObjectVisibility(const misObjectVisibilityMap& visibilityMap) = 0;
	virtual misObjectVisibilityMap GetAllObjectVisibility() const = 0;
	virtual void AddObjectVisibility(const misObjectVisibilityPair& objectVisibilty) = 0;
	virtual void RemoveObjcteVisibility(const misUID& segmentedObjUID) = 0;
	virtual void SetAlarmMargin(const misUID& SegmentedObjectUID, bool val) = 0;
	virtual void ShowMarginRegion(const misUID& SegmentedObjectUID, bool val) = 0;
	virtual void SetObjctVisibility(misUID, mis3DModelObjectOpacityPropertiesStrct) = 0;
	virtual void Set2dVisibility(misUID, bool visibility) = 0;
	virtual void Set3dVisibility(misUID, bool visibility) = 0;
	virtual void SetOpacity(misUID, double opacity) = 0;
	virtual void SetAllInvisible() = 0;
	virtual std::vector<misShort3DModelViewingStrct>  GetPolydataStrcViewing() const = 0;
	virtual void SetObjectColor(misUID polyDataUID, misColorStruct polyDataColor) = 0;
	virtual void ClearVisibilities() = 0;
	virtual bool HasVisibilityProperties(misUID polyDataUID) = 0;
	virtual void SetinitilizeProperties(double segmentedObjectOpacityScale, misUID imageUID) = 0;
	virtual std::vector<misSegmentedObjectTransferFunction> GetTransferFuncs() const = 0;
};
