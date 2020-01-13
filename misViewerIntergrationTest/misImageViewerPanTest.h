#pragma once

#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"

#include "vtkNIFTIReader.h"

#include "vtkImageMapToWindowLevelColors.h"
#include "vtkPNGReader.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTexturedActor2D.h"
#include "vtkProperty2D.h"
#include "vtkLight.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "mis3dTexture.h"
#include "misDIRReader.h"
#include "misImageGeoProperties.h"
#include "vtkImageReader.h"
#include "vtkimageCast.h"
#include "vtkTimerLog.h"
#include "misMacros.h"
#include "init.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misStrctColorData.h"
#include "misObjectPropertiesStruct.h"
#include "misPlanarRepresentation.h"
#include "misDICOMImageLoader.h"
#include "vtkImageShiftScale.h"
#include "misTransFunctionBuilder.h"

class misImageViewerPanTest
{
private:
	typedef misImageViewerPanTest Self;
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
	~misImageViewerPanTest(void);
	misImageViewerPanTest();
};

