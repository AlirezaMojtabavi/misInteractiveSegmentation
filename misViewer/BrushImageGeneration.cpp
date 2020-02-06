#include "stdafx.h"

#include "BrushImageGeneration.h"
#include "misImageToTextureMap.h"
#include "misTransFunctionBuilder.h"
#include <vtkImageWriter.h>


									

vtkStandardNewMacro(BrushImageGeneration);

void BrushImageGeneration::Create(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<IVolumeSlicer> Slicer,
                                           std::shared_ptr<ICornerProperties> cornerProperties
                                           , misVolumeRendererContainer::Pointer,
                                           std::shared_ptr<ICursorService> currentService,
                                           std::shared_ptr<misCameraInteraction> cameraInteraction)
{
	m_3DViewer = viewer;
	m_Slicer = Slicer;
	m_Cornerproperties = cornerProperties;
	m_CursorService = currentService;
	m_CameraService = cameraInteraction;
	m_ConvertMouseXYToWorldCoordinate = std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties);
	m_ErasedObjColor = { 255, 0, 0, 1 };
	m_SegmentationMode = Brush;
}

void BrushImageGeneration::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
	if (!m_IsActive)
		return;
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
	auto image = m_SegmentationMode == Erase ? FirstImage : SecondImage;
	if (!m_SegmentedImage)
	{
		m_SegmentedImage = m_Slicer->GetImageRprensentaion()->GetImage(SecondImage);
		m_OriginalImage = m_Slicer->GetImageRprensentaion()->GetImage(FirstImage);
		CreateTransferFunction();
	}
	
	m_ConvertMouseXYToWorldCoordinate->SetViewer(m_3DViewer);
	const auto interactor = dynamic_cast<vtkRenderWindowInteractor*>(m_3DViewer
	                                                                 ->GetWindow()->GetInterActor().GetPointer());
	auto position = m_ConvertMouseXYToWorldCoordinate->CalculateNewPosition(interactor);
	
 
	auto rawImageData = m_OriginalImage->GetRawImageData();
	auto spacing = m_OriginalImage->GetSpacing();
	auto extent = m_OriginalImage->GetRawImageData()->GetExtent();
	auto ptr = (misPixelType*)rawImageData->GetScalarPointer();
	int coordinate[3] = {position[0] / spacing[0], position[1] / spacing[1], position[2] / spacing[2]};
	auto dimension = m_OriginalImage->GetDimensions();
	int ImageIndex = (coordinate[0] ) + (coordinate[1]  * dimension[0] )+ coordinate[2] * dimension[1] * dimension[0];

	m_intensity.push_back(ptr[ImageIndex]);
	coordinate3D coord;
	coord._x = coordinate[0];
	coord._y = coordinate[1];
	coord._z = coordinate[2];
	m_Seeds.push_back(coord);

	EraseTexture(parcast::PointD3(position), m_SegmentationMode);
}


void BrushImageGeneration::EraseTexture(parcast::PointD3 point, SegmentMode segmentMode)
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* imageTexure = TextureHandler->LookUpTexture(m_SegmentedImage);
	const auto dataScalars = static_cast<misPixelType*>(imageTexure->GetTexturePropertyStrct().Data);
	tgt::ivec3 dim = imageTexure->GetTexturePropertyStrct().GetDimensions();
	tgt::vec3 spacing = imageTexure->GetTexturePropertyStrct().Spacing;
	double* TableRange = imageTexure->GetTableRange();
	int id = imageTexure->getId();
	auto spac  = parcast::PointD3(spacing.elem[0], spacing.elem[1], spacing.elem[2]);
	m_Eraser.SetEraserPosition(point, spac);
	m_Eraser.SetEraserSize(m_EraseSubBoxWidth);
	
	m_Eraser.EraseSphereTexture(dataScalars, parcast::Point<int, 3>(dim.elem), TableRange, id, segmentMode);
}

void BrushImageGeneration::CreateTransferFunction( )
{
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(m_SegmentedImage);
	auto TableRange = imageTexure->GetTableRange();

	misTransFunctionBuilder	trasferfunction;
	misDoubleColorListTypedef opacityColorMappingLst;
	opacityColorMappingLst[TableRange[0]] = misDoubleColorStruct(0, 0, 0, 0);
	//opacityColorMappingLst[-800] = misDoubleColorStruct(0, 0, 0, 0);
	//opacityColorMappingLst[-500] = misDoubleColorStruct(1, 0, 0, .2);
	//opacityColorMappingLst[-400] = misDoubleColorStruct(1, 0, 0, .2);
	//opacityColorMappingLst[-390] = misDoubleColorStruct(1, 0, 0, 0);

	opacityColorMappingLst[0] = misDoubleColorStruct(0, 0, 0, 0);
	opacityColorMappingLst[100] = misDoubleColorStruct(1, 0, 0, .4);
	opacityColorMappingLst[200] = misDoubleColorStruct(1, 0, 0, .4);
	opacityColorMappingLst[300] = misDoubleColorStruct(1, 0, 0, 0);
	opacityColorMappingLst[TableRange[1]] = misDoubleColorStruct(0, 0, 0, 0);
	auto transfunc = trasferfunction.GenerateTransferFunction(opacityColorMappingLst, TableRange);
	transfunc->updateTexture();
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	if (!imagePlane)
		return;
	imagePlane->SetColorMapTransFuncID(SecondImage, transfunc);
	imagePlane->SetVisiblityOfColorMap(SecondImage, true);
	
}
void BrushImageGeneration::Finalize()
{
	const bool testVisualization =false;
	if (!testVisualization)
	{
			auto vtkInputImage = m_OriginalImage->GetRawImageData(); // <vtkImageData>->Imagetype

			std::string outputFilename1 = "E:\\Interactive_Segmentation\\output3D\\input.vtk";
			vtkSmartPointer<vtkImageWriter> writer1 =
				vtkSmartPointer<vtkImageWriter>::New();

			writer1->SetFileName(outputFilename1.c_str());
			writer1->SetInputData(vtkInputImage);
			writer1->Update();

		typedef itk::VTKImageToImageFilter<ITKImageType> VTKImageToImageType;
		VTKImageToImageType::Pointer vtkImageToITKImage = VTKImageToImageType::New();
		vtkImageToITKImage->SetInput(vtkInputImage);
		vtkImageToITKImage->Update(); // ITKImage -> unsigned short

		ITKImageType_2_InternalType::Pointer internalImage = ITKImageType_2_InternalType::New();
		internalImage->SetInput(vtkImageToITKImage->GetOutput());
		internalImage->Update(); // internal image -> float

		MyAlgorithm3d algoritm(m_intensity, m_Seeds);
		algoritm.SetInternalImage(internalImage->GetOutput());
		algoritm.FastMarching(5);
		algoritm.LevelSet(350, 800, 1, 0.05);
		outputImage = algoritm.GetThresholder();
		outputImage->Update();
		//outputImage->FillBuffer(750);

		auto invertConvertor = itk::ImageToVTKImageFilter<misOutputImageType>::New();
		invertConvertor->SetInput(outputImage);
		invertConvertor->Update();

			std::string outputFilename2 = "E:\\Interactive_Segmentation\\output3D\\final.vtk";
			vtkSmartPointer<vtkImageWriter> writer2 =
				vtkSmartPointer<vtkImageWriter>::New();
				  
			writer2->SetFileName(outputFilename2.c_str());
			writer2->SetInputData(invertConvertor->GetOutput());
			writer2->Update();

		auto image = invertConvertor->GetOutput();
		m_SegmentedImage->GetRawImageData()->DeepCopy(image);
	}

	else
	{
		misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
		misOpenglTexture* imageTexure = TextureHandler->LookUpTexture(m_SegmentedImage);
		const auto dataScalars = static_cast<misPixelType*>(imageTexure->GetTexturePropertyStrct().Data);
		tgt::ivec3 dim = imageTexure->GetTexturePropertyStrct().GetDimensions();
		for (int i = dim[0] / 4; i < dim[0] / 2; i++)
			for (int j = dim[1] / 4; j < dim[1] / 2; j++)
				for (int k = dim[2] / 4; k < dim[2] / 2; k++)
					dataScalars[i + j * dim[0] + k * dim[0] * dim[1]] =750;
	}

	m_SegmentedImage->Modified();

}

void BrushImageGeneration::Activate()
{
	m_IsActive = true;
}

void BrushImageGeneration::DeActive()
{
	m_IsActive = false;
}
