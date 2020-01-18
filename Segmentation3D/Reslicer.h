#pragma once


class Reslicer
{
public:
	
	Reslicer(vtkSmartPointer<vtkImageData>  _Dicom) :m_Image(_Dicom) {}
	vtkSmartPointer < vtkDICOMImageReader> PrepareInputImage(vtkSmartPointer < vtkDICOMImageReader> _input);
	vtkSmartPointer< vtkMatrix4x4> GetAxes();
	void Reslicer::SetReslice3D(vtkSmartPointer<vtkImageReslice> _reslicer3d);
	void Reslicer::SetReslice2D(vtkSmartPointer<vtkImageReslice> _reslicer2d);


private:
	int extent[6];
	double spacing[3];
	double origin[3];
	double center[3];
	const double axialElements[16] = {
							1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1 };



	vtkSmartPointer<vtkImageData> m_Image;
	vtkSmartPointer< vtkImageReslice> Reslise3D;
	vtkSmartPointer< vtkImageReslice> Reslise2D;

	VTK_CREATE(vtkMatrix4x4, ResliceAxes);
};
