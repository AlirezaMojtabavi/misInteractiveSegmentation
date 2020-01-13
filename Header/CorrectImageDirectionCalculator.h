#pragma once

#include "vtkMatrix4x4.h"

class CorrectImageDirectionCalculator
{
public:
	CorrectImageDirectionCalculator();
	~CorrectImageDirectionCalculator();

	static vtkSmartPointer<vtkMatrix4x4> CalculateMatrix(std::string patientPosition, float* orientation);

};