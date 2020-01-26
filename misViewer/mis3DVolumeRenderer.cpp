#include "stdafx.h"
#include "mis3DVolumeRenderer.h"
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
#include "LandmarkLablePositionCalculatorFactory.h"
#include "ScrewViewerFactory.h"

using namespace std;
using namespace parcast;

#define  LINEDISTANCELANDMARK 20

mis3DVolumeRenderer::mis3DVolumeRenderer(std::shared_ptr<ScrewListType> screwServiceList,
	std::shared_ptr<Iwindows> pWindow, int index,
	std::shared_ptr<I3DViewer> viewer,
	std::shared_ptr<ICornerProperties> cornerProperties,
	std::shared_ptr<IInitializeScrewWidget> screwIntilizer,
	std::shared_ptr<IMedicalCameraDirection> medicalCameraDirection,
	std::shared_ptr<IVolumeRayCaster> volumeRenderer, misVolumeRendererContainer::Pointer dummy)
	: misVolumeRenderer(viewer, pWindow, index),
	m_ShowLabels(true),
	m_IsPointWidgetObserverAdded(false),
	m_IsPointSelectObserverAdded(false),
	m_CursorService(std::make_shared<misCursorService>()),
	m_ClippingPlaneWidget(vtkSmartPointer<misPlaneWidget>::New()),
	m_ShowManModel(true),
	m_ManModel(std::make_shared<misManModelrepresentation>("Man Model")),
	m_DentalSpecialViewEnable(false),
	m_VolumeRnderer(volumeRenderer),
	m_DentalSurgeryType(DentalSurgeryType::MAXILLA),
	m_Cornerproperties(cornerProperties),
	m_MedicalCameraDirection(medicalCameraDirection),

m_DummyObject(dummy)
{
	SetWindow(pWindow, index);
	m_DummyObject->SetViewer(static_cast<IVolumeRenderer*> (this));
	m_ScrewViewer = parcast::ScrewViewerFactory::Create(Dimention::_3D, screwIntilizer, screwServiceList,
		m_Cornerproperties, m_DummyObject);
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
	m_ScrewViewer->InitializeScrewWidget(initVals, orientation);
}

vtkRenderer* mis3DVolumeRenderer::GetRenderer()
{
	return m_Renderer;
}

misViewerTypeDirection mis3DVolumeRenderer::GetTypeDirection(void) const
{
	return misViewerTypeDirection::Viewer3DLandmark;
}


void mis3DVolumeRenderer::HighlightScrew(misUID screwUID, bool highlight)
{
	m_ScrewViewer->HighlightScrew(screwUID, highlight);
}

 
void mis3DVolumeRenderer::SetWindow(std::shared_ptr<Iwindows> pWindow, int index)
{
	m_IndexInGroup = index;
	m_3DViewer->SetWindow(pWindow, index);
	m_Renderer = pWindow->GetRenderer(index);
	if (m_VolumeRnderer)
		m_VolumeRnderer->SetRenderer(m_Renderer);
}

misVolumeRendererContainer::Pointer mis3DVolumeRenderer::GetDummySubject()
{
	return m_DummyObject;
}

void mis3DVolumeRenderer::SetTypeDirection(misViewerTypeDirection direction)
{
	m_ViewerTypeDirection = direction;

}


void mis3DVolumeRenderer::ZoomIn()
{
	if (!m_Renderer)
	{
		return;
	}
	auto Distance = m_Renderer->GetActiveCamera()->GetDistance();
	//auto Tickness = m_Renderer->GetActiveCamera()->GetThickness();
	if (Distance < 100)
		return;
	m_Renderer->GetActiveCamera()->Dolly(1.1);
	auto Position = m_Renderer->GetActiveCamera()->GetPosition();
	auto ViewUp = m_Renderer->GetActiveCamera()->GetViewUp();

}

void mis3DVolumeRenderer::ZoomOut()
{
	if (!m_Renderer)
	{
		return;
	}
	auto Distance = m_Renderer->GetActiveCamera()->GetDistance();
	auto Tickness = m_Renderer->GetActiveCamera()->GetThickness();
	if (Distance > Tickness)
		return;
	m_Renderer->GetActiveCamera()->Dolly(0.9);
}

void mis3DVolumeRenderer::ResetZoom()
{
	m_MedicalCameraDirection->SetDefaultVeiw();
}

std::shared_ptr<IMedicalCameraDirection> mis3DVolumeRenderer::GetMedicalCameraDirection() const
{
	return m_MedicalCameraDirection;
}

void mis3DVolumeRenderer::SetObliqueFlag(bool isOblique)
{
	m_Cornerproperties->SetObliqueMode(isOblique);
	m_IsOblique = isOblique;
}



 void mis3DVolumeRenderer::Reset()
{
	DeleteAllScrews();
	m_3DViewer->Reset();
	if (m_MainRepresentation)
	{
		m_MainRepresentation.reset();
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

std::shared_ptr<ICursorService> mis3DVolumeRenderer::GetCursorService()
{
	return m_CursorService;
}


void mis3DVolumeRenderer::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	m_3DViewer->RemoveRepresentation(pRepresent);
 
}



bool mis3DVolumeRenderer::ProcessRequest(const itk::EventObject* event)
{
	const auto res = false;
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
		m_ScrewViewer->ProcessUpdateScrewWidget(*pEventData, m_CursorService);
		
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

void mis3DVolumeRenderer::InitializeWidget(misCursorType widgetType, double pickingTolerance)
{
	m_Renderer = m_3DViewer->GetRenderer();
	m_CursorService->SetImageOrientation(UNKnownDirection);
	m_CursorService->SetWidgetType(widgetType);
	m_CursorService->CreateWidget(pickingTolerance);
	m_CursorService->SetCornerProperties(this->m_Cornerproperties);
	double bound[6];
	GetWidgetBoundingBox(bound);
	m_CursorService->SetWidgetBounds(bound);
	m_CursorService->UpdateWidgetPosition();
	if (!this->m_IsPointWidgetObserverAdded)
	{
		misMemberCommandCallback<mis3DVolumeRenderer>* widgetChangeCallback = misMemberCommandCallback<
			mis3DVolumeRenderer>::
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


void mis3DVolumeRenderer::WidgetChangeAction(vtkObject* caller, unsigned long eventId, void* callData)
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
			double pos[3];
			pointWidget->GetPosition(pos);
			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			InvokeEvent(ev);
		}
	}
}

void mis3DVolumeRenderer::UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData)
{
	m_ScrewViewer->UpdateScrewWidget(caller, eventId, callData);
}

void mis3DVolumeRenderer::AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation)
{
	if (!(m_3DViewer->CheckNewRepresentationValidity(pRepresentation)))
		return;
	m_3DViewer->AddRepresentation(pRepresentation);

	misMemberCommandCallback<mis3DVolumeRenderer>* ROIClickCallback = misMemberCommandCallback<mis3DVolumeRenderer>::
		New();
	ROIClickCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::ROIClickAction);
	if (!m_ROIBox->HasObserver(misROIWidgetChangeEvent))
		m_ROIBox->AddObserver(misROIWidgetChangeEvent, ROIClickCallback);

	misMemberCommandCallback<mis3DVolumeRenderer>* ROIChangeCallback = misMemberCommandCallback<mis3DVolumeRenderer>::
		New();
	ROIChangeCallback->SetCallbackFunction(this, &mis3DVolumeRenderer::UpdateWidgetBox);
	if (!m_ROIBox->HasObserver(vtkCommand::EndInteractionEvent))
		m_ROIBox->AddObserver(vtkCommand::EndInteractionEvent, ROIChangeCallback);
	AddAllPointSelectObserve();

	// If the newly added representation is a Voreen representation, assign its underlying volumeMapper to the interactionStyle of 
	// the viewer, set camera to anterior view.
	if (m_3DViewer->Get3DStyle())
	{
		if (m_VolumeRnderer)
		{
			const auto volume = std::dynamic_pointer_cast<IvolumeRepresentation>(pRepresentation);
			if (volume)
			{
				m_MedicalCameraDirection->SetDefaultVeiw();
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

void mis3DVolumeRenderer::InteractionStyleCallback(vtkObject* caller, unsigned long eventId, void* callData)
{
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




double* mis3DVolumeRenderer::GetROICompressData()
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

unsigned long mis3DVolumeRenderer::AddObserver(const itk::EventObject& event, itk::Command* command)
{
	return m_DummyObject->AddObserver(event, command);
}

void mis3DVolumeRenderer::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->InvokeEvent(event);
}

void mis3DVolumeRenderer::SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction)
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->SetVolume(pTexture, transferFunction);
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	m_MedicalCameraDirection->SetMainRepresentation(m_MainRepresentation);
	AddRepresentation(m_MainRepresentation);
}

void mis3DVolumeRenderer::SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs)
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->SetVolume(imageTexture, ImgCntTfs);
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	m_MedicalCameraDirection->SetMainRepresentation(m_MainRepresentation);
	AddRepresentation(m_MainRepresentation);
}

void mis3DVolumeRenderer::PassVolumeMapToRepresentation()
{
	if (!m_VolumeRnderer)
		return;

	m_VolumeRnderer->PassVolumeMapToRepresentation();
	m_MainRepresentation = m_VolumeRnderer->GetRepresentation();
	m_MedicalCameraDirection->SetMainRepresentation(m_MainRepresentation);
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

bool mis3DVolumeRenderer::HasObserver(const itk::EventObject& event) const
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
	m_MainRepresentation = nullptr;
	m_MedicalCameraDirection->SetMainRepresentation(m_MainRepresentation);
	if (m_VolumeRnderer)
		m_VolumeRnderer->Reset();
}


std::shared_ptr<IScrewCompound> mis3DVolumeRenderer::GetScrewWidgetService(misUID uid)
{
	return m_ScrewViewer->GetScrewWidgetService(uid);
}


void mis3DVolumeRenderer::UpdateWidgetBox(vtkObject* caller, unsigned long eventId, void* callData)
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

void mis3DVolumeRenderer::ROIClickAction(vtkObject* caller, unsigned long eventId, void* callData)
{
}

void mis3DVolumeRenderer::OffAllScrews()
{
	m_ScrewViewer->OffAllScrews();
}

void mis3DVolumeRenderer::OnAllScrews()
{
	m_ScrewViewer->OnAllScrews();
}

void mis3DVolumeRenderer::DeleteScrew(misUID screwUID)
{
	m_ScrewViewer->DeleteScrew(screwUID);
}

void mis3DVolumeRenderer::OnScrew(misUID screwUID)
{
	m_ScrewViewer->OnScrew(screwUID);
}

void mis3DVolumeRenderer::OffScrew(misUID screwUID)
{
	m_ScrewViewer->OffScrew(screwUID);
}

void mis3DVolumeRenderer::DeleteAllScrews()
{
	m_ScrewViewer->DeleteAllScrews();
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
	m_ScrewViewer->SetAllScrewsLocked(isLocked);
}


void mis3DVolumeRenderer::RemoveAllScrewServices()
{
	m_ScrewViewer->Clear();
}


void mis3DVolumeRenderer::SetShowManModel(bool val)
{
	m_ShowManModel = val;
}

void mis3DVolumeRenderer::SetPanoramicCoordinateConverter(
	std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
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
	MIS3DInteractionStyle* pStyle = Get3DViewer()->Get3dStyleCamera();
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


void mis3DVolumeRenderer::RemoveSegmentedVolume()
{
	if (m_VolumeRnderer)
		m_VolumeRnderer->RemoveSegmentedVolume();
}

void mis3DVolumeRenderer::SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION orientation)
{
	m_MainRepresentation = pMainRep;
	m_MedicalCameraDirection->SetMainRepresentation(m_MainRepresentation);
	InitializeCornerProperties();
	m_CursorService->SetImageOrientation(orientation);
	if (m_VolumeRnderer)
	{
		const auto volumeRep = std::dynamic_pointer_cast<IvolumeRepresentation>(m_MainRepresentation);
		m_VolumeRnderer->SetRepresentation(volumeRep);
	}
}


void mis3DVolumeRenderer::UpdateWindowSize(misStrctWindowSize& size)
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
	return m_MainRepresentation;
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
 