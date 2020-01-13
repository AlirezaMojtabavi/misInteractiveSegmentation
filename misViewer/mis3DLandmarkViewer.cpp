#include "stdafx.h"
#include "mis3DVolumeRenderer.h"

#include "Biopsy3dPlanCrossSectionFunction.h"
#include "Dental3dPlanCrossSectionFucntion.h"
#include "IVolumeRepresentation.h"
#include "misApplicationSetting.h"
#include "misColorPointWidget.h"
#include "misDistributionEvent.h"
#include "misEnumUtilities.h"
#include "misLandmarkVisualizer.h"
#include "misManModelrepresentation.h"
#include "misMemberCommandCallback.h"
#include "misPanoramicCoordinatesConverter.h"
#include "misScrewCompound.h"
#include "misSeedRepresentation.h"
#include "misCursorService.h"
#include "misMathUtils.h"
#include "DentalSurgeryType.h"
#include "mis2dImplant.h"
#include "I3DPlanCrossSectionFunction.h"
#include "LandmarkLablePositionCalculator.h"
#include "CameraPositionCalculator.h"

using namespace std;
using namespace parcast;

#define  LINEDISTANCELANDMARK 20

mis3DVolumeRenderer::mis3DVolumeRenderer(std::shared_ptr<ScrewListType> screwServiceList,std::shared_ptr<Iwindows> pWindow, int index,std::shared_ptr<I3DViewer> viewer,
                                         std::shared_ptr<ICornerProperties> cornerProperties,
                                         std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
                                         std::unique_ptr<IInitializeScrewWidget> screwIntilizer,
                                         std::shared_ptr<IVolumeRayCaster> volumeRenderer)
	: m_currentLandmarkIndex(-1),
	  m_CurrentLandmarkType(UnkownLandmarkType),
	  m_CurrentLandmarkLableType(NUMERICALLANDMARK),
	  m_CaptureLandmark(false),
	  m_UpdateLandmark(false),
	  m_ShowLabels(true),
	  m_IsPointWidgetObserverAdded(false),
	  m_IsPointSelectObserverAdded(false),
	  m_CursorService(std::make_shared<misCursorService>()),
	  m_ClippingPlaneWidget(vtkSmartPointer<misPlaneWidget>::New()),
	  m_ROIBox(vtkSmartPointer<misROIWidget>::New()),
	  m_IsROIActive(false),
	  m_maxLandmarkElementSize(20),
	  m_ShowManModel(true),
	  m_ManModel(std::make_shared<misManModelrepresentation>("Man Model")),
	  m_DentalSpecialViewEnable(false),
	  m_3DViewer(viewer),
	  m_VolumeRnderer(volumeRenderer),
	  m_DentalSurgeryType(DentalSurgeryType::MAXILLA),
	  m_UpdateLandmarkCameraViewer(updateLandmarkCameraViewer),
	  m_Cornerproperties(cornerProperties),
	  m_InitializeScrewWidget(std::move(screwIntilizer)),
	m_ScrewServiceList(screwServiceList)
{
	SetWindow(pWindow, index);
	m_Renderer = m_3DViewer->GetRenderer();
	m_landMarkList.resize(m_maxLandmarkElementSize);
	std::generate(m_landMarkList.begin(), m_landMarkList.end(), []()
	{
		return std::make_shared<misLandmarkPointerRepresentation>();
	});
	m_ViewPort = viewer->GetViewPort();
	m_IndexInGroup = viewer->GetIndexInGroup();
	m_CoordinateRenderers = viewer->GetCoordinateRenderers();
	m_SettingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
}
mis3DVolumeRenderer::~mis3DVolumeRenderer()
{
	Reset();

}

void mis3DVolumeRenderer::SetToolPosition(double xCoord, double yCoord, double zCoord)
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->SetToolPosition(xCoord, yCoord, zCoord);
}

void mis3DVolumeRenderer::InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation)
{
	auto screwCompound = m_InitializeScrewWidget->Initialize(initVals, orientation);
	if (screwCompound)
	{
		auto screwWidgetCallback = misMemberCommandCallback<mis3DVolumeRenderer>::New();
		screwWidgetCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::UpdateScrewWidget);
		if (!screwCompound->GetWidget()->HasObserver(vtkCommand::EndInteractionEvent))
			screwCompound->GetWidget()->AddObserver(vtkCommand::EndInteractionEvent, screwWidgetCallback);
	}
	
}

vtkRenderer* mis3DVolumeRenderer::GetRenderer()
{
	return m_Renderer;
}

misViewerTypeDirection mis3DVolumeRenderer::GetTypeDirection(void) const
{
	return m_3DViewer->GetTypeDirection();
}


void mis3DVolumeRenderer::HighlightScrew(misUID screwUID, bool highlight)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		(*m_ScrewServiceList)[i]->HighlightScrew(false);
		if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
		{
			(*m_ScrewServiceList)[i]->HighlightScrew(highlight);
		}
	}
}

void mis3DVolumeRenderer::AddLandmark(int index, const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType)
{
	if (m_landMarkList[index]->IsValid())
	{
		if (m_landMarkList[index]->GetCategory() == category)
		{
			SetLandmarkPosition(index, position);
			const auto boundingBox = m_MainRepresentation->GetBoundingBox();
			const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
			const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");

			auto lablePosition = GetLablePosition(position, boundingBox, handleLength, offsetAngle);
			m_landMarkList[index]->SetLabelPosition(lablePosition.Elements());
			UpdateLandmarkCameraView(index);
			return;
		}
	}
	AddOrSetNextLandmark(index, position, category, lableType);
}
//==================================================================================================================
int mis3DVolumeRenderer::AddNextLandmark(const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType)
{
	misCamera camera(m_3DViewer->GetRenderer()->GetActiveCamera()->GetPosition(), m_3DViewer->GetRenderer()->GetActiveCamera()->GetFocalPoint(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetViewUp());
	const parcast::Point<double, 3> point(position);
	misLandmarkVisualizer landmarkVisualizer(
		m_MainRepresentation->GetBoundingBox(), camera, m_landMarkList, category,
		lableType, m_ShowLabels, point, GetTypeDirection());

	AddRepresentation(landmarkVisualizer.GetRepresenTation());
	return landmarkVisualizer.GetIndex();
}

int mis3DVolumeRenderer::AddOrSetNextLandmark(const double position[3], misLandmarkType category,
	const LANDMARKLABLETYPE lableType)
{
	int index = -1;
	for (int i = 0; i < m_landMarkList.size(); i++)
	{
		if (!(m_landMarkList[i]->IsValid()))
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		index = static_cast<int> (m_landMarkList.size());
		auto emptyPointer = std::make_shared<misLandmarkPointerRepresentation>();
		emptyPointer->InValidate();
		m_landMarkList.push_back(emptyPointer);
	}

	if (m_landMarkList[index]->IsValid())
	{
		SetLandmarkPosition(index, position);
	}
	else
	{
		AddOrSetNextLandmark(index, position, category, lableType);
	}
	return index;
}

PointD3 mis3DVolumeRenderer::GetLablePosition(const double* position, const itk::BoundingBox<double, 3, double>::Pointer
	& boundingBox, const double handleLength, const double offsetAngle) const
{
	auto lablePositionCalculator = LandmarkLablePositionCalculator(PointD3(boundingBox->GetMinimum().GetDataPointer()),
		PointD3(boundingBox->GetMaximum().GetDataPointer()), handleLength, offsetAngle);
	const auto landmarkPos = PointD3(position[0], position[1], position[2]);
	return lablePositionCalculator.GetLabelPosition(landmarkPos, GetTypeDirection());
}

void mis3DVolumeRenderer::AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType)
{
	auto pLnd = std::make_shared<misLandmarkPointerRepresentation>(index + 1, NORMAL, category, position, lableType);
	pLnd->Validate();
	pLnd->SetVisibilityOn();
	const auto boundingBox = m_MainRepresentation->GetBoundingBox();
	const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
	const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");
	auto lablePosition = GetLablePosition(position, boundingBox, handleLength, offsetAngle);
	pLnd->SetLabelPosition(lablePosition.Elements());
	AddRepresentation(pLnd->GetSurface());
	m_landMarkList[index] = pLnd;
}

void mis3DVolumeRenderer::AddLandmarks(std::vector<mislandMarkPosAndStatusStr> landmarkList)
{
	AddLandmarks(landmarkList, GeneralSeed, NUMERICALLANDMARK);
}

void mis3DVolumeRenderer::AddLandmarks(std::vector<mislandMarkPosAndStatusStr> landmarkList, misLandmarkType landmarkType,
	LANDMARKLABLETYPE lableType/*= NUMERICALLANDMARK*/)
{
	ResetLandMarks();

	const auto landmarkSize = landmarkList.size();
	int i = 0;
	if (landmarkSize > 0)
	{
		for_each(landmarkList.begin(), landmarkList.end(), [&](mislandMarkPosAndStatusStr landmark)
		{
			if (landmark.status == ValidPoint)
			{
				double pos[3];
				std::copy(landmark.position.GetItkPoint().Begin(), landmark.position.GetItkPoint().End(), pos);
				AddLandmark(i, pos, landmarkType, lableType);
				m_Cornerproperties->SetCurrentPosition(pos);
				m_CursorService->UpdateWidgetPosition();
				misLandmarkInfoStruct landmarkStr;
				landmarkStr.Landmarktype = landmarkType;
				landmarkStr.CurrentPosition = pos;
				landmarkStr.landmarkIndex = i;
				landmarkStr.landmarkLableType = lableType;
				misAddLandmarkEvent LndEv;
				LndEv.Set(landmarkStr);
				InvokeEvent(LndEv);
			}
			i++;
		});
	}
}

void mis3DVolumeRenderer::RemoveLandmarkRepresentation(int index)
{
	const auto size = m_landMarkList.size();
	if ((index < size) && (index >= 0))
	{
		const auto  prep = m_landMarkList[index];
		RemoveRepresentation(prep->GetSurface());
	}
}

void mis3DVolumeRenderer::SetViewCentrePosition(const double position[3])
{
	if (!position)
	{
		return;
	}
	m_Cornerproperties->SetCurrentPosition(position);
	if (m_CursorService)
		m_CursorService->UpdateWidgetPosition();
	misUpdatePositionEvent ev;
	misUpdatePositionInfoStruct updateStr;
	updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
	updateStr.IsCameraUpdate = true;
	ev.Set(updateStr);
	InvokeEvent(ev);
}

void mis3DVolumeRenderer::SetLandmarkPosition(const int index, const double position[3])
{
	_ASSERT(position != NULL);
	if (!position)
	{
		return;
	}
	if (m_Cornerproperties->GetTransform() == 0)
		return;

	for (auto i = 0; i < m_landMarkList.size(); i++)
	{
		if (m_landMarkList[i]->IsValid())
		{
			if (i == index)
			{
				
				m_landMarkList[i]->UpdateAsSelected();
				m_landMarkList[i]->SetPosition(position);
				m_landMarkList[i]->Validate();

				SetViewCentrePosition(position);

				misUpdateLandmarkStatusEvent UpdateEv;
				misLandmarkInfoStruct infoStatus;
				infoStatus.CurrentPosition = position;
				infoStatus.landmarkIndex = index;
				infoStatus.Landmarktype = m_CurrentLandmarkType;
				UpdateEv.Set(infoStatus);
				InvokeEvent(UpdateEv);
			}
			else
			{
				m_landMarkList[i]->UpdateNormal();
			}
		}
	}
}

double* mis3DVolumeRenderer::GetLandmarkPosition(const int index)
{
	if (m_landMarkList[index]->IsValid())
	{
		const auto pos = new double[3];
		m_landMarkList[index]->GetPosition(pos);
		return pos;
	}
	return nullptr;
}

double* mis3DVolumeRenderer::GetLandmarkPosition(int index, misLandmarkType category)
{
	double* pos = 0;
	if ((index >= 0) && (index < m_landMarkList.size()))
	{
		auto seedList = GetLandmarkList(category);
		if ((index >= 0) && (index < seedList.size()))
		{
			if (seedList[index].validity)
			{
				pos = new double[3];
				pos[0] = seedList[index].data[0];
				pos[1] = seedList[index].data[1];
				pos[2] = seedList[index].data[2];
				return pos;
			}
		}
	}
	return pos;
}

void mis3DVolumeRenderer::Reset()
{
	InvalidateLandmarks();
	DeleteAllScrews();
	m_3DViewer->Reset();
	if (m_MainRepresentation)
	{
		m_MainRepresentation.reset();
	}
}

void mis3DVolumeRenderer::HideLandmarks()
{
	for (auto& i : m_landMarkList)
	{
		if (i->IsValid())
		{
			i->SetVisibilityOff();
		}
	}
}

void mis3DVolumeRenderer::ShowLandmarks()
{
	for (auto& landamrk : m_landMarkList)
	{
		if (landamrk->IsValid())
		{
			landamrk->SetVisibilityOn();
		}
	}

}

void mis3DVolumeRenderer::SetToolTransform(std::shared_ptr<ITransform> transform)
{
	auto trans = misMathUtils::CreateVtkTransform(transform);
	m_Cornerproperties->SetMatrix(trans->GetMatrix());
	if (m_CursorService)
	{
		m_CursorService->UpdateWidgetPosition();
	}
}

void mis3DVolumeRenderer::RemoveLandMarkRepresentations()
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid())
		{
			RemoveRepresentation(landmark->GetSurface());
		}
	}
}

void mis3DVolumeRenderer::InvalidateLandmark(const int index)
{
	if ((index >= 0) && (index < m_landMarkList.size()) && m_landMarkList[index])
	{
		RemoveLandmarkRepresentation(index);
		m_landMarkList[index]->InValidate();
	}
}

void mis3DVolumeRenderer::InvalidateLandmarks(void)
{
	for (auto i = 0; i < m_landMarkList.size(); i++)
	{
		RemoveLandmarkRepresentation(i);
		m_landMarkList[i]->InValidate();
	}
}

misSimplePointListType mis3DVolumeRenderer::GetLandmarkList(misLandmarkType seedType /*= seedCatergory::General*/)
{
	misSimplePointListType  res;
	for (const auto& landmark : m_landMarkList)
	{
		misSimplePointType seed;
		if (landmark)
		{
			if (landmark->GetCategory() == seedType)
			{
				double pos[3];
				landmark->GetPosition(pos);
				seed[0] = pos[0];
				seed[1] = pos[1];
				seed[2] = pos[2];
				seed.validity = landmark->IsValid();
				res.push_back(seed);
			}
		}
	}
	return  res;
}

mis3DVolumeRenderer::LandmarkListType mis3DVolumeRenderer::GetLandmarkList(void)
{
	return m_landMarkList;
}

void mis3DVolumeRenderer::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	m_3DViewer->RemoveRepresentation(pRepresent);
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->GetSurface() == pRepresent)
			landmark->InValidate();
	}
}

void mis3DVolumeRenderer::ResetLandMarks(void)
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid())
		{
			RemoveRepresentation(landmark->GetSurface());
			landmark->SetCategory(UnkownLandmarkType);
		}
	}
}

void mis3DVolumeRenderer::ResetLandMarks(misLandmarkType lndType)
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid() && landmark->GetCategory() == lndType)
		{
			RemoveRepresentation(landmark->GetSurface());
			landmark->SetCategory(UnkownLandmarkType);
		}
	}
}

std::shared_ptr<ICursorService> mis3DVolumeRenderer::GetCursorService()
{
	return m_CursorService;
}


void mis3DVolumeRenderer::SetCaptureLandmarkFlag(bool val)
{
	m_CaptureLandmark = val;
	m_CursorService->Set3DInteractionCapturedFlag(!val);
}

void mis3DVolumeRenderer::SetUpdateLandmarkFlag(bool val)
{
	m_UpdateLandmark = val;
}

 

void mis3DVolumeRenderer::SetCurrentLandmark(misLandmarkType val, int  index)
{
	if(index != -1)
		m_currentLandmarkIndex = index;
	SetCurrentLandmarkType(val);
}

void mis3DVolumeRenderer::SetCurrentLandmarkType(misLandmarkType val)
{
	m_CurrentLandmarkType = val;
	if (m_currentLandmarkIndex >= 0 && val != UnkownLandmarkType)
		m_landMarkList[m_currentLandmarkIndex]->SetCategory(val);
}

void mis3DVolumeRenderer::SetCurrentLandmarkIndex(int val)
{
	m_currentLandmarkIndex = val;
}

void mis3DVolumeRenderer::SetCurrentLandmarkLableType(LANDMARKLABLETYPE val)
{
	m_CurrentLandmarkLableType = val;
}

bool mis3DVolumeRenderer::ProcessRequest(const itk::EventObject* event)
{
	const auto res = false;
	if (typeid(*event) == typeid(misAddLandmarkEvent))
	{
		const auto pEventData = dynamic_cast<const misAddLandmarkEvent*>(event);
		const auto infoStr = pEventData->Get();
		auto position = m_Cornerproperties->GetCurrentPosition();
		AddLandmark(infoStr.landmarkIndex, position.Elements(), infoStr.Landmarktype, infoStr.landmarkLableType);

		m_CaptureLandmark = false;
		m_UpdateLandmark = false;
		return true;
	}
	if (typeid(*event) == typeid(misROIWidgetUpdateEvent))
	{
		const misROIWidgetUpdateEvent* pEventData = dynamic_cast<const misROIWidgetUpdateEvent*>(event);
		misDataBoundStr NewROIBound = pEventData->Get();
		double data[6];
		NewROIBound.GetArrayBound(data);
		m_ROIBox->PlaceWidget(data);
		return true;
	}
	if ((typeid(*event) == typeid(misScrewWidgetUpdateEvent)))
	{
		const misScrewWidgetUpdateEvent* pEventData = dynamic_cast<const misScrewWidgetUpdateEvent*>(event);
		misScrewWidgetData screwWidgetVals = pEventData->Get();

		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if (screwWidgetVals.GetScrewUID() == (*m_ScrewServiceList)[i]->GetScrewUID())
			{
				screwWidgetVals.SetInterationType(Free);
				(*m_ScrewServiceList)[i]->SetScrewWidget(screwWidgetVals); //NO limitation in 3D
				m_Cornerproperties->SetMatrix(screwWidgetVals.GetTransformMatrix());
				double* p1 = new double[3];
				screwWidgetVals.GetStartPoint().GetPoint(p1);
				m_Cornerproperties->SetCurrentPosition(p1);
				m_CursorService->UpdateWidgetPosition();
				misSimplePointType unknownPlaneNorm;
				delete[] p1;
				return true;
			}
		}
	}
	else if ((typeid(*event) == typeid(misUpdatePositionEvent)))
	{
		const auto pEventData = dynamic_cast<const misUpdatePositionEvent*>(event);
		const auto info = pEventData->Get();
		SetCurrentPosition(info.CornerTransform);
		return true;
	}
	return res;
}

void mis3DVolumeRenderer::SetCurrentPosition(vtkMatrix4x4* matrix)
{
	m_Cornerproperties->SetMatrix(matrix);
	m_CursorService->UpdateWidgetPosition();
}

void mis3DVolumeRenderer::UpdateLandmarkCameraView(const int index)
{
	if(m_UpdateLandmarkCameraViewer)
		m_UpdateLandmarkCameraViewer->Update(m_MainRepresentation->GetBoundingBox(), m_landMarkList[index]);
}

IMAGEORIENTATION mis3DVolumeRenderer::GetOrientationDirection()
{
	return UNKnownDirection;
}

void mis3DVolumeRenderer::SetViewPort(const misViewPort& val)
{
	m_ViewPort = val;
	m_3DViewer->SetViewPort(val);
}

void mis3DVolumeRenderer::SetROI(const double* data)
{


	SetROIInteractor();
	if (m_ROIBox)
	{
		m_ROIBox->SetPlaceFactor(1);
		m_ROIBox->OutlineCursorWiresOff();
		m_ROIBox->RotationEnabledOff();
		m_ROIBox->PlaceWidget();
		m_ROIBox->SetOrientation(VOLUME);
		m_ROIBox->PlaceWidget(data[0], data[1], data[2], data[3], data[4], data[5]);
	}
}

void mis3DVolumeRenderer::SetROI(misROI data)
{
	SetROI(data.getData());
	if (m_VolumeRnderer)
	{
		m_VolumeRnderer->SetROI(data);
	}
}

void mis3DVolumeRenderer::ROIWidgetActivation(bool activation)
{
	if (activation)
	{
		SetROIActive();
		m_ROIBox->On();
	}
	else
		m_ROIBox->Off();
}

void mis3DVolumeRenderer::InitializeWidget(misCursorType widgetType)
{
	m_Renderer = m_3DViewer->GetRenderer();
	m_CursorService->SetImageOrientation(UNKnownDirection);
	m_CursorService->SetWidgetType(widgetType);
	m_CursorService->CreateWidget();
	m_CursorService->SetCornerProperties(this->m_Cornerproperties);
	double bound[6];
	GetWidgetBoundingBox(bound);
	m_CursorService->SetWidgetBounds(bound);
	m_CursorService->UpdateWidgetPosition();
	if (!this->m_IsPointWidgetObserverAdded)
	{
		misMemberCommandCallback<mis3DVolumeRenderer>* widgetChangeCallback = misMemberCommandCallback<mis3DVolumeRenderer>::
			New();
		widgetChangeCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::WidgetChangeAction);

		m_CursorService->AddObserver(widgetChangeCallback);
		m_IsPointWidgetObserverAdded = true;
	}

	m_CursorService->SetWidgetInteractor(
		static_cast<vtkRenderWindowInteractor*>(m_Renderer->GetRenderWindow()->GetInteractor()));
	m_CursorService->SetRenderer(m_Renderer);

	vtkProp3D* widgetActor = nullptr;
	widgetActor = GetWidgetBoundedActor();
	if (widgetActor)
	{
		m_CursorService->ApplyWidget(widgetActor);
		m_CursorService->EnableWidget();
	}
}
vtkProp3D* mis3DVolumeRenderer::GetWidgetBoundedActor()
{
	if (!m_MainRepresentation)
		return nullptr;
	const auto widgetActor = dynamic_cast<vtkProp3D*>(m_MainRepresentation->GetActor(0));
	return widgetActor;
}


void mis3DVolumeRenderer::WidgetChangeAction(vtkObject *caller, unsigned long eventId, void* callData)
{
	if (eventId == vtkCommand::EndInteractionEvent)
	{
		if (m_Cornerproperties->GetTransform() == 0)
		{
			return;
		}

		auto pointWidget = dynamic_cast<misColorPointWidget*>(caller);
		if (pointWidget)
		{
			double  pos[3];
			pointWidget->GetPosition(pos);

			if (m_UpdateLandmark)
			{
				_ASSERT(m_currentLandmarkIndex != -1);
				if (m_currentLandmarkIndex == -1)
					return;

				SetLandmarkPosition(m_currentLandmarkIndex, pos);
				m_UpdateLandmark = false;

				misLandmarkInfoStruct landmarkStr;
				landmarkStr.CurrentPosition = pos;
				landmarkStr.landmarkIndex = m_currentLandmarkIndex;
				landmarkStr.Landmarktype = m_CurrentLandmarkType;
				landmarkStr.landmarkLableType = m_CurrentLandmarkLableType;
				misAddLandmarkEvent ev;
				ev.Set(landmarkStr);
				InvokeEvent(ev);
				m_UpdateLandmark = false;
				return;
			}

			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			InvokeEvent(ev);
		}
	}
}

void mis3DVolumeRenderer::UpdateScrewWidget(vtkObject *caller, unsigned long eventId, void* callData)
{
	auto lineCaller = dynamic_cast<misLineWidget2*>(caller);
	if (!lineCaller || m_ScrewServiceList->empty() || eventId != vtkCommand::EndInteractionEvent)
		return;
	const auto foundScrewServiceItr = std::find_if(m_ScrewServiceList->begin(), m_ScrewServiceList->end(),
		[&](std::shared_ptr<IScrewCompound> screwCompund) -> bool
	{
		return screwCompund->GetWidget()->GetLineWidgetUID() == lineCaller->GetLineWidgetUID();

	});

	if (foundScrewServiceItr == m_ScrewServiceList->end())
	{
		return;
	}
	auto foundScrewService = *foundScrewServiceItr;
	foundScrewService->CalcTransformMatrix(UNKnownDirection);
	vtkMatrix4x4* tmpMatrix = foundScrewService->GetTransformMatrix();
	m_Cornerproperties->SetMatrix(tmpMatrix);
	m_Cornerproperties->SetCurrentPosition(foundScrewService->GetPoint1WorldPosition());
	m_CursorService->UpdateWidgetPosition();

	misScrewWidgetUpdateEvent wchanged;
	misScrewWidgetData screwWidgetVal;
	screwWidgetVal.SetStartPoint(foundScrewService->GetPoint1WorldPosition());
	screwWidgetVal.SetEndPoint(foundScrewService->GetPoint2WorldPosition());
	screwWidgetVal.SetInterationType(foundScrewService->GetInteractionType());
	screwWidgetVal.SetScrewUID(foundScrewService->GetScrewUID());//currentScrewUID;
	screwWidgetVal.DeepCopyTransformMatrix(foundScrewService->GetTransformMatrix());
	wchanged.Set(screwWidgetVal);
	InvokeEvent(wchanged);
}

void mis3DVolumeRenderer::AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation)
{
	if (!(m_3DViewer->CheckNewRepresentationValidity(pRepresentation)))
		return;
	m_3DViewer->AddRepresentation(pRepresentation);

	misMemberCommandCallback<mis3DVolumeRenderer>* ROIClickCallback = misMemberCommandCallback<mis3DVolumeRenderer>::New();
	ROIClickCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::ROIClickAction);
	if (!m_ROIBox->HasObserver(misROIWidgetChangeEvent))
		m_ROIBox->AddObserver(misROIWidgetChangeEvent, ROIClickCallback);

	misMemberCommandCallback<mis3DVolumeRenderer>* ROIChangeCallback = misMemberCommandCallback<mis3DVolumeRenderer>::New();
	ROIChangeCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::UpdateWidgetBox);
	if (!m_ROIBox->HasObserver(vtkCommand::EndInteractionEvent))
		m_ROIBox->AddObserver(vtkCommand::EndInteractionEvent, ROIChangeCallback);

	misMemberCommandCallback<mis3DVolumeRenderer>* pointSelectCallback = misMemberCommandCallback<mis3DVolumeRenderer>::New();
	pointSelectCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::PointSelectAction);

	if (!m_IsPointSelectObserverAdded)
	{
		m_3DViewer->GetRenderer()->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, pointSelectCallback);
		m_3DViewer->GetRenderer()->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, pointSelectCallback);
		m_IsPointSelectObserverAdded = true;
	}
	// If the newly added representation is a Voreen representation, assign its underlying volumeMapper to the interactionStyle of 
	// the viewer, set camera to anterior view.
	if (m_3DViewer->Get3DStyle())
	{
		if (m_VolumeRnderer)
		{
			const auto volume = std::dynamic_pointer_cast<IvolumeRepresentation>(pRepresentation);
			if (volume)
			{
				SetAnteriorView();
				m_VolumeRnderer->UpdateRaycastingTexture();
				m_VolumeRnderer->UpdatePointPicker(m_3DViewer->Get3DStyle()->GetPointPicker());
			}
		}

	}
	AddImageOrientation3DModel(pRepresentation);
}

std::vector<std::shared_ptr<IRepresentation>> mis3DVolumeRenderer::FindRepresentationByName(const std::string& name)
{
	return m_3DViewer->FindRepresentationByName(name);
}

void mis3DVolumeRenderer::AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer)
{
	m_3DViewer->AddCoordinateSytemRenderer(coordianteRenderer);
}

void mis3DVolumeRenderer::PointSelectAction(vtkObject *caller, unsigned long eventId, void* callData)
{

	if (!m_CaptureLandmark)
	{
		return;
	}

	if (m_Cornerproperties->GetTransform() == nullptr)
	{
		m_CurrentLandmarkType = UnkownLandmarkType;
		m_currentLandmarkIndex = -1;
		m_CaptureLandmark = false;
		return;
	}

	auto *interactor = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
	int x;
	int y;
	interactor->GetEventPosition(x, y);

	double position[3];
	auto*  pStyle = dynamic_cast<MIS3DInteractionStyle*>(interactor->GetInteractorStyle());
	if (!pStyle)
		return;
	auto picker = dynamic_cast<vtkPicker*>(pStyle->GetPointPicker());
	if (!picker)
		return;
	picker->Pick(x, y, 0, m_3DViewer->GetRenderer());
	vtkPoints* pos = vtkPoints::New();
	pos = picker->GetPickedPositions();
	const auto num = pos->GetNumberOfPoints();
	if (num == 1)
		pos->GetPoint(0, position);
	else
		return;

	if ((0 == position[0]) && (0 == position[1]) && (0 == position[2]))
	{
		return;
	}

	if (num > 0)
	{
		m_Cornerproperties->SetCurrentPosition(position);

		if (m_currentLandmarkIndex == -1)
		{
			m_currentLandmarkIndex = AddNextLandmark(position, m_CurrentLandmarkType, m_CurrentLandmarkLableType);
		}
		else
		{
			AddLandmark(m_currentLandmarkIndex, position, m_CurrentLandmarkType, m_CurrentLandmarkLableType);
		}

		m_CursorService->UpdateWidgetPosition();
		m_Cornerproperties->SetCurrentPosition(position);

		misUpdatePositionEvent ev;
		misUpdatePositionInfoStruct updateStr;
		updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
		updateStr.IsCameraUpdate = true;
		ev.Set(updateStr);
		InvokeEvent(ev);

		if (m_currentLandmarkIndex != -1)
		{
			misLandmarkInfoStruct lndStr;
			lndStr.Landmarktype = m_CurrentLandmarkType;
			lndStr.CurrentPosition = position;
			lndStr.landmarkIndex = m_currentLandmarkIndex;
			lndStr.landmarkLableType = m_CurrentLandmarkLableType;

			misAddLandmarkEvent lndEv;
			lndEv.Set(lndStr);
			InvokeEvent(lndEv);
		}

		m_CurrentLandmarkType = UnkownLandmarkType;
		m_currentLandmarkIndex = -1;
		m_CaptureLandmark = false;
	}
}

void mis3DVolumeRenderer::ReleaseImageResource()
{
	ResetVolume();
	m_IsPointWidgetObserverAdded = false;
	m_IsPointSelectObserverAdded = false;
}

std::shared_ptr<ICornerProperties> mis3DVolumeRenderer::GetCornerProperties() const
{
	return m_Cornerproperties;
}

void mis3DVolumeRenderer::ClipingWidgetOn()
{
	if (m_ClippingPlaneWidget)
	{
		m_ClippingPlaneWidget->On();
		m_ClippingPlaneWidget->SetCenter(0, 0, 0);
		m_ClippingPlaneWidget->SetNormal(0, 0, -1);
	}
}


void mis3DVolumeRenderer::SetDentalSurgeryType(DentalSurgeryType surgeryType)
{
	m_DentalSurgeryType = surgeryType;
	m_Cornerproperties->SetDentalSurgeryType(surgeryType);
}

void mis3DVolumeRenderer::ClippingWidgetOff()
{
	if (m_ClippingPlaneWidget)
		m_ClippingPlaneWidget->Off();
}

void mis3DVolumeRenderer::InitializeCornerProperties()
{
	m_Cornerproperties->SetOrientation(UNKnownDirection);
}

// set camera point in to xPoint
void mis3DVolumeRenderer::SetSupriorView()
{
	if (!(m_3DViewer->GetRenderer()))
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();

	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 1, 0);
	const auto bounding = m_3DViewer->GetBoundingBox();
	const auto focal = m_3DViewer->GetFocalPoint();

	const double height = bounding[5] - bounding[4];
	m_3DViewer->GetRenderer()->GetActiveCamera()->SetPosition(
		focal[0], focal[1], focal[2] - height * m_3DViewer->GetScaleCameraPosition());
	m_3DViewer->GetRenderer()->GetRenderWindow()->Render();
}

// set camera point in to yPoint
void mis3DVolumeRenderer::SetInferiorView()
{
	if (!(m_3DViewer->GetRenderer()))
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();

	m_3DViewer->GetRenderer()->GetActiveCamera()->SetViewUp(0, 1, 0);
	const auto bounding = m_3DViewer->GetBoundingBox();

	const double height = bounding[5] - bounding[4];
	const auto focal = m_3DViewer->GetFocalPoint();

	m_Renderer->GetActiveCamera()->SetPosition(
		focal[0], focal[1], focal[2] + height * m_3DViewer->GetScaleCameraPosition());
	m_Renderer->GetRenderWindow()->Render();
}

// set camera point in to ZPoint  
void mis3DVolumeRenderer::SetAnteriorView()
{
	if (!m_Renderer)
	{
		return;
	}

	m_3DViewer->SetDefaultFocalPoint();
	double bounds[6];

	if (m_MainRepresentation)
		m_MainRepresentation->GetBoundingBox(bounds);
	else
	{
		bounds[0] = bounds[2] = bounds[4] = 0;
		bounds[1] = bounds[3] = bounds[5] = 500;
	}
	const auto focal = m_3DViewer->GetFocalPoint();
	m_Renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
	const auto width = bounds[3] - bounds[2];
	const auto y = focal[1] + width * m_3DViewer->GetScaleCameraPosition();
	m_Renderer->GetActiveCamera()->SetPosition(focal[0], y, focal[2]);
}

void mis3DVolumeRenderer::SetPosteriorView()
{
	if (!m_Renderer)
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();

	m_Renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
	const auto focal = m_3DViewer->GetFocalPoint();
	double bounding[6];
	if (m_MainRepresentation)
	{
		m_MainRepresentation->GetBoundingBox(bounding);
	}
	const auto width = bounding[3] - bounding[2];
	m_Renderer->GetActiveCamera()->SetPosition(
		focal[0], focal[1] - width * m_3DViewer->GetScaleCameraPosition(), focal[2]);
}

// set camera point in to xPoint
void mis3DVolumeRenderer::SetLeftView()
{
	if (!m_Renderer)
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();
	const auto focal = m_3DViewer->GetFocalPoint();
	const auto bounding = m_3DViewer->GetBoundingBox();
	m_Renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
	const double xDirectionWidth = (bounding[1] - bounding[0]);
	m_Renderer->GetActiveCamera()->SetPosition(
		focal[0] + xDirectionWidth * m_3DViewer->GetScaleCameraPosition(), focal[1], focal[2]);
}

// set camera point in to yPoint
void mis3DVolumeRenderer::SetRightView()
{
	if (!m_Renderer)
	{
		return;
	}
	m_3DViewer->SetDefaultFocalPoint();
	const auto focal = m_3DViewer->GetFocalPoint();
	const auto bounding = m_3DViewer->GetBoundingBox();
	m_Renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
	const double xDirectionWidth = bounding[1] - bounding[0];
	m_Renderer->GetActiveCamera()->SetPosition(
		focal[0] - xDirectionWidth * m_3DViewer->GetScaleCameraPosition(), focal[1], focal[2]);
}

double * mis3DVolumeRenderer::GetROICompressData()
{
	vtkPoints* p = m_ROIBox->GetPoints();
	double* compData = m_ROIBox->GetCompressData(p);
	m_ROIBox->UpdateWidgetData();
	return compData;
}

void mis3DVolumeRenderer::SetROIInteractor()
{
	m_ROIBox->SetInteractor((vtkRenderWindowInteractor*)(m_3DViewer->GetWindow()->GetInterActor()));
}


void mis3DVolumeRenderer::SetROIActive()
{
	m_IsROIActive = true;
}

void mis3DVolumeRenderer::ResetROI()
{
	m_IsROIActive = false;
	if (m_ROIBox)
		m_ROIBox->Off();
}

misROIWidget* mis3DVolumeRenderer::GetROIBox()
{
	if (m_ROIBox)
	{
		return m_ROIBox;
	}
	return nullptr;
}

void mis3DVolumeRenderer::Render()
{
	m_3DViewer->Render();

	if (!(m_3DViewer->IsWindowsSizeChanged()))
		return;
	int size[2];
	m_3DViewer->GetWindowSize(size);
	int windowsize[2];
	m_3DViewer->GetWindowSize(windowsize);
	windowsize[0] = size[0];
	windowsize[1] = size[1];
	m_Renderer->GetRenderWindow()->SetSize(windowsize);
	if (m_VolumeRnderer)
		m_VolumeRnderer->Render();
	m_Renderer->GetRenderWindow()->Render();
}
unsigned long mis3DVolumeRenderer::AddObserver(const itk::EventObject & event, itk::Command *command)
{
	return m_DummyObject->AddObserver(event, command);
}

void mis3DVolumeRenderer::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->SetViewer(this);
	m_DummyObject->InvokeEvent(event);
}

void mis3DVolumeRenderer::SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction)
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->SetVolume(pTexture, transferFunction);
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	AddRepresentation(m_MainRepresentation);
}

void mis3DVolumeRenderer::SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs)
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->SetVolume(imageTexture, ImgCntTfs);
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	AddRepresentation(m_MainRepresentation);
}

void mis3DVolumeRenderer::PassVolumeMapToRepresentation()
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->PassVolumeMapToRepresentation();
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	AddRepresentation(m_MainRepresentation);
}

void mis3DVolumeRenderer::ClippingOn()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->ClippingOn();
}

void mis3DVolumeRenderer::ClippingOff()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->ClippingOff();
}

void mis3DVolumeRenderer::SetClippingPlane(tgt::vec4 plane)
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->SetClippingPlane(plane);
}


void mis3DVolumeRenderer::ModifyVolume()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->ModifyVolume();
}

void mis3DVolumeRenderer::CompileVolumeShader()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->CompileVolumeShader();
}



void mis3DVolumeRenderer::RemoveRenderingVolume()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->RemoveRenderingVolume();
}

bool mis3DVolumeRenderer::HasObserver(const itk::EventObject & event) const
{
	return m_DummyObject->HasObserver(event);
}


void mis3DVolumeRenderer::ResetVolume()
{
	auto reperesenations = m_3DViewer->GetRepresentations();
	auto volumeResource = std::find_if(reperesenations.cbegin(), reperesenations.cend(), [](auto rep)
	{
		auto volumeRep = std::dynamic_pointer_cast<IvolumeRepresentation>(rep);
		return static_cast<bool>(volumeRep);
	});

	if (volumeResource != reperesenations.end())
		RemoveRepresentation(*volumeResource);
	if (m_VolumeRnderer)
		m_VolumeRnderer->Reset();
}




std::shared_ptr<IScrewCompound> mis3DVolumeRenderer::GetScrewWidgetService(misUID uid)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if (uid == (*m_ScrewServiceList)[i]->GetScrewUID())
		{
			return (*m_ScrewServiceList)[i];
		}
	}
	return 0;
}


void mis3DVolumeRenderer::UpdateWidgetBox(vtkObject *caller, unsigned long eventId, void* callData)
{
	if (eventId != vtkCommand::EndInteractionEvent)
		return;

	double* data = GetROICompressData();
	m_ROIBox->PlaceWidget(data);
	misROIWidgetUpdateEvent wchanged;
	misDataBoundStr ROIBound;
	ROIBound.SetArrayBound(data);
	wchanged.Set(ROIBound);
	InvokeEvent(wchanged);
	Render();
}

DentalSurgeryType mis3DVolumeRenderer::GetDentalSurgeryType()
{
	return m_DentalSurgeryType;
}

void mis3DVolumeRenderer::ROIClickAction(vtkObject *caller, unsigned long eventId, void *callData)
{

}

void mis3DVolumeRenderer::OffAllScrews()
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetSelected(false);
			(*m_ScrewServiceList)[i]->Off();
		}
	}
}

void mis3DVolumeRenderer::OnAllScrews()
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetSelected(true);
			(*m_ScrewServiceList)[i]->On();
		}
	}
}

void mis3DVolumeRenderer::DeleteScrew(misUID screwUID)
{
	if (m_ScrewServiceList->empty())
		return;
	OffScrew(screwUID);
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
		{
			(*m_ScrewServiceList)[i]->SetInteractor(NULL);
			m_ScrewServiceList->erase(m_ScrewServiceList->begin() + i);
		}
	}
}

void mis3DVolumeRenderer::OnScrew(misUID screwUID)
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
			{
				(*m_ScrewServiceList)[i]->SetSelected(true);
				(*m_ScrewServiceList)[i]->On();
			}
		}
	}
}

void mis3DVolumeRenderer::OffScrew(misUID screwUID)
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
			{
				(*m_ScrewServiceList)[i]->SetSelected(false);
				(*m_ScrewServiceList)[i]->Off();
			}
		}
	}
}

void mis3DVolumeRenderer::DeleteAllScrews()
{
	if (m_ScrewServiceList && !m_ScrewServiceList->empty())
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetInteractor(NULL);
		}
		m_ScrewServiceList->clear();
	}
}


void mis3DVolumeRenderer::GetWidgetBoundingBox(double bounds[6], double extensionScaleFactor)
{
	auto cornerBounds = m_Cornerproperties->GetBounds();
	if (!cornerBounds)
		return;
	double length = cornerBounds[1] - cornerBounds[0];
	double width = cornerBounds[3] - cornerBounds[2];
	double height = cornerBounds[5] - cornerBounds[4];
	delete cornerBounds;

	bounds[0] = -extensionScaleFactor * length;
	bounds[1] = extensionScaleFactor * length;
	bounds[2] = -extensionScaleFactor * width;
	bounds[3] = extensionScaleFactor * width;
	bounds[4] = -extensionScaleFactor * height;
	bounds[5] = extensionScaleFactor * height;
}

void mis3DVolumeRenderer::LockAllScrews()
{
	SetAllScrewsLocked(true);
}

void mis3DVolumeRenderer::UnlockAllScrews()
{
	SetAllScrewsLocked(false);
}

void mis3DVolumeRenderer::SetAllScrewsLocked(bool isLocked)
{
	if (m_ScrewServiceList->empty())
		return;

	for (auto screwItr = m_ScrewServiceList->begin(); screwItr != m_ScrewServiceList->end(); screwItr++)
	{
		(*screwItr)->SetLocked(isLocked);
	}
}


void mis3DVolumeRenderer::RemoveAllScrewServices()
{
	m_ScrewServiceList->clear();
}


void mis3DVolumeRenderer::SetShowManModel(bool val)
{
	m_ShowManModel = val;
}

void mis3DVolumeRenderer::SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
{
	m_Cornerproperties->SetPanoramicCoordinateConverter(coordinateConverter);
}

void mis3DVolumeRenderer::SetDentalSpecialViewsEnable(bool enabled)
{
	m_DentalSpecialViewEnable = enabled;
}

std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> mis3DVolumeRenderer::GetVolumeMap() const
{
	return m_VolumeRnderer->GetVolumeMap();

}

std::shared_ptr<Iwindows> mis3DVolumeRenderer::GetWindow() const
{
	return m_3DViewer->GetWindow();
}

void mis3DVolumeRenderer::SetState(int val)
{
	MIS3DInteractionStyle * pStyle = Get3DViewer()->Get3dStyleCamera();
	if (pStyle)
	{
		pStyle->SetState(val);
		GetRenderer()->GetRenderWindow()->GetInteractor()->SetInteractorStyle(pStyle);
	}
}

bool mis3DVolumeRenderer::HasRepresentationByName(const std::string& name)
{
	return !(FindRepresentationByName(name).empty());
}



void mis3DVolumeRenderer::MakeCurrentRenderer()
{
	m_3DViewer->GetWindow()->GetRenderWindow()->MakeCurrent();
}

void mis3DVolumeRenderer::SetWindow(std::shared_ptr<Iwindows> pWindow, int index)
{
	m_IndexInGroup = index;
	m_3DViewer->SetWindow(pWindow, index);
	m_Renderer = pWindow->GetRenderer(index);
	if (m_VolumeRnderer)
		m_VolumeRnderer->SetRenderer(m_Renderer);
}

void mis3DVolumeRenderer::RemoveSegmentedVolume()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->RemoveSegmentedVolume();
}

void mis3DVolumeRenderer::SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION orientation)
{
	m_MainRepresentation = pMainRep;
	InitializeCornerProperties();
	m_CursorService->SetImageOrientation(orientation);
	if (m_VolumeRnderer)
	{
		const auto volumeRep = std::dynamic_pointer_cast<IvolumeRepresentation>(m_MainRepresentation);
		m_VolumeRnderer->SetRepresentation(volumeRep);
	}
}



void mis3DVolumeRenderer::UpdateWindowSize(misStrctWindowSize &size)
{
	tgt::ivec2 newWindowSize = tgt::ivec2(size.width, size.height);
	m_3DViewer->SetWindowSizeUpdated(size.width, size.height);
	if (m_VolumeRnderer)
		m_VolumeRnderer->UpdateWindowSize(size);
}

std::shared_ptr<TransFuncIntensity> mis3DVolumeRenderer::GetColormapTransferFunction() const
{
	return m_ColormapTransferFunction;
}

void mis3DVolumeRenderer::SetColormapTransferFunction(std::shared_ptr<TransFuncIntensity> val)
{
	m_ColormapTransferFunction = val;
}

bool mis3DVolumeRenderer::GetShowLabels() const
{
	return m_ShowLabels;
}

void mis3DVolumeRenderer::SetShowLabels(bool val)
{
	m_ShowLabels = val;
}

std::shared_ptr<IRepresentation> mis3DVolumeRenderer::GetMainRepresentation()
{
	return 	m_MainRepresentation;

}

void mis3DVolumeRenderer::RemoveRepresentationByName(std::string name)
{
	m_3DViewer->RemoveRepresentationByName(name);
}

std::shared_ptr<I3DViewer> mis3DVolumeRenderer::Get3DViewer() const
{
	return m_3DViewer;
}


void mis3DVolumeRenderer::AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation)
{
	m_Renderer = m_3DViewer->GetRenderer();
	if (!m_ShowManModel)
		return;

	int numOfActor = pRepresentation->GetNumberOfActors();
	if (numOfActor == 0)
		return;


	vtkProp3D* prop = dynamic_cast<vtkProp3D*>(pRepresentation->GetActor(0));
	if (!prop)
		return;

	m_3DViewer->RemoveRepresentationByName("Man Model");
	double* maninREpresentationPosition = prop->GetCenter();
	m_ManModel->Init(maninREpresentationPosition, m_Renderer);
	m_3DViewer->AddRepresentation(m_ManModel);
}

bool mis3DVolumeRenderer::IsDentalSpecialViewsEnabled() const
{
	return m_DentalSpecialViewEnable;
}

