#pragma once

#include "misAppControlMacroes.h"
#include "misSeconderyNeededHeader.h"
#include "ISequenceManager.h"
#include "misSequenceManager.h"
#include "ITabAndSubTabActicationControl.h"

class ISequenceManager;
class misDatasetManager;
class misTabAndSubTabName;


class  misTabAndSubTabActicationControl :public ITabAndSubTabActicationControl
{
public:
	misTabAndSubTabActicationControl();
 	void PushBackNewSequence(std::shared_ptr<ISequenceManager> pSequnce ) override;
	void UpdateSequenceActivationState(void) override;
	void UpdateSettingFromAppSetting( void ) override;

protected:

	bool                          m_CheckSubSeqActivation;
	sequenceListTypdef            m_SequenceList;
	misDatasetManager*            m_DatasetManger;

	std::shared_ptr<ISequenceManager>   m_TabHome;
	std::shared_ptr<misSubSequence>       m_Home;

	std::shared_ptr<ISequenceManager>   m_TabDataMan;
	std::shared_ptr<misSubSequence>       m_DataChecking;
	std::shared_ptr<misSubSequence>       m_DataUploading;
	std::shared_ptr<misSubSequence>       m_Correlation;

	std::shared_ptr<ISequenceManager>   m_TabCreate3D;
	std::shared_ptr<misSubSequence>       m_Segmentation;
	std::shared_ptr<misSubSequence>       m_Composite;

	std::shared_ptr<ISequenceManager>   m_TabPlan;
	std::shared_ptr<misSubSequence>       m_Planning;

	std::shared_ptr<ISequenceManager>   m_TabReg;
	std::shared_ptr<misSubSequence>       m_landSelction;
	std::shared_ptr<misSubSequence>       m_landRegistration;
	std::shared_ptr<misSubSequence>       m_SurfRegistration;
	std::shared_ptr<ISequenceManager>   m_TabTacking;
	std::shared_ptr<misSubSequence>       m_Tracking;
	std::shared_ptr<ISequenceManager>   m_TabNav;
	std::shared_ptr<misSubSequence>       m_Navigation;
	std::shared_ptr<ISequenceManager>   m_TabSnapShot;
	std::shared_ptr<misSubSequence>       m_SnapShot;
	misTabAndSubTabName*           m_SubsequenceName;
	std::shared_ptr<misSubSequence>  GetSubSequece(std::string subSequenceName);

	void DeActiveAll(void);
	void UpdateSequencePointers();
	void Active_Analysis_Plan_landmaekSelection(void);
	void Active_Correlation_Composite(void);
	void Check_Registaration_Navigation(void);
private:
};