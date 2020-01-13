#pragma once
#include "misSequenceManager.h"
#include "igstkMacros.h"
#include "misBiopsyRobotManager.h"
class misBiopsyRobotProcedure : public misSequenceManager
{
private:
		misBiopsyRobotManager::Pointer    m_BiopsyRobotSubSequence;
public:
	igstkStandardClassBasicTraitsMacro( misBiopsyRobotProcedure, misSequenceManager );
	igstkNewMacro( Self ); 
	misBiopsyRobotProcedure(void);
	~misBiopsyRobotProcedure(void);
	virtual void Initialize(misStrctTabModel   dataTab,itk::Command* pCommand);
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();
};

