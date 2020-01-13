#pragma once
#include "IMultiplaViewCorrelationAdapter.h"
#include "misImageCorrelationSetting.h"

class INavigationViewersNView;
class ISimpleDataPackage;

struct misOpacityAndUID;

enum misPlaneEnum;

typedef std::string misUID;

class misMultiplaViewCorrelationAdapter : public IMultiplaViewCorrelationAdapter
{
public:
	misMultiplaViewCorrelationAdapter(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ISimpleDataPackage> package, misUID fixedImageUId, misUID movingImageUID,
		const ImageCorrelationSetting& colorSetting, const misOpacityAndUID& opacityPack);
	void SetViewPortTypeToMultiple() override;
private:

	std::vector<std::map<misPlaneEnum, bool>> CreateDefaultVisibiltyAlltrue();

	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::weak_ptr<ISimpleDataPackage> m_CurrentPackage;
	misUID m_FixedImageUID;
	misUID m_MovingImageUID;
	const ImageCorrelationSetting& m_ColorSetting;
};

