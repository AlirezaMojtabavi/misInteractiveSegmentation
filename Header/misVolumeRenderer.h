#pragma once
#include "IVolumeRenderer.h"
#include <ISettingsContainer.h>
#include "misROIWidget.h"

// C.129 iso c++ core guideline
class misVolumeRenderer : public virtual IVolumeRenderer
{
public:
	misVolumeRenderer(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<Iwindows> pWindow, int index);
	~misVolumeRenderer();
	void ResetROI() override;

protected:
	bool m_IsROIActive;
	std::shared_ptr<I3DViewer> m_3DViewer;
	misViewPort m_ViewPort;
	LandmarkListType m_landMarkList;
	const int m_maxLandmarkElementSize = 20;
	vtkSmartPointer<vtkRenderer> m_Renderer;	// The renderer object in charge of rendering the spatial objects, etc.
	int m_IndexInGroup;
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> m_CoordinateRenderers;
	std::shared_ptr<ISettingsContainer> m_SettingContainer;
	vtkSmartPointer<misROIWidget> m_ROIBox;

};

