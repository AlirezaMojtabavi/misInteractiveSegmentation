#pragma once
#include "I3DViewer.h"
#include "../misViewer/ConvertMousexyToWorldCoordinate.h"
#include "IVolumeSlicer.h"
#include "misVolumeRendererContainer.h"
#include "IBackToPanMode.h"
#include <IImage.h>
#include "misTextureEraser.h"
 #include "ImageType.h"
#include "../Segmentation3D/MySpeedFunction3D.h"
#include "../Segmentation3D/MyAlgorithm3d.h"

class BrushImageGeneration : public vtkCommand
{
public:
	static BrushImageGeneration* New();
	vtkBaseTypeMacro(BrushImageGeneration, vtkCommand);
	void Create(std::shared_ptr<I3DViewer>, std::shared_ptr<IVolumeSlicer> Slicer,
	                     std::shared_ptr<ICornerProperties>,
	                     misVolumeRendererContainer::Pointer, std::shared_ptr<ICursorService>,
	                     std::shared_ptr<misCameraInteraction>);
	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;
	void Finalize();
	void Activate();
	void DeActive();
private:
	void EraseTexture(parcast::PointD3 point, SegmentMode);
	void Colortexture(parcast::PointD3 point);
	void CreateTransferFunction();
	std::shared_ptr<I3DViewer> m_3DViewer;
	std::shared_ptr<IVolumeSlicer> m_Slicer;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	std::shared_ptr<misCameraInteraction> m_CameraService;
	std::shared_ptr<ICursorService> m_CursorService;
	std::unique_ptr<ConvertMousexyToWorldCoordinate> m_ConvertMouseXYToWorldCoordinate;
	std::shared_ptr<IImage>  m_SegmentedImage;
	std::shared_ptr<IImage>  m_OriginalImage;
	bool m_ErasingMode = false;
	int	m_EraseSubBoxWidth = 20;
	misColorStruct m_ErasedObjColor;
	misTextureEraser m_Eraser;
	SegmentMode m_SegmentationMode;
	bool m_IsActive = false;
	std::vector<misPixelType> m_intensity;
	std::vector<coordinate3D> m_Seeds;
	misSpeedFunction3DType::Pointer SegmentationSpeedFunction = misSpeedFunction3DType::New();									 																		   
};
