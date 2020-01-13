#pragma once
#include "misColorStruct.h"
#include "misCroppingDirectionInVR.h"
#include "misDataProdecureEnum.h"
#include "misDistributionStruct.h"
#include "misGuiStructures.h"
#include "misPlanSTRCT.h"
#include "BiopsyPlanInformation.h"
#include "IPackageViewingExtractor.h"
#include <ISettingsContainer.h>

class ISimpleDataPackage;
class misScrewWidgetData;

class IBiopsyPlanningHelper
{
public:
	virtual bool AcceptPlan(const BiopsyPlanInformation &planInformation) = 0;
	virtual bool ChangePlanColor(const misColorStruct &color) = 0;
	virtual bool CreateNewApproach() = 0;
	virtual bool DeleteEntryPoint() = 0;
	virtual bool DeleteTargetPoint() = 0;
	virtual bool DenyPlan() = 0;
	virtual bool ModifyEntryPoint() = 0;
	virtual bool ModifyTargetPoint() = 0;
	virtual bool SetEntryPoint() = 0;
	virtual void SetPlanFlowSlider(const double &value) = 0;
	virtual bool SetPlanTrancparency(const ApproachAndModelOpacityInformation &opacity) = 0;
	virtual bool SetTargetPoint() = 0;
	virtual bool ShowSelectedPackage(const misUID& newPackageUID) = 0;
	virtual void StartPlanFlow() = 0;
	virtual void StopPlanFlow() = 0;
	virtual bool UpdateCroppingDirectionInViewes(const misCroppingDirectionInVR &direction) = 0;
	virtual bool UpdatePackageList() = 0;
	virtual void Render() = 0;
	virtual void SequenceActivated() = 0;
	virtual void SequenceDeactivated() = 0;
	virtual void SetFlowDirection(const misCineDirection &direction) = 0;
	virtual void AddLandmarkToBiopsyPlan(const misLandmarkInfoStruct &lndStr) = 0;
	virtual void UpdateCurrentPackage(const std::shared_ptr<ISimpleDataPackage> currentPackage) = 0;
	virtual void UpdateScrewWidget(const misScrewWidgetData& screwWidgetVal) = 0;
	virtual void SetObliqueFlag(bool isObique) = 0;
	virtual void SelectPlan(const ApproachAndModelInformationStrct& item) = 0;
	virtual void UpdateUITree(std::shared_ptr<ISimpleDataPackage> firstPackage) = 0;
	virtual bool UpdateCompletetreeViewList(const PackageViewingListTypedef& packages) = 0;
	virtual unsigned int GetNumberOfPlanes() = 0;
	virtual void SetObliqueButtonState(bool isActive) = 0;
	virtual bool IsSelectedPlane() = 0;
	virtual misColorStruct GetColorFromSetting(const std::shared_ptr<const ISettingsContainer>& settings,
		const std::string & settingName) = 0;
	virtual misColorStruct GetDefaultPlanColorFormSetting() = 0;
	virtual void UpdatePlanColorInGUI() = 0;
	
};