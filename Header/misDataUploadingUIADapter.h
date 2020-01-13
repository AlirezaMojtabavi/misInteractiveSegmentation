#pragma once
#include "IDataUploadingUIADapter.h"

class misDataUploadingUIADapter :public IDataUploadingUIADapter
{
public:
	misDataUploadingUIADapter(itk::Object::Pointer parent);
 	virtual void UpdateDicomPropertiesEvent(const misDicomDataViewingProperties& viewingProp) override;
	virtual void LoadedDicomListEventCore(ImageViewingListTypedef imageList) override;
 	void UpdateThreshold(const misSliderStrc& sliderRange) const override;

private:
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload) const;

	template <class EventType>
	void InvokeUnloadedEvent() const;
private:
	std::string m_SequenceName;
	std::string m_SubsequenceName;
	itk::Object::Pointer m_Parent;
};

