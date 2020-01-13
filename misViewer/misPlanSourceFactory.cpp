#include "stdafx.h"
#include "misPlanSourceFactory.h"
#include "I3DPlanCrossSectionFunction.h"
#include "Dental3dPlanCrossSectionFucntion.h"
#include "Biopsy3dPlanCrossSectionFunction.h"
#include "mis3DImplant.h"
#include "mis2dImplant.h"
#include "BiopsyPlanSettingParam.h"

std::shared_ptr<IImplantSource> misPlanSourceFactory::CreatePlanSource(
	std::shared_ptr<ICornerProperties> cornerProperties, IMAGEORIENTATION orientaion,
	misApplicationType apptype, bool displayCross)
{
	auto planRepresentationShader = "PlanFragment.frag";
	std::unique_ptr<parcast::I3DPlanCrossSectionFunction> crossSectionFunction;
	crossSectionFunction = std::make_unique<parcast::Dental3dPlanCrossSectionFucntion>();
	auto appTypeIsSpineOrDental = apptype != Dental && apptype != Spine;
	if (appTypeIsSpineOrDental)
	{
		crossSectionFunction = std::make_unique<parcast::Biopsy3DPlanCrossSectionFunction>();
		planRepresentationShader = "BiopsyPlanShader.frag";
	}
	std::shared_ptr<IImplantSource> implantSource;		
	const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();

	if (orientaion == UNKnownDirection)
	{
		const auto supportedAppType = (apptype == Dental || apptype == Spine) ? true : false;
		
		const auto lineRadius = settingContainer->GetDouble("misPlanningSetting/LineRadius");
		const auto lineHeight = settingContainer->GetDouble("misPlanningSetting/LineHeight");
		const auto displayExtension = settingContainer->GetBoolean("misPlanningSetting/DisplayExtension");

		implantSource = std::make_shared<mis3DImplant>(std::move(crossSectionFunction), supportedAppType && displayExtension, lineRadius, lineHeight);
	}
	else
	{
		PlanSettingParam biopsyPlanParam;
		biopsyPlanParam.borderInlineOpacity = settingContainer->GetDouble("misPlanningSetting/BorderInlineOpacity");
		biopsyPlanParam.borderOpacity = settingContainer->GetDouble("misPlanningSetting/BordereOpacity");
		biopsyPlanParam.displayCrossSection = settingContainer->GetBoolean("misPlanningSetting/DisplayCrossSection");
		biopsyPlanParam.displayProjection = settingContainer->GetBoolean("misPlanningSetting/DisplayProjection");
		biopsyPlanParam.planDiameter = settingContainer->GetDouble("misPlanningSetting/PlanDiameter");
		biopsyPlanParam.dashLineSize = settingContainer->GetDouble("misPlanningSetting/DashLineSize");
		biopsyPlanParam.intersectionColor.r = settingContainer->GetDouble("misPlanningSetting/IntersectionRedColor");
		biopsyPlanParam.intersectionColor.g = settingContainer->GetDouble("misPlanningSetting/IntersectionGreenColor");
		biopsyPlanParam.intersectionColor.b = settingContainer->GetDouble("misPlanningSetting/IntersectionBlueColor");
		biopsyPlanParam.intersectionColor.opacity = settingContainer->GetDouble("misPlanningSetting/IntersectionOpacity");
		biopsyPlanParam.intersectionRadius = settingContainer->GetDouble("misPlanningSetting/IntersectionRadius");


		implantSource = std::make_shared<mis2DImplant>(planRepresentationShader, cornerProperties, biopsyPlanParam, displayCross);
	}
	return implantSource;
}
