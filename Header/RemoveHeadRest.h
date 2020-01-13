#pragma once
#include "IRemoveHeadRest.h"
#include <IImage.h>
#include "ICreateSkinFilledVolume.h"
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"
#include "misRemoveHeadRestAlgoritm.h"
#include "IScrewPlanView.h"
#include "IApplySubSegStatesEventToGUI.h"

namespace  parcast
{
	class RemoveHeadRest : public IRemoveHeadRest
	{
	public:
		RemoveHeadRest(std::shared_ptr<INavigationViewersNView>, 
			std::shared_ptr<parcast::IScrewPlanView>, std::shared_ptr<IApplySubSegStatesEventToGUI> , 
			itk::Object::Pointer parent);
		void SetNormalizedHeadRestVolumeThreshold(double normThreshold) final;
		void SetRemoveHeadRestState() final;
		void CreateTemporaryPackage();
		bool ApplyRemoveHeadRest() override;
		void InvokeEvent(const misEvent& evOpen);
		void ResetHeadRest(misImageStatus& iamStatus) override;
		void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> package) final;
		void SeedUpdateInRemoveHeadRest() final; 
	private:

		std::shared_ptr<ICreateSkinFilledVolume> m_CreateSkinFilled;
		std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
		std::shared_ptr<ISimpleDataPackage> m_TemporaryPackage;
 		std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
		std::shared_ptr<IApplySubSegStatesEventToGUI>  m_ApplySubSegStatesEventToGUI;
		std::unique_ptr<misRemoveHeadRestAlgoritm> m_HeadRest;
		template <class EventType, typename PayloadType>
		void InvokeLoadedEvent(const PayloadType& payload) const;
				template <class EventType>
		void InvokeUnloadedEvent() const;

		itk::Object::Pointer m_Parent;	
		std::string m_SubsequenceName;
		std::string m_SequenceName;

	};

}
