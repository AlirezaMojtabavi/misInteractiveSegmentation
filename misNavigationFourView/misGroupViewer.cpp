#include "Stdafx.h"
#include "misGroupViewer.h"
#include "IVolume3DRenderer.h"
#include "IImagePositionUpdater.h"
#include "IPackageDataRenderingAdapter.h"
#include "IScrewCompound.h"
#include "mis3DViewer.h"
#include "misCursorService.h"
#include "misEnumUtilities.h"
#include "misImagePositionUpdater.h"
#include "misImageToTextureMap.h"
#include "misVolumeSlicer.h"
#include "misMathUtils.h"
#include "misPackage2DDataRenderingAdapter.h"
#include "misPackage3DDataRenderingAdapter.h"
#include "misPanoramicCoordinatesConverter.h"
#include "misPanoramicToolCoordSysRenderer.h"
#include "misRepresentationContainer.h"
#include "misSurgeryDirectionViewerType.h"
#include "misTransform.h"
#include "misWindow.h"
#include "misPackagePanoramicDataRenderingAdapter.h"
#include "misUpdateViewPortToStandard.h"
#include "misUpdateViewPortToOblique.h"
#include "IVolumeSlicerEvents.h"
#include "misVisibiltyHolder.h"
#include "UpdatePlaneVisibilitiy.h"
#include "misImageVisibiltyMapGenerator.h"

using namespace std;

misGroupViewer::misGroupViewer(
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
	correlationManager,
	std::shared_ptr<IGroupViewerSetting> groupViwerSetting,
	std::shared_ptr<Injector> injector)
	: m_ExternalEventViewer(nullptr),
	m_GroupViewSetting(std::move(groupViwerSetting)),
	m_UpdateViewPortsToStandard(
		std::make_shared<misUpdateViewPortToStandard>()),
	m_UpdateViewPortsToOblique(
		std::make_shared<misUpdateViewPortToOblique>()),
	m_CSCorrelationManager(correlationManager) {
	InitializeGeneralTimers();
	m_AppSetting = misApplicationSetting::GetInstance();

	m_ImagesColor.clear();
	if (!injector)
		m_Injector = std::make_shared<Injector>();
	flyZoneStatusText.resize(6);
}
misGroupViewer::~misGroupViewer()
{
	Reset();

}

void misGroupViewer::SetObliqueChangedObserver(std::weak_ptr<IObliqueChanged> observer)
{
	m_ObliqueChangedObserver = observer;
}

void misGroupViewer::SetPlanIsSelectedInViewerObserver(std::weak_ptr<IPlanSelectedInViewer> observer)
{
	m_PlanSelectedInViewerObserver = observer;
}


void misGroupViewer::Render()
{
	auto timer = vtkSmartPointer<vtkTimerLog>::New();
	timer->StartTimer();
	for (auto adapter : m_2DViewers)
	{
		adapter->GetViewer()->Render();
	}
	for (auto adapter : m_3DViewers)
	{
		adapter->GetViewer()->Render();
	}
	timer->StopTimer();
	double elpsedTime = timer->GetElapsedTime(); // in milliseconds
	int fps = static_cast<int>(1.0 / elpsedTime);
	for (auto adpater : GetAllPackageViewers())
	{
		adpater->GetViewer()->Get3DViewer()->SetFPS(fps);
	}

}

void misGroupViewer::SetImagePlanePosition(const double pos[3])
{
	if (m_PanoramicCoordinateConverter)
		m_PanoramicCoordinateConverter->SetImageCoordinates(pos[0], pos[1], pos[2]);

	parcast::Point<double, 3> point(pos);
	for (auto adapter2D : m_2DViewers)
	{
		adapter2D->UpdatePosition(point);
	}
	for (auto adapter3D : m_3DViewers)
	{
		adapter3D->UpdatePosition(point);
	}

}

void misGroupViewer::SetTransformMatrix(vtkMatrix4x4* toolTransform)
{
	double toolTipPoint[] = { toolTransform->GetElement(0, 3), toolTransform->GetElement(1, 3), toolTransform->GetElement(2, 3) };
	if (m_PanoramicCoordinateConverter)
		m_PanoramicCoordinateConverter->SetImageCoordinates(toolTipPoint[0], toolTipPoint[1], toolTipPoint[2]);

	auto all3dViewers = Get3DViewers();
	for (auto viewer : all3dViewers)
	{
		viewer->SetToolTransform(misMathUtils::CreateTransform(toolTransform));
		viewer->GetCornerProperties()->SetMatrix(toolTransform);
		viewer->GetCursorService()->UpdateWidgetPosition();

	}
	auto all2dViewers = Get2DViewers();
	for (auto imageViewer : all2dViewers)
	{
		imageViewer->SetToolTransform(misMathUtils::CreateTransform(toolTransform));
		imageViewer->GetCornerProperties()->SetMatrix(toolTransform);
		imageViewer->GetCursorService()->UpdateWidgetPosition();
		imageViewer->UpdateImage(true);

	}
}


void misGroupViewer::Add2DInternalObservers()
{
	for (auto adapter2D : m_2DViewers)
	{

		AddObservers(adapter2D->GetViewer());
		ObserverType::Pointer      ContrastObserver = ObserverType::New();
		ContrastObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
		ObserverType::Pointer      backToMapObserver = ObserverType::New();
		backToMapObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
		ObserverType::Pointer      stateObsrever = ObserverType::New();
		stateObsrever->SetCallbackFunction(this, &misGroupViewer::ChangeInteractionState);
		adapter2D->AddInternalObservers(ContrastObserver, backToMapObserver, stateObsrever);

	}


}

void misGroupViewer::AddObservers(std::shared_ptr<IVolumeRenderer> viewer)
{
	typedef itk::MemberCommand< misGroupViewer >   ObserverType;
	ObserverType::Pointer      addNextLandmarkObserver = ObserverType::New();
	addNextLandmarkObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
	if (!viewer->HasObserver(misAddLandmarkEvent()))
	{
		viewer->AddObserver(misAddLandmarkEvent(), addNextLandmarkObserver);
	}

	ObserverType::Pointer      updateLandmarkStatusObserver = ObserverType::New();
	updateLandmarkStatusObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
	if (!viewer->HasObserver(misUpdateLandmarkStatusEvent()))
	{
		viewer->AddObserver(misUpdateLandmarkStatusEvent(), updateLandmarkStatusObserver);
	}

	ObserverType::Pointer      PointSelectObserver = ObserverType::New();
	PointSelectObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
	if (!viewer->HasObserver(misUpdatePositionEvent()))
	{
		viewer->AddObserver(misUpdatePositionEvent(), PointSelectObserver);
	}

	ObserverType::Pointer      ScrewWidgetUpdateObserver = ObserverType::New();
	ScrewWidgetUpdateObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
	if (!viewer->HasObserver(misScrewWidgetUpdateEvent()))
	{
		viewer->AddObserver(misScrewWidgetUpdateEvent(), ScrewWidgetUpdateObserver);
	}

	ObserverType::Pointer      ROIWidgetChangeObserver = ObserverType::New(); //misSegmentationView::UpdateAllWidgets
	ROIWidgetChangeObserver->SetCallbackFunction(this, &misGroupViewer::DistributeEvent);
	//	if (!viewer->HasObserver(misROIWidgetUpdateEvent()))
	{
		viewer->AddObserver(misROIWidgetUpdateEvent(), ROIWidgetChangeObserver);
	}
}

void misGroupViewer::UpdatePlaneVisibilities(std::vector<std::map<misPlaneEnum, bool>> planeVisiblities)
{
	unsigned int index = 0;
	for (auto viewer : m_2DViewers)
	{
		auto planeVisibilitySetting = std::make_unique<UpdatePlaneVisibilitiy>(
			viewer->GetSlicer(), std::make_shared<misVisibiltyHolder>(planeVisiblities[index]));
		misImageVisibilityMapGenerator mapGenerator(m_CurrentPackage.lock());
		planeVisibilitySetting->UpdatePlaneVisibilities(mapGenerator.GetVisibilityMap(),
			planeVisiblities[index]);
		index++;
	}
}


void  misGroupViewer::SetVolumeViewingType(misVolumeViewingTypes volumeViewingType)
{
	for (auto viewer : m_3DViewers)
		viewer->SetVolumeViewingType(volumeViewingType);
}


void misGroupViewer::InitializeGeneralTimers(void)
{
	for (int i = 0; i < m_StateVars.m_NumberOfGeneralTimers; i++)
	{
		m_StateVars.m_UsedGerenalTimers.push_back(false);
		m_StateVars.m_GeneralTimersString.push_back("");
		m_StateVars.m_GeneralAccumulatingTime.push_back(0);
		m_StateVars.m_GeneralAverageTime.push_back(-1);

		vtkTimerLog* newTimer = vtkTimerLog::New();
		m_StateVars.m_GeneralTimers.push_back(newTimer);
	}
}



void misGroupViewer::ResetCamera()
{
	for (auto viewer : m_2DViewers)
	{
		viewer->GetViewer()->Get3DViewer()->ResetCamera();
	}
}

void misGroupViewer::DisableWidget()
{
	for (auto viewer : GetAllPackageViewers())
	{
		viewer->GetViewer()->GetCursorService()->DisableWidget();
		viewer->GetViewer()->GetCursorService()->SetWidgetType(NoCursor);
	}


}

void misGroupViewer::SetRealTimeMode(bool val)
{
	m_StateVars.m_RealTimeMode = val;
	for (auto viewer : m_2DViewers)
	{
		viewer->SetRealTimeMode(val);
	}
}

void misGroupViewer::ResetMeasurment()
{
	for (auto viewer : m_2DViewers)
	{
		viewer->ResetMeasurment();
	}
}

void misGroupViewer::Add3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep)
{
	for (auto viewer : m_3DViewers)
		viewer->GetVolumeViewer()->AddRepresentation(PSurfaceRep);
}

int misGroupViewer::GetCurrentZoomPercentage()
{
	auto imageViewers = Get2DViewers();
	vector<int> tempPercentage;
	for (auto viewer : imageViewers)
	{
		tempPercentage.push_back(viewer->GetCameraService()->GetCurrentZoomPercentage());
	}
	int count = 1;
	for (int i = 1; i < tempPercentage.size(); i++)
	{
		if (tempPercentage[0] == tempPercentage[i])
		{
			count++;
		}
	}
	if (count == tempPercentage.size())
	{
		m_StateVars.m_CurrentZoomPercentage = tempPercentage[0];
	}
	return m_StateVars.m_CurrentZoomPercentage;
}

double misGroupViewer::GetCurrentZoomProportion()
{
	auto imageViewers = Get2DViewers();
	vector<double> tempProportion;
	for (auto viewer : imageViewers)
	{
		tempProportion.push_back(viewer->GetCameraService()->GetCurrentZoomProportion());
	}

	int count = 1;
	for (int i = 1; i < tempProportion.size(); i++)
	{
		if (tempProportion[0] == tempProportion[i])
		{
			count++;
		}
	}
	if (count == tempProportion.size())
	{
		m_StateVars.m_CurrentZoomProportion = tempProportion[0];
	}
	return m_StateVars.m_CurrentZoomProportion;
}

void misGroupViewer::SetOpacityValueToTexture(misUID imageUID, float val)
{
	for (auto viewer : m_2DViewers)
		viewer->SetOpacityValueToTexture(imageUID, val);
}

void misGroupViewer::SetVisibilityValueToTexture(misUID imageUID, bool val)
{
	for (auto viewer : m_2DViewers)
		viewer->SetVisibilityValueToTexture(imageUID, val);
}

void misGroupViewer::SetColorValueToTexture(misUID imageUID, misColorStruct Color)
{
	misDoubleColorStruct normalizedColor;
	normalizedColor.Red = (double)(Color.red / 255.0);
	normalizedColor.Green = (double)(Color.green / 255.0);
	normalizedColor.Blue = (double)(Color.blue / 255.0);
	for (auto viewer : m_2DViewers)
		viewer->SetColorValueToTexture(imageUID, normalizedColor);

}

void misGroupViewer::ApplyWindowlevel(misUID imageUID, misWindowLevelStr winLevStr)
{
	_ASSERT(winLevStr.GetWindowWidth() > 0);

	if (winLevStr.GetWindowWidth() <= 0)
		return;
	for (auto viewer : m_2DViewers)
		viewer->ApplyWindowlevel(imageUID, winLevStr);
}

misWindowLevelStr misGroupViewer::GetCurrentWindowLevel(misUID imageUID)
{
	misWindowLevelStr currentWinLevel;
	for (auto viewer : m_2DViewers)
	{
		currentWinLevel = viewer->GetCurrentWindowLevel(imageUID);
		break;
	}
	return  currentWinLevel;
}


void misGroupViewer::ChangeWidgetType(misCursorType cursorType)
{
	if (cursorType == NoCursor)
	{
		DisableWidget();
		return;
	}
	for (auto viewer : m_2DViewers)
	{
		auto imageViewer = viewer->GetViewer();
		imageViewer->GetCursorService()->ChangeWidgetType(cursorType);
	}
	for (auto viewer : m_3DViewers)
		viewer->GetVolumeViewer()->GetCursorService()->ChangeWidgetType(cursorType);
}

std::shared_ptr<IPackage3DDataRenderingAdapter> misGroupViewer::GetVolumePackageViewer()
{
	if (!m_3DViewers.empty())
		return m_3DViewers[0];
	return{};
}

vector<std::shared_ptr<I3DViewer>> misGroupViewer::GetAllViewers() const
{
	vector<std::shared_ptr<I3DViewer>> AllViewers;
	for (auto packageViewer : GetAllPackageViewers())
	{
		std::shared_ptr<I3DViewer> viwer3d = packageViewer->GetViewer()->Get3DViewer();
		AllViewers.push_back(viwer3d);
	}

	return AllViewers;
}



std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> misGroupViewer::GetAllPackageViewers() const
{
	std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> allviewer;
	for (auto viewer : m_2DViewers)
		allviewer.push_back(viewer);
	for (auto viewer : m_3DViewers)
		allviewer.push_back(viewer);
	return allviewer;
}


std::vector<std::shared_ptr<IVolumeSlicer>> misGroupViewer::Get2DViewers()
{
	vector<std::shared_ptr<IVolumeSlicer>> p2DViewers;
	for (auto viewer : m_2DViewers)
	{
		auto imageViewer = std::dynamic_pointer_cast<misVolumeSlicer>(viewer->GetViewer());
		if (imageViewer)
			p2DViewers.push_back(imageViewer);
	}
	return p2DViewers;
}

std::vector<std::shared_ptr<IVolume3DRenderer>>  misGroupViewer::Get3DViewers()
{
	vector<std::shared_ptr<IVolume3DRenderer>> p3DViewers;
	for (auto viewer : m_3DViewers)
		p3DViewers.push_back(viewer->GetVolumeViewer());
	return p3DViewers;
}



void misGroupViewer::SetErasedObjDisplayStatus(bool DisplayStatus)
{
	for (auto viewer : m_2DViewers)
	{
		auto gpu2DRep = viewer->GetSlicer()->GetImageRprensentaion();
		if (gpu2DRep)
			gpu2DRep->SetErasedObjDisplayStatus(DisplayStatus);
	}

}

void misGroupViewer::SetErasedObjColor(misColorStruct ColorStr)
{
	for (auto viewer : m_2DViewers)
	{
		auto gpu2DRep = viewer->GetSlicer()->GetImageRprensentaion();
		if (gpu2DRep)
			gpu2DRep->SetErasedObjectColor(ColorStr);
	}
}

void misGroupViewer::ResetAllLandMarks()
{
	for (auto packageViewer : GetAllPackageViewers())
		packageViewer->GetViewer()->ResetLandMarks();
}

void misGroupViewer::ShowLandmarks()
{
	for (auto viewer : m_3DViewers)
		viewer->GetVolumeViewer()->ShowLandmarks();
}

void misGroupViewer::HideLandmarks(misGroupViewer::TypeOfViewer typeOfviewer)
{
	if (typeOfviewer == ALLVIEWERS)
		for (auto packageViewer : GetAllPackageViewers())
			packageViewer->GetViewer()->HideLandmarks();
	else
		for (auto adapter : GetAllPackageViewers())
		{
			auto imageViewer = std::dynamic_pointer_cast<misVolumeSlicer> (adapter->GetViewer());
			if (imageViewer && typeOfviewer == D2VIEWER)
				imageViewer->HideLandmarks();
			else if (!imageViewer && typeOfviewer == D3VIEWER)
				adapter->GetViewer()->HideLandmarks();
		}
}



void misGroupViewer::InvalidateLandmark(int index)
{
	for (auto packageViewer : GetAllPackageViewers())
		packageViewer->GetViewer()->InvalidateLandmark(index);
}

void misGroupViewer::ChangeInteractionState(itk::Object *caller, const itk::EventObject & event)
{
	const misChangedInterctionStateEvent* pEventDat = dynamic_cast<const misChangedInterctionStateEvent*>(&event);
	if (pEventDat)
	{
		int state = pEventDat->Get();
	}
}

void misGroupViewer::Reset(void)
{
	for (auto packageViewer : GetAllPackageViewers())
		packageViewer->GetViewer()->Reset();
	m_PanoramicCoordinateConverter = nullptr;
}

void misGroupViewer::ClearViewers()
{
	m_2DViewers.clear();
	m_3DViewers.clear();
	m_Windows.clear();
}

void misGroupViewer::ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/,
	LANDMARKLABLETYPE lableType /*= NUMERICALLANDMARK*/)
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_2DViewers)
	{
		viewer->ImageLandmarkCaptureEnable(pLandmarkType, index, lableType);
	}
}


void misGroupViewer::ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index /*=-1*/)
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_2DViewers)
	{
		viewer->ImageLandmarkUpdateEnable(pLandmarkType, index);
	}
}
void misGroupViewer::ImageLandmarkUpdateDisable()
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_2DViewers)
	{
		viewer->ImageLandmarkUpdateDisable();
	}
}

void misGroupViewer::VolumeLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/, LANDMARKLABLETYPE lableType /*= NUMERICALLANDMARK*/)
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;

	for (auto viewer : m_3DViewers)
	{
 		viewer->GetVolumeViewer()->SetCurrentLandmark(pLandmarkType, index);
		viewer->GetVolumeViewer()->SetCurrentLandmarkLableType(lableType);
		viewer->GetVolumeViewer()->SetCaptureLandmarkFlag(true);

	}
	for (auto viewer : m_2DViewers)
	{
		viewer->GetViewer()->SetCurrentLandmark(pLandmarkType, index);
		viewer->GetViewer()->SetCurrentLandmarkLableType(lableType);
	}
}

void misGroupViewer::DistributeEvent(itk::Object *caller, const itk::EventObject& pEvent)
{
	size_t callerIndex = 0;

	auto const found = FindDistributerViewer(caller, callerIndex);

	if (typeid(pEvent) == typeid(misUpdatePositionEvent))
	{
		if (!found)
			return;
		HandleUpdatePositionEvent(dynamic_cast<const misUpdatePositionEvent*>(&pEvent));
	}


	if (typeid(pEvent) == typeid(misScrewWidgetUpdateEvent))
	{
		const misScrewWidgetUpdateEvent* pEventData = dynamic_cast<const misScrewWidgetUpdateEvent*>(&pEvent);
		auto planSelectedObserver = m_PlanSelectedInViewerObserver.lock();
		if (planSelectedObserver)
			planSelectedObserver->Selected(pEventData->Get().GetScrewUID());
	}

	misDistributionMap* targetMap = m_GroupViewSetting->FindDistributionMap(&pEvent);
	if (!targetMap)
		return;

	for (int i = 0; i < GetAllPackageViewers().size(); i++)
	{
		auto viewer = GetAllPackageViewers()[i]->GetViewer();

		if (viewer && targetMap->GetMap()[callerIndex][i] || typeid(pEvent) == typeid(misScrewWidgetUpdateEvent))
			viewer->ProcessRequest(&pEvent);
	}
	m_DummyObject->InvokeEvent(pEvent);
	if (m_ExternalEventViewer)
		m_ExternalEventViewer(caller, pEvent);
}

void misGroupViewer::HandleUpdatePositionEvent(const misUpdatePositionEvent* updatePositionEvent)
{
	misUpdatePositionInfoStruct info = updatePositionEvent->Get();
	auto conerMatrix = info.CornerTransform;
	double toolTipPoint[] = { conerMatrix->GetElement(0, 3), conerMatrix->GetElement(1, 3), conerMatrix->GetElement(2, 3) };

	if (m_PanoramicCoordinateConverter)
		m_PanoramicCoordinateConverter->SetImageCoordinates(toolTipPoint[0], toolTipPoint[1], toolTipPoint[2]);

	auto volumes = Get3DViewers();
	for (int i = 0; i < volumes.size(); i++)
	{
		volumes[i]->SetToolPosition(toolTipPoint[0], toolTipPoint[1], toolTipPoint[1]);
	}
}

void misGroupViewer::SetPanoCoordConverterToPackageViewers(std::shared_ptr<ISimpleDataPackage> pPackage)
{
	if (m_AppSetting->m_WorkflowButtonSet != Dental)
		return;

	if (m_RereadPanoramicCurve)
	{
		if (pPackage->GetParametricSpline().size() > 2)
		{
			m_PanoramicCoordinateConverter = make_shared<misPanoramicCoordinatesConverter>(
				pPackage->GetParametricSpline(), pPackage->GetMainImage()->GetROI().GetDepth());
			auto currentPosition = GetCurrentPosition();
			m_PanoramicCoordinateConverter->SetImageCoordinates(currentPosition[0], currentPosition[1], currentPosition[2]);
		}
		else
			m_PanoramicCoordinateConverter = nullptr;

		m_RereadPanoramicCurve = false;
	}
	std::shared_ptr<const IPanoramicCoordinatesConverter> readOnlyPanoramicConverter = m_PanoramicCoordinateConverter;

	for (auto adapter : GetAllPackageViewers())
	{
		adapter->SetPanoramicCoordinateConverter(readOnlyPanoramicConverter, adapter->GetViewer());
		if (readOnlyPanoramicConverter)
			adapter->SetDentalSpecialViewsEnable(adapter->GetViewer(), true);
		else
			adapter->SetDentalSpecialViewsEnable(adapter->GetViewer(), false);
	}
}


int misGroupViewer::ShowVolumes(VolumeDataDependencyListTypes NewVolumeDataDependencies)
{
	int numOfVolume = 0;
	for (auto adapter : GetAllPackageViewers())
	{
		adapter->SetWidgetType(m_GroupViewSetting->GetMainWidgetType());
		numOfVolume += adapter->ShowVolumes(NewVolumeDataDependencies);
	}
	for (auto adapter3D : m_3DViewers)
		AddObservers(adapter3D->GetVolumeViewer());
	return numOfVolume;
}

void misGroupViewer::ShowPackgeIn2DAdapter(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom)
{
	int d2index = 0;
	for (auto packageViwer : m_2DViewers)
	{

		packageViwer->ShowPackage(pPackage,
			m_AppSetting->m_VisulaizationSetting,
			m_AppSetting->m_segmentationSetting,
			m_AppSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel,
			resetZoom, m_GroupViewSetting->GetMainWidgetType(), m_DefaultVisibilityPlan[d2index]);
		if (std::dynamic_pointer_cast<misPackagePanoramicDataRenderingAdapter>(packageViwer))
			continue;
		d2index++;
	}

	ImageDependencyListTypes images = pPackage->GetImageDataDependencies();
	if (m_GroupViewSetting->GetKeepColor() && !images.empty())
	{

		misColorStruct defaultColor;
		misUID packageUID = pPackage->GetObjectUID();

		for (int i = 0; i < images.size(); i++)
		{
			defaultColor.SetWhiteColor();
			misUID imageUID = images[i]->GetImage()->GetUID();
			vector<misUID> UIDs;
			UIDs.resize(2);
			UIDs[0] = packageUID;
			UIDs[1] = imageUID;

			if (m_ImagesColor.find(UIDs) == m_ImagesColor.end())
				m_ImagesColor[UIDs] = defaultColor;
			defaultColor = m_ImagesColor[UIDs];
			SetColorValueToTexture(imageUID, defaultColor);
		}
	}
	Add2DInternalObservers();

}

void misGroupViewer::ShowPackageIn3dAdapter(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom)
{
	const auto index = 0;
	for (auto packageViwer : m_3DViewers)
	{
		packageViwer->SetWidgetType(m_GroupViewSetting->GetMainWidgetType());
		packageViwer->ShowPackage(pPackage,
			m_AppSetting->m_VisulaizationSetting,
			m_AppSetting->m_segmentationSetting,
			m_AppSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel,
			resetZoom, m_GroupViewSetting->GetMainWidgetType(), m_DefaultVisibilityPlan[index]);
		packageViwer->ModifyVolume();

	}
	for (auto adapter3D : m_3DViewers)
		AddObservers(adapter3D->GetVolumeViewer());
}

void misGroupViewer::ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom)
{
	if (!pPackage)
		return;
	m_CurrentPackage = pPackage;
	SetPanoCoordConverterToPackageViewers(pPackage);


	ShowPackgeIn2DAdapter(pPackage, resetZoom);
	ShowPackageIn3dAdapter(pPackage, resetZoom);

	auto  appSetting = misApplicationSetting::GetInstance();
	const auto  activateFpsDisplaying = appSetting->GetGUISetting().showFPSInRenderes;
	ShowFPS(activateFpsDisplaying);
}

void misGroupViewer::ShowPackageImages(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom)
{
	int d2index = 0;
	for (auto packageViwer : m_2DViewers)
	{
		packageViwer->ShowImages(pPackage, m_AppSetting->m_VisulaizationSetting,
			m_AppSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel,
			resetZoom, m_GroupViewSetting->GetMainWidgetType(), pPackage->GetMainImage());
		if (std::dynamic_pointer_cast<misPackagePanoramicDataRenderingAdapter>(packageViwer))
			continue;
		d2index++;
	}

	ImageDependencyListTypes images = pPackage->GetImageDataDependencies();
	if (m_GroupViewSetting->GetKeepColor() && !images.empty())
	{

		misColorStruct defaultColor;
		misUID packageUID = pPackage->GetObjectUID();

		for (int i = 0; i < images.size(); i++)
		{
			defaultColor.SetWhiteColor();
			misUID imageUID = images[i]->GetImage()->GetUID();
			vector<misUID> UIDs;
			UIDs.resize(2);
			UIDs[0] = packageUID;
			UIDs[1] = imageUID;

			if (m_ImagesColor.find(UIDs) == m_ImagesColor.end())
				m_ImagesColor[UIDs] = defaultColor;
			defaultColor = m_ImagesColor[UIDs];
			SetColorValueToTexture(imageUID, defaultColor);
		}
	}
	Add2DInternalObservers();
}

void misGroupViewer::ShowPlan(std::shared_ptr< parcast::IPackagePlanRel> rel)
{
	if (!rel)
	{
		return;
	}
	for (int i = GetAllPackageViewers().size() - 1; i >= 0; i--)
	{
		GetAllPackageViewers()[i]->ShowPlan(rel);
	}
}

void misGroupViewer::Remove3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep)
{
	if (!PSurfaceRep)
		return;
	auto viewers = GetAllViewers();
	for (auto viewer : viewers)
		viewer->RemoveRepresentation(PSurfaceRep);
}

void misGroupViewer::ReleaseResource()
{
	for (auto packageViwer : m_2DViewers)
	{
		packageViwer->ReleaseImageResources();
		packageViwer->Reset();
	}
	for (auto packageViwer : m_3DViewers)
	{
		packageViwer->ReleaseImageResources();
		packageViwer->Reset();
	}
	ResetAllLandMarks();
	ImageLandmarkCaptureDisable();
	ImageLandmarkUpdateDisable();
	VolumeLandmarkCaptureDisable();
	m_CurrentPackage.reset();
}



void misGroupViewer::UpdateViewingPropertiesTexture(bool DisplayErasedObjectStatus, misColorStruct ColorStr)
{
	SetErasedObjColor(ColorStr);
	SetErasedObjDisplayStatus(DisplayErasedObjectStatus);

	for (auto viewer : m_2DViewers)
	{

		auto gpu2DRep = viewer->GetSlicer()->GetImageRprensentaion();

		if (gpu2DRep)
			gpu2DRep->SetWindowLevelTransferFunction();
	}

}

parcast::Point<double, 3> misGroupViewer::GetCurrentPosition()
{
 	if (m_2DViewers.empty())
		return{};
	return m_2DViewers[0]->GetViewer()->GetCornerProperties()->GetCurrentPosition();
}

void misGroupViewer::SetGroupViewerSetting(std::shared_ptr<IGroupViewerSetting> pSettingStr)
{
	m_GroupViewSetting = pSettingStr;
}

std::shared_ptr<IGroupViewerSetting> misGroupViewer::GetGroupViewerSetting()
{
	return m_GroupViewSetting;
}

void  misGroupViewer::GetCurrentPosition(double currentPos[3])
{
	currentPos[0] = -1;
	currentPos[1] = -1;
	currentPos[2] = -1;
	auto viewers = Get3DViewers();
	if (viewers.empty())
		return;
	auto  pos = viewers[0]->GetCornerProperties()->GetCurrentPosition();
	currentPos[0] = pos[0];
	currentPos[1] = pos[1];
	currentPos[2] = pos[2];
}

void misGroupViewer::ResetLandMarks(misLandmarkType lndType)
{
	for (auto packageViwer : GetAllPackageViewers())
		packageViwer->GetViewer()->ResetLandMarks(lndType);
}


void misGroupViewer::SetImageColor(vector<misUID> UIDs, misColorStruct imageColor)
{
	m_ImagesColor[UIDs] = imageColor;
}

misColorStruct misGroupViewer::GetImageColor(vector<misUID> UIDs)
{
	misColorStruct resColor;
	resColor.SetBlackColor();
	map<vector<misUID>, misColorStruct>::iterator imageColorIter;

	imageColorIter = m_ImagesColor.find(UIDs);
	if (imageColorIter != m_ImagesColor.end())
	{
		resColor = imageColorIter->second;
	}
	else
		_ASSERT(0 == 1);
	return resColor;
}

void misGroupViewer::ShowFPS(bool showFPS)
{
	auto allViewers = GetAllViewers();
	for (int i = 0; i < allViewers.size(); i++)
	{
		if (allViewers[i])
		{
			if (true == showFPS)
				allViewers[i]->ShowFPSOn();
			else
				allViewers[i]->ShowFPSOff();
		}
	}
}


void misGroupViewer::ImageLandmarkCaptureDisable()
{
	for (auto viewer : m_2DViewers)
	{
		viewer->ImageLandmarkCaptureDisable();
	}
}

void misGroupViewer::VolumeLandmarkCaptureDisable()
{
	for (auto viewer : m_3DViewers)
	{
		viewer->GetVolumeViewer()->SetCurrentLandmarkType(UnkownLandmarkType);
		viewer->GetVolumeViewer()->SetCaptureLandmarkFlag(false);
		viewer->GetVolumeViewer()->SetCurrentLandmarkIndex(-1);
	}
}

void misGroupViewer::UpdateImageAnnotation(misVolumeSlicer* imageViewer)
{
	imageViewer->SetAnnotationEnabled(m_AppSetting->m_VisulaizationSetting.ShowImageAnnotation);
	imageViewer->SetProstrateState(m_AppSetting->m_VisulaizationSetting.ProstrateState);
	imageViewer->SetSurgeryType(m_AppSetting->m_WorkflowButtonSet);
}

void misGroupViewer::SetOrientation(IMAGEORIENTATION newOrientation)
{
	for (auto packageViewer : m_2DViewers)

		packageViewer->SetOrientation(newOrientation);

}

void misGroupViewer::ChangeViewerToMultipleImages()
{
	int index = 0;
	for (auto viewer : m_2DViewers)
	{
		viewer->SetOrientation(IMAGEORIENTATION(index));
		viewer->UpdateSliderInGUI();
		index++;
	}

}


std::vector<std::shared_ptr<IVolumeRenderer>> misGroupViewer::GetAllLandMarkViewers()const
{
	vector<std::shared_ptr<IVolumeRenderer>> AllViewers;
	auto allpackge = GetAllPackageViewers();
	for (auto packgeViewer : allpackge)
	{
		AllViewers.push_back(packgeViewer->GetViewer());

	}
	return AllViewers;
}


void misGroupViewer::UpdateRepresentationTransforms(std::shared_ptr<ISimpleDataPackage> package)
{
	if (!package)
		return;
	for (auto packgeViewer : GetAllPackageViewers())
		packgeViewer->UpdateRepresentationTransforms(packgeViewer->GetViewer(), package);

}

void misGroupViewer::SetDentalSurgeryType(DentalSurgeryType surgeryType)
{
	for (auto packgeViewer : GetAllPackageViewers())
		packgeViewer->GetViewer()->SetDentalSurgeryType(surgeryType);
}

void misGroupViewer::SetWidgetLineWeight(double weight)
{
	for (auto packgeViewer : GetAllPackageViewers())
		packgeViewer->GetViewer()->GetCursorService()->SetWidgetLineWeight(weight);
}


bool misGroupViewer::FindDistributerViewer(itk::Object* caller, size_t& viewerIndex)
{
	auto containerRepresnetation = dynamic_cast<misRepresentationContainer*>(caller);
	auto containerViewer = dynamic_cast<misVolumeRendererContainer*>(caller);

	std::shared_ptr<IRepresentation> callerRepresentation;
	IVolumeRenderer* callerViewer = nullptr;

	if (containerRepresnetation)
		callerRepresentation = containerRepresnetation->GetRepresenation();
	if (containerViewer)
		callerViewer = containerViewer->GetViewer();

	if ((callerRepresentation) || (callerViewer))
	{
		for (int i = 0; i < GetAllPackageViewers().size(); i++)
		{
			auto viewer = GetAllPackageViewers()[i]->GetViewer();
			if (viewer)
			{
				const bool imageMatch = viewer.get() == callerViewer;
				bool repMatch = false;
				auto currentRep = std::dynamic_pointer_cast<IRepresentation>(viewer->GetMainRepresentation());
				if (currentRep)
					repMatch = currentRep == callerRepresentation;
				if (repMatch || imageMatch)
				{
					viewerIndex = i;
					return true;
				}
			}
		}
	}
	return false;
}


void misGroupViewer::ModifyBiopsyPoint(misLandmarkType landmarkType)
{
	auto volumelist = Get3DViewers();
	if (volumelist.empty())
		return;
	std::shared_ptr< IVolume3DRenderer> volumeViewer = volumelist[0];
	if (!volumeViewer)
		return;
	volumeViewer->SetCurrentLandmarkType(landmarkType);
	ImageLandmarkUpdateDisable();
	VolumeLandmarkCaptureDisable();
	ImageLandmarkUpdateEnable(landmarkType, 0);
}


void misGroupViewer::UpdateLandmarks(misLandmarkInfoStruct &landmarkInfo)
{
	auto viewers = GetAllLandMarkViewers();
	for (auto &viewer : viewers)
	{
		if (viewer->GetTypeDirection() == PanormaicView)
			continue;

		if (viewer && landmarkInfo.validity)
			viewer->AddLandmark(landmarkInfo.landmarkIndex, landmarkInfo.CurrentPosition.GetDataPointer(),
				landmarkInfo.Landmarktype, landmarkInfo.landmarkLableType);
	}
}

std::shared_ptr<IVolumeRenderer> misGroupViewer::GetViewerByType(misViewerTypeDirection type) const
{
	std::shared_ptr<IVolumeRenderer> viewer = nullptr;
	auto viewers = GetAllLandMarkViewers();
	auto foundViewer = std::find_if(viewers.begin(), viewers.end(),
		[type](auto viewer) -> bool
	{
		return viewer->GetTypeDirection() == type;
	});

	if (foundViewer == viewers.end())
		return nullptr;

	viewer = *foundViewer;
	return viewer;
}

void misGroupViewer::SetExternalEventViewer(std::function<void(itk::Object *caller, const itk::EventObject& pEvent) > val)
{
	m_ExternalEventViewer = val;
}


void misGroupViewer::ClippingOff()
{
	auto volumeViewers = Get3DViewers();
	for (int i = 0; i < volumeViewers.size(); i++)
		volumeViewers[i]->ClippingOff();
}


void misGroupViewer::SetPanoramicTransformConvertor(std::shared_ptr<IPanoramicTransformConverter> panoramicTransformConvertor)
{
	m_PanoramicTransformConvertor = panoramicTransformConvertor;

}

void misGroupViewer::UpdateSliderInGUI()
{
	for (auto adapter : m_2DViewers)
	{
		adapter->UpdateSliderInGUI();
	}
}

void misGroupViewer::Freeze()
{
	SetRealTimeMode(false);
	UpdateSliderInGUI();
}

void misGroupViewer::Unfreeze()
{
	SetRealTimeMode(true);

}

void misGroupViewer::SetObliqueFlag(bool isOblique)
{
	auto obliqueObserver = m_ObliqueChangedObserver.lock();
	if (obliqueObserver)
		obliqueObserver->Changed(isOblique);
	for (auto viewer : m_2DViewers)
	{

		viewer->SetObliqueFlag(isOblique);
		viewer->UpdateImageAnnotation();
	}
	for (auto viewer : m_3DViewers)
	{
		viewer->SetObliqueFlag(isOblique);
	}
}

void misGroupViewer::SetCroppingDirection(misCroppingDirectionInVR croppingDirection, const double* center, bool isOblique)
{
	if (isOblique)
		return;
	auto p3DViewers = Get3DViewers();
	for (int i = 0; i < p3DViewers.size(); i++)
	{
		p3DViewers[i]->SetToolPosition(center[0], center[1], center[2]);
		p3DViewers[i]->Get3DViewer()->SetCroppingDirection(croppingDirection);
	}
}

void misGroupViewer::AddLandmark(unsigned int landmarkIndex, itk::Point<double, 3> landmark, misLandmarkType landmarkType,
	LANDMARKLABLETYPE lableType)
{
	for (const auto adapter2D : m_2DViewers)
	{
		adapter2D->GetViewer()->AddLandmark(landmarkIndex, landmark.GetDataPointer(), landmarkType, lableType);
	}
	for (const auto adapter3D : m_3DViewers)
	{
		adapter3D->GetViewer()->AddLandmark(landmarkIndex, landmark.GetDataPointer(), landmarkType, lableType);
	}
}

void misGroupViewer::Reset2DZoom()
{
	auto tmp2DViewers = Get2DViewers();
	for (int i = 0; i < tmp2DViewers.size(); i++)
	{
		tmp2DViewers[i]->ResetZoom();
	}
}


void misGroupViewer::ClipVolumeWithObliquePlane(const double* planeNormal, const double* center)
{
	tgt::dvec3 toolOrientation;
	std::copy(planeNormal, planeNormal + 3, toolOrientation.elem);
	vector<std::shared_ptr< IVolume3DRenderer>> p3DViewers = Get3DViewers();
	for (int i = 0; i < p3DViewers.size(); i++)
	{
		p3DViewers[i]->SetToolPosition(center[0], center[1], center[2]);
		p3DViewers[i]->ClippingOn();
		tgt::dvec3 position(center[0], center[1], center[2]);
		// ax + by + cz + d = 0 being the plane equation,
		double d = tgt::dot(-toolOrientation, position);
		tgt::vec4 vec = tgt::vec4(-toolOrientation, d);
		p3DViewers[i]->SetClippingPlane(vec);
		p3DViewers[i]->ModifyVolume();
	}
}

void misGroupViewer::SetAnnotationDetailToViewer()
{
	ApplyShowAnnotationDetailToViewer(true);
}

void misGroupViewer::ClearAnnotationDetailFromViewer()
{
	ApplyShowAnnotationDetailToViewer(false);
}

void misGroupViewer::ApplyShowAnnotationDetailToViewer(bool show)
{
	auto viwerList = Get2DViewers();
	for_each(viwerList.begin(), viwerList.end(), [show](auto viewer)
	{
		if (viewer)
			viewer->SetShowAnnotationDetail(show);
	});
}

void misGroupViewer::UpdateViewerROI(misROI roi)
{
	auto  viewers = GetAllLandMarkViewers();
	for_each(viewers.begin(), viewers.end(), [&](auto viewer)
	{
		viewer->SetROI(roi);
		viewer->ROIWidgetActivation(true);
	});
	for (auto volumeViewer : m_3DViewers)
	{
		volumeViewer->ModifyVolume();
	}
}
void misGroupViewer::ResetROI(misROI roi)
{
	auto viewers = GetAllLandMarkViewers();
	for (auto viewer : viewers)
	{
		viewer->SetROI(roi);
		viewer->ResetROI();
		viewer->ROIWidgetActivation(false);
	}
}
void misGroupViewer::ResetROI()
{
	auto viewers = GetAllLandMarkViewers();
	for (auto viewer : viewers)
	{
		if (viewer)
			viewer->ResetROI();
	};
}


void misGroupViewer::UpdateViewerWithImage(std::shared_ptr<IImage> image)
{
	misOpenglTexture* imageTexure = misImageToTextureMap::GetInstance()->LookUpTexture(image);
	auto viewers = Get2DViewers();
	for_each(viewers.begin(), viewers.end(), [&](auto imageViewer)
	{
		auto imagePlane = std::dynamic_pointer_cast<misPlanarRepresentation>(imageViewer->GetMainRepresentation());
		imagePlane->SetImageSource(image, FirstImage, MainImage);
		imagePlane->SetTexture(FirstImage, MainImage, imageTexure, imageTexure->GetTexturePropertyStrct());
	});
}



void misGroupViewer::SetRoiWidgetActivation(const double* roi, bool activation)
{

	auto viewers = GetAllLandMarkViewers();
	for (auto viewer : viewers)
	{
		if (activation)
			viewer->SetROI(roi);
		else
			viewer->ResetROI();
		viewer->ROIWidgetActivation(activation);
	};
}

void misGroupViewer::UpdatePanoramicCurve()
{
	m_RereadPanoramicCurve = true;
}

std::shared_ptr<IPanoramicCoordinatesConverter> misGroupViewer::GetPanoramicCoordinateConverter() const
{
	return m_PanoramicCoordinateConverter;
}

unsigned long misGroupViewer::AddObserver(const itk::EventObject & event, itk::Command *command)
{
	return m_DummyObject->AddObserver(event, command);
}

bool misGroupViewer::HasObserver(const itk::EventObject & event) const
{
	return m_DummyObject->HasObserver(event);
}

void misGroupViewer::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->InvokeEvent(event);
}

std::shared_ptr<Iwindows> misGroupViewer::Injector::CreateRenderingWindow()
{
	return std::make_shared<misWindow>();
}

void misGroupViewer::ShowPackage(std::shared_ptr<ISimpleDataPackage> package, const misVisualizationSetting& vs,
	const misSegmentationSetting& segmentationSetting, double minOpacity, bool resetZoom, misCursorType pWidgetType,
	std::map<misPlaneEnum, bool> pPlaneVisible)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->ShowPackage(package, vs, segmentationSetting, minOpacity, resetZoom, pWidgetType, pPlaneVisible);
	}
}

void misGroupViewer::ShowVolume(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->ShowVolume(volumeProp);
	}
}

void misGroupViewer::UpdateColormap(std::shared_ptr<IVolumeDataDependency> volumeProp)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->UpdateColormap(volumeProp);
	}
}

void misGroupViewer::UpdateRepresentationTransforms(std::shared_ptr<IVolumeRenderer> viewer,
	std::shared_ptr<ISimpleDataPackage> newPackage)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->UpdateRepresentationTransforms();
	}
}

void misGroupViewer::UpdateRepresentationTransforms()
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->UpdateRepresentationTransforms();
	}
}

void misGroupViewer::ReleaseImageResources()
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->ReleaseImageResources();
	}
}

void misGroupViewer::SetWidgetType(misCursorType pWidgetType)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->SetWidgetType(pWidgetType);
	}
}

std::shared_ptr<IVolumeRenderer> misGroupViewer::GetViewer()
{
	return  nullptr;
}

void misGroupViewer::SetSceneReferenceCoordinateSystem(const std::string& coordSysUid,
	std::shared_ptr<ISimpleDataPackage> package)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->SetSceneReferenceCoordinateSystem(coordSysUid, package);
	}
}

void misGroupViewer::SetDentalSpecialViewsEnable(std::shared_ptr<IVolumeRenderer> viewer, bool enabled)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->SetDentalSpecialViewsEnable(viewer, enabled);
	}
}

void misGroupViewer::SetPanoramicCoordinateConverter(
	std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter, std::shared_ptr<IVolumeRenderer> viewer)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->SetPanoramicCoordinateConverter(coordinateConverter, viewer);
	}
}

int misGroupViewer::ShowSegmentedObjects(const misSegmentationSetting& segmentationSetting,
	ImageContainedPolydataDependencyListTypes containedPolys,
	double minOpacity)
{
	int numberOfSegmneted = 0;
	for (auto packageAdapter : GetAllPackageViewers())
	{
		numberOfSegmneted += packageAdapter->ShowSegmentedObjects(segmentationSetting, containedPolys, minOpacity);
	}
	return numberOfSegmneted;
}

int misGroupViewer::ShowPlans(std::shared_ptr<IVolumeRenderer> viewer,
	std::shared_ptr<PlanDataListDependencyTypedef> rels)
{
	int numOfPlan = 0;
	for (auto packageAdapter : GetAllPackageViewers())
	{
		numOfPlan += packageAdapter->ShowPlans(viewer, rels);
	}
	return numOfPlan;
}

void misGroupViewer::UpdatePosition(parcast::Point<double, 3> position)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->UpdatePosition(position);
	}
}

void misGroupViewer::SetVisibilityOfSegmentedImage(misUID imageuid, bool val)
{
	for (auto packageAdapter : GetAllPackageViewers())
	{
		packageAdapter->SetVisibilityOfSegmentedImage(imageuid, val);
	}
}

void misGroupViewer::ChangeViewerToSameImages()
{
	for (auto packageAdapter : m_2DViewers)
	{
		packageAdapter->UpdateSliderInGUI();
	}
}

std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp>  misGroupViewer::GetRenderingToolExtension()const
{
	std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp> vieweres;

	auto lViewers = GetAllLandMarkViewers();
	int viewerIndex = 0;
	for (int i = 0; i < m_GroupViewSetting->GetNumberOfGroupElement(); i++)
	{
		if (m_GroupViewSetting->GetElement(i).GetTypeOfViewer() == Video)
			continue;
		for (int j = 0; j < m_GroupViewSetting->GetElement(i).GetNumberOfViewer(); j++)
		{
			vieweres[lViewers[viewerIndex]].UpdateByVirtualTip =
				m_GroupViewSetting->GetElement(i).IsUpdateByVirtualTip();
			vieweres[lViewers[viewerIndex]].ShowToolExtenstion =
				m_GroupViewSetting->GetElement(i).GetShowToolExtension();
			viewerIndex++;
		}
	}

	return vieweres;

}

void misGroupViewer::RefreshCurrentPackage()
{
	auto packge = m_CurrentPackage.lock();
	if (!packge)
		return;
	ShowPackage(packge, false);
}

void misGroupViewer::SetPlanCentricViewAngle(double angle)
{
	auto viewers = GetAllLandMarkViewers();
	for (auto& viewer : viewers)
	{
		viewer->GetCornerProperties()->SetPlanCentricViewAngle(angle);
		viewer->GetCursorService()->UpdateWidgetPosition();
	}
}

void misGroupViewer::Add2DViewer(std::shared_ptr<IPackage2DDataRenderingAdapter> adapter, std::shared_ptr<Iwindows> window)
{
	m_2DViewers.push_back(adapter);
	m_Windows.push_back(window);
}

void misGroupViewer::Add3DViewer(std::shared_ptr<IPackage3DDataRenderingAdapter> adapter, std::shared_ptr<Iwindows> window)
{
	m_3DViewers.push_back(adapter);
	m_Windows.push_back(window);
}

void misGroupViewer::SetDefaultVisibilityMap(std::vector<std::map<misPlaneEnum, bool>> map)
{
	m_DefaultVisibilityPlan = map;
}

void misGroupViewer::SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val)
{
	for (auto adpater : GetAllPackageViewers())
	{
		adpater->SetVisiblityOfColorMap(planeIndex, val);;
	}
}

void misGroupViewer::SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val)
{
	for (auto adpater : GetAllPackageViewers())
	{
		adpater->SetColorMapTransFuncID(planeIndex, val);;
	}
}

void misGroupViewer::SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal)
{
	for (auto adpater : GetAllPackageViewers())
	{
		adpater->SetColorValueToTexture(planeIndex, colorVal);;
	}
}

void misGroupViewer::SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)
{
	for (auto adpater : GetAllPackageViewers())
	{
		adpater->SetOpacityValueToTexture(planeIndex, opacityValue);;
	}
}

std::vector<std::shared_ptr<Iwindows>> misGroupViewer::GetAllWindow()
{
	return m_Windows;
}


void misGroupViewer::WarnFlyZone(const  vector<PropertiesOfPixelInImageType>& FlyZoneStatus)
{
	auto WidgetPos = GetCurrentPosition();
	auto packge = m_CurrentPackage.lock();
	if (!packge)
		return;
	auto imageContainedPolydatas = packge->GetImageContainedPolydataDependencies();
	const char* FlyZoneTextBuff = "";
	string tempStr;
	for (int i = 0; i < FlyZoneStatus.size(); i++)
	{
		for (int j = 0; j < FlyZoneStatus[i].size(); j++)
		{
			if (FlyZoneStatus[i][j].pixelType != misBackground)
			{
				tempStr.append(misEnumUtilities::ConvertFlyZoneTypeEnumToString(FlyZoneStatus[i][j].pixelType));
				tempStr.append(" Object : ");
				tempStr.append(FlyZoneStatus[i][j].PolyDataName);
			}
		}
	}
	if (!tempStr.empty())
	{
		FlyZoneTextBuff = tempStr.data();
	}
	auto imageViewers = Get2DViewers();
	for (int i = 0; i < imageViewers.size(); i++)
	{
		if (!flyZoneStatusText[i])
		{
			flyZoneStatusText[i] = vtkTextActor::New();
			imageViewers[i]->GetRenderer()->AddActor(flyZoneStatusText[i]);
		}
		flyZoneStatusText[i]->SetInput(FlyZoneTextBuff);
		flyZoneStatusText[i]->SetPosition(10, 10);
	}
}

