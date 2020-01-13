#pragma once

class misGUIEventConvertor;
class misTabAndSubTabName;
class misSubSequence;
class misGUIEvent;
class IDataBaseManager;

template < typename CST >
class ICoordinateSystemCorrelationManager;

struct CurrentSubSequenseStateStrct;
struct TabAbstractState;

class  ISequenceManager
{
public:
	virtual ~ISequenceManager() = default;
	virtual void SetMuteKe(std::string RK) = 0;
	virtual std::string  GetTabName() = 0;
	virtual void  SetLastActivatedSubTabName(std::string lastActivatedSubTabName) = 0;
	virtual std::string  GetLastActivatedSubTabName() = 0;
	virtual int GetNumberOfSubSequences() = 0;
	virtual std::shared_ptr<misSubSequence> GetSubSequence(int subsequenceID) = 0;
	virtual std::shared_ptr<misSubSequence> GetSubSequence(std::string subsequenceName) = 0;
	virtual misGUIEventConvertor*  GetGuiConvertorList() = 0;
	virtual bool RequestSelectSubTab(std::string subTabName) = 0;
	virtual void RequestDeselectAll() = 0;
	virtual bool RequestAcitvateSubTab(std::string subTabName) = 0;
	virtual void RequestDeAcitvateAll() = 0;
	virtual bool GetSelectionStatus() = 0;
	virtual bool GetActivationStatus() = 0;
	virtual bool GetSelectedSubTabName() = 0;
	virtual bool GetActivatedSubTabName() = 0;
	virtual TabAbstractState GetTabState() = 0;
	virtual void UpdateCurrentSelectedSubSequenseState() = 0;
	virtual CurrentSubSequenseStateStrct   GetCurrentSelectedSubSequenseState() = 0;
	virtual void AddCommand(itk::Command* pCommand) = 0;
	virtual bool ProcessRequest(misGUIEvent* pEvent) = 0;
	virtual void UpdateStatus(long long int puls) = 0;
	virtual void Reset() = 0;
	virtual void UpdateSettingFromAppSetting() = 0;
	virtual void AddViewer(void *pViwer) = 0;
	virtual void SetDataBaseManager(std::shared_ptr<IDataBaseManager> val) = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
};
typedef std::vector<std::shared_ptr<ISequenceManager>>   sequenceListTypdef;
