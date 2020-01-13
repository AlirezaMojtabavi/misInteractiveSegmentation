#pragma once
#ifndef misPlanData_H
#define misPlanData_H

#include "IPlan.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "BusinessEntities\Point.h"
#include "misObject.h"

namespace parcast
{
	class IPackagePlanRelRepo;
	class IPlanRepo;
	class IPlanCorrelationManager;
	class IPlanTransformCalculator;
	class ITransformFactory;
}

class misPlanData : public parcast::IPlan
{
public:

	misPlanData(
		const std::string& parentImageUid,
		std::weak_ptr<parcast::IPackagePlanRelRepo> pkgPlanRelRepo,
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
		std::weak_ptr<parcast::ITransformFactory> tranformFactory,
		std::weak_ptr<parcast::IPlanRepo> planRepo, double targetRegionRadius, double screwDiameter	);

	double GetPlanCentricViewAngle() const override;
	void SetPlanCentricViewAngle(const double& angle) override;
	misSetMacro(PlannigColor, misColorStruct);
	misColorStruct GetPlannigColor() override;
	misUID GetParentImageUID() const override;
	std::string GetUID() const override;
	void SetUID(const std::string& id) override;
	void SetPlanName(std::string planName) override;
	std::string GetPlanName() override;
	bool GetPlanValidity() override;
	void ResetPlan() override;
	void SetScrewSourceType(ScrewWidgetSourceType srcType) override;
	ScrewWidgetSourceType GetScrewSourceType() override;
	void SetScrewInterationType(ScrewWidgetInteractionType interactionType) override;
	ScrewWidgetInteractionType GetScrewInterationType() override;
	void SetScrewDiameter(double diameter) override;
	double GetScrewDiameter() override;
	std::vector<std::shared_ptr<parcast::IPackagePlanRel>> GetPackageRels() override;
	void SetEntryPoint(const parcast::Point<double, 3>& point) override;
	parcast::Point<double, 3> GetEntryPoint() override;
	bool GetEntryValidity()override;
	void ResetEntryPoint()override;
	void SetTargetPoint(const parcast::Point<double, 3>& point) override;
	parcast::Point<double, 3> GetTargetPoint() override;
	bool GetTargetValidity() override;
	void ResetTargetPoint() override;
	std::shared_ptr<const ITransform> GetTransform() override;
	virtual void DeepCopy(misPlanData* planData);
	void DeletePlan() override;

	void SetTargetRegionRadius(double radius) override;
	double GetTargetRegionRadius() const override;
	double GetLength() const override;
	virtual bool GetScrewPlacementFinalized() { return false; }
		virtual void SetScrewPlacementFinalized(bool isFinished) {}
protected:

	misColorStruct m_PlannigColor;
	std::string m_PlanName;
	bool m_ModificationFlag;
	misUID m_ParentImageUID;
	bool m_ValidTarget = false;
	bool m_ValidEntry = false;
	double m_CentricViewAngle = 0;

private:

	void SetTransform(const parcast::Point<double, 3>& entry, const parcast::Point<double, 3>& target);
	enum class PointType { Entry, Target };
	parcast::Point<double, 3> GetPointFromTransform(const PointType type);

	friend class misPlanDatabaseIO;
	std::weak_ptr<parcast::IPackagePlanRelRepo> m_PkgPlanRelRepo;
	std::weak_ptr<parcast::IPlanRepo> m_PlanRepo;
	std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
	std::weak_ptr<parcast::IPlanTransformCalculator> m_PlanTransformCalculator;
	std::weak_ptr<parcast::ITransformFactory> m_TransformFactory;
	misUID m_DataObjectUID;
	ScrewWidgetSourceType m_ScrewSourceType;
	ScrewWidgetInteractionType m_ScrewInterationType;
	double m_PlanLength ;
	double m_TargetRegionRadius  ;
	double m_ScrewDiameter ;

};

typedef std::vector<std::weak_ptr<parcast::IPlan>> PlanDataListTypedef;
#endif
