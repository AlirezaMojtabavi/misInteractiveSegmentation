#pragma once
#include "IBiopsyPlanningUIUpdater.h"
#include "misMultiViewSubSequence.h"

class misBiopsyPlanningUIUpdater :public IBiopsyPlanningUIUpdater
{
public:
	misBiopsyPlanningUIUpdater(misMultiViewSubSequence* observingSubsequence);

	void ChangeStatus(const std::string& statusString) override;
	void ClearPackageList() override;
	void Deactivated() override;
	void RefreshGUI() override;
	void SendLastPointInfo(double value) override;
	void SetPlanFlowEndDirection(const misCineDirection &direction) override;
	void UpdataCroppingDirectionInGUI(misCroppingDirectionInVR croppingDirection) override;
	void UpdateCompletetreeViewList(const PackageViewingListTypedef& packageList) override;
	void ClearCompletetreeViewList() override;
	void UpdatePackageList(const PackageViewingListTypedef& packageList) override;
	void UpdatePlanPropertyIndicatorValue(const misShort3DModelViewingStrct& indicatorVal) override;
	void UpdateZoomPercentage(int pZoomPercentage, double pZoomProportion) const override;
	void UpdatePlanColor(const misColorStruct& planColor) override;
 private:
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnLoadedEvent();

	std::string m_SequenceName, m_SubTabName;
	misMultiViewSubSequence* m_ObservingSubseq;
};