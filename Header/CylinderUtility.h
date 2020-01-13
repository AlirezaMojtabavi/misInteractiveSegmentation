#pragma once
#include "ICylinderUtility.h"

#include "Cylinder.h"

namespace parcast
{

	class CylinderUtility : public ICylinderUtility
	{
	public:
		CylinderUtility(const Cylinder& cylinder);

		bool IsInCylinder(const Point<double, 3>& x) const override;

	private:
		Cylinder m_Cylinder;
	};

}
