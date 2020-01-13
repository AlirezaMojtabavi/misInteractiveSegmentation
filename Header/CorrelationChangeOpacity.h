#pragma once
#include "ICorrelationChangeOpacity.h"
#include <misImageCorrelationSetting.h>
#include "ICorrelationShowVolumes.h"
#include "INavigationViewersNView.h"

class CorrelationChangeOpacity :
	public ICorrelationChangeOpacity
{
public:
	CorrelationChangeOpacity(std::shared_ptr<ImageCorrelationSetting>, std::shared_ptr<ICorrelationShowVolumes>,
	                         std::shared_ptr<INavigationViewersNView>);
 
	void ChangeOpacity(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, const misOpacityAndUID& opacityPack, ViewPortType viewPort,
		const misUID& fixedImageUID, const misUID& movingImageUID,
		const misColorStruct& m_FixedColor, const misColorStruct& m_MovingColor) override;
	void SetCalculatedOpacityToImages(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, ViewPortType,
	                                  const misUID& fixedImageUID, const misUID& movingImageUID, const misColorStruct& m_FixedColor, const misColorStruct& m_MovingColor) override;
	void ChangeViewerOpacities(std::shared_ptr<IVolumeSlicer> imageViewer, double fixedImageOpacity,
	                           double movingImageOpacity);
	void CaluateOpacity(const misOpacityAndUID& opacityPack, const misUID& fixedImageUID, const misUID& movingImageUID) override;

private:
	std::shared_ptr<ImageCorrelationSetting> m_ImageCorrelationSetting;
	std::shared_ptr<ICorrelationShowVolumes>  m_CorrelationShowVolumes;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
 


};

