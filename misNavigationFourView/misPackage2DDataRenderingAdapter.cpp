#include "stdafx.h"

#include "ICursorService.h"
#include "IScrewCompound.h"
#include "mis2DImageRenderingAdapter.h"
#include "misImageToTextureMap.h"
#include "misVolumeSlicer.h"
#include "misPackage2DDataRenderingAdapter.h"
#include "misPackageDataRenderingAdapter.h"
#include "mis2DPackageTransformUpdater.h"
#include "misSurgeryDirectionViewerType.h"
#include "misPlaneVisibilityUpdater.h"
#include "misVisibiltyHolder.h"
#include "misDistributionEvent.h"
#include "misCameraInteraction.h"
#include "misImageContained.h"
#include "misVolumeData.h"
#include "misSegmentedObjectTransferFunction.h"
#include "IVolumeSlicerEvents.h"
#include "UpdatePlaneVisibilitiy.h"
#include "misImageVisibiltyMapGenerator.h"
#include "misImageIOProperties.h"
#include "ImagePriorty.h"
#include "misVertebraScrewPlanData.h"

class misImageVisibilityMapGenerator;

misPackage2DDataRenderingAdapter::misPackage2DDataRenderingAdapter(
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
	misSurgeryDirectionViewerType currentTypeDir,
	double offset, std::shared_ptr<IVolumeSlicer> slicer,
	std::shared_ptr<IRepresentationFactory>
	representationFactor, std::unique_ptr<I2DImageRenderingAdapter> imageRenderer, 
	std::shared_ptr<IPackageTransformUpdater> packageTransformUpdater) :
	misPackageDataRenderingAdapter(correlationManger, packageTransformUpdater, currentTypeDir),
	m_ImageRenderer(std::move(imageRenderer)),
	m_NumberOfViewableObject(0),
	m_Slicer(slicer)
 
{
	m_Slicer->ApplyOffset(offset);
}

misPackage2DDataRenderingAdapter::~misPackage2DDataRenderingAdapter()
{
}

std::shared_ptr<IVolumeRenderer> misPackage2DDataRenderingAdapter::GetViewer()
{
	return m_Slicer;
}



void misPackage2DDataRenderingAdapter::SetColorValueToTexture(misUID imageUID, misDoubleColorStruct Color)
{
	misPlaneEnum planeIndex = GetCorrespondingPlaneIndex(imageUID);

	if (planeIndex != UnSetPlane)
	{
		auto gpu2DRep = m_Slicer->GetImageRprensentaion();
 			if (gpu2DRep)
			{
				gpu2DRep->SetColorValueToTexture(planeIndex, Color);
			}
	}
}

void misPackage2DDataRenderingAdapter::UpdatePosition(parcast::Point<double, 3> position)
{
	m_Slicer->GetCornerProperties()->SetCurrentPosition(position.Elements());
	m_Slicer->UpdateImage(true);
	m_Slicer->GetCursorService()->UpdateWidgetPosition();
}

void misPackage2DDataRenderingAdapter::SetObliqueFlag(bool isOblique)
{
	m_Slicer->SetObliqueFlag(isOblique);
}

void misPackage2DDataRenderingAdapter::UpdateImageAnnotation()
{
	m_Slicer->CreateImageAnnotation();
}

void misPackage2DDataRenderingAdapter::AddInternalObservers(itk::Command* ContrastObserver,
	itk::Command* backToMapObserver, itk::Command* stateObsrever)
{
	auto imageRep = m_Slicer->GetImageRprensentaion();
	if (imageRep)
	{
		auto observable = std::dynamic_pointer_cast<IRepresentation>(imageRep);
		if (!observable->HasObserver(misPlaneContrastEvent()))
		{
			observable->AddObserver(misPlaneContrastEvent(), ContrastObserver);
		}
	}
	if (!m_Slicer->HasObserver(misBackToPanModeEvent()))
	{
		m_Slicer->AddObserver(misBackToPanModeEvent(), backToMapObserver);
	}
	m_Slicer->AddObserver(misChangedInterctionStateEvent(), stateObsrever);
}

void misPackage2DDataRenderingAdapter::SetRealTimeMode(bool val)
{
	m_Slicer->SetRealTimeMode(val);
}

void misPackage2DDataRenderingAdapter::ResetMeasurment()
{
	m_Slicer->GetMeasurmentService()->ResetMeasurmentWidget();
}

 

void misPackage2DDataRenderingAdapter::SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val)
{
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	imagePlane->SetVisiblityOfColorMap(planeIndex, val);
}

void misPackage2DDataRenderingAdapter::SetColorMapTransFuncID(misPlaneEnum planeIndex,
	std::shared_ptr<TransFuncIntensity> val)
{
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	imagePlane->SetColorMapTransFuncID(planeIndex, val);
}

void misPackage2DDataRenderingAdapter::SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal)
{
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	imagePlane->SetColorValueToTexture(planeIndex, colorVal);
}

void misPackage2DDataRenderingAdapter::SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)
{
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	imagePlane->SetOpacityValueToTexture(planeIndex, opacityValue);
}




misWindowLevelStr misPackage2DDataRenderingAdapter::GetCurrentWindowLevel(misUID imageUID)
{
	return m_ImageRenderer->GetCurrentWindowLevel(imageUID);
}

void misPackage2DDataRenderingAdapter::ApplyWindowlevel(misUID imageUID, misWindowLevelStr winLevStr)
{
	misPlaneEnum planeIndex = GetCorrespondingPlaneIndex(imageUID);
	if (planeIndex != UnSetPlane)
	{
		m_Slicer->SetViewingProperties(planeIndex, winLevStr);
	}
}

void misPackage2DDataRenderingAdapter::SetOpacityValueToTexture(misUID imageUID, float val)
{
	misPlaneEnum planeIndex = GetCorrespondingPlaneIndex(imageUID);
	if (planeIndex != UnSetPlane)
	{
		auto gpu2DRep = m_Slicer->GetImageRprensentaion();
		if (gpu2DRep)
		{
			gpu2DRep->SetOpacityValueToTexture(planeIndex, val);
		}
	}
}

void misPackage2DDataRenderingAdapter::SetVisibilityValueToTexture(misUID imageUID, bool val)
{
	misPlaneEnum planeIndex = GetCorrespondingPlaneIndex(imageUID);
	if (planeIndex != UnSetPlane)
	{
		auto gpu2DRep = m_Slicer->GetImageRprensentaion();
		if (gpu2DRep)
			gpu2DRep->SetVisibilityOfMainTexture(planeIndex, val);

	}
}

void misPackage2DDataRenderingAdapter::SetOrientation(IMAGEORIENTATION newOrientation)
{
	m_Slicer->SetOrientationDirection(newOrientation);
}

void misPackage2DDataRenderingAdapter::RemoveImageLyer(std::shared_ptr<I2DRepresetation> Gpu2DRep)
{
	Gpu2DRep->RemoveLayer(FirstImage, SegmentedImage);
	Gpu2DRep->RemoveLayer(SecondImage, SegmentedImage);
}

int misPackage2DDataRenderingAdapter::ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting,
	ImageContainedPolydataDependencyListTypes newImageContainedPolydataDependencies, double minOpacity)
{
	int currentNumberOfViewableObject = 0;
	for (auto PolyContained : newImageContainedPolydataDependencies)
	{
		if (PolyContained->GetImageContained())
			currentNumberOfViewableObject +=
			PolyContained->GetImageContained()->SetViewableObjectByMap(PolyContained->GetAllObjectVisibility());
	}
	auto Gpu2DRep = m_Slicer->GetImageRprensentaion();
	if (!Gpu2DRep)
		return 0;
	if (currentNumberOfViewableObject != m_NumberOfViewableObject)
		RemoveImageLyer(Gpu2DRep);
	m_NumberOfViewableObject = currentNumberOfViewableObject;
	int PolyContainedSize = newImageContainedPolydataDependencies.size();
	if (PolyContainedSize == 0)
		return 0;
	for (auto PolyContained : newImageContainedPolydataDependencies)
	{
		if (PolyContained->GetImageContained())
		{
			PolyContained->GetImageContained()->SetOpacityScale(
				segmentationSetting.m_SegmentedObjectOpacityScale);
			ShowSegmentedObjectsIn2Dviewers(PolyContained, minOpacity);
		}
	}
	return currentNumberOfViewableObject;
}

void misPackage2DDataRenderingAdapter::ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
	if (!volumeProp->GetVolume() || !volumeProp->GetImage() ||
		volumeProp->GetAllObjectVisibility().empty() || !volumeProp->GetVisibilityIn2D())
	{
		return;
	}
	volumeProp->GetVolume()->SetImageModality(volumeProp->GetImage()->GetImageModality());
	const auto CorrespondingPlaneEnum = GetCorrespondingPlaneIndex(volumeProp->GetParentImageUID());
	if (CorrespondingPlaneEnum == UnSetPlane)
	{
		return;
	}
	auto gpu2DRep = m_Slicer->GetImageRprensentaion();

	if (!gpu2DRep)
	{
		return;
	}
	misImageToTextureMap*	TextureHandler = misImageToTextureMap::GetInstance();
	bool  opacityTestIn2d = true;
	auto visibilities = volumeProp->GetAllObjectVisibility();
	misOpenglTexture*	imageTexure = TextureHandler->LookUpTexture(volumeProp->GetImage());
	double* TableRange = imageTexure->GetTableRange();
	if (!TableRange)
	{
		return;
	}
	auto transfunc = volumeProp->GetTransferFunction(twoDimension);
	transfunc->updateTexture();
	SetVolumeTextureUIDVisibility(CorrespondingPlaneEnum, transfunc);
}

int misPackage2DDataRenderingAdapter::ShowVolumes(VolumeDataDependencyListTypes newVolumeDataDependencies)
{
	const int newVolumeDataSize = newVolumeDataDependencies.size();
	auto gpuRep = m_Slicer->GetImageRprensentaion();
	if (gpuRep)
	{
		gpuRep->RemoveColorMap(FirstImage);
		gpuRep->RemoveColorMap(SecondImage);
	}
	if (newVolumeDataSize == 0)
	{
		return 0;
	}
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

int misPackage2DDataRenderingAdapter::ShowSegmentedObjectsIn2Dviewers(
	const std::shared_ptr<const ICompeleteImageContainedPolydataDependensiesStrct>& polyContained,
	double minOpacity)
{
	auto numberOfAddedItem = polyContained->GetAllObjectVisibility().size();
	if (numberOfAddedItem == 0)
	{
		return 0;
	}
	if (!polyContained->GetImageContained())
	{
		return 0;
	}
	const misUID parentImageUID = polyContained->GetParentUID();
	const misPlaneEnum correspondingPlaneEnum = GetCorrespondingPlaneIndex(parentImageUID);
	if (correspondingPlaneEnum == UnSetPlane)
	{
		return 0;
	}
	auto gpu2DRep = m_Slicer->GetImageRprensentaion();
	if (!gpu2DRep)
	{
		return numberOfAddedItem;
	}


	std::shared_ptr<IImage>	pImage = polyContained->GetImageContained()->GetSegmentedImage();
	pImage->SetParentImageUID(parentImageUID);
	_ASSERT(pImage != NULL);
	if (!pImage)
	{
		return 0;
	}
	ImageContainedTransferFuncs ImgContTFs = polyContained->GetTransferFuncs();
	if (!ImgContTFs.empty())
	{
		switch (correspondingPlaneEnum)
		{
		case FirstImage:
		{
			m_ImageRenderer->SetImage(SegmentedImage, pImage, minOpacity);
			numberOfAddedItem++;
			break;
		}
		case SecondImage:
		{
			m_ImageRenderer->SetNextImage(SecondImage, SegmentedImage, pImage, minOpacity);
			numberOfAddedItem++;
			break;
		}
		default: ;
		}
		gpu2DRep->SetPolyDataTransferFunction(correspondingPlaneEnum, ImgContTFs);
		gpu2DRep->SetVisibilityOfSegmentedImage(correspondingPlaneEnum, true);
	}
	else
	{
		gpu2DRep->SetVisibilityOfSegmentedImage(correspondingPlaneEnum, false);
	}
	return numberOfAddedItem;
}

misPlaneEnum misPackage2DDataRenderingAdapter::GetCorrespondingPlaneIndex(misUID ParentImageUID)
{
	return m_ImageRenderer->GetCorrespondingPlaneIndex(ParentImageUID);
}

void misPackage2DDataRenderingAdapter::SetSegmentedTextureUIDVisibility(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf)
{
	auto gpu2DRep = m_Slicer->GetImageRprensentaion();
	if (gpu2DRep)
	{
		gpu2DRep->SetTransferFunction(planeIndex, tf);
		if (tf->getTexture()->getId() > 0)
		{
			gpu2DRep->SetVisibilityOfSegmentedImage(planeIndex, true);
		}
		else
		{
			gpu2DRep->SetVisibilityOfSegmentedImage(planeIndex, false);
		}
	}
}

void misPackage2DDataRenderingAdapter::SetVolumeTextureUIDVisibility(misPlaneEnum CorrespondingPlaneEnum, std::shared_ptr<TransFuncIntensity> val)
{
	auto imagePlane = m_Slicer->GetImageRprensentaion();
	if (!imagePlane)
		return;
	imagePlane->SetColorMapTransFuncID(CorrespondingPlaneEnum, val);
	if (val->getTexture()->getId() > 0)
	{
		imagePlane->SetVisiblityOfColorMap(CorrespondingPlaneEnum, true);
	}
	else if (val->getTexture()->getId() < 0)
	{
		imagePlane->SetVisiblityOfColorMap(CorrespondingPlaneEnum, false);
	}
}

void misPackage2DDataRenderingAdapter::UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
}

std::shared_ptr<IVolumeSlicer> misPackage2DDataRenderingAdapter::GetSlicer()
{
	return  m_Slicer;
}

void misPackage2DDataRenderingAdapter::SetVisibilityOfSegmentedImage(misUID imageuid, bool val)
{
	auto imageRep = m_Slicer->GetImageRprensentaion();
	if (!imageRep)
		return;
	const auto firstPlaneUId = imageRep->GetImageUID(FirstImage);
	const auto secondPlaneUId = imageRep->GetImageUID(SecondImage);
	if (firstPlaneUId == imageuid)
		imageRep->SetVisibilityOfSegmentedImage(FirstImage, val);
	else 	if (secondPlaneUId == imageuid)
		imageRep->SetVisibilityOfSegmentedImage(SecondImage, val);


}

void misPackage2DDataRenderingAdapter::ShowPlan(std::shared_ptr< parcast::IPackagePlanRel> rel)
{
	auto plan = rel->GetPlanEntity();
	if (!plan)
	{
		return;
	}
	double planLenght = (plan->GetEntryPoint() - plan->GetTargetPoint()).Length();
	if (planLenght == 0)
	{
		return;
	}
	auto screwPlanData = std::dynamic_pointer_cast<misVertebraScrewPlanData>(plan);
	if (!screwPlanData)
	{
		return;
	}
	if (m_Slicer->GetScrewWidgetService(screwPlanData->GetUID()))
	{
		if (rel->GetVisibility().visibilityIn2DScene)
		{
			m_Slicer->OnScrew(screwPlanData->GetUID());
		}
		else
		{
			m_Slicer->OffScrew(screwPlanData->GetUID());
		}
		auto screwWidget = m_Slicer->GetScrewWidgetService(screwPlanData->GetUID());
		screwWidget->SetColor(plan->GetPlannigColor());
		screwWidget->SetWidth(screwPlanData->GetScrewDiameter());
		screwWidget->SetEntry(plan->GetEntryPoint());
		screwWidget->SetTarget(plan->GetTargetPoint());
		screwWidget->SetTargetRadius(plan->GetTargetRegionRadius());
	}
	else
	{
		CreateScrewPlansIn2Dviewers(rel);
	}
}

bool misPackage2DDataRenderingAdapter::ShowImages(std::shared_ptr<ISimpleDataPackage> newPackage,
                                                  const misVisualizationSetting& visualSetting, double minOpacity,
                                                  bool resetZoom, misCursorType pWidgetType,
                                                  std::shared_ptr<IImage>& mainImage)
{
	if (!newPackage)
	{
		ReleaseImageResources();
		return true;
	}
	SetWidgetType(pWidgetType);

	const auto package = m_CurrentPackage.lock();
	if (!package || newPackage->GetObjectUID() != package->GetObjectUID())
	{
		ReleaseImageResources();
	}
	m_CurrentPackage = newPackage;
	mainImage = newPackage->GetMainImage();
	const auto  imagePriory = ImagePriorty(newPackage->GetImageDataDependencies());
 
	m_ImageRenderer->ShowImages(imagePriory.GetMainImage(), imagePriory.GetMainImageVisibility(),
	                            imagePriory.GetSecondImage(), imagePriory.GetSecondImageVisibility(), minOpacity);
	if (mainImage)
	{
		double zoomFactor = GetSliceViewerZoomFactor(visualSetting, m_Slicer->GetTypeDirection(), mainImage->GetImageModality());
		m_Slicer->SetImageSliceViewerZoomFactor(zoomFactor);
		if (resetZoom)
		{
			m_Slicer->ResetZoom();
			double widgetPos[3];
			m_Slicer->GetWidgetFocalPoint(widgetPos);
			m_Slicer->GetCameraService()->UpdateZoom(ResetZoom, widgetPos);
		}
	}
	UpdateSliderInGUI();
	return false;
}


void misPackage2DDataRenderingAdapter::UpdateImagePlaneDimension(ImageDependencyListTypes &images)
{
	const auto referenceImageDependency = std::find_if(images.cbegin(), images.cend(), [this](auto imageDep)
	{
		return static_cast<bool>(imageDep->GetImage()->GetUID() == m_SceneReferenceUID);
	});
	if (referenceImageDependency == images.end())
		return;
	const auto extent = (*referenceImageDependency)->GetImage()->GetImageIOProperties().extent;
	const auto spacing = (*referenceImageDependency)->GetImage()->GetImageIOProperties().spacing;
	const ImageBoundingProperty imageBoundingProp(extent, spacing);
	m_Slicer->GetCornerProperties()->SetImageBounding(imageBoundingProp);
	
}

void misPackage2DDataRenderingAdapter::ShowPackage(std::shared_ptr<ISimpleDataPackage> newPackage, const misVisualizationSetting& visualSetting,
	const misSegmentationSetting& segmentationSetting, double minOpacity, bool resetZoom, misCursorType pWidgetType,
	std::map<misPlaneEnum, bool> pPlaneVisible)

{

	std::shared_ptr<IImage> mainImage;
	if (ShowImages(newPackage, visualSetting, minOpacity, resetZoom, pWidgetType, mainImage)) return;
	m_CurrentImageContainedPolydataDependencies = newPackage->GetImageContainedPolydataDependencies();
	const auto currentVolumeDataDependencies = newPackage->GetVolumeDataDependencies();
	m_CurrentPackage = newPackage;
	int volumeNum = ShowVolumes(currentVolumeDataDependencies);
	int segmentedNum = ShowSegmentedObjects(segmentationSetting,
		newPackage->GetImageContainedPolydataDependencies(), minOpacity);
	auto viewPort = m_Slicer->GetRenderer()->GetViewport();
	auto viewDimes = (viewPort[2] - viewPort[0] )* (viewPort[3] - viewPort[1]);
	auto viewIsFull = viewDimes >= 1.0;
	int planNum = 0;
	if(viewIsFull )
		ShowPlans(m_Slicer, newPackage->GetPlanDataDependencies());
	if (mainImage)
	{
		m_Slicer->SetDentalSpecialViewsEnable(!newPackage->GetParametricSpline().empty());
	}
	m_PackageTransformUpdater->SetSceneReferenceAndPackge(m_SceneReferenceUID, newPackage);
	UpdateRepresentationTransforms();
	auto  planeVisibilitySetting = std::make_unique<UpdatePlaneVisibilitiy>(m_Slicer, std::make_shared<misVisibiltyHolder>(pPlaneVisible));
	misImageVisibilityMapGenerator  mapGenerator(newPackage);
	planeVisibilitySetting->UpdatePlaneVisibilities(mapGenerator.GetVisibilityMap(), pPlaneVisible);
	UpdateSliderInGUI();
}
void misPackage2DDataRenderingAdapter::UpdateSliderInGUI()
{
	if ( !m_CurrentPackage.lock())
		return;
	auto images = m_CurrentPackage.lock()->GetImageDataDependencies();
	UpdateImagePlaneDimension(images);

	UpdateSliders();
	auto corner = m_Slicer->GetCornerProperties();
	int sliceIndex = corner->GetCurrentSliceNumber();
	if (sliceIndex > -1)
	{
		sliderInfoStruct tempStrct;
		tempStrct.sliderIndex = m_Slicer->GetWindow()->GetWindowIndex();
		tempStrct.sliderValue = sliceIndex;
		misCurrentSliceChangedCore ev2;

		ev2.Set(tempStrct);
		ev2.SetSequenceName(m_Slicer->GetWindow()->GetParentTabName());
		ev2.SetSubTab(m_Slicer->GetWindow()->GetParentSubTabName());
		ev2.Set(tempStrct);
		m_Slicer->InvokeEvent(ev2);
	}
}

void misPackage2DDataRenderingAdapter::UpdateSliders()
{
	if (!m_Slicer->GetImageRprensentaion())
		return;
	auto corner = m_Slicer->GetCornerProperties();
	int maxSlide = corner->GetMaxSliceNumber();
	misSliderStrc  sliderStr;
	sliderStr.maxSliderValue = maxSlide;
	sliderStr.minSliderValue = 0;
	sliderStr.SliderIndex = m_Slicer->GetWindow()->GetWindowIndex();
	misSetSliderInfoEventCore ev;
	ev.Set(sliderStr);
	ev.SetSequenceName(m_Slicer->GetWindow()->GetParentTabName());
	ev.SetSubTab(m_Slicer->GetWindow()->GetParentSubTabName());
	m_Slicer->InvokeEvent(ev);

}


void misPackage2DDataRenderingAdapter::Reset()
{
	m_Slicer->GetCursorService()->ReleaseWidget();
	m_Slicer->Reset();
	m_Slicer->ResetROI();
	m_ImageRenderer->Reset();
	m_CurrentImageContainedPolydataDependencies.clear();
}

void misPackage2DDataRenderingAdapter::ReleaseImageResources()
{
	auto package = m_CurrentPackage.lock();
	if (!package)
	{
		return;
	}
	m_Slicer->ReleaseImageResource();
 	m_Slicer->ResetROI();
	m_Slicer->GetCursorService()->ReleaseWidget();
	m_CurrentImageContainedPolydataDependencies.clear();
}

void misPackage2DDataRenderingAdapter::SetWidgetType(misCursorType pWidgetType)
{
	m_WidgetType = pWidgetType;
	m_ImageRenderer->SetWidgetType(pWidgetType);
}

int misPackage2DDataRenderingAdapter::CreateScrewPlansIn2Dviewers(std::shared_ptr< parcast::IPackagePlanRel> rel)
{
	auto planDep = rel->GetPlanEntity();
	int numberOfAddedItem = 0;
	auto ScrewPlanData = std::dynamic_pointer_cast<misVertebraScrewPlanData>(planDep);
	if (!ScrewPlanData)
	{
		return numberOfAddedItem;
	}
	misScrewWidgetData initVals;
	initVals.SetInterationType(ScrewPlanData->GetScrewInterationType());
	initVals.SetSourceType(ScrewPlanData->GetScrewSourceType());
	initVals.SetScrewUID(ScrewPlanData->GetUID());
	initVals.SetScrewDiameter(ScrewPlanData->GetScrewDiameter());
	initVals.SetStartPoint(ScrewPlanData->GetEntryPoint().Elements());
	initVals.SetEndPoint(ScrewPlanData->GetTargetPoint().Elements());
	initVals.SetTargetRadius(ScrewPlanData->GetTargetRegionRadius());

	auto orientation = UNKnownDirection;
	orientation = m_Slicer->GetImageRprensentaion()->GetOrientation();
	m_Slicer->InitializeScrewWidget(initVals, orientation);
	m_Slicer->GetScrewWidgetService(initVals.GetScrewUID())->SetColor(ScrewPlanData->GetPlannigColor());
	m_Slicer->GetCursorService()->Set3DInteractionCapturedFlag(false);
	numberOfAddedItem++;
	if (ScrewPlanData->GetScrewPlacementFinalized())
	{
		m_Slicer->GetScrewWidgetService(initVals.GetScrewUID())->SetLocked(true);
	}
	if (!planDep->GetPackageRels()[0]->GetVisibility().visibilityIn2DScene)
	{
		m_Slicer->OffScrew(initVals.GetScrewUID());
	}
	return numberOfAddedItem;
}