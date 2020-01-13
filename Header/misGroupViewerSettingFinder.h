#pragma once

#include "misGroupViewer.h"
#include "misGroupViewerSetting.h"
#include "IGroupViewerSettingFinder.h"


class misGroupViewerSettingFinder : public IGroupViewerSettingFinder
{
public :
	 std::shared_ptr<IGroupViewerSetting> MakePckageGroupViewer(std::string subTabName) override;

private:
	 std::shared_ptr<IGroupViewerSetting> CreateDataChecking();
	 std::shared_ptr<IGroupViewerSetting> CreateDataUploading();
	 std::shared_ptr<IGroupViewerSetting> CreateDentalImplantPlanning();
	 std::shared_ptr<IGroupViewerSetting> CreateImageCorrelation();
	 std::shared_ptr<IGroupViewerSetting> CreateScrewPlanning();
	 std::shared_ptr<IGroupViewerSetting> CreateDentalImplantNavigation();
	 std::shared_ptr<IGroupViewerSetting> CreateSpineNavigation();
	 std::shared_ptr<IGroupViewerSetting> CreateENTBraineNavigation();
	 std::shared_ptr<IGroupViewerSetting> CreateCMFNavigation() const;
	 void CreateTestXnX(std::shared_ptr<IGroupViewerSetting> viewerLayout);
	 void CreateTestConfig(std::shared_ptr<IGroupViewerSetting> viewerLayout );
	 std::shared_ptr<IGroupViewerSetting> CreateBiopsyNavigation();
};
