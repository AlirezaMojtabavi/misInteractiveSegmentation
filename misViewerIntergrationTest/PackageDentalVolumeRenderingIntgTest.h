#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misDICOMImageLoader.h"
#include "misCorrectionTransformBox.h"
#include "ITFILoader.h"
#include "misTFIAddressMapper.h"
#include "misPackage3DDataRenderingAdapter.h"


class PackageDentalVolumeRenderingIntgTest : public misIntegrationTestApplication
{
public:
	PackageDentalVolumeRenderingIntgTest(int &argc, char ** argv);
	virtual void PulseHandler();
	void LoadTFIMap();
	std::shared_ptr<ITFILoader> GetTFILoader() const { return m_TFILoader1; }
	void SetTFILoader(std::shared_ptr<ITFILoader> val) { m_TFILoader1 = val; }
	misColorListTypedef GetColorList() const { return m_ColorList1; }
	void SetColorList(misColorListTypedef val) { m_ColorList1 = val; }

private:
 	void InitiVoreenShaders();
	void AddPackage();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misPackage3DDataRenderingAdapter>  m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	voreen::VoreenApplication* voreen;
	vtkSphereSource* m_Sphere;
	std::shared_ptr<ITFILoader> m_TFILoader1;
	misColorListTypedef   m_ColorList1;
 
	vtkRenderer* refernceCheck;
	std::shared_ptr<misTFIAddressMapper> addressMapper;
};



