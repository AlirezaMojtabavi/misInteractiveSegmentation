

#include "pch.h"
#include "MyCallback3D.h"
#include "MyCanvas3D.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
//#include "StatusMessage.h"

MyCallback3D * MyCallback3D::New()
{
	return new MyCallback3D;
}

void MyCallback3D::SetInternalImage(InternalImageType::Pointer _InternalImage)
{
	IS_InternalImage = _InternalImage;
}

/*void MyCallback3D::SetImageReslice(vtkSmartPointer<vtkImageReslice> reslice,
	vtkSmartPointer<vtkImageReslice> _viewer_reslice)
{
	ImageReslice = reslice;
	viewer_reslice = _viewer_reslice;
}*/

void MyCallback3D::SetStyle(MyInteractionStyle3D*_style)
{
	style = _style;
	IS_Algorithm->SetStyle(style);
}

void MyCallback3D::SetDiagram(vtkSmartPointer<MyCanvas3D> _canvas)
{
	IS_MyCanvas3D = _canvas;
}

void MyCallback3D::SetSpeed(MySpeedFunction3DType::Pointer _Function)
{
	My_Function = _Function;
}

/*void MyCallback3D::SetRenderer(vtkSmartPointer<vtkRenderer> _renderer)
{
	renderer = _renderer;
}

void MyCallback3D::SetWindow(vtkSmartPointer<vtkRenderWindow> _window)
{
	window = _window;
}*/

void MyCallback3D::SetInteractor(vtkRenderWindowInteractor * interactor)
{
	this->Interactor = interactor;
}

inline void MyCallback3D::Execute(vtkObject *caller, unsigned long event, void *)
{
	//std::string outputFilename1 = "C:\\Users\\a.mojtabavi\\Desktop\\final_write\\seri"; // level set output
	//const char * outputDirectory2 = "C:\\Users\\a.mojtabavi\\Desktop\\final_write\\seri2\\";
	const char * outputDirectory1 = "E:\\Interactive_Segmentation\\output3D";

	if (style->GetFlag() > 0)
	{
		auto interctor = (vtkRenderWindowInteractor*)(caller);
		double x = interctor->GetEventPosition()[0];
		double y = interctor->GetEventPosition()[1];
		int z = IS_MyCanvas3D->GetCurrentSlice();

		Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->SetDisplayPoint(interctor->GetEventPosition()[0], interctor->GetEventPosition()[1], 0);
		Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->DisplayToWorld();
		double* position = Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetWorldPoint();

		IS_MyCanvas3D->SetLastposition(position[0], position[1], z);

		//cout << "X: " << position[0] << "\t\tY: " << position[1] << "\t\tZ: " << z << "\n\n\n";
		Interactor->Render();

		if (style->GetFlag() == 4 || style->GetFlag() == 1 || style->GetFlag() == 5)
		{
			MyAlgorithm3d* IS_Algorithm = new MyAlgorithm3d(IS_InternalImage);
			IS_Algorithm->Set_Function(My_Function);
			IS_Algorithm->set_Canvas(IS_MyCanvas3D);
			IS_Algorithm->FastMarching(5);
			IS_Algorithm->Level_Set(191, 450, 0, 0.05);

			if (style->GetFlag() == 4 || style->GetFlag() == 5)
			{
				cout << "\t\t\tPlease Wait ..." << "\n\n\n";

				//MySeg->Level_Set(1, 0.05);
				IS_Algorithm->Get_thresholder()->Update();
				
				//this->Overlay();
			}
		}
	}
}

/*void MyCallback3D::Overlay()
{

	typedef itk::RescaleIntensityImageFilter< ImageType, ImageType > RescaleFilterType;
	RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
	rescaleFilter->SetInput(MyImage->GetItkImage()->GetOutput());
	rescaleFilter->SetOutputMinimum(0);
	rescaleFilter->SetOutputMaximum(255);

	typedef itk::ImageToVTKImageFilter<ImageType>   ConnectorType;
	ConnectorType::Pointer mrconnector = ConnectorType::New();
	mrconnector->SetInput(rescaleFilter->GetOutput());
	mrconnector->Update();

	//-----------------------------------------------------

	typedef itk::CastImageFilter<OutputImageType, ImageType> OutputImageType_2_ImageType;
	OutputImageType_2_ImageType::Pointer thcaster = OutputImageType_2_ImageType::New();
	thcaster->SetInput(IS_Algorithm->Get_thresholder());
	thcaster->Update();

	ConnectorType::Pointer thconnector = ConnectorType::New();
	thconnector->SetInput(thcaster->GetOutput());
	thconnector->Update();
	//----------------------------viewer-----------------------

	VTK_CREATE(vtkImageBlend, blend);
	blend->AddInputData(thconnector->GetOutput());
	blend->AddInputData(mrconnector->GetOutput());
	blend->SetOpacity(0.5, 0.5);
	blend->SetOpacity(1, .5);
	blend->Update();

	viewer_reslice->SetInputConnection(blend->GetOutputPort());

	VTK_CREATE(vtkImageActor, DataActor);
	DataActor->GetMapper()->SetInputConnection(viewer_reslice->GetOutputPort());
	renderer->AddActor(DataActor);
	window->AddRenderer(renderer);
	window->Render();
}*/