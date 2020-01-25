#pragma once
#include <misLandmarkenums.h>
#include "IPackage2DLandmarkAdapter.h"

struct misLandmarkInfoStruct;

class  ILandmarkViewerCollection
{
public:
	enum TypeOfViewer { D2VIEWER, D3VIEWER, ALLVIEWERS };

	virtual ~ILandmarkViewerCollection() = default;

	virtual void VolumeLandmarkCaptureDisable() = 0;
	virtual void ImageLandmarkCaptureEnable(
		misLandmarkType pLandmarkType, int index = -1, LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) = 0;
	virtual void ImageLandmarkCaptureDisable() = 0;
	virtual void Render() = 0;
	virtual void ResetLandMarks(misLandmarkType lndType) = 0;
	virtual void ResetAllLandMarks() = 0;
	virtual void ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index) = 0;
	virtual void ImageLandmarkUpdateDisable() = 0;
	virtual void AddLandmark(unsigned int landmarkIndex, itk::Point<double, 3> landmark, misLandmarkType landmarkType,
		LANDMARKLABLETYPE lableType) = 0;
	virtual	void VolumeLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index = -1, LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) = 0;
	virtual void ShowLandmarks() = 0;
	virtual void HideLandmarks(TypeOfViewer typeOfViewer) = 0;
	virtual void InvalidateLandmark(int index) = 0;
	virtual void UpdateLandmarks(misLandmarkInfoStruct &lndStr) = 0;
	virtual std::vector<std::shared_ptr<IPackage2DLandmarkAdapter>>  GetLandmarkViewers() = 0;
	virtual std::shared_ptr<IPackage2DLandmarkAdapter>  GetLandmark3DViewer() = 0;
	virtual void AddAdapter(std::shared_ptr<IPackage2DLandmarkAdapter>) = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual void SetExternalEventViewer(std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> val) = 0;

};
