#include "StdAfx.h"
#include "misSimpleImageContourViewer.h"
#include "misImage.h"
#include "misIntegrationTestTools.h"


misSimpleImageContourViewer::misSimpleImageContourViewer(int argc, char* argv[])
{

	//std::shared_ptr<misImage> image = misIntegrationTestTools::LoadImageData("C:/Users/EM/Documents/MATLAB", 0);//fails ct params
	//std::shared_ptr<misImage> image = misIntegrationTestTools::LoadImageData("Correlation Test/ct", 0);
	//m_Image = misIntegrationTestTools::LoadImageData("Correlation Test/loqman", 1);
	//m_Image = misIntegrationTestTools::LoadImageData("Correlation Test/new_test", 2);
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	std::shared_ptr<misImage> image = testTools.LoadImageData(argv[1], seriesNumber);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Boostani Alireza\\MRI", 3);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Zabeti Hossein\\Mr", 4);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Yasini Mehdi\\MRI",3);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Vashmeh Neda (Erfan)\\Mr", 2);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Soleymanzadeh-Changiz\\Mr", 4);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Zare zadeh-Mohamad\\Mr", 2);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Maroufi-GH.Reze-MRI", 4);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Dicom Data\\Qolipour-Fatemeh\\MRI", 3);
	//m_Image = misIntegrationTestTools::LoadImageData("\\\\parsiss-server\\Team Folders\\E.Mosaddegh\\MR\\Alirast Shahla", 3);
	image->Update();
	double range[2];
	image->GetRawImageData()->GetScalarRange(range);

	auto segmentedSurface = vtkSmartPointer<vtkContourFilter>::New();
	segmentedSurface->ComputeGradientsOff();
	segmentedSurface->ComputeNormalsOff();
	segmentedSurface->SetInputData(image->GetRawImageData());
	segmentedSurface->SetNumberOfContours(1);
	segmentedSurface->SetValue(-10, 0);
	segmentedSurface->Update();



	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(segmentedSurface->GetOutput());

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetPointSize(1);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);

	renderWindow->Render();
	renderWindowInteractor->Start();

}


misSimpleImageContourViewer::~misSimpleImageContourViewer(void)
{
}
