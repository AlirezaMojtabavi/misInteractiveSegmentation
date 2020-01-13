#pragma once
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkParametricFunctionSource.h>
#include "SampleParametricFunction.h"

class TestVtkVolumeRendering
{
public:


	int Start(int argc, char *argv[])
	{
		// Select one of the following (matching the selection above)
		vtkSmartPointer<SampleParametricFunction> parametricObject = vtkSmartPointer<SampleParametricFunction>::New();


		vtkSmartPointer<vtkParametricFunctionSource> parametricFunctionSource =
			vtkSmartPointer<vtkParametricFunctionSource>::New();
		parametricFunctionSource->SetParametricFunction(parametricObject);
		parametricFunctionSource->SetVResolution(100);
		parametricFunctionSource->SetUResolution(40);

		parametricFunctionSource->Update();

		// Visualize
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(parametricFunctionSource->GetOutputPort());

		// Create an actor for the contours
		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderWindow> renderWindow =
			vtkSmartPointer<vtkRenderWindow>::New();
		renderWindow->AddRenderer(renderer);
		vtkSmartPointer<vtkRenderWindowInteractor> interactor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		interactor->SetRenderWindow(renderWindow);

		renderer->AddActor(actor);
		renderer->SetBackground(1, 1, 1); // Background color white

		renderWindow->Render();
		interactor->Start();

		return EXIT_SUCCESS;
	}
};
