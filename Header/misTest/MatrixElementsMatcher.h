#pragma once

#include "misMathUtils.h"

// Matcher used in tests to verify if a given array[16] of double values, taken to be row by row elements of a 4x4 transform matrix,
// match a previously specified matrix. Two tolerance values should be provided separately, one for the elements of the rotation
// part, and the other for the elements of the translation part.
class MatrixElementsMatcher
{
public:
	MatrixElementsMatcher(double expectedMatrixElements[16], double toleranceMatrix[16] = nullptr)
	{
		std::copy(expectedMatrixElements, expectedMatrixElements + 16, m_ExpectedArray);
		if (toleranceMatrix)
			std::copy(expectedMatrixElements, expectedMatrixElements + 16, m_ToleranceMatrix);
		else
			std::fill(m_ToleranceMatrix, m_ToleranceMatrix + 16, 0.001);
	}

	bool operator()(const double rcvdMatElems[16])
	{
		bool match = true;
		for (int i = 0; i < 16 && match; ++i)
			match = match && misMathUtils::IsClose(m_ExpectedArray[i], rcvdMatElems[i], m_ToleranceMatrix[i]);
		return match;
	}

private:
	double m_ExpectedArray[16], m_ToleranceMatrix[16];
};