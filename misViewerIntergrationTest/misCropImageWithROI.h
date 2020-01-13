#pragma once
#include "igstkPulseGenerator.h"
#include "misImage.h"
#include "misNativeWindow.h"
#include "misVolumeSlicer.h"
#include "misWindow.h"
#include "voreenapplication.h"
#include "vtkImageViewer2.h"

//The class provided roi widget interaction obsever for croping image
class misCropImageWithROI
{
public:
	~misCropImageWithROI(void);
	misCropImageWithROI();

private:
	typedef misCropImageWithROI Self;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;

	void InitPulseLoop();
	void InitViewer( );
	void InitVTKViewer();
	void AddImage();
	void ReadDicomImage();
	void Render();

	void RenderWithMisRenderingMethoth();

	void RenderVTkiMageviewer();
	// Roi interaction calll back
	virtual void UpdateRoi(itk::Object *caller,const itk::EventObject& pEvent );
	void UpdateRoiInVolume( const double * bnd );
	misPlanarRepresentation::Pointer m_MainRep;
	std::shared_ptr<misImage> m_Image1;
	misROI m_OriginalRoi;
	vtkImageViewer2*  viewerVTK;
	voreen::VoreenApplication* m_VoreenApp;
	igstk::PulseGenerator::Pointer m_PulseGenerator;
	ObserverType::Pointer m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow m_MainWindow; 
	std::shared_ptr<misVolumeSlicer> m_Viewer;
};