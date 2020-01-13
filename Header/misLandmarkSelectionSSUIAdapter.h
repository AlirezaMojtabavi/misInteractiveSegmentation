#pragma once
#include "ILandmarkSelectionSSUIAdapter.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"

class misLandmarkSelectionSSUIAdapter : public ILandmarkSelectionSSUIAdapter
{
public:
	misLandmarkSelectionSSUIAdapter();
	void UpdateThresholdSlider(double normalizedValue, misObjectRangeStr foundRange) override;
	void SetParent(itk::Object::Pointer parent);
	void SaveSoloution() override;
	void BackToPanStateEventCore() override;
	void SendVolumeTypeEvent(misVolumeViewingTypes) override;
	void SendImageModalityEvent(misImageDataModality modality) override;
	 void RegistrationLandmarkSelectionIDChanged(unsigned int landmarkIndex) override;
private:

	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnloadedEvent();



	std::string m_SequenceName;
	std::string m_SubsequenceName;
	itk::Object::Pointer m_Parent;
};

