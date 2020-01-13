#pragma once
#pragma once

#include "misStrctColorData.h"

namespace parcast
{
	class misDoubleColorStructMacther
	{

	public:

		explicit misDoubleColorStructMacther(misDoubleColorStruct color) :m_Color(color)
		{

		}
		bool operator()(misDoubleColorStruct other) const
		{
			return AreEqual(m_Color, other);
		}

		static bool AreEqual(misDoubleColorStruct a, misDoubleColorStruct b)
		{
			return a.Red == b.Red&&
				a.Green == b.Green&&
				a.Blue == b.Blue&&
				a.Alpha == b.Alpha;
				
		}
	private:
		misDoubleColorStruct m_Color;
	};
}
