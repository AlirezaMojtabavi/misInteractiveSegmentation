#pragma once
#include "IPlan.h"
#include "BusinessEntities\Point.h"

using ParcastPointType = parcast::Point<double, 3>;

namespace parcast
{
	MOCK_BASE_CLASS(MockDentalPlan, IPlan)
	{
		MOCK_CONST_METHOD(GetParentImageUID, 0, misUID());
		MOCK_NON_CONST_METHOD(SetScrewInterationType, 1, void(ScrewWidgetInteractionType interactionType));
		MOCK_NON_CONST_METHOD(GetScrewInterationType, 0, ScrewWidgetInteractionType());
		MOCK_NON_CONST_METHOD(SetScrewSourceType, 1, void(ScrewWidgetSourceType srcType));
		MOCK_NON_CONST_METHOD(GetScrewSourceType, 0, ScrewWidgetSourceType());
		MOCK_NON_CONST_METHOD(SetPlannigColor, 1, void(misColorStruct color));
		MOCK_NON_CONST_METHOD(GetPlannigColor, 0, misColorStruct());
		MOCK_NON_CONST_METHOD(SetScrewDiameter, 1, void(double diameter));
		MOCK_NON_CONST_METHOD(GetScrewDiameter, 0, double());
		MOCK_NON_CONST_METHOD(SetPlanName, 1, void(std::string planName));
		MOCK_NON_CONST_METHOD(GetPlanName, 0, std::string());
		MOCK_NON_CONST_METHOD(SetEntryPoint, 1, void(const ParcastPointType&));
		MOCK_NON_CONST_METHOD(GetEntryPoint, 0, ParcastPointType());
		MOCK_NON_CONST_METHOD(SetTargetPoint, 1, void(const ParcastPointType&));
		MOCK_NON_CONST_METHOD(GetTargetPoint, 0, ParcastPointType());
		MOCK_CONST_METHOD(GetUID, 0, std::string());
		MOCK_NON_CONST_METHOD(SetUID, 1, void(const std::string& id));
		MOCK_NON_CONST_METHOD(GetPackageRels, 0, std::vector<std::shared_ptr<IPackagePlanRel>>());
		MOCK_NON_CONST_METHOD(GetPlanValidity, 0, bool());
		MOCK_NON_CONST_METHOD(GetTransform, 0, std::shared_ptr<const ITransform>());
		MOCK_CONST_METHOD(GetPlanCentricViewAngle, 0, double());
		MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void (const double& angle));
		MOCK_NON_CONST_METHOD(DeletePlan, 0, void());
		MOCK_NON_CONST_METHOD(SetTargetRegionRadius, 1, void(double radius) noexcept);
		MOCK_CONST_METHOD(GetTargetRegionRadius, 0, double() noexcept);
		MOCK_CONST_METHOD(GetLength, 0, double() noexcept);
		MOCK_NON_CONST_METHOD(GetScrewPlacementFinalized, 0, bool () );
		MOCK_NON_CONST_METHOD(SetScrewPlacementFinalized, 1,  void (bool ));
		MOCK_NON_CONST_METHOD(GetTargetValidity, 0, bool () );
		MOCK_NON_CONST_METHOD(ResetTargetPoint,0, void () );
		MOCK_NON_CONST_METHOD(GetEntryValidity,  0,bool () );
		MOCK_NON_CONST_METHOD(ResetEntryPoint, 0, void () );
		MOCK_NON_CONST_METHOD(ResetPlan, 0, void () );


	};
}