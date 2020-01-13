#pragma once
#include "IVisibilityMangement.h"
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"

namespace parcast
{
	class PlanVisibilityManagement :
		public IVisibilityMangement
	{
	public:
		PlanVisibilityManagement(std::shared_ptr<ISimpleDataPackage> package,
			std::weak_ptr<INavigationViewersNView> groupViewer);
		void SetVisibility(const ApproachAndModelVisibilityInformation&) override;
		void SetVisibility2D(const ApproachAndModelVisibilityInformation&) override;
		void SetVisibility3D(const ApproachAndModelVisibilityInformation&) override;

	private:
		void SetVisibilityofDimension(ApproachAndModelInformationStrct selectedObjectInformation, misPresentationDimension presentationDim, bool visibility);
		std::weak_ptr<ISimpleDataPackage> m_Package;
		std::weak_ptr<INavigationViewersNView> m_GroupViewer;

	};

}
