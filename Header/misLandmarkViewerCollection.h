#pragma once
#include <misLandmarkenums.h>
#include "IGroupViewerSetting.h"
#include "ILandmarkViewerCollection.h"
#include "ILandmarkViewer.h"
#include "IPackage2DLandmarkAdapter.h"
#include "IVolumeRenderer.h"

class misUpdatePositionEvent;

class misLandmarkViewerCollection : public ILandmarkViewerCollection
{
public:
	misLandmarkViewerCollection(std::shared_ptr<IGroupViewerSetting> groupViewerSetting);
	void ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index = -1,
		LANDMARKLABLETYPE lableType = NUMERICALLANDMARK);
	virtual void ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index) override;
	void ImageLandmarkCaptureDisable();
	virtual void ImageLandmarkUpdateDisable();
	virtual void VolumeLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index = -1,
		LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) override;
	void VolumeLandmarkCaptureDisable();
	void Render() override;
	void ResetAllLandMarks();
	void ResetLandMarks(misLandmarkType lndType) override;
	virtual void ShowLandmarks() override;
	void HideLandmarks(TypeOfViewer typeOfviewer) override;
	void InvalidateLandmark(int index) override;
	virtual void UpdateLandmarks(misLandmarkInfoStruct& lndStr) override;
	void ReleaseResource();
	virtual void AddLandmark(unsigned int landmarkIndex, itk::Point<double, 3> landmark, misLandmarkType landmarkType,
		LANDMARKLABLETYPE lableType);
	std::vector<std::shared_ptr<IPackage2DLandmarkAdapter>> GetLandmarkViewers() override;
	void AddAdapter(std::shared_ptr<IPackage2DLandmarkAdapter>) override;
	std::shared_ptr<IPackage2DLandmarkAdapter> GetLandmark3DViewer() override;
private:

	void HandleUpdatePositionEvent(const misUpdatePositionEvent* pEvent);
	void AddObservers(std::shared_ptr<parcast::ILandmarkViewer> viewer);
	
	void DistributeEvent(itk::Object* caller, const itk::EventObject& pEvent);

public:
	bool HasObserver(const itk::EventObject& event) const override;
	unsigned long AddObserver(const itk::EventObject& event, itk::Command* command) override;
	void InvokeEvent(const itk::EventObject& event) override;
	void SetExternalEventViewer(std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> val) override;
	bool FindDistributerViewer(itk::Object* caller, size_t& viewerIndex);
private:
	std::vector<std::shared_ptr<IPackage2DLandmarkAdapter>> m_LandmarkViewerAdapters;
	std::shared_ptr<IGroupViewerSetting> m_GroupViewSetting;
itk::Object::Pointer m_DummyObject = itk::Object::New();
std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> m_ExternalEventViewer;
};






