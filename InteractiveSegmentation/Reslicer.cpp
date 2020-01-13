#include "pch.h"
#include "Reslicer.h"

vtkSmartPointer<vtkImageReslice> Reslicer::GetResliceDicom(int Dimension)
{
	ResliceDicom->SetInputConnection(IS_DicomInput->GetOutputPort());
	ResliceDicom->SetOutputDimensionality(Dimension);
	ResliceDicom->SetResliceAxes(this->GetAxes());
	ResliceDicom->SetInterpolationModeToLinear();
	ResliceDicom->Update();

	return ResliceDicom;
}

vtkSmartPointer<vtkMatrix4x4> Reslicer::GetAxes()
{
	int extent[6];
	double spacing[3];
	double origin[3];
	double center[3];

	IS_DicomInput->GetOutput()->GetExtent(extent);
	IS_DicomInput->GetOutput()->GetSpacing(spacing);
	IS_DicomInput->GetOutput()->GetOrigin(origin);
	IS_DicomInput->GetDataExtent();

	center[0] = origin[0];// +spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1];// +spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2];// +spacing[2] * 0.5 * (extent[4] + extent[5]);

						  // Matrices for axial
	static double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	ResliceAxes->DeepCopy(axialElements);
	ResliceAxes->SetElement(0, 3, center[0]);
	ResliceAxes->SetElement(1, 3, center[1]);
	ResliceAxes->SetElement(2, 3, center[2]);

	return ResliceAxes;
}
