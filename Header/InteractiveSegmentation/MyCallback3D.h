
#pragma once
#include"vtkCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageBlend.h"
#include <vtkImageViewer2.h>
#include "vtkCoordinate.h"
#include "MyAlgorithm3d.h"
#include "MyInteractionStyle3D.h"
#include "MySpeedFunction3D.h"
#include "ImageConverter.h"
#include "SeedList.h"
//#include "ViewerStyle.h"


class MyCallback3D : public vtkCommand
{
public:
	static MyCallback3D *New();
	void SetInternalImage(InternalImageType::Pointer _InternalImage);
	void SetDiagram(vtkSmartPointer<MyCanvas3D>);
	void SetImageReslice(vtkSmartPointer<vtkImageReslice>, vtkSmartPointer<vtkImageReslice>);
	void SetStyle(MyInteractionStyle3D*_style);
	typedef MySpeedFunction3D< InternalImageType, InternalImageType > MySpeedFunction3DType;
	void SetSpeed(MySpeedFunction3DType::Pointer);

	MyAlgorithm3d* GetAlgorithm() { return IS_Algorithm; }

	//void SetRenderer(vtkSmartPointer<vtkRenderer>);
	//void SetWindow(vtkSmartPointer<vtkRenderWindow>);
	void SetInteractor(vtkRenderWindowInteractor* interactor);

	virtual void Execute(vtkObject *, unsigned long event, void *);
	//void Overlay();

private:

	InternalImageType* IS_InternalImage;
	MyAlgorithm3d* IS_Algorithm = new MyAlgorithm3d(IS_InternalImage);
	vtkImageReslice* ImageReslice;
	 
	MySpeedFunction3DType::Pointer My_Function = MySpeedFunction3DType::New();
	SeedList  m_SeedList;
};