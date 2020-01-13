#include "stdafx.h"
#include "PlanVisibilityManagement.h"
#include "MockNavigationViewersNView.h"
#include "MockSimpleDataPackage.h"
#include "misEventFromGui.h"
#include "MockPlanRepo.h"
#include <MockPackagePlanRel.h>
#include "MockDentalPlan.h"
#include "MockPackageDataRenderingAdapter.h"

using namespace parcast;

struct PlanVisibilityManagementTestFixture
{
	PlanVisibilityManagementTestFixture()
	{
		PlanVisibilityMgmt = std::make_shared<parcast::PlanVisibilityManagement>(PackageData, GroupVwr);
		ObjectProperties.packegeUID = "testPackageUid";
		ObjectProperties.objectUID = "testObjectUid";

	}
	std::shared_ptr<PlanVisibilityManagement> PlanVisibilityMgmt;
	std::shared_ptr<MockNavigationViewersNView> GroupVwr = std::make_shared<MockNavigationViewersNView>();
	std::shared_ptr<MockSimpleDataPackage> PackageData = std::make_shared<MockSimpleDataPackage>();
	std::shared_ptr<MockDentalPlan> DentalPlan = std::make_shared<MockDentalPlan>();
	std::shared_ptr<MockPackageDataRenderingAdapter> sliceViewer = std::make_shared<MockPackageDataRenderingAdapter>();
	ApproachAndModelVisibilityInformation VisibilityInfo;
	ApproachAndModelInformationStrct ObjectProperties;
};

BOOST_FIXTURE_TEST_SUITE(PlanVisibilityManagementSuite, PlanVisibilityManagementTestFixture)

BOOST_AUTO_TEST_CASE(construction)
{
}
BOOST_AUTO_TEST_CASE(GivenEventWithObjectContainerUid_WhenSetVisibilityIsCalled_ThenPlanVisibilityMustBeCalled)
{
	ObjectProperties.objectContainerUID = "objectContainerUid";
	ObjectProperties.objectUID = "123";
	VisibilityInfo.visibility = false;
	VisibilityInfo.objectInformation = ObjectProperties;
	//typedef  std::vector<std::shared_ptr<parcast::IPackagePlanRel>> PlanDataListDependencyTypedef;
	auto plan = std::make_shared<MockPackagePlanRel>();
	const auto plans = std::make_shared< PlanDataListDependencyTypedef >();
	plans->push_back(plan);
	MOCK_EXPECT(PackageData->GetPlanDataDependencies).returns(plans);
	std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> viewers;
	viewers.push_back(sliceViewer);
	MOCK_EXPECT(DentalPlan->GetUID).returns("123");
	MOCK_EXPECT(plan->GetPlanEntity).returns(DentalPlan);
	MOCK_EXPECT(GroupVwr->GetAllPackageViewers).returns(viewers);
	mis3DModelObjectOpacityPropertiesStrct visibilty;
	MOCK_EXPECT(plan->GetVisibility).returns(visibilty);
	mis3DModelObjectOpacityPropertiesStrct expectedVisibility;
	expectedVisibility.visibilityIn2DScene = false;
	MOCK_EXPECT(plan->SetVisibility).with(expectedVisibility);
	MOCK_EXPECT(GroupVwr->Render);
	PlanVisibilityMgmt->SetVisibility(VisibilityInfo);
}
BOOST_AUTO_TEST_SUITE_END()