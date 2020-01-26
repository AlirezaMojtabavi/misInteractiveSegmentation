#pragma once
#include "LandmarkViewer.h"
namespace parcast
{
	class SlicerLandmarkViewer :
		public LandmarkViewer
	{
	public:

		SlicerLandmarkViewer(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<LandmarkDataAndType> landmarkData,
			std::shared_ptr<ICornerProperties> cornerProperties,
			std::shared_ptr<ICursorService> cursorService,
			std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
			double differenceForViewingSeed, misViewerTypeDirection typeDirection , misVolumeRendererContainer::Pointer dummy);
		int AddNextLandmark(const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType) final;
		virtual void AddLandamrk(const misLandmarkInfoStruct& landmark) final;
		void SetCaptureLandmarkFlag(bool val) final;

		~SlicerLandmarkViewer();
	private:
		std::unique_ptr<ILandmarkVisibilty> m_LandmarkVisibilty;
		void CheckVisibility() const ;

	public:
		void Render() override;
		void AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
			LANDMARKLABLETYPE lableType) final;
		void SetLandmarkPosition(int index, const double position[3]) final;

	};
}


