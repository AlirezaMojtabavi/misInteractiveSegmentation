#pragma once

class FloatingPointCompare
{
public:
	// Test approximate equality for floating point types since precise equality is not supported.
	template<typename T>
	static bool IsClose(T val1, T val2, T tolerance = static_cast<T>(1e-6))
	{
		return (val1 - val2) * (val1 - val2) <= tolerance * tolerance;
	}

	// Test approximate equality for floating point combo types (vectors, points, ...) since precise equality is not supported.
	template <typename ComboType1, typename ComboType2>	// itk::Point, itk::Vector, ...
	static bool AreCoordinatesClose(ComboType1 point1, ComboType2 point2, double tolerance = 1e-6)
	{
		return IsClose(point1[0], point2[0], tolerance) &&
			IsClose(point1[1], point2[1], tolerance) &&
			IsClose(point1[2], point2[2], tolerance);
	}

	// Test approximate equality for floating point, one dimensional arrays of equal size (vectors, points, ...) since 
	// precise equality is not supported.
	template <int Size, typename ArrayType1, typename ArrayType2>	// double[N], std::vector<double>, itk::Point, itk::Vector, ...
	static bool AreArraysClose(ArrayType1 array1, ArrayType2 array2, double tolerance = 1e-6)
	{
		bool areClose = true;
		for (int i = 0; i < Size; i++)
			areClose = areClose && IsClose(array1[i], array2[i], tolerance);
		return areClose;
	}

	// Clips a value between a minimum and a maximum value. It returns the value if it is within the given range, min if
	// it is below the given minimum, and max if it is above the given maximum.
	template <class T>
	static const T& ClipValue(T inputValue, T min, T max)
	{
		return std::min(std::max(inputValue, min), max);
	}
};

