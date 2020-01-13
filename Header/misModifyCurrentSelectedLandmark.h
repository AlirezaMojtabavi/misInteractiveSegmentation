#pragma once
#include "IModifyCurrentSelectedLandmark.h"
#include "INavigationViewersNView.h"

class misModifyCurrentSelectedLandmark : public IModifyCurrentSelectedLandmark
{
public:
	misModifyCurrentSelectedLandmark(std::shared_ptr<INavigationViewersNView> );
	void Modify(int landmarkIndex, misLandmarkType landmarkType, bool modifiability)  override;
private:
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
};

