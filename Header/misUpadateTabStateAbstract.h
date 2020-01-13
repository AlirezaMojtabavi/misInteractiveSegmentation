#pragma once
#include "misGUITypes.h"
#include "misSequenceManager.h"

class misUpadateTabStateAbstract
{
public:
	misUpadateTabStateAbstract(	sequenceListTypdef  sequenceList);

	void UpadateTabStateAbstract();

	~misUpadateTabStateAbstract();
	
	TabAbstractStateListTypdef GetTabAbstractStateList() const;
	void SetTabAbstractStateList(const TabAbstractStateListTypdef& tabAbstractStateList) ;
	sequenceListTypdef SequenceList() const;
	void SequenceList(sequenceListTypdef val);
private:
	
	sequenceListTypdef  m_SequenceList;
	TabAbstractStateListTypdef    m_AllTabsStateAbstract;

};

