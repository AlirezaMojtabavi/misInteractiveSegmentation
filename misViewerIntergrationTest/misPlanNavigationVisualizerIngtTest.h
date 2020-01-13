#pragma once
#include "misIntegrationTestApplication.h"
#include "misPlannedNavigationStage.h"
#include "mis3DVolumeRenderer.h"
#include "misDICOMImageLoader.h"
#include "ITFILoader.h"
#include "misWindow.h"
#include "misPlanNavigationVisualizer.h"
#include "CustomizeArcTan.h"
#include "AdaptiveZoomCalculator.h"
#include "PositionInPlanCoordinateSystemCalculator.h"


class misPlanNavigationVisualizerIngtTest : public misIntegrationTestApplication
{
public:
	misPlanNavigationVisualizerIngtTest(int &argc, char ** argv);
	void PulseHandler();
private:
	
	const parcast::CustomizeArcTan ExpFunction = parcast::CustomizeArcTan(0.1951, 0.19, 37.7, 0.7278);
	std::shared_ptr<parcast::PositionInPlanCoordinateSystemCalculator> m_PositionInPlanCoordinateSystemCalculator;;
	std::shared_ptr<parcast::AdaptiveZoomCalculator> m_AdaptiveZoomCalculator;
	std::shared_ptr<parcast::misPlanNavigationVisualizer> m_PlanNavigationVisulizer;

	misUID planCoordinate;
	misUID tipCoordinate;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CsManager;
	vtkSmartPointer<vtkTransform> m_Transform = vtkSmartPointer<vtkTransform>::New();

	std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(double* TableRange, misImageDataModality modality);
	void InitiVoreenShaders();
	void AddVolume();
	void LoadTFIMap();
	std::shared_ptr<ITFILoader> GetTFILoader() const { return m_TFILoader1; }
	void SetTFILoader(std::shared_ptr<ITFILoader> val) { m_TFILoader1 = val; }
	misColorListTypedef GetColorList() const { return m_ColorList1; }
	void SetColorList(misColorListTypedef val) { m_ColorList1 = val; }
	float ConvertIntensityToKeyValue(const double* TableRange, double val);
	void ReInitialize();
	void CreatePlanANdvolume(char ** argv);

	std::shared_ptr<Iwindows> m_wnd = std::make_shared<misWindow>();
	std::shared_ptr<mis3DVolumeRenderer>  m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	voreen::VoreenApplication* voreen;
	vtkSphereSource* m_Sphere;
	std::shared_ptr<ITFILoader> m_TFILoader1;
	misColorListTypedef   m_ColorList1;
	vtkRenderer* refernceCheck;
};

