#pragma once

#include "mis3dTexture.h"
#include "misDICOMImageLoader.h"
#include "misDIRReader.h"
#include "misPlanarRepresentation.h"
#include "misImageCallback.h"
#include "misImageGeoProperties.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misVolumeSlicer.h"
#include "misInteractorSTyleImageExtend.h"
#include "misMacros.h"
#include "misNativeWindow.h"
#include "misObjectPropertiesStruct.h"
#include "misStrctColorData.h"
#include "misTransFunctionBuilder.h"
#include "misVisualizationUtils.h"
#include "misWindow.h"

class misImageViewerWidgetIntgTest
{
private:
	typedef misImageViewerWidgetIntgTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   
	misPlanarRepresentation::Pointer  MultiPlane;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;
	int * m_Size;
	void LoadGui();

	void InitViewer( );
	void AddImage();
	vtkSmartPointer<vtkImageData> m_pImage1;
	void ReadDicomImage();
	void Render();


public:
	~misImageViewerWidgetIntgTest(void);
	misImageViewerWidgetIntgTest();
};

