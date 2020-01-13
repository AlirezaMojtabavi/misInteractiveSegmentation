#pragma once
#include "misSequenceManager.h"
#include "SubSeqNameStr.h"
 #include "misUpadateTabStateAbstract.h"
#include "misUpdateMainMenuInGUI.h"
#include "misSolutionControlGuiAdapter.h"
#include "IPulsDistributer.h"

class misSequenceChanger
{
public:
	misSequenceChanger(sequenceListTypdef  sequenceList,misTabAndSubTabName*  tabAndSubTabName, 
		std::shared_ptr<misSolutionControlGuiAdapter> solutionUiAdapter);

	 bool SwitchTab(const std::string& sequenceName, const std::string& subsequnecName, 
		 const SubSeqNameStr& newSelectedName, TabAbstractStateListTypdef states);
	 bool RequestSelectSubSequence(SubSeqNameStr newSelectedName, TabAbstractStateListTypdef states);

	~misSequenceChanger();
 
	sequenceListTypdef SequenceList() const;
	void SequenceList(sequenceListTypdef val);

private:
	sequenceListTypdef  m_SequenceList;
	misTabAndSubTabName*  m_TabAndSubTabName;
	std::shared_ptr<misSolutionControlGuiAdapter> m_SolutionUiAdapter;
	SubSeqNameStr m_LastActivatedSubTab;
	SubSeqNameStr m_PreviousActivatedSubTab;
	CurrentSubSequenseStateStrct  m_CurrentSelectedSubSequence;

};

