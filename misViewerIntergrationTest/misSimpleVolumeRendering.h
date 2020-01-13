#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misDICOMImageLoader.h"
#include "misCorrectionTransformBox.h"
#include "ITFILoader.h"
#include "mis3DVolumeRenderer.h"


class misSimpleVolumeRendering : public misIntegrationTestApplication
{
public:
	misSimpleVolumeRendering(int &argc, char ** argv);
	virtual void PulseHandler();

	void LoadTFIMap();

	std::shared_ptr<ITFILoader> GetTFILoader() const { return m_TFILoader1; }
	void SetTFILoader(std::shared_ptr<ITFILoader> val) { m_TFILoader1 = val; }
	misColorListTypedef GetColorList() const { return m_ColorList1; }
	void SetColorList(misColorListTypedef val) { m_ColorList1 = val; }

private:
	std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(double* TableRange, misImageDataModality modality);
	void InitiVoreenShaders();
	void AddVolume();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;	
	voreen::VoreenApplication* voreen;
	vtkSphereSource* m_Sphere;
	std::shared_ptr<ITFILoader> m_TFILoader1;
	misColorListTypedef   m_ColorList1;
	float ConvertIntensityToKeyValue(const double* TableRange, double val);
	void ReInitialize();
	vtkRenderer* refernceCheck;
};



