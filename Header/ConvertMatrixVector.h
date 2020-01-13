#pragma once

#include "misLibraryMacroes.h"

class MISLIBRARYEXPORT  MatrixConversion
{
public:
	MatrixConversion(void);
	~MatrixConversion(void);

	static std::vector<double> VTkMatrixToVector(vtkMatrix4x4* matrix);
	static vtkMatrix4x4*  VectorToVTKMatrix(std::vector<double> vector);
	static vtkMatrix4x4*  IGSTKkToVTK(igstk::Transform transform);
};

