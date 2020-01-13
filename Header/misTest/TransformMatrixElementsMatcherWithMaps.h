#pragma once

#include "FloatingPointCompare.h"

// Matcher used in tests to verify if a given array of 16 double values, taken to be row by row elements of a 4x4 transform matrix,
// when used to initialize a VTK transform transform a previously specified set of vectors and a point to an expected set of 
// vectors and a point. A tolerance can be specified for matching coordinates of the vectors and the point.
class TransformMatrixElementsMatcherWithMaps
{
public:
	typedef itk::Vector<double, 3> VectorType;

	TransformMatrixElementsMatcherWithMaps(
		const std::vector< itk::Vector<double, 3> >& inputVecs, const std::vector< itk::Vector<double, 3> >& outputVecs, 
		const itk::Point<double, 3>& inputPoint, const itk::Point<double, 3>& outputPoint, double tol = 1e-6)
		: InputVectors(inputVecs), OutputVectors(outputVecs), InputPoint(inputPoint), OutputPoint(outputPoint), Tolerance(tol)
	{
	}

	bool operator()(const double rcvdMatElems[16])
	{
		auto trans = vtkSmartPointer<vtkTransform>::New();
		trans->SetMatrix(rcvdMatElems);
		auto outPoint = trans->TransformDoublePoint(InputPoint.GetDataPointer());
		bool match = FloatingPointCompare::AreArraysClose<3>(outPoint, OutputPoint.GetDataPointer(), Tolerance);
		for (auto vecItr = InputVectors.cbegin(), outVecItr = OutputVectors.cbegin(); 
			vecItr != InputVectors.cend() && outVecItr != OutputVectors.cend() && match; ++vecItr, ++outVecItr)
		{
			auto outVec = trans->TransformDoubleVector(vecItr->GetDataPointer());
			match = match && FloatingPointCompare::AreArraysClose<3>(outVec, outVecItr->GetDataPointer(), Tolerance);
		}
		return match;
	}

private:
	const std::vector< itk::Vector<double, 3> >& InputVectors;
	const std::vector< itk::Vector<double, 3> >& OutputVectors;
	const itk::Point<double, 3>& InputPoint;
	const itk::Point<double, 3>& OutputPoint;
	const double Tolerance;
};

namespace parcast
{

	class VtkTransformElementwiseMatcher
	{
	public:
		static bool AreEqual(vtkTransform* a, vtkTransform* b)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
				{
					if (a->GetMatrix()->GetElement(i, j) != b->GetMatrix()->GetElement(i, j))
						return false;
				}
			return true;
		}
	};

}