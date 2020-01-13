#pragma once

#include "BusinessEntities/Vector.h"

namespace parcast
{
	struct ViewVectors
	{
		typedef Vector<double, 3> VectorType;

		VectorType UpView;
		VectorType RightView;
	};
}

