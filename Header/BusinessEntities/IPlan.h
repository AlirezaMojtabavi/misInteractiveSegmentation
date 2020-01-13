#pragma once

#include "ICoordinateSystem.h"
#include "misVertebraEnum.h"
#include "BusinessEntities\Point.h"

class ITransform;

namespace parcast
{

	class IPackagePlanRel;

	class IPlan : public ICoordinateSystem
	{
	public:

		virtual misUID GetParentImageUID() const = 0;
		virtual void SetScrewInterationType(ScrewWidgetInteractionType interactionType) = 0;
		virtual ScrewWidgetInteractionType GetScrewInterationType() = 0;
		virtual void SetScrewSourceType(ScrewWidgetSourceType srcType) = 0;
		virtual ScrewWidgetSourceType GetScrewSourceType() = 0;
		virtual void SetPlannigColor(misColorStruct color) = 0;
		virtual misColorStruct GetPlannigColor() = 0;
		virtual void SetScrewDiameter(double diameter) = 0;
		virtual double GetScrewDiameter() = 0;
		virtual void SetPlanName(std::string planName) = 0;
		virtual std::string GetPlanName() = 0;
		virtual void SetEntryPoint(const Point<double, 3>& point) = 0;
		virtual Point<double, 3> GetEntryPoint() = 0;
		virtual void SetTargetPoint(const Point<double, 3>& point) = 0;
		virtual Point<double, 3> GetTargetPoint() = 0;
		virtual std::vector<std::shared_ptr<IPackagePlanRel>> GetPackageRels() = 0;
		virtual bool GetPlanValidity() = 0;
		virtual std::shared_ptr<const ITransform> GetTransform() = 0;
		virtual double GetPlanCentricViewAngle() const = 0;
		virtual void SetPlanCentricViewAngle(const double& angle) = 0;
		virtual void DeletePlan() = 0;
		virtual void SetTargetRegionRadius(double radius) = 0;
		virtual double GetTargetRegionRadius() const = 0;
		virtual double GetLength() const = 0;
		virtual bool GetScrewPlacementFinalized() = 0;
		virtual void SetScrewPlacementFinalized(bool isFinished) = 0;
		virtual bool GetTargetValidity() = 0;
		virtual void ResetTargetPoint() = 0;
		virtual bool GetEntryValidity()= 0;
		virtual void ResetEntryPoint() = 0;
		virtual void ResetPlan() = 0;
	};

}
