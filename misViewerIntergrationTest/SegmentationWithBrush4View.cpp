 #include "stdafx.h"
#include "SegmentationWithBrush4View.h"

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misGroupViewerSettingFinder.h"
#include "misIntegrationTestTools.h"
#include "misToolShapeBuilder.h"
#include "misTFIAddressMapper.h"
//#include "misSolutionControl.h"
#include "misCoordinateSystemRepository.h"
#include "misDataSetManager.h"
//#include "misTabAndSubTabActicationControl.h"
#include "misGroupViewerFactory.h"
#include "misTabAndSubTabName.h"
#include "misViewerFactory.h" 
#include "IToolRepresentation.h"
#include "misENTBraineNavigationLayoutFactory.h"
#include "BrushImageGeneration.h"
#include "misCursorService.h"
#include "BackToPanMode.h"
#include <vtkPointPicker.h>
#include "misBrushViewerFactory.h"
#include "resource.h"
#include <misMathUtils.h>
#include "misImageToTextureMap.h"

 using namespace std;

SegmentationWithBrush4View::SegmentationWithBrush4View(int &argc, char ** argv)
	:misIntegrationNView(argc, argv)
{
	vtkObject::GlobalWarningDisplayOff();
	
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);

	
	m_SegemntedImage = testTools.LoadImageData(argv[1], seriesNumber);
	m_SegemntedImage->Update();
	auto segementationIMage = m_SegemntedImage->GetRawImageData();
	int* dims = m_Image->GetDimensions();
	misPixelType* pointerImage = (misPixelType*)segementationIMage->GetScalarPointer();
	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
				pointerImage[z*(dims[1] * dims[0]) + y * dims[0] + x] = 0;

	m_Image->SetConfirmedDirection(true);
	m_SegemntedImage->SetConfirmedDirection(true);

	std::shared_ptr<misCoordinateSystemRepository> reposity = make_shared<misCoordinateSystemRepository>();
	misDatasetManager::GetInstance()->SetCSRepository(reposity);
	correlationManager = make_shared<misCoordinateSystemCorrelationTreeManager>();

	misDatasetManager::GetInstance()->AddCoordinateSystem(m_Image);
	misGroupViewerSettingFinder groupViewerSettingFinder;
	auto layout = groupViewerSettingFinder.MakePckageGroupViewer("NavigationTab");
	misGroupViewerFactory groupViewerFactory;
	auto subtabModel = GetSubTabModel();
	subtabModel->SetName(misTabAndSubTabName::GetInstanse()->GetSubTabNameNavigatoinMain(ENT));
	m_GroupViewer = groupViewerFactory.Create(layout, subtabModel, ENT,
		std::make_shared<misBrushViewerFactory>(), correlationManager, 5);

	auto slicers = m_GroupViewer->Get2DViewers();
	brushObserverList.clear();
	for (auto i = 0; i < slicers.size(); i++)
	{
		auto brushobserver = vtkSmartPointer<BrushImageGeneration>::New();
		brushobserver->Create(slicers[i]->Get3DViewer(), slicers[i], slicers[i]->GetCornerProperties(), slicers[i]->GetDummySubject(), slicers[i]->GetCursorService(),
			slicers[i]->GetCameraService());
		brushObserverList.push_back(brushobserver);

		const auto pairEvent3 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::MouseMoveEvent, brushObserverList[i]);
		auto pairEvent4 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::LeftButtonPressEvent, brushObserverList[i]);
		auto pairEvent5 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::LeftButtonReleaseEvent, brushObserverList[i]);
		slicers[i]->AddPointSelectObserver(pairEvent3);
		slicers[i]->AddPointSelectObserver(pairEvent4);
		slicers[i]->AddPointSelectObserver(pairEvent5);
	}
	misIntegrationTestTools::InitializeRendering(m_GroupViewer->GetAllViewers());
	packages = misDatasetManager::GetInstance()->GetPackageDataS();
	InitiVoreenShaders();
	LoadTFIMap();

	auto tansform = vtkTransform::New();
	tansform->Identity();
	auto identityMat = misMathUtils::CreateTransform(tansform->GetMatrix());

	//correlationManager->SetTransform(image->GetUID(), SegemntedImage->GetUID(), identityMat);
	packages[0]->SetImageToRelatedImageDataDependancy(m_SegemntedImage);

	auto volumeSlicers = m_GroupViewer->Get2DViewers();
	auto allSlicer = m_GroupViewer->GetAllViewers();
	std::shared_ptr<I3DViewer> viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	auto interactorStyleImageExtend = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	
	auto measureMent = misMeasurment::New();
	auto imageStyle = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	auto dummy = misVolumeRendererContainer::New();
	auto cursorService = std::make_shared<misCursorService>();
	auto backToPan = std::make_shared<BackToPanMode>(measureMent, imageStyle, viewer, dummy);
	auto pan = std::make_shared<BackToPanMode>(measureMent, interactorStyleImageExtend, viewer, dummy);
	auto corner = std::make_shared<misCornerProperties>(misApplicationSetting::GetInstance()->m_WorkflowButtonSet);
	m_GroupViewer->ShowPackage(packages[0], 0);

	//brushObserver->CreateTExture();
}
void SegmentationWithBrush4View::InitiVoreenShaders()
{
	auto basePath_ = FileSystem::currentDirectory();
	auto shaderPath_ = basePath_ + "/glsl";
	tgt::ShaderManager* shdrmgr = Singleton<tgt::ShaderManager>::GetInstance();
	shdrmgr->addPath(shaderPath_);

	voreen::VoreenApplication* m_Voreen = new voreen::VoreenApplication();
	m_Voreen->init();
	m_Voreen->initGL();
	glewInit();
}

 

void SegmentationWithBrush4View::PulseHandler()
{
	SetMouseCursor();
	auto handleVal = GetReceivedMessage().wParam;
	auto message = GetReceivedMessage();
	if (message.message == WM_KEYDOWN)
	{
		switch (handleVal)
		{
		case  VK_END:

		{
			
			break;
		}

		
		case VK_BACK:
		{

			brushObserverList[0]->Finalize();
			m_GroupViewer->Reset();
			auto package = std::make_shared<misSimpleDataPackage>(misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
			package->SetImageToRelatedImageDataDependancy(m_SegemntedImage);
			package->SetImageToRelatedImageDataDependancy(m_Image);
			m_GroupViewer->ShowPackage(package, false);
			m_GroupViewer->SetColorValueToTexture(FirstImage, misDoubleColorStruct(1,0,0,.9));
		}
		
		case  'a':
		case  'A':

		{
			for (auto observer : brushObserverList)
				observer->Activate();
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->SetInteractionState(InteractionState::WidgetInteractionState);
				viewer->SetInteractionMode(NoState);
 			}
			break;
		}

		case  'd':
		case  'D':

		{
			for (auto observer : brushObserverList)
				observer->DeActive();
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->ResetContrast();
				viewer->SetInteractionState(InteractionState::ContrastState);
				viewer->SetInteractionMode(ContrastEvent);
			}

			break;
		}
		case 'r':
		case 'R':

		{
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->ResetContrast();
 			}
			break;
		}
		}
	}
	m_GroupViewer->Render();


}
void SegmentationWithBrush4View::UpdateTexture()
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(m_Image);
	auto slicers = m_GroupViewer->Get2DViewers();
	for (auto slicer : slicers)
	{
		auto mainRep = slicer->GetImageRprensentaion();
		mainRep->SetImageSource(m_Image, FirstImage, MainImage);
		mainRep->SetTexture(FirstImage, MainImage, imageTexure);

		
		auto imageTexure2 = TextureHandler->LookUpTexture(m_SegemntedImage);
		mainRep->SetImageSource(m_SegemntedImage, SecondImage, MainImage);
		mainRep->SetTexture(SecondImage, MainImage, imageTexure2);

	}
}
void SegmentationWithBrush4View::LoadTFIMap()
{
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	auto addressMapper = std::make_shared<misTFIAddressMapper>();
	std::map<misImageDataModality, std::string> modalityStrings;
	std::map<misVolumeViewingTypes, std::string> viewingTypeStrings;
	modalityStrings[CT] = "CT";
	modalityStrings[MRI] = "MRI";
	modalityStrings[fMRI] = "fMRI";
	modalityStrings[XRay] = "XRay";
	modalityStrings[DXRay] = "DXRay";
	modalityStrings[PET] = "PET";
	modalityStrings[SPECT] = "SPECT";
	modalityStrings[Angio] = "Angio";
	modalityStrings[DAngio] = "DAngio";
	modalityStrings[US] = "US";
	modalityStrings[NM] = "NM";
	modalityStrings[NoData] = "NoData";
	viewingTypeStrings[misVolumeViewingTypes::misSkinFilledViewing] = "SkinFilledViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSkinviewing] = "SkinViewing";
	viewingTypeStrings[misVolumeViewingTypes::misBoneViwing] = "BoneViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSpineViewing] = "SpineViewing";
	viewingTypeStrings[misVolumeViewingTypes::misMetalViewing] = "MetalViewing";
	viewingTypeStrings[misVolumeViewingTypes::misAllViewing] = "AllViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSinusesViewing] = "SinusesViewing";
	viewingTypeStrings[misVolumeViewingTypes::misTeethViewing] = "TeethViewing";
	viewingTypeStrings[misVolumeViewingTypes::UnsetViewingType] = "UnsetViewingType";
	viewingTypeStrings[misVolumeViewingTypes::misAnimalViewing] = "AnimalViewing";
	for (auto modalityItr = modalityStrings.cbegin(); modalityItr != modalityStrings.cend(); ++modalityItr)
	{
		for (auto viewingTypItr = viewingTypeStrings.cbegin(); viewingTypItr != viewingTypeStrings.cend(); ++viewingTypItr)
		{
			std::string node =
				"misVisualizationSetting/TransFunctionsAddresses/" + modalityItr->second + "/" + viewingTypItr->second;
			if (appSettings->IsParamSet(node))
				addressMapper->SetTFIFileName(modalityItr->first, viewingTypItr->first, appSettings->GetString(node));
		}
	}
	misApplicationSetting::GetInstance()->SetTFIAddressMap(addressMapper);
}
void SegmentationWithBrush4View::SetMouseCursor()
{

	HCURSOR hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR2));
	SetCursor(hCursor);

}

//int
//wirtie()
//{
//	// if( argc < 3 )
//	//  {
//	//  std::cerr << "Usage: " << argv[0] <<
//	//    " DicomDirectory  OutputDicomDirectory" << std::endl;
//	//  return EXIT_FAILURE;
//	//  }
//
//	auto directory = R"(F:\Parsiss Data\Prosthesis Container)";
//	using PixelType = signed short;
//	constexpr unsigned int Dimension = 3;
//
//	using ImageType = itk::Image< PixelType, Dimension >;
//	using ReaderType = itk::ImageSeriesReader< ImageType >;
//
//	using ImageIOType = itk::GDCMImageIO;
//	using NamesGeneratorType = itk::GDCMSeriesFileNames;
//
//	ImageIOType::Pointer        gdcmIO = ImageIOType::New();
//	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
//
//	namesGenerator->SetInputDirectory(directory);
//
//	const ReaderType::FileNamesContainer& filenames = namesGenerator->GetInputFileNames();
//	// Software Guide : EndCodeSnippet
//
//	std::size_t numberOfFileNames = filenames.size();
//	std::cout << numberOfFileNames << std::endl;
//	for (unsigned int fni = 0; fni < numberOfFileNames; ++fni)
//	{
//		std::cout << "filename # " << fni << " = ";
//		std::cout << filenames[fni] << std::endl;
//	}
//
//
//	ReaderType::Pointer reader = ReaderType::New();
//
//	reader->SetImageIO(gdcmIO);
//	reader->SetFileNames(filenames);
//	auto image = reader->GetOutput();
//
//	using FilterType = itk::BinaryThresholdImageFilter< ImageType, ImageType >;
//	FilterType::Pointer filter = FilterType::New();
//
//	try
//	{
//		// Software Guide : BeginCodeSnippet
//		// auto image = reader->GetOutput();
//		reader->Update();
//		//typedef ImageType::RegionType RegionType;
//		//RegionType::SizeType          size;
//		//size.Fill( 50 );
//		//RegionType::IndexType index;
//		//index.Fill( 1 );
//		//auto       Olderegion = image->GetBufferedRegion();
//		//RegionType region( index, size );
//		//// image->SetBufferedRegion( region );
//		//// image->FillBuffer( -3000 );
//		//// image->Update();
//		//// image->SetRegions( Olderegion );t
//		auto dimens = image->GetImageDimension();
//		auto allRegion = image->GetLargestPossibleRegion();
//		auto size = allRegion.GetSize();
//		for (unsigned int i = 0; i < size[0]; i++)
//			for (unsigned int j = 0; j < size[1]; j++)
//				for (unsigned int k = 0; k < static_cast<int>(size[2] * 0.9); k++)
//				{
//					ImageType::IndexType pixelIndex;
//					pixelIndex[0] = i;
//					pixelIndex[1] = j;
//					pixelIndex[2] = k;
//
//					image->SetPixel(pixelIndex, 0);
//				}
//		image->Update();
//		// using OutputPixelType = short;
//		  // const OutputPixelType outsideValue = -3000;
//		  // const OutputPixelType insideValue = 1000;
//		  // using InputPixelType = short;
//		  // filter->SetInput( reader->GetOutput() );
//		  // const InputPixelType lowerThreshold =100;
//		  // const InputPixelType upperThreshold = 2000;
//
//		  //// Software Guide : BeginCodeSnippet
//		  // filter->SetLowerThreshold( lowerThreshold );
//		  // filter->SetUpperThreshold( upperThreshold );
//		  //// Software Guide : BeginCodeSnippet
//		  // filter->SetOutsideValue( outsideValue );
//		  // filter->SetInsideValue( insideValue );
//		  // filter->Update();
//	}
//	catch (itk::ExceptionObject & excp)
//	{
//		std::cerr << "Exception thrown while writing the image" << std::endl;
//		std::cerr << excp << std::endl;
//		return EXIT_FAILURE;
//	}
//
//
//	const char* outputDirectory = R"(C:\parsiss\MIS-4.4.1-rc9-1910\outPut9)";
//
//	itksys::SystemTools::MakeDirectory(outputDirectory);
//
//	using OutputPixelType = signed short;
//	constexpr unsigned int OutputDimension = 2;
//
//	using Image2DType = itk::Image< OutputPixelType, OutputDimension >;
//
//	using SeriesWriterType = itk::ImageSeriesWriter< ImageType, Image2DType >;
//
//	SeriesWriterType::Pointer seriesWriter = SeriesWriterType::New();
//
//	seriesWriter->SetInput(image);
//	seriesWriter->SetImageIO(gdcmIO);
//
//	namesGenerator->SetOutputDirectory(outputDirectory);
//
//	seriesWriter->SetFileNames(namesGenerator->GetOutputFileNames());
//
//	seriesWriter->SetMetaDataDictionaryArray(reader->GetMetaDataDictionaryArray());
//
//	try
//	{
//		seriesWriter->Update();
//	}
//	catch (itk::ExceptionObject & excp)
//	{
//		std::cerr << "Exception thrown while writing the series " << std::endl;
//		std::cerr << excp << std::endl;
//		return EXIT_FAILURE;
//	}
//
//
//	return EXIT_SUCCESS;
//}



int Test(int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cerr << "Usage: ImageReadImageSeriesWrite inputFile outputPrefix outputExtension" << std::endl;
		return EXIT_FAILURE;
	}

	//  Software Guide : BeginLatex
	//
	//  The type of the input image is declared here and it is used for declaring
	//  the type of the reader. This will be a conventional 3D image reader.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	using ImageType = itk::Image< unsigned char, 3 >;
	using ReaderType = itk::ImageFileReader< ImageType >;
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The reader object is constructed using the \code{New()} operator and
	//  assigning the result to a \code{SmartPointer}. The filename of the 3D
	//  volume to be read is taken from the command line arguments and passed to
	//  the reader using the \code{SetFileName()} method.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The type of the series writer must be instantiated taking into account that
	//  the input file is a 3D volume and the output files are 2D images.
	//  Additionally, the output of the reader is connected as input to the writer.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	using Image2DType = itk::Image< unsigned char, 2 >;

	using WriterType = itk::ImageSeriesWriter< ImageType, Image2DType >;

	WriterType::Pointer writer = WriterType::New();

	writer->SetInput(reader->GetOutput());
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The writer requires a list of filenames to be generated. This list can be
	//  produced with the help of the \doxygen{NumericSeriesFileNames} class.
	//
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	using NameGeneratorType = itk::NumericSeriesFileNames;

	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The \code{NumericSeriesFileNames} class requires an input string in order
	//  to have a template for generating the filenames of all the output slices.
	//  Here we compose this string using a prefix taken from the command line
	//  arguments and adding the extension for PNG files.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	std::string format = argv[2];
	format += "%03d.";
	format += argv[3];   // filename extension

	nameGenerator->SetSeriesFormat(format.c_str());
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The input string is going to be used for generating filenames by setting
	//  the values of the first and last slice. This can be done by collecting
	//  information from the input image. Note that before attempting to take any
	//  image information from the reader, its execution must be triggered with
	//  the invocation of the \code{Update()} method, and since this invocation
	//  can potentially throw exceptions, it must be put inside a
	//  \code{try/catch} block.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject & excp)
	{
		std::cerr << "Exception thrown while reading the image" << std::endl;
		std::cerr << excp << std::endl;
	}
	// Software Guide : EndCodeSnippet

	// Software Guide : BeginLatex
	//
	// Now that the image has been read we can query its largest possible region
	// and recover information about the number of pixels along every dimension.
	//
	// Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	ImageType::ConstPointer inputImage = reader->GetOutput();
	ImageType::RegionType   region = inputImage->GetLargestPossibleRegion();
	ImageType::IndexType    start = region.GetIndex();
	ImageType::SizeType     size = region.GetSize();
	// Software Guide : EndCodeSnippet

	// Software Guide : BeginLatex
	//
	// With this information we can find the number that will identify the first
	// and last slices of the 3D data set. These numerical values are then passed to
	// the filename generator object that will compose the names of the files
	// where the slices are going to be stored.
	//
	// Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	const unsigned int firstSlice = start[2];
	const unsigned int lastSlice = start[2] + size[2] - 1;

	nameGenerator->SetStartIndex(firstSlice);
	nameGenerator->SetEndIndex(lastSlice);
	nameGenerator->SetIncrementIndex(1);
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  The list of filenames is taken from the names generator and it is passed to
	//  the series writer.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	writer->SetFileNames(nameGenerator->GetFileNames());
	// Software Guide : EndCodeSnippet

	//  Software Guide : BeginLatex
	//
	//  Finally we trigger the execution of the pipeline with the \code{Update()}
	//  method on the writer. At this point the slices of the image will be saved
	//  in individual files containing a single slice per file. The filenames used
	//  for these slices are those produced by the filename generator.
	//
	//  Software Guide : EndLatex

	// Software Guide : BeginCodeSnippet
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & excp)
	{
		std::cerr << "Exception thrown while reading the image" << std::endl;
		std::cerr << excp << std::endl;
	}
	// Software Guide : EndCodeSnippet

	// Software Guide : BeginLatex
	//
	// Note that by saving data into isolated slices we are losing information
	// that may be significant for medical applications, such as the interslice
	// spacing in millimeters.
	//
	// Software Guide : EndLatex

	return EXIT_SUCCESS;
}
