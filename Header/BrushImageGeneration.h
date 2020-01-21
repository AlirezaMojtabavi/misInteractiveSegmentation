#pragma once
#include "I3DViewer.h"
#include "../misViewer/ConvertMousexyToWorldCoordinate.h"
#include "IVolumeSlicer.h"
#include "misVolumeRendererContainer.h"
#include "IBackToPanMode.h"
#include <IImage.h>
#include "misTextureEraser.h"
#include "../Segmentation3D/MyAlgorithm3d.h"


class BrushImageGeneration : public vtkCommand
{
public:
	BrushImageGeneration(std::shared_ptr<I3DViewer>, std::shared_ptr<IVolumeSlicer> Slicer,
	                     std::shared_ptr<ICornerProperties>,
	                     misVolumeRendererContainer::Pointer, std::shared_ptr<ICursorService>,
	                     std::shared_ptr<misCameraInteraction>, std::shared_ptr<IImage>  image, std::shared_ptr<IImage> origin);
	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;
	void CreateTExture();
	void Finalize();
private:
	void EraseTexture(parcast::PointD3 point);
	void Colortexture(parcast::PointD3 point);
	std::shared_ptr<I3DViewer> m_3DViewer;
	std::shared_ptr<IVolumeSlicer> m_Slicer;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	std::shared_ptr<misCameraInteraction> m_CameraService;
	std::shared_ptr<ICursorService> m_CursorService;
	std::unique_ptr<ConvertMousexyToWorldCoordinate> m_ConvertMouseXYToWorldCoordinate;
	std::shared_ptr<IImage>  m_Image;
	std::shared_ptr<IImage>  m_OriginImage;
	bool m_ErasingMode = false;
	int	m_EraseSubBoxWidth = 14;
	misColorStruct m_ErasedObjColor;
	misTextureEraser m_Eraser;
	
	std::vector<short> m_intensity;
	std::vector<coordinate3D> m_Seeds;
	misSpeedFunction3DType::Pointer SegmentationSpeedFunction = misSpeedFunction3DType::New();
};
