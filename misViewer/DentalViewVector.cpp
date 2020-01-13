#include "stdafx.h"
#include "DentalViewVector.h"

#include "IVectorRotator.h"

using namespace parcast;

DentalViewVector::DentalViewVector(std::shared_ptr<IVectorRotator> vectorRotator)
	: m_PlanDir(0.0, 0.0, -1.0),
	m_MesiodistalDir(1.0, 0.0, 0.0),
	m_VectorRotator(vectorRotator),
	m_Angle(0.0)
{
}

parcast::Vector<double, 3> DentalViewVector::CalculateNormalUpView() const
{
	auto upView = m_PlanDir * -Sign(m_PlanDir[2]);
	upView.Normalize();
	return upView;
}

ViewVectors DentalViewVector::CalculateMesiodistalView() const
{
	const auto upView = CalculateNormalUpView();

	auto rightView = VectorMath::CrossProduct(upView, VectorMath::CrossProduct(m_MesiodistalDir, upView));
	rightView.Normalize();

	if (m_Angle == 0)
		return ViewVectors{ upView , rightView };

	return ViewVectors{ upView, m_VectorRotator->Rotate(rightView, upView, m_Angle) };
}

ViewVectors DentalViewVector::CalculateOcclusalView() const
{
	const Vec j(0.0, 1.0, 0.0);
	auto rightView = VectorMath::CrossProduct(m_PlanDir, j) * Sign(m_PlanDir[2]) * -1.0;
	rightView.Normalize();
	auto upView = VectorMath::CrossProduct(m_PlanDir * -1., rightView);
	upView.Normalize();
	return ViewVectors{ upView, rightView };
}

ViewVectors DentalViewVector::CalculateBuccolingualView() const
{
	auto upView = CalculateNormalUpView();

	auto rightView = VectorMath::CrossProduct(m_MesiodistalDir, upView);
	rightView.Normalize();

	if (m_Angle == 0)
		return ViewVectors{ upView , rightView };

	return ViewVectors{ upView, m_VectorRotator->Rotate(rightView, upView, m_Angle) };
}

void DentalViewVector::SetViewDirections(const Vec& plan, const Vec& mesiodistal)
{
	m_PlanDir = plan;
	m_MesiodistalDir = mesiodistal;
}

void DentalViewVector::SetRightViewAngularOffset(double angle)
{
	m_Angle = angle;
}

double DentalViewVector::Sign(double a)
{
	return 0.0 < a ? 1.0 : a == 0.0 ? 0.0 : -1.0;
}