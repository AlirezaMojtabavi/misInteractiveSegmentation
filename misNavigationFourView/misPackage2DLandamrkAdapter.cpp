#include "stdafx.h"
#include "..\Header\misPackage2DLandamrkAdapter.h"
#include "misInteractorStyleImageExtend.h"


misPackage2DLandmarkAdapter::misPackage2DLandmarkAdapter(std::shared_ptr<parcast::ILandmarkViewer> landmarkViewer)
	:m_LandmarkViewer(landmarkViewer)
{
}

void misPackage2DLandmarkAdapter::ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index,
	LANDMARKLABLETYPE lableType)
{
	m_LandmarkViewer->SetCurrentLandmark(pLandmarkType, index);
	m_LandmarkViewer->SetCurrentLandmarkLableType(lableType);
	m_LandmarkViewer->SetCaptureLandmarkFlag(true);
}

void misPackage2DLandmarkAdapter::ImageLandmarkCaptureDisable()
{
	m_LandmarkViewer->SetCurrentLandmarkType(UnkownLandmarkType);
	m_LandmarkViewer->SetCaptureLandmarkFlag(false);
	m_LandmarkViewer->ResetCurrentLandmarkIndex();
}

void misPackage2DLandmarkAdapter::ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index)
{

	m_LandmarkViewer->SetCurrentLandmark(pLandmarkType, index);
	m_LandmarkViewer->SetUpdateLandmarkFlag(true);

}

void misPackage2DLandmarkAdapter::ImageLandmarkUpdateDisable()
{
	m_LandmarkViewer->SetCurrentLandmarkType(UnkownLandmarkType);
	m_LandmarkViewer->SetUpdateLandmarkFlag(false);
	m_LandmarkViewer->ResetCurrentLandmarkIndex();
}

void misPackage2DLandmarkAdapter::ReleaseImageResources()
{
	m_LandmarkViewer->RemoveLandMarkRepresentations();
}

std::shared_ptr<parcast::ILandmarkViewer> misPackage2DLandmarkAdapter::GetLandmarkViewer()
{
	return  m_LandmarkViewer;
}

void misPackage2DLandmarkAdapter::SetCurrentLandmarkType(misLandmarkType val)
{
	m_LandmarkViewer->SetCurrentLandmarkType(val);
}
