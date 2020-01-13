#pragma once
#include "IVisibiltyHolder.h"

MOCK_BASE_CLASS(MockVisibiltyHolder, IVisibiltyHolder)
{
	MOCK_NON_CONST_METHOD(SetVisibilty, 2, void(misPlaneEnum, bool));
	MOCK_NON_CONST_METHOD(GetVisibilty, 1, bool(misPlaneEnum ));

};
