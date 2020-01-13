#pragma once
#include <numeric>

namespace parcast
{

	template< typename ValueType, int Dimensions = 3 >
	class Vector
	{
	public:
		Vector()
		{
			for (int i = 0; i < Dimensions; i++)
				m_Elements[i] = ValueType();
		}

		template<typename... T>
		explicit Vector(T... elements) : m_Elements{ elements... }
		{
			static_assert(Dimensions == sizeof...(elements), "sizes do not match");
		}

		explicit Vector(ValueType const* elements)
		{
			std::copy(elements, elements + Dimensions, m_Elements);
		}

		explicit Vector(ValueType* elements)
		{
			std::copy(elements, elements + Dimensions, m_Elements);
		}

		ValueType & operator[](const size_t index)
		{
			return m_Elements[index];
		}


		bool operator==(const Vector<ValueType, Dimensions>& other) const
		{
			return std::equal(std::cbegin(m_Elements), std::cend(m_Elements), other.Elements());
		}

		bool operator!=(const Vector<ValueType, Dimensions>& other) const
		{
			return !std::equal(std::cbegin(m_Elements), std::cend(m_Elements), other.Elements());
		}

		const ValueType & operator[](const size_t index) const
		{
			return m_Elements[index];
		}

		void Normalize()
		{
			auto length = Length();
			if (length == ValueType())
				return;

			auto divFunc = [length](const ValueType v) { return v / length; };
			std::transform(std::cbegin(m_Elements), std::cend(m_Elements), std::begin(m_Elements), divFunc);
		}

		Vector<ValueType, Dimensions> GetNormalized() const
		{
			auto copy = *this;
			copy.Normalize();
			return copy;
		}

		ValueType Length() const
		{
			auto lengthSqr = std::inner_product(
				std::cbegin(m_Elements), std::cend(m_Elements), std::cbegin(m_Elements), ValueType());
			return static_cast<ValueType>(std::sqrt(lengthSqr));
		}

		const ValueType* Elements()
		{
			return m_Elements;
		}

		ValueType const* Elements() const
		{
			return m_Elements;
		}

		Vector<ValueType, Dimensions> operator-() const
		{
			ValueType res[Dimensions];
			std::transform(std::cbegin(m_Elements), std::cend(m_Elements),
				std::begin(res), std::negate<ValueType>());
			return Vector<ValueType, Dimensions>(res);
		}

		Vector<ValueType, Dimensions> operator-(const Vector<ValueType, Dimensions>& right) const
		{
			ValueType res[Dimensions];
			std::transform(std::cbegin(m_Elements), std::cend(m_Elements), std::cbegin(right.m_Elements),
				std::begin(res), std::minus<ValueType>());
			return Vector<ValueType, Dimensions>(res);
		}

		Vector<ValueType, Dimensions> operator+(const Vector<ValueType, Dimensions>& right) const
		{
			ValueType res[Dimensions];
			std::transform(std::cbegin(m_Elements), std::cend(m_Elements), std::cbegin(right.m_Elements),
				std::begin(res), std::plus<ValueType>());
			return Vector<ValueType, Dimensions>(res);
		}

		Vector<ValueType, Dimensions> operator*(const ValueType coef) const
		{
			ValueType res[Dimensions];
			auto mulFunc = [&coef](const ValueType v) { return v * coef; };
			std::transform(std::cbegin(m_Elements), std::cend(m_Elements), std::begin(res), mulFunc);
			return Vector<ValueType, Dimensions>(res);
		}

		ValueType operator*(const Vector<ValueType, Dimensions>& other) const
		{
			return std::inner_product(std::cbegin(m_Elements), std::cend(m_Elements), other.Elements(), ValueType{0});
		}

	private:
		ValueType m_Elements[Dimensions];
	};

	namespace VectorMath
	{

		template <class T>
		Vector<T, 3> CrossProduct(const Vector<T, 3>& a, const Vector<T, 3>& b)
		{
			return Vector<T, 3>((a[1] * b[2]) - (a[2] * b[1]), (a[2] * b[0]) - (a[0] * b[2]), (a[0] * b[1]) - (a[1] * b[0]));
		}

		template <typename SourceType, typename DestinationType, int Size>
		DestinationType ConvertVector(const SourceType& sourceVector)
		{
			DestinationType destinationVector;
			for (int i = 0; i < Size; ++i)
				destinationVector[i] = sourceVector[i];
			return destinationVector;
		}

	}

	using VectorD3 = Vector<double, 3>;

}

template <typename T, int D>
std::ostream& operator<<(std::ostream& os, parcast::Vector<T, D> const& vec)
{
	os << "Vector { ";
	for (int i = 0; i < D - 1; ++i)
		os << vec[i] << ", ";
	if (D > 0)
		os << vec[D - 1];
	os << " }";
	return os;
}