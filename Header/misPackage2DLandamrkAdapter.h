#pragma once
#include <misLandmarkenums.h>
#include "IPackage2DLandmarkAdapter.h"
#include "ILandmarkViewer.h"

class misPackage2DLandmarkAdapter : public IPackage2DLandmarkAdapter
{
public:
	explicit misPackage2DLandmarkAdapter(std::shared_ptr<parcast::ILandmarkViewer>);
	void ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/,
		LANDMARKLABLETYPE lableType) override;
	void ImageLandmarkCaptureDisable() override;
	void ImageLandmarkUpdateEnable(misLandmarkType, int) override;
	void ImageLandmarkUpdateDisable() override;
	void ReleaseImageResources() override;
	std::shared_ptr<parcast::ILandmarkViewer> GetLandmarkViewer() override;
	void SetCurrentLandmarkType(misLandmarkType val) override;
private:
	std::shared_ptr<parcast::ILandmarkViewer> m_LandmarkViewer;


};

