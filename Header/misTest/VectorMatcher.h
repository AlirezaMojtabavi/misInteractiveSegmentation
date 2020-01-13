#pragma once

//This class created for Vector and itk::Vector classes
namespace parcast
{

	template<typename VecType1, typename VecType2, typename ValueType = double, int Size = 3>
	class VectorMatcher
	{
	public:
		VectorMatcher(const VecType1& thisVector, double tolerance = 0.02)
			: m_ThisVector(thisVector),
			m_Tolerance(tolerance)
		{ }

		bool operator()(const VecType2& otherVector)
		{
			return IsEqual(m_ThisVector, otherVector, m_Tolerance);
		}

		static bool IsEqual(const VecType1& a, const VecType2& b, ValueType tolerance = ValueType())
		{
			for (int i = 0; i < Size; ++i)
				if ((a[i] - b[i]) * (a[i] - b[i]) > tolerance * tolerance)
					return false;
			return true;
		}

	private:
		VecType1 m_ThisVector;
		double m_Tolerance;
	};

}

