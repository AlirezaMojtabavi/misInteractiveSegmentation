#pragma once

#include "BusinessEntities\Point.h"


class ISimpleDataPackage;

namespace parcast
{

	class IPlan;

	class IDentalPlanning
	{
	public:
		using PointType = parcast::Point<double, 3>;
		using SplinePoints = std::vector<itk::Point<double, 3> >;
		virtual ~IDentalPlanning() = default;

		virtual void StartUp() = 0;
		virtual void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> pkg) = 0;
		virtual void SetCurrentPlan(std::shared_ptr<IPlan> plan) = 0;
		virtual void CapturePoint(const PointType& point) = 0;
		virtual void EnableAddPlanMode() = 0;
		virtual void ModifyPlan(std::shared_ptr<IPlan> plan, const PointType& startPoint, const PointType& endPoint) = 0;
		virtual void NewSpline() = 0;
		virtual void AcceptSpline(const SplinePoints& points) = 0;
		virtual void SetScrewDiameter(double diameter) = 0;
		virtual void SetScrewVisiblity(bool isVisible) = 0;
		virtual void SetPlanCentricViewAngle(double angle) = 0;
		virtual void DeletePlan() = 0;
	};

}