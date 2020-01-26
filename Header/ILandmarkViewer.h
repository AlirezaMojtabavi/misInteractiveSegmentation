#pragma once
#include <misLandmarkenums.h>
#include "misSimplePointType.h"
#include "misROI.h"
#include "ILandmarkPointerRepresentation.h"
#include <IImage.h>
#include <LandmarkDataAndType.h>
#include <misVolumeRendererContainer.h>

struct misLandmarkInfoStruct;
typedef std::vector < std::shared_ptr < ILandmarkPointerRepresentation >> LandmarkListType;

namespace parcast
{

	class ILandmarkViewer
	{
	public:
		virtual ~ILandmarkViewer() = default;
		virtual bool ProcessRequest(const itk::EventObject* event) = 0;

		virtual void SetCurrentLandmarkType(misLandmarkType val) = 0;
		virtual void HideLandmarks() = 0;
		virtual int AddOrSetNextLandmark(const double position[3], misLandmarkType category,
			const LANDMARKLABLETYPE lableType) = 0;
		virtual void UpdateLandmarkCameraView(const int index) = 0;
		virtual misSimplePointListType GetLandmarkList(std::shared_ptr<IImage> pImage, misLandmarkType seedType) = 0;
		virtual void SetLandmarkPosition(int index, const double position[3]) = 0;
		virtual int AddNextLandmark(const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType= NUMERICALLANDMARK) = 0;
		virtual void AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
			LANDMARKLABLETYPE lableType) = 0;
		virtual void AddLandmark(int index, const double position[3], misLandmarkType category,
			LANDMARKLABLETYPE lableType = NUMERICALLANDMARK) = 0;
		virtual double* GetLandmarkPosition(std::shared_ptr<IImage> pImage, int index, misLandmarkType category) = 0;
		virtual void InvalidateLandmarks(void) = 0;
		virtual void RemoveLandmarkRepresentation(int index) = 0;
		virtual void AddLandamrk(const misLandmarkInfoStruct& landmark) = 0;
		virtual misLandmarkInfoStruct UpdateCurrentLandmark(double* pos) = 0;
		virtual void SetCaptureLandmark(bool val)= 0;
		virtual misLandmarkInfoStruct UpdateLandmarkByWidget(double* pos) = 0;
		virtual bool GetCaptureLandmarkFlag() const = 0 ;
		virtual  misLandmarkInfoStruct PickLandmark(double* position) = 0;
		virtual void ResetLandMarks() = 0;
		virtual void SetCaptureLandmarkFlag(bool val) = 0;
		virtual void ResetCurrentLandmarkIndex() const = 0;
		virtual void SetUpdateLandmarkFlag(bool val) = 0;
		virtual void SetCurrentLandmarkIndex(unsigned int val) = 0;
		virtual void SetCurrentLandmark(misLandmarkType val, int index) = 0;
		virtual void SetCurrentLandmarkLableType(LANDMARKLABLETYPE val) = 0;
		virtual void ResetLandMarks(misLandmarkType lndType) = 0;
		virtual void InvalidateLandmark(int index) = 0;
		virtual void RemoveLandMarkRepresentations() = 0;
		virtual void ShowLandmarks() = 0;
		virtual misROI GetSeedBounding(std::shared_ptr<IImage> pImage, int* dimenstion, double* spacing) = 0;
		virtual LandmarkListType GetLandmarkList(void) = 0;
		virtual void Reset() = 0;
		virtual double* GetLandmarkPosition(int index) = 0;
		virtual std::shared_ptr<LandmarkDataAndType> GetLandmarkData() const= 0;
		virtual bool HasObserver(const itk::EventObject & event) const = 0;
		virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
		virtual void Render() = 0;
		virtual misVolumeRendererContainer::Pointer GetDummySubject() = 0;
	};
}