#pragma once
#include "ICorrelationShowVolumes.h"
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"

class CorrelationShowVolumes :
	public ICorrelationShowVolumes
{
public:
	CorrelationShowVolumes(std::shared_ptr<INavigationViewersNView> );
 	void ShowVolumes(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, double fixedImageOpacity, double movingImageOpacity, misUID m_FixedImageUID,
                     misUID m_MovingImageUID, misColorStruct m_FixedColor, misColorStruct m_MovingColor	) 	override;
private:
 
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;

};

