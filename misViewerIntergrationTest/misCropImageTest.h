#pragma once

#include "igstkPulseGenerator.h"
#include "misImage.h"
#include "misNativeWindow.h"
#include "misImageViewer.h"
#include "misWindow.h"
#include "voreenapplication.h"
#include "vtkImageViewer2.h"

class misCropImageTest
{
public:
	~misCropImageTest(void);
	misCropImageTest();

private:
	typedef misCropImageTest Self;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;

	void InitPulseLoop();
	void InitViewer( );
	void InitVTKViewer();
	void AddImage();
	void ReadDicomImage();
	void Render();

	void RenderWithMisRenderingMethoth();

	void RenderVTkiMageviewer();


	misGpuRepresentation::Pointer m_MainRep;
	std::shared_ptr<misImage> m_Image1;
	misROI m_OriginalRoi;
	vtkImageViewer2*  viewerVTK;
	voreen::VoreenApplication* m_VoreenApp;
	igstk::PulseGenerator::Pointer m_PulseGenerator;
	ObserverType::Pointer m_PusleObserver;
	misWindow::Pointer m_wnd;
	misNativeWindow m_MainWindow; 
	misImageViewer::Pointer m_Viewer;
};