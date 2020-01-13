#pragma once
#include "misTypes.h"
#include "misColorStruct.h"
namespace parcast
{

	class IScrewPlanView
	{
	public:

		virtual void FreeImagesScrew(misUID screwUID) = 0;
		virtual void LockScrews(misUID screwUID) = 0;
		virtual void UnLockScrew(misUID screwUID) = 0;
		virtual void SetScrewInteractionStyleToFreeLength(misUID screwUID) = 0;
		virtual void DeleteScrew(misUID screwUID) = 0;
		virtual void ShowScrew(misUID screwUID) = 0;
		virtual void HighlightScrew(misUID screwUID, bool highight) = 0;
		virtual void DeleteAllScrews() = 0;
		virtual void Lock3DWiewerScrews() = 0;
		virtual void Lock2DWiewerScrews() = 0;
		virtual void ResetScrewTransfom() = 0;
		virtual void SetScrewColor(misUID screwUID, misColorStruct color) = 0;
		virtual void SetScrewWidth(misUID screwUID, double width) = 0;
		virtual void LockAllScrews() = 0;
	};

}
