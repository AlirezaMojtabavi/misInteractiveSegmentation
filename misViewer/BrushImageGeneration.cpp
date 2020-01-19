#include "stdafx.h"
#include "BrushImageGeneration.h"
#include "misImageToTextureMap.h"
#include "misTransFunctionBuilder.h"
#include "../Segmentation3D/MyAlgorithm3d.h"


BrushImageGeneration::BrushImageGeneration(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<IVolumeSlicer> Slicer,
                                           std::shared_ptr<ICornerProperties> cornerProperties
                                           , misVolumeRendererContainer::Pointer,
                                           std::shared_ptr<ICursorService> currentService,
                                           std::shared_ptr<misCameraInteraction> cameraInteraction, std::shared_ptr<IImage>  image)
	: m_3DViewer(viewer),
	  m_Slicer(Slicer),
	  m_Cornerproperties(cornerProperties),
	  m_CursorService(currentService),
	  m_CameraService(cameraInteraction),
m_Image(image),
	  m_ConvertMouseXYToWorldCoordinate(
		  std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties, m_CameraService)),
	m_ErasedObjColor(255, 0, 0, 1)
{
	CreateTExture();
}

void BrushImageGeneration::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
	std::cout << eventId << std::endl;
	std::cout << m_ErasingMode << std::endl;

	if (eventId == vtkCommand::LeftButtonPressEvent)
	{
		m_ErasingMode = true;
	}
	else if (eventId == vtkCommand::LeftButtonReleaseEvent)
	{
		m_ErasingMode = false;
	}
	if (!m_ErasingMode)
		return;
	if (!m_Slicer->GetMainRepresentation() || !m_Slicer->GetCameraService()->GetCamera() || !m_Slicer
	                                                                                         ->GetCornerProperties()->
	                                                                                         GetTransform())
		return;


	m_ConvertMouseXYToWorldCoordinate->SetMainRepresentation(m_Slicer->GetMainRepresentation());
	const auto interactor = dynamic_cast<vtkRenderWindowInteractor*>(m_3DViewer
	                                                                 ->GetWindow()->GetInterActor().GetPointer());
	auto position = m_ConvertMouseXYToWorldCoordinate->CalculateNewPosition(interactor);
	auto rawImageData = m_Image->GetRawImageData();
	auto spacing = m_Image->GetSpacing();
	auto extent = m_Image->GetRawImageData()->GetExtent();
	auto ptr = (short*)rawImageData->GetScalarPointer();
	int coordinate[3] = {position[0] / spacing[0], position[1] / spacing[1], position[2] / spacing[2]};
	auto dimension = m_Image->GetDimensions();
	int ImageIndex = (coordinate[0] ) + (coordinate[1]  * dimension[0] )+ coordinate[2] * dimension[1] * dimension[0];

	m_intensity.push_back(ptr[ImageIndex]);
	coordinate3D coord;
	coord._x = coordinate[0];
	coord._y = coordinate[1];
	coord._z = coordinate[2];
	m_Seeds.push_back(coord);
	//for (int x = 0; x < 20; x++)
	//	for (int y = 0; y < 20; y++)
	//		for (int z = 0; z < 20; z++)
	//		{
	//			vtkIdType incs[3];
	//			auto* scalars = rawImageData->GetPointData()->GetScalars();
	//			rawImageData->GetArrayIncrements(scalars, incs);

	//			bool validINdex = true;
	//			for (auto idx = 0; idx < 3; ++idx)
	//			{
	//				if (coordinate[idx] < extent[idx * 2] ||
	//					coordinate[idx] > extent[idx * 2 + 1])
	//				{
	//					validINdex = false;
	//				}
	//			}

	//			const int idx = ((coordinate[0] + x - extent[0]) * incs[0]
	//				+ (coordinate[1] + y - extent[2]) * incs[1]
	//				+ (coordinate[2] + z - extent[4]) * incs[2]);

	//			if (validINdex)
	//				ptr[idx] = -1000;
		//	}
	EraseTexture(parcast::PointD3(position));
}


void BrushImageGeneration::EraseTexture(parcast::PointD3 point)
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* imageTexure = TextureHandler->LookUpTexture(m_Image);
	const auto dataScalars = static_cast<short*>(imageTexure->GetTexturePropertyStrct().Data);
	tgt::ivec3 dim = imageTexure->GetTexturePropertyStrct().GetDimensions();
	tgt::vec3 spacing = imageTexure->GetTexturePropertyStrct().Spacing;
	double* TableRange = imageTexure->GetTableRange();
	int id = imageTexure->getId();
	auto spac  = parcast::PointD3(spacing.elem[0], spacing.elem[1], spacing.elem[2]);
	m_Eraser.SetEraserPosition(point, spac);
	m_Eraser.SetEraserSize(m_EraseSubBoxWidth);
	//m_Eraser.EraseTexture(dataScalars, parcast::Point<int, 3>(dim.elem), TableRange, id);
	m_Eraser.EraseSphereTexture(dataScalars, parcast::Point<int, 3>(dim.elem), TableRange, id);
}

void BrushImageGeneration::CreateTExture( )
{
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(m_Image);
	auto TableRange = imageTexure->GetTableRange();

	misTransFunctionBuilder	trasferfunction;
	misDoubleColorListTypedef opacityColorMappingLst;
	opacityColorMappingLst[TableRange[0]] = misDoubleColorStruct(0, 0, 0, 0);
	opacityColorMappingLst[-800] = misDoubleColorStruct(0, 0, 0, 0);
	//opacityColorMappingLst[-750] = misDoubleColorStruct(0, 0, 1, .5);
	//opacityColorMappingLst[-600] = misDoubleColorStruct(0, 0, 1, 0.5);
	//opacityColorMappingLst[-501] = misDoubleColorStruct(0, 0, 1, 0.5);
	opacityColorMappingLst[-500] = misDoubleColorStruct(1, 0, 0, .2);
	opacityColorMappingLst[-400] = misDoubleColorStruct(1, 0, 0, .2);
	opacityColorMappingLst[-390] = misDoubleColorStruct(1, 0, 0, 0);
	opacityColorMappingLst[TableRange[1]] = misDoubleColorStruct(0, 0, 0, 0);
	
	auto transfunc = trasferfunction.GenerateTransferFunction(opacityColorMappingLst, TableRange);


	transfunc->updateTexture();

	auto imagePlane = m_Slicer->GetImageRprensentaion();
	if (!imagePlane)
		return;
	imagePlane->SetColorMapTransFuncID(SecondImage, transfunc);
	imagePlane->SetVisiblityOfColorMap(SecondImage, true);
	//imagePlane->SetColorMapTransFuncID(FirstImage, transfunc);
	//imagePlane->SetVisiblityOfColorMap(FirstImage, true);
	
  
}

void BrushImageGeneration::Finalize()
{
	auto casting = vtkSmartPointer<vtkImageCast>::New();
	casting->SetInputData(m_Image->GetRawImageData());
	casting->SetOutputScalarTypeToFloat();
	casting->Update();
	auto convertor = VTKImageToImageType::New();
	convertor->SetInput(casting->GetOutput());
	convertor->Update();
	MyAlgorithm3d algoritm(m_intensity, m_Seeds);
	algoritm.SetInternalImage(convertor->GetOutput());
	
}
