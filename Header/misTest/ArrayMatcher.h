#pragma once

template<typename T, size_t N>
class ArrayMatcher
{
public:
	explicit ArrayMatcher(const T array[N] , T tolerance = T()) : Tolerance(tolerance)
	{
		std::copy(array, array + N, m_Array);
	}

	bool operator()(const T other[N]) const
	{
		return IsEqual(m_Array, other);
	}

	bool IsEqual(const T a[N], const T b[N]) const
	{
		return std::inner_product(a, a + N, b, true, std::logical_and<>(),
			[tolerance = Tolerance](const T& a, const T& b) { return (std::abs<T>(a - b) <= tolerance); });
	}

private:
	const T Tolerance;
	T m_Array[N];
};