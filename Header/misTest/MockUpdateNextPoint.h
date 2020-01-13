#pragma once
#include "IUpdateNextPoint.h"
MOCK_BASE_CLASS(MockUpdateNextPoint, IUpdateNextPoint)
{
 	MOCK_NON_CONST_METHOD(Update, 3,  int (int& , misLandmarkType ,bool& ) );

};
