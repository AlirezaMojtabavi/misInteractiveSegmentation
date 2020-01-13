#pragma once

#include "ApproachAndModelInformationStrct.h"
#include "misDataSetManager.h"
#include "misGuiEvent.h"
#include "misSimpleDataPackage.h"
#include "IVisibilityMangement.h"

class INavigationViewersNView;



namespace parcast
{
	class VisibilityManagement : public IVisibilityMangement
	{
	public:

		VisibilityManagement(std::shared_ptr<ISimpleDataPackage> package,
			std::weak_ptr<INavigationViewersNView> groupViewer, std::shared_ptr<IVisibilityMangement> planVisibilityManagement);
		void SetVisibility(const ApproachAndModelVisibilityInformation&) override;
		void SetVisibility2D(const ApproachAndModelVisibilityInformation&) override;
		void SetVisibility3D(const ApproachAndModelVisibilityInformation&) override;

	private:
		void SetVisibilityofDimension(ApproachAndModelInformationStrct selectedObjectInformation, misPresentationDimension presentationDim, bool visibility);
		std::weak_ptr<ISimpleDataPackage> m_Package;
		std::weak_ptr<INavigationViewersNView> m_GroupViewer;
		std::shared_ptr<IVisibilityMangement> m_PlanVisibilityManagement;
	};
}


