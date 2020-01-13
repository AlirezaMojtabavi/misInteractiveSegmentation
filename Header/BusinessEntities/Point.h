#pragma once

#include "Vector.h"

namespace parcast
{

	template< typename T, int Dimensions = 3>
	class Point
	{
	public:
		using ValueType = T;

		Point()
		{
			for (int i = 0; i < Dimensions; i++)
				m_Elements[i] = ValueType();
		}

		template<typename... T>
		explicit Point(T... inputArray) : m_Elements{ inputArray... }
		{
			static_assert(Dimensions == sizeof...(inputArray), "sizes do not match");
		}

		explicit Point(ValueType const* elements)
		{
			std::copy(elements, elements + Dimensions, m_Elements);
		}

		explicit Point(ValueType* elements)
		{
			std::copy(elements, elements + Dimensions, m_Elements);
		}

		ValueType & operator[](const size_t index)
		{
			return m_Elements[index];
		}

		const ValueType & operator[](const size_t index) const
		{
			return m_Elements[index];
		}

		Point<ValueType, Dimensions> operator+(const Vector<ValueType, Dimensions>& vector) const
		{
			Point<ValueType, Dimensions> result(
				m_Elements[0] + vector[0], m_Elements[1] + vector[1], m_Elements[2] + vector[2]);
			return result;
		}

		Point<ValueType, Dimensions> operator-(const Vector<ValueType, Dimensions>& vector) const
		{
			Point<ValueType, Dimensions> result(
				m_Elements[0] - vector[0], m_Elements[1] - vector[1], m_Elements[2] - vector[2]);
			return result;
		}

		Vector<ValueType, Dimensions> operator-(const Point<ValueType, Dimensions>& right) const
		{
			Vector<ValueType, Dimensions> res;
			for (int i = 0; i < Dimensions; i++)
				res[i] = m_Elements[i] - right[i];

			return res;
		}

		const ValueType* Elements()
		{
			return m_Elements;
		}

		ValueType const* Elements() const
		{
			return m_Elements;
		}

		bool operator==(const Point<ValueType, Dimensions>& right) const
		{
			for (int i = 0; i < Dimensions; i++)
				if (m_Elements[i] != right[i])
					return false;

			return true;
		}

	private:
		ValueType m_Elements[Dimensions];
	};

	using PointD3 = Point<double, 3>;

}

template <typename T, int D>
std::ostream& operator<<(std::ostream& os, parcast::Point<T, D> const& point)
{
	//static_assert(D > 0);

	os << "Point { ";
	for (int i = 0; i < D - 1; ++i)
		os << point[i] << ", ";
	if (D > 0)
		os << point[D - 1];
	os << " }";
	return os;
}