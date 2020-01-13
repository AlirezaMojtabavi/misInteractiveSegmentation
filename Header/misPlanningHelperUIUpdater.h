#pragma once

#include "misMultiViewSubSequence.h"
#include "IPlanningHelperUIUpdater.h"

class misPlanningHelperUIUpdater : public IPlanningHelperUIUpdater
{
public:
	misPlanningHelperUIUpdater(misMultiViewSubSequence* observingSubsequence);

	void ChangeStatus(const std::string& statusString) override;
	void Deactivated() override;
	void UpdateImageAnd3DModelProperties( const misImageAnd3DModelPropertiesSettingStrct& currentProp ) override;
	void UpdatePlanPropertyIndicatorValue( const ScrewPlanPropertyIndicator& indicatorVal ) override;
	void UpdateCompletetreeViewList(const PackageViewingListTypedef& packageList) override;
	void ClearCompletetreeViewList() override;
	void UpdatePackageList(const PackageViewingListTypedef& packageList) override;
	void ClearPackageList() override;

	void UpdateZoomPercentage(int percentage , double proportion) override;
	void UpdateCutDirectionButtons(misCroppingDirectionInVR croppingDirection) override;

private:
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnLoadedEvent();

	std::string m_SequenceName, m_SubTabName;
	misMultiViewSubSequence* m_ObservingSubseq;
};
