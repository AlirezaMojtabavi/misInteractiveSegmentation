#pragma once
#include "IScrewPlanView.h"
MOCK_BASE_CLASS(MockScrewPlanView, IScrewPlanView)
{
	MOCK_NON_CONST_METHOD(LockAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(FreeImagesScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(LockScrews, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(SetScrewInteractionStyleToFreeLength, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(DeleteScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(ShowScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(HighlightScrew, 2, void(misUID screwUID, bool highight));
	MOCK_NON_CONST_METHOD(DeleteAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(Lock3DWiewerScrews, 0, void());
	MOCK_NON_CONST_METHOD(Lock2DWiewerScrews, 0, void());
	MOCK_NON_CONST_METHOD(ResetScrewTransfom, 0, void());
	MOCK_NON_CONST_METHOD(SetScrewColor, 2, void(misUID screwUID, misColorStruct color));
	MOCK_NON_CONST_METHOD(UnLockScrew, 1, void(misUID));
	MOCK_NON_CONST_METHOD(SetScrewWidth, 2, void(misUID, double));


};
