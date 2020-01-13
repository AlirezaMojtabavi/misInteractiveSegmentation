#pragma once
class ISequenceManager;
class ITabAndSubTabActicationControl
{
public:
	virtual void PushBackNewSequence(std::shared_ptr<ISequenceManager> pSequnce) = 0;
	virtual void UpdateSequenceActivationState(void) = 0;
	virtual void UpdateSettingFromAppSetting(void) = 0;
	~ITabAndSubTabActicationControl(){}
};
