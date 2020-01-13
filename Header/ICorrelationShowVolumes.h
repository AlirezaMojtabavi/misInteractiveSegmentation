#pragma once
 #include "ISimpleDataPackage.h"
struct misColorStruct;

class ICorrelationShowVolumes
{
public:
	virtual ~ICorrelationShowVolumes() = default;
	virtual	void ShowVolumes(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, double fixedImageOpacity, double movingImageOpacity, misUID m_FixedImageUID,
		misUID m_MovingImageUID, misColorStruct m_FixedColor, misColorStruct m_MovingColor) 	= 0;

};
