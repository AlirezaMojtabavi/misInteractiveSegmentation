#pragma once
#include <VisualizationGeneralTypes.h>
#include "../misRegistrationProdecure/mis3DMOdelTypeSelector.h"
#include "ISimpleDataPackage.h"
struct misOpacityAndUID;

class ICorrelationChangeOpacity
{
public:
	virtual ~ICorrelationChangeOpacity() = default;
	virtual void ChangeOpacity(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, const misOpacityAndUID& opacityPack, ViewPortType viewPort,
		const misUID& fixedImageUID, const misUID& movingImageUID,
		const misColorStruct& m_FixedColor, const misColorStruct& m_MovingColor) = 0;
	virtual void SetCalculatedOpacityToImages(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, ViewPortType,
		const misUID& fixedImageUID, const misUID& movingImageUID, const misColorStruct& m_FixedColor, const misColorStruct& m_MovingColor) = 0;
	virtual void CaluateOpacity(const misOpacityAndUID& opacityPack ,  const misUID& fixedImageUID, const misUID& movingImageUID) = 0;
};
