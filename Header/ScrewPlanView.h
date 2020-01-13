#pragma once
#include "IScrewPlanView.h"
#include "IVolumeRenderer.h"
#include "INavigationViewersNView.h"


namespace parcast
{
	class ScrewPlanView :
		public IScrewPlanView
	{
	public:
		ScrewPlanView(std::shared_ptr<INavigationViewersNView> n4View);
		~ScrewPlanView();
		void DeleteAllScrews() final;
		void Lock3DWiewerScrews() final;
		void Lock2DWiewerScrews() final;
		void ResetScrewTransfom() final;
		virtual void FreeImagesScrew(misUID screwUID) final;
		virtual void SetScrewInteractionStyleToFreeLength(misUID screwUID)final;
		virtual void DeleteScrew(misUID screwUID)final;
		virtual void ShowScrew(misUID screwUID)final;
		virtual void SetScrewColor(misUID screwUID, misColorStruct color);
		virtual void HighlightScrew(misUID screwUID, bool highight);
		void SetScrewWidth(misUID screwUID, double width) final;
		virtual void LockAllScrews()final;
		void LockScrews(misUID screwUID)final;
		void UnLockScrew(misUID screwUID) final;
	private:

		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	};

}
