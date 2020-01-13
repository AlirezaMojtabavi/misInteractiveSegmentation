#pragma once
#include <VisualizationGeneralTypes.h>
#include "ISimpleDataPackage.h"
struct misOpacityAndUID;
struct misColorStruct;

namespace parcast
{
class ICorrelationShowImagesAndVolumes
{
public:
	virtual ~ICorrelationShowImagesAndVolumes() = default;
	virtual void SetExternalEventViewer(std::function<void(itk::Object *caller, const itk::EventObject& pEvent)> val) = 0;

	virtual void ShowImagesAndVolumes(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, std::shared_ptr<IImage> m_FixedImage, std::shared_ptr<IImage> m_MovingImage, const misUID& fixedImageUID, const misUID& movingImageUID, const misColorStruct& fixed, const misColorStruct& moving, misOpacityAndUID lastOpacityPack, ViewPortType) = 0;
};	
}
