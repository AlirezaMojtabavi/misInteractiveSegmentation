#pragma once

#include "IVisibilityMangement.h"

MOCK_BASE_CLASS(MockVisibilityMangement, IVisibilityMangement)
{
	MOCK_NON_CONST_METHOD(SetVisibility, 1, void(const ApproachAndModelVisibilityInformation& pEvent));
	MOCK_NON_CONST_METHOD(SetVisibility2D, 1, void(const ApproachAndModelVisibilityInformation& pEvent));
	MOCK_NON_CONST_METHOD(SetVisibility3D, 1, void(const ApproachAndModelVisibilityInformation& pEvent));
};
