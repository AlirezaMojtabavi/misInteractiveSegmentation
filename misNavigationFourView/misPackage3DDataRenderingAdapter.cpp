#include "stdafx.h"

#include "misPackage3DDataRenderingAdapter.h"
#include "misDataSetManager.h"
#include "misEnumUtilities.h"
#include "misImageToTextureMap.h"
#include "misMathUtils.h"
#include "misPlanData.h"
#include "misTransFunctionBuilder.h"
#include "misVertebraScrewPlanData.h"
#include "mis3DPackageTransformUpdater.h"
#include "mis3DImageRenderer.h"
#include "IScrewCompound.h"
#include "IVolumeRepresentation.h"
#include "ICursorService.h"
#include "misImageContained.h"
#include "ICornerProperties.h"
#include "misDefaultVolumeRenderer.h"

using namespace std;

misPackage3DDataRenderingAdapter::misPackage3DDataRenderingAdapter(
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
	std::shared_ptr<Iwindows> pWindow,
	int index,
	misSurgeryDirectionViewerType currentTypeDir,
	std::shared_ptr<IVolume3DRenderer> viewer,
	std::shared_ptr<mis3DImageRenderer> imageRenderer,
	std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater,
	std::shared_ptr<IVolumeViewerInitilizer> volumeinitializer)
	: misPackageDataRenderingAdapter(correlationManger, packageTransformUpdater, currentTypeDir),
	  m_viewer(viewer),
	  m_ImageRenderer(imageRenderer),
	  m_VolumeViewerInitializer(volumeinitializer),
	  m_DefaultVolumeRenderer(std::make_unique<misDefaultVolumeRenderer>(correlationManger, viewer, volumeinitializer))
{
	m_CurrentImageContainedPolydataDependencies.clear();
	m_CurrentVolumeDataDependencies.clear();
}

void misPackage3DDataRenderingAdapter::SetWidgetType(misCursorType pWidgetType)
{
	m_WidgetType = pWidgetType;
	m_DefaultVolumeRenderer->SetWidgetType(m_WidgetType);
	m_ImageRenderer->SetWidgetType(pWidgetType);
	m_VolumeViewerInitializer->SetWidgetType(pWidgetType);
}

void misPackage3DDataRenderingAdapter::ReleaseImageResources()
{
	m_viewer->ResetROI();
	m_viewer->GetCursorService()->ReleaseWidget();
	m_CurrentImageContainedPolydataDependencies.clear();
	m_CurrentVolumeDataDependencies.clear();
	m_viewer->ReleaseImageResource();

}


int misPackage3DDataRenderingAdapter::ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting,
                                                           ImageContainedPolydataDependencyListTypes
                                                           newImageContainedPolydataDependencies, double minOpacity)
{
	int currentNumberOfViewableObject = 0;
	for (auto PolyContained : newImageContainedPolydataDependencies)
	{
		if (PolyContained->GetImageContained())
		{
			currentNumberOfViewableObject +=
				PolyContained->GetImageContained()->SetViewableObjectByMap(PolyContained->GetAllObjectVisibility());
		}
	}
	int PolyContainedSize = newImageContainedPolydataDependencies.size();
	if (PolyContainedSize == 0)
	{
		return 0;
	}
	for (auto PolyContained : newImageContainedPolydataDependencies)
	{
		if (PolyContained->GetImageContained())
		{
			PolyContained->GetImageContained()->SetOpacityScale(
				segmentationSetting.m_SegmentedObjectOpacityScale);
			ShowSegmentedObjectsIn3Dviewers(PolyContained);
		}
	}
	return currentNumberOfViewableObject;
}

int misPackage3DDataRenderingAdapter::ShowSegmentedObjectsIn3Dviewers(
	std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> PolyContained)
{
	int numberOfAddedItem = 0;
	if (!PolyContained->GetImageContained())
	{
		return 0;
	}
	if (PolyContained->GetAllObjectVisibility().empty())
	{
		m_viewer->RemoveSegmentedVolume();
		return 0;
	}
	auto pImage = PolyContained->GetImageContained()->GetSegmentedImage();
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(pImage);
	misPolyDatesColormapTypedef polydataColorMap = PolyContained->GetImageContained()->GetPolyDatasColorMap();
	misPolyDatesColormapTypedef::iterator mapIter;
	ImageContainedTransferFuncs3D ImgContTFs;
	misTransFunctionBuilder pTrasferfunction;
	for (mapIter = polydataColorMap.begin(); mapIter != polydataColorMap.end(); mapIter++)
	{
		if (mapIter->second.colorVector3D.size() > 0)
		{
			SegmentedObjectTransferFunction3D segmentedObjTF;
			segmentedObjTF.allocatedByte = mapIter->first;
			segmentedObjTF.transferFunction = pTrasferfunction.GenerateTransferFunction(mapIter->second.colorVector3D);
			ImgContTFs.push_back(segmentedObjTF);
		}
	}
	if (ImgContTFs.size() > 0)
	{
		numberOfAddedItem++;
		m_viewer->SetVolume(imageTexure, ImgContTFs);
	}
	else
	{
		m_viewer->RemoveSegmentedVolume();
	}
	return numberOfAddedItem;
}


int misPackage3DDataRenderingAdapter::ShowVolumes(VolumeDataDependencyListTypes newVolumeDataDependencies)
{
	const int newVolumeDataSize = newVolumeDataDependencies.size();
	const int OldVolumeDataSize = m_CurrentVolumeDataDependencies.size();
	const bool reset = NeedToResetVolumes(newVolumeDataSize, OldVolumeDataSize, newVolumeDataDependencies);
	if (reset)
	{
		m_viewer->ReleaseImageResource();
	}
	if (newVolumeDataDependencies.empty())
	{
		return 0;
	}
	m_CurrentVolumeDataDependencies = newVolumeDataDependencies;
	int numberOfViewingObjects = 0;
	for (int i = 0; i < newVolumeDataSize; i++)
	{
		auto volumeProp = newVolumeDataDependencies[i];
		if (volumeProp->GetVolume())
		{
			numberOfViewingObjects += volumeProp->SetComponentVisiblityByMap(volumeProp->GetAllObjectVisibility());
			ShowVolume(volumeProp);
		}
	}
	return numberOfViewingObjects;
}

std::shared_ptr<IVolume3DRenderer> misPackage3DDataRenderingAdapter::GetVolumeViewer()
{
	return m_viewer;
}

void misPackage3DDataRenderingAdapter::UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
	auto volume = volumeProp->GetVolume();
	auto image = volumeProp->GetImage();
	if (!volume || !image)
	{
		return;
	}
	volume->SetImageModality(image->GetImageModality());
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(image);
	if (!imageTexure)
	{
		return;
	}
	auto tableRange = imageTexure->GetTableRange();
	if (!tableRange)
	{
		return;
	}
	auto transfunc = volumeProp->GetTransferFunction(threeDimension);
	m_viewer->SetVolume(imageTexure, transfunc);
}

std::shared_ptr<IVolumeRenderer> misPackage3DDataRenderingAdapter::GetViewer()
{
	return m_viewer;
}

void misPackage3DDataRenderingAdapter::SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val)
{
}

void misPackage3DDataRenderingAdapter::SetColorMapTransFuncID(misPlaneEnum planeIndex,
                                                              std::shared_ptr<TransFuncIntensity> val)
{
}

void misPackage3DDataRenderingAdapter::SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal)
{

}

void misPackage3DDataRenderingAdapter::SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)
{
}

void misPackage3DDataRenderingAdapter::UpdatePosition(parcast::Point<double, 3> position)
{
	m_viewer->GetCornerProperties()->SetCurrentPosition(position.Elements());
	m_viewer->GetCursorService()->UpdateWidgetPosition();
}



void misPackage3DDataRenderingAdapter::ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
	auto volume = volumeProp->GetVolume();
	auto image = volumeProp->GetImage();
	if (!volume || !image)
	{
		return;
	}
	m_VolumeViewerInitializer->Initialize(image);
	auto textureHandler = misImageToTextureMap::GetInstance();
	volume->SetImageModality(image->GetImageModality());
	auto imageTexture = textureHandler->LookUpTexture(image);
	auto tableRange = imageTexture->GetTableRange();
	const auto transFunction = volumeProp->GetTransferFunction(threeDimension);
	imageTexture->SetROI(image->GetWorldDiemension());
	m_viewer->SetVolume(imageTexture, transFunction);
	UpdateRepresentationTransforms();
}

int misPackage3DDataRenderingAdapter::CreatePlansIn3Dviewers(std::shared_ptr<parcast::IPackagePlanRel> rel)
{
	int numberOfAddedItem = 0;
	auto planDep = rel->GetPlanEntity();
	auto ScrewPlanData = std::dynamic_pointer_cast<misVertebraScrewPlanData>(planDep);
	if (ScrewPlanData)
	{
		misScrewWidgetData initVals;
		initVals.SetSourceType(ScrewPlanData->GetScrewSourceType());
		initVals.SetScrewUID(ScrewPlanData->GetUID());
		initVals.SetTargetRadius(ScrewPlanData->GetTargetRegionRadius());
		initVals.SetStartPoint(ScrewPlanData->GetEntryPoint().Elements());
		initVals.SetEndPoint(ScrewPlanData->GetTargetPoint().Elements());
		initVals.SetScrewDiameter(ScrewPlanData->GetScrewDiameter());
		m_viewer->InitializeScrewWidget(initVals, UNKnownDirection);
		m_viewer->GetScrewWidgetService(initVals.GetScrewUID())->SetColor(ScrewPlanData->GetPlannigColor());
		numberOfAddedItem++;
		if (ScrewPlanData->GetScrewPlacementFinalized())
		{
			m_viewer->GetScrewWidgetService(initVals.GetScrewUID())->SetLocked(true);
		}
		if (!rel->GetVisibility().GetVisibilityIn3DScene())
		{
			m_viewer->OffScrew(initVals.GetScrewUID());
		}
	}
	return numberOfAddedItem;
}

void misPackage3DDataRenderingAdapter::SetVisibilityOfSegmentedImage(misUID imageuid, bool val)
{
	ShowPackage(m_CurrentPackage.lock(),
		m_VisualizationSetting,
		m_SegmentationSetting, m_MinOpacity, false, m_WidgetType, m_PlaneVisibility);
}

void misPackage3DDataRenderingAdapter::SetObliqueFlag(bool isOblique)
{
	m_viewer->SetObliqueFlag(isOblique);
}

void misPackage3DDataRenderingAdapter::ModifyVolume()
{
	m_viewer->ModifyVolume();
}


void misPackage3DDataRenderingAdapter::ShowPlan(std::shared_ptr<parcast::IPackagePlanRel> rel)
{
	auto plan = rel->GetPlanEntity();
	if (!plan)
	{
		return;
	}
	double planLenght = (plan->GetEntryPoint() - plan->GetTargetPoint()).Length();
	if (planLenght == 0)
		return;

	auto screwPlanData = std::dynamic_pointer_cast<misVertebraScrewPlanData>(plan);
	if (!screwPlanData)
		return;

	if (m_viewer->GetScrewWidgetService(screwPlanData->GetUID()))
	{
		if (rel->GetVisibility().GetVisibilityIn3DScene())
		{
			m_viewer->OnScrew(screwPlanData->GetUID());
		}
		else
		{
			m_viewer->OffScrew(screwPlanData->GetUID());
		}
		auto screwWidget = m_viewer->GetScrewWidgetService(screwPlanData->GetUID());
		screwWidget->SetColor(plan->GetPlannigColor());
		screwWidget->SetWidth(screwPlanData->GetScrewDiameter());
		screwWidget->SetEntry(plan->GetEntryPoint());
		screwWidget->SetTarget(plan->GetTargetPoint());
		screwWidget->SetTargetRadius(plan->GetTargetRegionRadius());
	}
	else
	{
		CreatePlansIn3Dviewers(rel);
	}
}

bool misPackage3DDataRenderingAdapter::NeedToResetVolumes(int NewVolumeDataSize, int OldVolumeDataSize,
                                                          VolumeDataDependencyListTypes& NewVolumeDataDependencies)
{
	if (NewVolumeDataSize != OldVolumeDataSize)
	{
		return true;
	}
	else
	{
		for (int index = 0; index < NewVolumeDataSize; index++)
		{
			if (!NewVolumeDataDependencies[index]->GetVolume() || !m_CurrentVolumeDataDependencies[index]->GetVolume()
				||
				NewVolumeDataDependencies[index]->GetVolume()->GetUID() !=
				m_CurrentVolumeDataDependencies[index]->GetVolume()->GetUID())
			{
				return true;
			}
			if (NewVolumeDataDependencies[index]->GetAllObjectVisibility().size() !=
				m_CurrentVolumeDataDependencies[index]->GetAllObjectVisibility().size())
			{
				return false;
			}
		}
	}
	return false;
}

void misPackage3DDataRenderingAdapter::ShowPackage(std::shared_ptr<ISimpleDataPackage> newPackage,
                                                   const misVisualizationSetting& visualSetting,
                                                   const misSegmentationSetting& segmentationSetting,
                                                   double minOpacity, bool resetZoom, misCursorType pWidgetType,
                                                   std::map<misPlaneEnum, bool> planeVisible)
{
	m_VisualizationSetting = visualSetting;
	m_SegmentationSetting = segmentationSetting;
	m_MinOpacity = minOpacity;
	m_PlaneVisibility = planeVisible;
	if (!newPackage)
	{
		ReleaseImageResources();
		return;
	}
	const auto package = m_CurrentPackage.lock();
	if (!package || newPackage->GetObjectUID() != package->GetObjectUID())
	{
		ReleaseImageResources();
	};

	auto mainImage = newPackage->GetMainImage();
	m_VolumeViewerInitializer->SetWidgetType(pWidgetType);
	m_VolumeViewerInitializer->Initialize(mainImage);
	m_CurrentImageContainedPolydataDependencies = newPackage->GetImageContainedPolydataDependencies();
	m_CurrentVolumeDataDependencies = newPackage->GetVolumeDataDependencies();
	m_CurrentPackage = newPackage;
	m_PackageTransformUpdater->SetSceneReferenceAndPackge(m_SceneReferenceUID, newPackage);
	const auto segmentedNum = ShowSegmentedObjects(segmentationSetting,
		newPackage->GetImageContainedPolydataDependencies(), minOpacity);
	auto planNum = ShowPlans(m_viewer, newPackage->GetPlanDataDependencies());

	const auto volumeNum = ShowVolumes(m_CurrentVolumeDataDependencies);
	if (volumeNum == 0)
	{
		m_DefaultVolumeRenderer->SetSceneReferenceUID(m_PackageTransformUpdater->GetRefrenceId());
		m_DefaultVolumeRenderer->ShowDefaultVolume(segmentedNum, newPackage->GetImageDataDependencies(),
		                                           m_VolumeViewingType);
		UpdateRepresentationTransforms();
	}

	m_viewer->CompileVolumeShader();
}

void misPackage3DDataRenderingAdapter::Reset()
{
	m_viewer->ReleaseImageResource();
	m_viewer->Reset();
	m_viewer->ResetROI();
	m_viewer->GetCursorService()->ReleaseWidget();
	m_ImageRenderer->Reset();
	m_CurrentImageContainedPolydataDependencies.clear();
	m_CurrentVolumeDataDependencies.clear();
}
