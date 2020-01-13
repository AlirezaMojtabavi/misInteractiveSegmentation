#pragma once

#include "misColorStruct.h"
#include "misDistributionStruct.h"
#include "misGuiStructures.h"
#include "misPlanSTRCT.h"
#include "misStringTools.h"
#include "misVertebraEnum.h"
#include "misDataProdecureEnum.h"
#include "INavigationViewersNView.h"

// The IPlanningHelper is the abstract interface to the business logic regarding the planning process. This involves (possibly) 
// interactive adding, removing, modifying plans and their characteristics. This interface has been extracted from the 
// planning subsequence to serve as a general logic for planning regardless of the application type (Spine, ENT, biopsy ...)
class IPlanningHelper
{
public:

	virtual bool SelectApproachAndModelItem(const ApproachAndModelInformationStrct& item) = 0;
	virtual void SelectApproachAndModelItem(misUID planId) = 0;
	virtual bool SelectApproachAndModelSettings(const ApproachAndModelInformationStrct& item) = 0;
	virtual void Render() = 0;
	virtual void SequenceActivated() = 0;
	virtual void SequenceDeactivated() = 0;
	virtual void AddPlanPoint(const misLandmarkInfoStruct& lndStr) = 0;
	virtual bool UpdatePackageList(const PackageViewingListTypedef&) = 0;
	virtual bool UpdateCompletetreeViewList(const PackageViewingListTypedef&) = 0;
	virtual void ClearCompletetreeViewList() = 0;
	virtual bool ShowSelectedPackage(const misUID& newPackageUID) = 0;
	virtual bool SetScrewSourceType(ScrewWidgetSourceType widgetSrcType) = 0;
	virtual void CreateScrew() = 0;
	virtual bool SetStartPointState() = 0;
	virtual bool SetEndPointState() = 0;
	virtual bool DeleteEndPoint() = 0;
	virtual bool DeleteStartPoint() = 0;
	virtual bool ModifyStartPoint() = 0;
	virtual bool ModifyEndPoint() = 0;
	virtual bool SetScrewInteractionStyleToFree() = 0;
	virtual bool SetScrewInteractionStyleToFreeLength() = 0;
	virtual void SetObliqueObserver(std::weak_ptr<INavigationViewersNView::IObliqueChanged> observer) = 0;
	virtual bool UpdateScrewColor(const misColorStruct& newColour) = 0;
	virtual void AcceptPlan(const ScrewPlanInformation& planInfo, std::shared_ptr<ISimpleDataPackage> package) = 0;
	virtual bool DeleteCurrentPlan() = 0;
	virtual bool UpdateScrewWidth( double screwWidth ) = 0;
	virtual void UpdateScrewWidget( const misScrewWidgetData& screwWidgetVal ) = 0;
	virtual bool UpdateItemSelections(const ImageInformationStrct& clickedItem) = 0;
	virtual bool IsInModifyingMode() const = 0;
	virtual std::weak_ptr<parcast::IPlan> GetCurrentlySelectedPlan() const = 0;
	virtual ~IPlanningHelper() {};
};