#pragma once
#include "LandmarkViewer.h"
namespace  parcast
{
class Volume3DLandmarkViewer :
	public LandmarkViewer
{
public:

	Volume3DLandmarkViewer(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<LandmarkDataAndType> landmarkData,
		std::shared_ptr<ICornerProperties> cornerProperties,
		std::shared_ptr<ICursorService> cursorService,
		std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
		double differenceForViewingSeed, misVolumeRendererContainer::Pointer dummy);
		int AddNextLandmark(const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType) final;
		virtual void AddLandamrk(const misLandmarkInfoStruct& landmark) final;
		void SetCaptureLandmarkFlag(bool val) final;

~Volume3DLandmarkViewer();
void AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType) final;
void SetLandmarkPosition(int index, const double position[3]) final;
	void SetViewCentrePosition(const double position[3]);
	void Render() override;
};

	
}
