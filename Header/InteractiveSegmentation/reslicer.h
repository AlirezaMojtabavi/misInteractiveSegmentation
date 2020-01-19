#pragma once
#include "vtkSmartPointer.h"
#include "vtkDICOMImageReader.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()


class Reslicer
{
public:
	
	Reslicer(vtkSmartPointer<vtkDICOMImageReader> DicomInput) :IS_DicomInput(DicomInput) {}
	vtkSmartPointer< vtkImageReslice> GetResliceDicom(int Dimension);

private:
	vtkSmartPointer<vtkDICOMImageReader> IS_DicomInput;
	vtkSmartPointer<vtkMatrix4x4> GetAxes();

	VTK_CREATE(vtkMatrix4x4, ResliceAxes);
	VTK_CREATE(vtkImageReslice, ResliceDicom);

};

