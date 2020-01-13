#include "stdafx.h"
#include "PlanTransformUpdater.h"

#include "ITransformFactory.h"
#include "VectorRotator.h"

using namespace parcast;

PlanTransformUpdater::PlanTransformUpdater(
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationMnager,
	std::shared_ptr<ITransformFactory> transformFactory,
	std::shared_ptr<IVectorRotator> vectorRotator)
	:m_CSCorrelationManager(correlationMnager),
	m_TransformFactory(transformFactory),
	m_VectorRotator(vectorRotator)
{
}

void PlanTransformUpdater::Rotate(const std::string& planUId, const std::string& parentImageUid, double angle)
{
	Rotate(planUId, parentImageUid, angle, false);
}

void PlanTransformUpdater::RotateToLastAccumulatedAngle(const std::string& planUId, const std::string& parentImageUid)
{
	if (m_AccumulatedAngle == 0.0)
	{
		return;
	}
	Rotate(planUId, parentImageUid, m_AccumulatedAngle, true);
}

void PlanTransformUpdater::Rotate(
	const std::string& planUId,
	const std::string& parentImageUid,
	double angle, bool absolute)
{
	auto const correlation = m_CSCorrelationManager->GetTransform(planUId, parentImageUid);
	auto const transform = correlation->GetTransform();

	double transMat[16];
	transform->GetMarixElements(transMat);

	auto xAxis = VectorD3(transMat[0], transMat[4], transMat[8]);
	auto yAxis = VectorD3(transMat[1], transMat[5], transMat[9]);
	auto zAxis = VectorD3(transMat[2], transMat[6], transMat[10]);

	if(absolute)
	{
		yAxis = VectorMath::CrossProduct(zAxis, VectorD3(1., 0., 0.)).GetNormalized();
		xAxis = VectorMath::CrossProduct(yAxis, zAxis).GetNormalized();
	}
	else
	{
		m_AccumulatedAngle += angle;
	}

	auto xRotatedAxis = m_VectorRotator->Rotate(xAxis, zAxis, angle);
	auto yRotatedAxis = m_VectorRotator->Rotate(yAxis, zAxis, angle);

	double newTransMat[16] =
	{ xRotatedAxis[0], yRotatedAxis[0], zAxis[0], transMat[3],
		xRotatedAxis[1], yRotatedAxis[1], zAxis[1], transMat[7],
		xRotatedAxis[2], yRotatedAxis[2], zAxis[2], transMat[11],
		0, 0, 0, 1.0 };

	auto const newTransform = m_TransformFactory->Create(newTransMat);
	m_CSCorrelationManager->SetTransform(planUId, parentImageUid, newTransform);
}
