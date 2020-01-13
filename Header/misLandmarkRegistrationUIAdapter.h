#pragma once
#include "ILandmarkRegistrationUIAdapter.h"
#include "ProjectConfig\misSubSequenseGeneralStateEnums.h"
#include "ProjectConfig\misResultMessageEnums.h"
#include "misGUITypes.h"

class misLandmarkRegistrationUIAdapter :	public ILandmarkRegistrationUIAdapter
{
public:
	misLandmarkRegistrationUIAdapter(std::string sequenceName,
		std::string subsequenceName);
	~misLandmarkRegistrationUIAdapter() = default;
	void UpdateGUI(std::vector<mislandMarkPosAndStatusStr> movables,
		bool lastMustBeSelected,
		int currentSelectedLandmarkIndex, bool subTabCompleteness,
		subSequenseGeneralStateEnums trackingState) override;
	void UpdateLandmarkErrorListInGUI(std::vector<mislandMarkPosAndStatusStr>& landmarks,
		bool m_LastMustBeSelected, int m_CurrentSelectedLandmarkIndex) override;
	void UpdateLandRegState(bool subTabCompleteness,
		subSequenseGeneralStateEnums trackingState);
	void SetSubSequenseStatusToCompletedTask(void); 
	void SetSubSequenseStatusToInitlaize(void);
	void SetSubSequenseStatusToUnderGoingTask(std::string state, misResultMessageEnums resultType, std::string resultDescrpition);
 	void SetParentInvoker(itk::Object::Pointer val);
private:
	
	itk::Object::Pointer m_ParentInvoker;
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnloadedEvent();
	void SendUpdateGUIStateToGUI(void);

	stringListTypdef m_AllStatesList;
	CurrentSubSequenseStateStrct m_CurrentSubSequenseState;
	std::string m_SequenceName;
	std::string m_SubsequenceName;
};

