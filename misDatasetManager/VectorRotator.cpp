#include "stdafx.h"
#include "VectorRotator.h"

using namespace parcast;

IVectorRotator::VectorType VectorRotator::Rotate(const VectorType& vector, const VectorType& axis, double angle)
{
	auto transform = vtkSmartPointer<vtkTransform>::New();
	transform->RotateWXYZ(angle, axis[0], axis[1], axis[2]);
	auto const rotatedVec = transform->TransformVector(vector[0], vector[1], vector[2]);
	return VectorType(rotatedVec);
}
