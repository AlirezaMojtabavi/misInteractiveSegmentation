#include "stdafx.h"
#include "misPackageViewingExtractor.h"
#include "misCompeleteImageContainedPolydataDependensiesStrct.h"
#include "misCompeleteImageDependensies.h"
#include "misCompeletePolyDataDependensiesStrct.h"
#include "misVolumeDataDependensies.h"
#include "misVolumeData.h"
#include "misStrctVolumeData.h"
#include "IPackagePlanRel.h"
#include "IPlan.h"


misPackageViewingExtractor::misPackageViewingExtractor(std::shared_ptr<const ISimpleDataPackage> packge,
	std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo) :
	m_Packge(packge),
	m_PackagePlanRelRepo(planRepo)
	 
{
	Update();
}

inline void misPackageViewingExtractor::Update()
{
	auto package = m_Packge.lock();
	if (!package)
		return;
	m_PackageViweingStrct.name = package->GetName();
	m_PackageViweingStrct.packegeUID = package->GetObjectUID();
	m_PackageViweingStrct.packageType = package->GetObjectType();
	UpdateImageViewingParts();
	m_PackageViweingStrct.polyaDataProperties.clear();
	UpdateImageContainedPolyDataParts();
	UpdateVolumeViewingParts();
	m_PackageViweingStrct.planningDataProperties.clear();
	UpdatePlansViewingParts();
	
}
 



void misPackageViewingExtractor::UpdateImageViewingParts()
{
	auto package = m_Packge.lock();
	if (!package)
		return;

	m_PackageViweingStrct.imageProperties.clear();
	auto images = package->GetImageDataDependencies();
	for (auto imageDependency : images)
	{
		misShortImageViewingStrct imageViewingProp;
		misCompeleteImageDependencies internalImageDependensies;
		imageViewingProp.name = imageDependency->GetName();
		imageViewingProp.objectUID = imageDependency->GetObjectUID();
		imageViewingProp.visibility = imageDependency->GetVisibility();
		imageViewingProp.opacity = imageDependency->GetOpacity();
		m_PackageViweingStrct.imageProperties.push_back(imageViewingProp);
	}
}



void misPackageViewingExtractor::UpdateImageContainedPolyDataParts()
{
 
	if(auto package = m_Packge.lock())
	{
		auto imageCOntaineds = package->GetImageContainedPolydataDependencies();
	for (const auto  containedDepndencies : imageCOntaineds)
	{
		auto polyViewingList = containedDepndencies->GetPolydataStrcViewing();
		for (auto polydataViewingProp : polyViewingList)
			m_PackageViweingStrct.polyaDataProperties.push_back(polydataViewingProp);
	}
	
	}

}

void misPackageViewingExtractor::UpdateVolumeViewingParts()
{
	auto package = m_Packge.lock();
	if (!package)
		return;
	auto volumes = package->GetVolumeDataDependencies();
	for (auto volumedataIter : volumes)
	{
		auto VolumeData = volumedataIter->GetVolume();
		if (!VolumeData)
			continue;
		auto volumeComponentProperty = VolumeData->GetColormaps();
		if (volumedataIter->GetAutomaticallyCreated())
			continue;
		for (auto iter = volumeComponentProperty.begin(); iter != volumeComponentProperty.end(); iter++)
		{
			mis3DModelObjectOpacityPropertiesStrct modelProp;
			auto volumeUID = VolumeData->GetObjectUID(iter->first);
			bool found = volumedataIter->GetObjectVisibilityProperties(volumeUID, modelProp);
			if (!found)
				continue;
			misShort3DModelViewingStrct	PolydataViewingProp;
			PolydataViewingProp.name = iter->second.Name;
			PolydataViewingProp.color = iter->second.volumeColor;
			PolydataViewingProp.parentImageUID = volumedataIter->GetParentImageUID();
			PolydataViewingProp.objectContainerUID = VolumeData->GetUID();
			PolydataViewingProp.objectUID = volumeUID;
			PolydataViewingProp.visibility3D = modelProp.GetVisibilityIn3DScene();
			PolydataViewingProp.segmentedObjectVisibility = modelProp.visibilityIn2DScene;
			PolydataViewingProp.opacity = modelProp.GetOpacityIn2DScene();
			PolydataViewingProp.renderingType = misVolumeRendering;
			m_PackageViweingStrct.polyaDataProperties.push_back(PolydataViewingProp);
		}
	}
}

void misPackageViewingExtractor::UpdatePlansViewingParts()
{
	auto package = m_Packge.lock();
	if (!package)
		return;
	auto packagePlanRelRepo = m_PackagePlanRelRepo.lock();
	if (!packagePlanRelRepo)
		return;
	auto rels = packagePlanRelRepo->GetByPackageUid(package->GetObjectUID());
	for (auto const& rel : rels)
	{
		misShort3DModelViewingStrct plandataViewingProp;
		auto plan = rel->GetPlanEntity();
		plandataViewingProp.name = plan->GetPlanName();
		plandataViewingProp.objectUID = plan->GetUID();
		plandataViewingProp.parentImageUID = plan->GetParentImageUID();
		plandataViewingProp.objectContainerUID = plan->GetParentImageUID();
		auto visibility = rel->GetVisibility();
		plandataViewingProp.visibility3D = visibility.GetVisibilityIn3DScene();
		plandataViewingProp.opacity = visibility.OpacityIn3DScene;
		plandataViewingProp.segmentedObjectVisibility = visibility.visibilityIn2DScene;
		plandataViewingProp.color = plan->GetPlannigColor();
		m_PackageViweingStrct.planningDataProperties.push_back(plandataViewingProp);
	}
	std::sort(m_PackageViweingStrct.planningDataProperties.begin(), m_PackageViweingStrct.planningDataProperties.end(),
		[](auto const& leftPlanItem, auto const& rightPlanItem) {
		return leftPlanItem.name < rightPlanItem.name;
	});
}
