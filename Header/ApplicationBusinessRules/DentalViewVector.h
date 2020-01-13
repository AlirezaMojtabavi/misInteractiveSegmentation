#pragma once

#include "IDentalViewVector.h"

namespace parcast
{

	class IVectorRotator;

	class DentalViewVector : public IDentalViewVector
	{
	public:
		using Vec = ViewVectors::VectorType;

		DentalViewVector(std::shared_ptr<IVectorRotator> vectorRotator);

		ViewVectors CalculateOcclusalView() const override;
		ViewVectors CalculateBuccolingualView() const override;
		ViewVectors CalculateMesiodistalView() const override;
		void SetViewDirections(const Vec& plan, const Vec& mesiodistal) override;
		void SetRightViewAngularOffset(double angle) override;

	private:
		static double Sign(double a);
		Vector<double, 3> DentalViewVector::CalculateNormalUpView() const;

		std::shared_ptr<IVectorRotator> m_VectorRotator;
		Vec m_PlanDir;
		Vec m_MesiodistalDir;
		double m_Angle;
	};

}