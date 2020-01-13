#pragma once

#include "misColorStruct.h"
#include "misPolyData.h"
#include "misStringTools.h"

struct misCompeletePolyDataDependensiesStrct 
{
public:
	// these two items fill automatically recursively
	std::string                          name;
	misColorStruct                  color;

	// these two items update automatically
	misPolyData*                    objectPointer;

	double                          opacity;
	misUID                          objectUID;
	misUID                          parentImageUID;

	bool							Visibility;
	misCompeletePolyDataDependensiesStrct(void);
};
typedef  std::vector<misCompeletePolyDataDependensiesStrct>					  PolyDataDependencyListTypes;