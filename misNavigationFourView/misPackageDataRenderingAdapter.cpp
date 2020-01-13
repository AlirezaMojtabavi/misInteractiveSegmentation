#include "stdafx.h"

#include "misDataSetManager.h"
#include "misEnumUtilities.h"
#include "mis2DPackageTransformUpdater.h"
#include "misPackageDataRenderingAdapter.h"
#include "misTransFunctionBuilder.h"
#include "misViewerTypeDirection.h"
#include "misImageContained.h"

misPackageDataRenderingAdapter::misPackageDataRenderingAdapter(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlation, 
	std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater, 
	misSurgeryDirectionViewerType currentTypeDir)
	:
	m_VolumeViewingType(misVolumeViewingTypes::misSkinFilledViewing),
	m_CurrentTypeDir(currentTypeDir),
	m_WidgetType(CompleteCursor),
	m_PackageTransformUpdater(packageTransformUpdater),
	m_CSCorrelationManager(correlation)
{
}


void misPackageDataRenderingAdapter::SetVolumeViewingType(misVolumeViewingTypes volumeViewingType)
{

	m_VolumeViewingType = volumeViewingType;
}




void misPackageDataRenderingAdapter::UpdateRepresentationTransforms()
{
	m_PackageTransformUpdater->UpdateRepresentationTransforms();
 }

void misPackageDataRenderingAdapter::UpdateRepresentationTransforms(std::shared_ptr<IVolumeRenderer> viewer,
                                                                    std::shared_ptr<ISimpleDataPackage> newPackage)
{
	UpdateRepresentationTransforms();
}



void misPackageDataRenderingAdapter::SetSceneReferenceCoordinateSystem(const std::string& coordSysUid, 
	std::shared_ptr<ISimpleDataPackage> package)
{
	m_SceneReferenceUID = coordSysUid;
	if (m_PackageTransformUpdater)
		m_PackageTransformUpdater->SetSceneReferenceAndPackge(m_SceneReferenceUID, package);
}


void misPackageDataRenderingAdapter::SetDentalSpecialViewsEnable(std::shared_ptr<IVolumeRenderer> viewer, bool enabled)
{
	m_DentalSpecialViewEnable = enabled;
	viewer->SetDentalSpecialViewsEnable(enabled);
}


double misPackageDataRenderingAdapter::GetSliceViewerZoomFactor(const misVisualizationSetting& visualSetting,
                                                                misViewerTypeDirection orientation,
                                                                misImageDataModality modality)
{
	if (m_DentalSpecialViewEnable && (orientation == misViewerTypeDirection::SagittalDirection ||
		orientation == misViewerTypeDirection::CoronalDirection))
		return visualSetting.GetDentalSpecificViewsZoomFactor();

	if (modality == CT)
		return visualSetting.GetImageSliceViewerZoomFactorForCtImages();

	return visualSetting.GetImageSliceViewerZoomFactor();
}

void misPackageDataRenderingAdapter::SetPanoramicCoordinateConverter(
	std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter, std::shared_ptr<IVolumeRenderer> viewer)
{
	viewer->SetPanoramicCoordinateConverter(coordinateConverter);
}

std::shared_ptr<TransFuncIntensity> misPackageDataRenderingAdapter::GenerateTransferFunctionForPolyContainedData(
	std::shared_ptr<misImageContained> imageContainedPolyData, misUID ImageContainedUID /* ="" */)
{
	if (0 == imageContainedPolyData)
	{
		_ASSERT(true == false);
		return 0;
	}
	std::vector<misColorStruct> colorStruct;
	std::vector<misUID> SelectedPolyDatasTypedef;
	misTransFunctionBuilder pTrasferfunction;


	if ("tempUID" == ImageContainedUID)
	{
		SelectedPolyDatasTypedef.push_back(ImageContainedUID);
		int numberOfViewableObjetc = imageContainedPolyData->SetViewableObjectUIDsOnly(SelectedPolyDatasTypedef);
		colorStruct = imageContainedPolyData->GetColorMap3D()->GetColortableVectorForSegmentedImage();
	}
	else
	{
		colorStruct = imageContainedPolyData->GetColorMap3D()->GetColortableVectorForSegmentedImage();
	}

	return pTrasferfunction.GenerateTransferFunction(colorStruct);
}

int misPackageDataRenderingAdapter::ShowPlans(std::shared_ptr<IVolumeRenderer> viewer, std::shared_ptr<PlanDataListDependencyTypedef> rels)
{
	viewer->RemoveAllScrewServices();
	if (rels->empty())
		return 0;

	for (int i = 0; i < rels->size(); i++)
	{
		ShowPlan((*rels)[i]);
	}

	return rels->size();
}
