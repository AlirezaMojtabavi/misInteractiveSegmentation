#pragma once

// this class take array of 16 elements and return acceptable vector for transform class
class FillMatrixArray
{
public:
	template<typename ArrayT>
	FillMatrixArray(const ArrayT& array)
		: Array(std::cbegin(array), std::cend(array))
	{
	}

	void operator()(double matrixElements[16])
	{
		std::copy(Array.cbegin(), Array.cend(), matrixElements);
	}

private:
	const std::vector<double> Array;
};