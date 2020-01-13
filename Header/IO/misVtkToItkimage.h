#ifndef __misVtkToItkimage_h
#define __misVtkToItkimage_h

class  misVtkToItkimage
{
public:

	//typedef vtkImageData InputImageType;
	typedef itk::Image< float , 3 > OutputImageType;
	OutputImageType::Pointer ConvertfloatToOut(vtkImageData* inputImage);
	OutputImageType::Pointer ConvertshortToOut(vtkImageData* inputImage);

public:
	misVtkToItkimage();
	~misVtkToItkimage();
};

#endif
