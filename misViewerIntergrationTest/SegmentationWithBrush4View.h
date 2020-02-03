 

#pragma once

#include "misIntegrationNView.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "BrushImageGeneration.h"

//#include "misGUIInteractionDispatchers.h"

//The misGroupViewIntegrationTest class shows an image in 3 axial, coronal, sagittal, and a volume view using misGroupViewer.
class SegmentationWithBrush4View : public misIntegrationNView
{
public:
	SegmentationWithBrush4View(int &argc, char ** argv);
	virtual void PulseHandler();
	void UpdateTexture();

private:
	void LoadTFIMap();
	void SetMouseCursor();
	void InitiVoreenShaders();
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	PackagesListTypedef packages;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager;
	//std::unique_ptr<misGUIInteractionDispatchers> m_EventDispacth;
	std::vector<BrushImageGeneration*> brushObserverList;
	std::shared_ptr<IImage> m_Image;
	std::shared_ptr<IImage> m_SegemntedImage;
};


