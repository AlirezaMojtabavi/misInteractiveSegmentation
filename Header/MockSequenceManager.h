#pragma once

#include "ISequenceManager.h"

MOCK_BASE_CLASS(MockSequenceManager, ISequenceManager)
{
	MOCK_NON_CONST_METHOD(SetMuteKe, 1, void(std::string ));
	MOCK_NON_CONST_METHOD(GetTabName, 0, std::string(void));
	MOCK_NON_CONST_METHOD(SetLastActivatedSubTabName, 1, void(std::string ));
	MOCK_NON_CONST_METHOD(GetLastActivatedSubTabName, 0 , std::string  (void) , identifier_1);
	MOCK_NON_CONST_METHOD(GetNumberOfSubSequences, 0, int(void));
	MOCK_NON_CONST_METHOD(GetSubSequence, 1, std::shared_ptr<misSubSequence>(int ), identifier_2);
	MOCK_NON_CONST_METHOD(GetSubSequence, 1, std::shared_ptr<misSubSequence>(std::string), identifier_3);
	MOCK_NON_CONST_METHOD(GetActivatedSubTabName, 0,  bool (void) );
	MOCK_NON_CONST_METHOD(GetGuiConvertorList, 0, misGUIEventConvertor*());
	MOCK_NON_CONST_METHOD(RequestSelectSubTab, 1, bool(std::string subTabName));
	MOCK_NON_CONST_METHOD(RequestDeselectAll, 0, void(void));
	MOCK_NON_CONST_METHOD(RequestAcitvateSubTab, 1, bool(std::string subTabName));
	MOCK_NON_CONST_METHOD(RequestDeAcitvateAll, 0, void(void));
	MOCK_NON_CONST_METHOD(GetSelectionStatus, 0, bool(void));
	MOCK_NON_CONST_METHOD(GetActivationStatus, 0, bool(void));
	MOCK_NON_CONST_METHOD(GetSelectedSubTabName, 0, bool(void));
	MOCK_NON_CONST_METHOD(GetTabState, 0, TabAbstractState(void));
	MOCK_NON_CONST_METHOD(UpdateCurrentSelectedSubSequenseState, 0, void(void));
	MOCK_NON_CONST_METHOD(GetCurrentSelectedSubSequenseState, 0, CurrentSubSequenseStateStrct(void));
	MOCK_NON_CONST_METHOD(AddCommand, 1, void(itk::Command*));
	MOCK_NON_CONST_METHOD(ProcessRequest, 1, bool(misGUIEvent* ));
	MOCK_NON_CONST_METHOD(UpdateStatus, 1, void(long long int puls));
	MOCK_NON_CONST_METHOD(SetLogger, 1, void(misLogger*));
	MOCK_NON_CONST_METHOD(Reset, 0, void(void));
	MOCK_NON_CONST_METHOD(UpdateSettingFromAppSetting, 0, void(void));
	MOCK_NON_CONST_METHOD(AddViewer, 1, void(void *));
	MOCK_CONST_METHOD(GetCSCorrelationManager, 0, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >());
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > ));
	MOCK_NON_CONST_METHOD(SetDataBaseManager, 1, void(std::shared_ptr<IDataBaseManager> ));
	MOCK_NON_CONST_METHOD(AddObserver, 2, unsigned long (const itk::EventObject & , itk::Command*) );
	MOCK_NON_CONST_METHOD(InvokeEvent, 1,  void (const itk::EventObject& ) );
	MOCK_CONST_METHOD(HasObserver, 1,  bool (const itk::EventObject& ) );
};
