#pragma once
#include "FloatingPointCompare.h"

// The TransformMatrixElementsMatcher matches a received array of matrix elements by creating the equivalent transform and making
// sure that it transforms each vector from a given set to a vector that is almost equal to the same vector being transformed by
// a vtkTransform object and mean vector computed.
class TransformMatrixElementsMatcher
{
public:
	typedef itk::Vector<double, 3> VectorType;

	TransformMatrixElementsMatcher(std::vector< vtkSmartPointer<vtkTransform> > transforms,
		const std::vector<VectorType>& arbitraryVecs, double tolerance = 1e-3)
		: m_Transforms(transforms), m_ArbitraryVecs(arbitraryVecs), Tolerance(tolerance)
	{
	}

	bool operator()(const double rcvdMatElems[16])
	{
		bool match = true;
		for (int i = 0; i < m_ArbitraryVecs.size(); ++i)
			match = match && DoesMatrixMatchForVector(rcvdMatElems, m_ArbitraryVecs[i]);
		return match;
	}

private:
	bool DoesMatrixMatchForVector(const double rcvdMatElems[16], const VectorType& vec)
	{
		auto meanVec = VectorType(0.0);
		for (int i = 0; i < m_Transforms.size(); i++)
		{
			auto transformedVec = VectorType(m_Transforms[i]->TransformDoubleVector(vec.GetDataPointer()));
			meanVec += transformedVec;
		}
		meanVec /= m_Transforms.size();
		auto equivTrans = vtkSmartPointer<vtkTransform>::New();
		equivTrans->SetMatrix(rcvdMatElems);
		auto expectedVec = VectorType(equivTrans->TransformDoubleVector(vec.GetDataPointer()));
		bool retVal = FloatingPointCompare::AreCoordinatesClose(meanVec, expectedVec, Tolerance);
		return retVal;
	}

	const double Tolerance;
	// 
	std::vector< vtkSmartPointer<vtkTransform> > m_Transforms;
	std::vector<VectorType> m_ArbitraryVecs;
};

namespace parcast
{

	class MatrixElementwiseMatcher
	{
	public:
		template <class CollT>
		MatrixElementwiseMatcher(const CollT& expectedElements, double tolerance = 1e-3)
			: ExpectedElements(std::cbegin(expectedElements), std::cend(expectedElements)),
			Tolerance(tolerance)
		{
		}

		bool operator()(vtkMatrix4x4* receivedMatrix)
		{
			for (auto i = 0; i < 4; ++i)
				for (auto j = 0; j < 4; ++j)
					if (!FloatingPointCompare::IsClose(receivedMatrix->GetElement(i, j), ExpectedElements[i * 4 + j], Tolerance))
						return false;
			return true;
		}

	private:
		const std::vector<double> ExpectedElements;
		const double Tolerance;
	};
}

namespace parcast
{

	class ElementwiseTransformMatcher
	{
	public:
		ElementwiseTransformMatcher(std::shared_ptr<ITransform> expectedTransform, double tolerance = 1e-3)
			:Tolerance(tolerance)
		{
			expectedTransform->GetMarixElements(m_ExpectedElements);
		}

		bool operator()(std::shared_ptr<ITransform> transform)
		{
			double transElements[16];
			transform->GetMarixElements(transElements);


			return std::equal(m_ExpectedElements, m_ExpectedElements + 16, transElements,
				[tolerance = Tolerance](double num1, double num2)
			{
				return FloatingPointCompare::IsClose(num1, num2, tolerance);
			});

		}

	private:
		const double Tolerance;
		double m_ExpectedElements[16];
	};
}