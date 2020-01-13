#pragma  once
#include "ICompeleteImageContainedPolydataDependensiesStrct.h"

class misImageContained;
class misSegmentedObjectTransferFunction;
class mis3DModelObjectOpacityPropertiesStrct;


struct misColorStruct;

typedef std::string misUID;
typedef std::map<misUID, mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityMap;
typedef std::pair<misUID, mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityPair;

class  misCompeleteImageContainedPolydataDependensiesStrct : public ICompeleteImageContainedPolydataDependensiesStrct
{
public:

	misCompeleteImageContainedPolydataDependensiesStrct();

	void SetParentUID(const misUID& uid) override;
	misUID GetParentUID() const override;
	void SetImageContained(const std::shared_ptr<IImageContained> imageCOntained) override;
	std::shared_ptr<IImageContained> GetImageContained() const override;
	void SetObjectUID(const misUID& uid) override;
	misUID GetObjectUID() const override;
	void SetAllObjectVisibility(const misObjectVisibilityMap& visibilityMap) override;
	misObjectVisibilityMap GetAllObjectVisibility() const override;
	void AddObjectVisibility(const misObjectVisibilityPair& objectVisibilty) override;
	void RemoveObjcteVisibility(const misUID& segmentedObjUID) override;
	void SetAlarmMargin(const misUID& SegmentedObjectUID, bool val) override;
	void ShowMarginRegion(const misUID& SegmentedObjectUID, bool val) override;
	void SetObjctVisibility(misUID, mis3DModelObjectOpacityPropertiesStrct) override;
	void Set2dVisibility(misUID, bool visibility) override;
	void Set3dVisibility(misUID, bool visibility)override ;
	void SetOpacity(misUID, double opacity)override ;

	void SetAllInvisible() override;
	std::vector<misShort3DModelViewingStrct>  GetPolydataStrcViewing() const override;
	void SetObjectColor(misUID polyDataUID, misColorStruct polyDataColor) override;
	void ClearVisibilities() override;
	bool HasVisibilityProperties(misUID polyDataUID) override;
	void SetinitilizeProperties(double segmentedObjectOpacityScale, misUID imageUID)override ;
	std::vector<misSegmentedObjectTransferFunction> GetTransferFuncs() const override;

private:
	misUID  m_ParentUID;
	std::shared_ptr<IImageContained> m_ImageContained;
	misUID m_ObjectUID;
	misObjectVisibilityMap m_AllObjectVisibility;

};
typedef  std::vector<std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct>>   ImageContainedPolydataDependencyListTypes;

