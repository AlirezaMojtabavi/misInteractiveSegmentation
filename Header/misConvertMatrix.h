#pragma once

#include "misMultiResCorrelation.h"
#include "misitkTypdef.h"

class  misConvertMatrix
{
public:
	typedef itk::Rigid3DTransform<double> Rigid3DTransformType;
	typedef itk::Matrix <double,4,4> InitialMatrixType;

	static itk::Rigid3DTransform<double>::Pointer  ConvertVTKMatrix2ITKMatrix( vtkMatrix4x4 *pVTKMatrix );
	static vtkMatrix4x4* ConvertITKMatrix2VTKMatrix(misItkMatrix4X4 pITKMatrix ,  misItkVectorType offSet );
	static InitialMatrixType CovertITKTransform2ITKMatrix(itk::Rigid3DTransform<double>::Pointer pITKTransform);
};
