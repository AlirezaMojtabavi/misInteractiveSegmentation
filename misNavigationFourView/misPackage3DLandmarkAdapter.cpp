#include "stdafx.h"
#include "misPackage3DLandmarkAdapter.h"

 
misPackage3DLandmarkAdapter::misPackage3DLandmarkAdapter(std::shared_ptr<parcast::ILandmarkViewer> landmarkViewer)
:m_LandmarkViewer(landmarkViewer)
{
}
void misPackage3DLandmarkAdapter::ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index,
	LANDMARKLABLETYPE lableType)
{
	m_LandmarkViewer->SetCurrentLandmark(pLandmarkType, index);
	m_LandmarkViewer->SetCurrentLandmarkLableType(lableType);
	m_LandmarkViewer->SetCaptureLandmarkFlag(true);
}

void misPackage3DLandmarkAdapter::ImageLandmarkCaptureDisable()
{
	m_LandmarkViewer->SetCurrentLandmarkType(UnkownLandmarkType);
	m_LandmarkViewer->SetCaptureLandmarkFlag(false);
	m_LandmarkViewer->ResetCurrentLandmarkIndex();
}

void misPackage3DLandmarkAdapter::ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index)
{

	m_LandmarkViewer->SetCurrentLandmark(pLandmarkType, index);
	m_LandmarkViewer->SetUpdateLandmarkFlag(true);

}

void misPackage3DLandmarkAdapter::ImageLandmarkUpdateDisable()
{
	m_LandmarkViewer->SetCurrentLandmarkType(UnkownLandmarkType);
	m_LandmarkViewer->SetUpdateLandmarkFlag(false);
	m_LandmarkViewer->ResetCurrentLandmarkIndex();
}

void misPackage3DLandmarkAdapter::ReleaseImageResources()
{
	m_LandmarkViewer->RemoveLandMarkRepresentations();
}

std::shared_ptr<parcast::ILandmarkViewer> misPackage3DLandmarkAdapter::GetLandmarkViewer()
{
	return  m_LandmarkViewer;
}

void misPackage3DLandmarkAdapter::SetCurrentLandmarkType(misLandmarkType val)
{
	m_LandmarkViewer->SetCurrentLandmarkType(val);
}
