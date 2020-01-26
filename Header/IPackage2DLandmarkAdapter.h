#pragma once
#include <misLandmarkenums.h>
#include "ILandmarkViewer.h"

class IPackage2DLandmarkAdapter
{
public:
	virtual ~IPackage2DLandmarkAdapter() = default;

	virtual void ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/,
		LANDMARKLABLETYPE lableType) = 0;
	virtual void ImageLandmarkCaptureDisable() = 0;
	virtual void ImageLandmarkUpdateEnable(misLandmarkType, int) = 0;
	virtual void  ImageLandmarkUpdateDisable() = 0;
	virtual void ReleaseImageResources() = 0;
	virtual std::shared_ptr<parcast::ILandmarkViewer> GetLandmarkViewer() = 0;
	virtual void SetCurrentLandmarkType(misLandmarkType val) = 0;

};

