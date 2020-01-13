#pragma once

// this class take array of 16 elements and return acceptable vector for transform class
class MatrixFillingFunctor
{
public:
	MatrixFillingFunctor(double array[16])
		: m_Array(array, array + 16)
	{
	}

	void operator()(double matrixElements[16])
	{
		std::copy(m_Array.cbegin(), m_Array.cend(), matrixElements);
	}

private:
	std::vector<double> m_Array;
};
