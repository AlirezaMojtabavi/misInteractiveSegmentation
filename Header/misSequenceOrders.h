#pragma once

#include "SubSeqNameStr.h"
#include "misAppControlMacroes.h"
#include "misTabAndSubTabName.h"

class  misSequenceOrders
{
	typedef std::map<SubSeqNameStr,sequenceNameListTypdef>   SequenceOrderMapTypdef;
	typedef std::map<SubSeqNameStr,SubSeqNameStr>            BeforeNextMapTypdef;

     SequenceOrderMapTypdef  m_NextActivatedMap;
	 SequenceOrderMapTypdef  m_NextInActivatedMap;

	 BeforeNextMapTypdef     m_BeforNextSubSeqsMap;    // to illustrated the next and back sub sequence  

	 SubSeqNameStr m_HomeSB;
	 SubSeqNameStr m_DataUPSB;
	 SubSeqNameStr m_DataCHSB;
	 SubSeqNameStr m_DataCORSB;
	 SubSeqNameStr m_SegmSB;
	 SubSeqNameStr m_CompSB;
	 SubSeqNameStr m_BiopSB;
	 SubSeqNameStr m_TrackingSB;
	 SubSeqNameStr m_RegLanSelSB;
	 SubSeqNameStr m_LanRegSB;
	 SubSeqNameStr m_NavSB;
 
	 misTabAndSubTabName*  m_TabAndSubTabName;

	 void InitializeSubSeqName(void);
///////////////////////////////////////////////////////////////////////
	 void InitializeNextActivatedMap(void);
	 void HomeNextActivatedMap(void);
	 void DataManipulationNextActivatedMap(void);
	 void AnalysisNextActivatedMap(void);
	 void PlanningNextActivatedMap(void);
	 void TrackingNextActivatedMap(void);
	 void RegistrationNextActivatedMap(void);
	 void NavigationNextActivatedMap(void);
///////////////////////////////////////////////////////////////////
	 void InitializeNextInActivatedMap(void);
	 void HomeNextInActivatedMap(void);
	 void DataManipulationInNextActivatedMap(void);
	 void AnalysisNextInActivatedMap(void);
	 void PlanningNextInActivatedMap(void);
	 void TrackingNextInActivatedMap(void);
	 void RegistrationNextInActivatedMap(void);
	 void NavigationNextInActivatedMap(void);


public:

	SubSeqNameStr GetBeforeSubSequence(std::string TabName, std::string SubTabName);
	SubSeqNameStr GetBeforeSubSequence(SubSeqNameStr subSequenceName);

	SubSeqNameStr GetNextSubSequence(std::string TabName, std::string SubTabName);
	SubSeqNameStr GetNextSubSequence(SubSeqNameStr subSequenceName);

	sequenceNameListTypdef GetNextSubSeqMustBeActive(std::string readyForLeaveTabName, std::string readyForLeaveSubTabName);
	sequenceNameListTypdef GetNextSubSeqMustBeActive(SubSeqNameStr readyForLeaveName);

	sequenceNameListTypdef GetNextSubSeqMustBeInActive(std::string readyForLeaveTabName, std::string readyForLeaveSubTabName);
	sequenceNameListTypdef GetNextSubSeqMustBeInActive(SubSeqNameStr readyForLeaveName);

	misSequenceOrders(void);
	~misSequenceOrders(void);
};
