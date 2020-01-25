#pragma once
#include "IPackage2DLandmarkAdapter.h"
class misPackage3DLandmarkAdapter : public IPackage2DLandmarkAdapter
{
public:
	misPackage3DLandmarkAdapter(std::shared_ptr<parcast::ILandmarkViewer>);
 	void ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index, LANDMARKLABLETYPE lableType) override;
	void ImageLandmarkCaptureDisable() override;
	void ImageLandmarkUpdateEnable(misLandmarkType, int) override;
	void ImageLandmarkUpdateDisable() override;
	void ReleaseImageResources() override;
	std::shared_ptr<parcast::ILandmarkViewer> GetLandmarkViewer() override;
	void SetCurrentLandmarkType(misLandmarkType val) override;
private:
private:
	std::shared_ptr<parcast::ILandmarkViewer> m_LandmarkViewer;

};

