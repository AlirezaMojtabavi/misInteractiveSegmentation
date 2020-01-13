#pragma once
#include "BusinessEntities\Vector.h"

namespace parcast
{
	template< typename T, int Dimensions = 3 >
	class Vertex
	{
	public:
		T GetElement(size_t index) const
		{
			return m_Elements[index];
		}
		T & operator[](const size_t index) 
		{
			return m_Elements[index];
		}
 
		Vector<T, Dimensions>	operator -( const Vertex<T,Dimensions>& right) const
		{
			Vector<T, Dimensions> res;
			for (int i = 0;i < Dimensions; i++)
				res[i] = m_Elements[i] - right.GetElement(i);
			return res;
		}
	private:
		T m_Elements[Dimensions];
	};
}
