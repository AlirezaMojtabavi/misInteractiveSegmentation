#pragma once

#include "misResultMessageEnums.h"
#include "misSubSequenseGeneralStateEnums.h"
#include "subTabAbstractState.h"

typedef std::vector<std::string>  stringListTypdef;



struct TabAbstractState
{
	std::string   TabName;
	std::string   LastActicatedSubTabName;
	bool Selected = false;
	bool Activated = false;
	subTabAbstractStateListTypdef  SubTabStatus;
};

typedef std::vector<TabAbstractState> TabAbstractStateListTypdef;

struct misSubTabNameStrct
{
	std::string TabName;
	std::string SubTabName;
};
