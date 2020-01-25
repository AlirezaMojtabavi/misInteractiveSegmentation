#pragma once
#include <misLandmarkenums.h>
#include "LandmarkDataAndType.h"
#include "ILandmarkPointerRepresentation.h"
#include "IUpdateLandmarkCameraView.h"
#include "misSimplePointType.h"
#include "I3DViewer.h"
#include <ISettingsContainer.h>
#include <Point.h>
#include "LandmarkLablePositionCalculator.h"
#include "TypeDirection.h"
#include "ILandmarkViewer.h"
#include "ILandmarkVisibilty.h"
#include "ICursorService.h"
#include "mis3DVolumeRenderer.h"

struct misLandmarkInfoStruct;

namespace parcast
{
	class LandmarkViewer : public ILandmarkViewer
	{
	public:
		LandmarkViewer(std::shared_ptr<I3DViewer>, std::shared_ptr<LandmarkDataAndType>,
		               std::shared_ptr<ICornerProperties> cornerProperties, std::shared_ptr<ICursorService>,
		               std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
		               double differenceForViewingSeed, misViewerTypeDirection, misVolumeRendererContainer::Pointer);
		virtual bool ProcessRequest(const itk::EventObject* event) final;
		misROI GetSeedBounding(std::shared_ptr<IImage> pImage, int* dimenstion, double* spacing) final;
		void SetCurrentLandmarkType(misLandmarkType val) final;
		void HideLandmarks() final;
		int AddOrSetNextLandmark(const double position[3], misLandmarkType category,
		                         const LANDMARKLABLETYPE lableType) final;
		using ILandmarkViewer::AddOrSetNextLandmark;
		void UpdateLandmarkCameraView(const int index) final;
		misSimplePointListType GetLandmarkList(std::shared_ptr<IImage> pImage, misLandmarkType seedType) final;
		void AddLandmark(int index, const double position[3], misLandmarkType category,
		                 LANDMARKLABLETYPE lableType) final;
		double* GetLandmarkPosition(std::shared_ptr<IImage> pImage,int index, misLandmarkType category) final;
		void InvalidateLandmarks(void) final;
		void RemoveLandmarkRepresentation(int index) final;
		void ResetLandMarks(void);

		void ResetLandMarks(misLandmarkType lndType);

		void InvalidateLandmark(int index);

		void Reset() final;
		void SetCurrentLandmark(misLandmarkType val, int index) final;

		void SetCurrentLandmarkLableType(LANDMARKLABLETYPE val) final;

		virtual bool GetCaptureLandmarkFlag() const final;
		void RemoveLandMarkRepresentations() final;
		void SetCurrentLandmarkIndex(unsigned int val) final;
		void ResetCurrentLandmarkIndex() const final;

		LandmarkListType GetLandmarkList(void);
		double* GetLandmarkPosition(const int index);
		virtual void AddLandamrk(const misLandmarkInfoStruct& landmark) override;
		virtual misLandmarkInfoStruct UpdateCurrentLandmark(double* pos) final;
		virtual void SetCaptureLandmark(bool val);
		void SetUpdateLandmarkFlag(bool val) final;
		misLandmarkInfoStruct PickLandmark(double* position) final;
		void ShowLandmarks();
		misLandmarkInfoStruct UpdateLandmarkByWidget(double* pos) final;

		std::shared_ptr<LandmarkDataAndType> GetLandmarkData() const final;
		bool HasObserver(const itk::EventObject& event) const final;
		unsigned long AddObserver(const itk::EventObject& event, itk::Command* command) final;
		
	protected:

		std::shared_ptr<LandmarkDataAndType> m_LandmarkData;
		LandmarkListType m_landMarkList;
		std::shared_ptr<IUpdateLandmarkCameraView> m_UpdateLandmarkCameraViewer;
		std::shared_ptr<I3DViewer> m_3DViewer;
		std::shared_ptr<ISettingsContainer> m_SettingContainer;
		misViewerTypeDirection m_ViewerTypeDirection;
		bool m_ShowLabels = true;
		const int m_maxLandmarkElementSize = 20;
		std::shared_ptr<ICursorService> m_CursorService;
		std::shared_ptr<ICornerProperties> m_Cornerproperties;
		bool m_UpdateLandmark;
		misVolumeRendererContainer::Pointer m_DummyObject;

		void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent);
		parcast::PointD3 GetLablePosition(const double* position,
		                                  const itk::BoundingBox<double, 3, double>::Pointer
		                                  & boundingBox, const double handleLength,
		                                  const double offsetAngle) const;
		itk::BoundingBox<double, 3, double>::Pointer GetBoundingBox()const;
	public:
		misVolumeRendererContainer::Pointer GetDummySubject() override;
	};
}
