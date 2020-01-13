#include "stdafx.h"
#include "misColorPointWidget.h"

#include "VisualizationGeneralTypes.h"
#include "misCursor.h"
#include "misCursorFactory.h"

using namespace std;

misColorPointWidget::misColorPointWidget()
	: m_XAxisPicker(NULL), m_YAxisPicker(NULL), m_ZAxisPicker(NULL), m_LineWidth(1)
{
	m_WidgetState = Start;
	EventCallbackCommand->SetCallback(misColorPointWidget::ProcessEvents);
	m_Cursor3D = 0;
	m_Mode = 0;
	ConstraintAxis = -1;
	PlaceFactor = 1.0;
	HotSpotSize = 0.0/*0.05*/;
	WaitingForMotion = 0;
	m_ActiveLandmark = -1;
	m_InteractionCaptured = true;
}

void misColorPointWidget::Init()
{
	m_Cursor3D->Initialization();
}

void misColorPointWidget::SetEnabled(int enabling)
{
	if (!Interactor)
		return;

	if (enabling) //-----------------------------------------------------------
	{
		vtkDebugMacro(<< "Enabling point widget");

		if (Enabled) //already enabled, just return
			return;
		_ASSERT(CurrentRenderer != NULL);
		Enabled = 1;
		// listen for the following events
		vtkRenderWindowInteractor *i = Interactor;
		i->AddObserver(vtkCommand::MouseMoveEvent, EventCallbackCommand,
			Priority);
		i->AddObserver(vtkCommand::LeftButtonPressEvent,
			EventCallbackCommand, Priority);
		i->AddObserver(vtkCommand::LeftButtonReleaseEvent,
			EventCallbackCommand, Priority);
		i->AddObserver(vtkCommand::MiddleButtonPressEvent,
			EventCallbackCommand, Priority);
		i->AddObserver(vtkCommand::MiddleButtonReleaseEvent,
			EventCallbackCommand, Priority);
		i->AddObserver(vtkCommand::RightButtonPressEvent,
			EventCallbackCommand, Priority);
		i->AddObserver(vtkCommand::RightButtonReleaseEvent,
			EventCallbackCommand, Priority);

		// Add the line
		AddActors();
		m_Cursor3D->Update();
		InvokeEvent(vtkCommand::EnableEvent, NULL);
	}

	else //disabling----------------------------------------------------------
	{
		vtkDebugMacro(<< "Disabling point widget");
		if (!Enabled) //already disabled, just return
			return;
		Enabled = 0;
		// don't listen for events any more
		Interactor->RemoveObserver(EventCallbackCommand);
		// turn off the line
		RemoveActors();
		InvokeEvent(vtkCommand::DisableEvent, NULL);
	}

	Interactor->Render();
}

void misColorPointWidget::ProcessEvents(vtkObject* vtkNotUsed(object), unsigned long event, void* clientdata, void* vtkNotUsed(calldata))
{
	misColorPointWidget* self = reinterpret_cast<misColorPointWidget *>(clientdata);
	if (self->m_CursorType == Complete)
	{
		switch (event)
		{
		case vtkCommand::LeftButtonPressEvent:
			//if(self->m_ProcessEvent == true)
			self->OnLeftButtonDown();
			break;
		case vtkCommand::LeftButtonReleaseEvent:
			//if(self->m_ProcessEvent == true)
			self->OnLeftButtonUp();
			break;
		case vtkCommand::MiddleButtonPressEvent:
			//if(self->m_ProcessEvent == true)
			self->OnMiddleButtonDown();
			break;
		case vtkCommand::MiddleButtonReleaseEvent:
			//if(self->m_ProcessEvent == true)
			self->OnMiddleButtonUp();
			break;
		case vtkCommand::RightButtonPressEvent:
			//if(self->m_ProcessEvent == true)
			self->OnRightButtonDown();
			break;
		case vtkCommand::RightButtonReleaseEvent:
			//if(self->m_ProcessEvent == true)
			self->OnRightButtonUp();
			break;
		case vtkCommand::MouseMoveEvent:
			//if(self->m_ProcessEvent == true)
			self->OnMouseMove();
			break;
		}
	}
}



void misColorPointWidget::Highlight(int highlight)
{
	if (highlight)
	{
		m_XAxisPicker->GetPickPosition(LastPickPosition);
		ValidPick = 1;
	}
}

int misColorPointWidget::DetermineConstraintAxis(int constraint, double *x)
{
	// Look for trivial cases
	if (!Interactor->GetShiftKey())
	{
		return -1;
	}
	else if (constraint >= 0 && constraint < 3)
	{
		return constraint;
	}

	// Okay, figure out constraint. First see if the choice is
	// outside the hot spot
	if (!WaitingForMotion)
	{
		double p[3], d2, tol;
		m_XAxisPicker->GetPickPosition(p);
		d2 = vtkMath::Distance2BetweenPoints(p, LastPickPosition);
		tol = HotSpotSize*InitialLength;
		if (d2 > (tol*tol))
		{
			WaitingForMotion = 0;
			return m_XAxisPicker->GetCellId();
		}
		else
		{
			WaitingForMotion = 1;
			WaitCount = 0;
			return -1;
		}
	}
	else if (WaitingForMotion && x)
	{
		double v[3];
		WaitingForMotion = 0;
		v[0] = fabs(x[0] - LastPickPosition[0]);
		v[1] = fabs(x[1] - LastPickPosition[1]);
		v[2] = fabs(x[2] - LastPickPosition[2]);
		return (v[0] > v[1] ? (v[0] > v[2] ? 0 : 2) : (v[1] > v[2] ? 1 : 2));
	}
	else
	{
		return -1;
	}
}

void misColorPointWidget::OnLeftButtonDown()
{
	if (m_InteractionCaptured == false)
		return;
	if (!Interactor)
		return;

	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Okay, make sure that the pick is in the current renderer
	if (!CurrentRenderer || !CurrentRenderer->IsInViewport(X, Y))
	{
		m_WidgetState = Outside;
		return;
	}
	vtkProp *prop = NULL;
	vtkAssemblyPath *path1 = NULL;
	vtkAssemblyPath *path2 = NULL;
	vtkAssemblyPath *path3 = NULL;
	int counter = 0;
	if (!m_XAxisPicker || !m_YAxisPicker || !m_ZAxisPicker)
		return;
	if (!CurrentRenderer)
		return;
	m_XAxisPicker->Pick(X, Y, 0.0, CurrentRenderer);
	path1 = m_XAxisPicker->GetPath();

	m_YAxisPicker->Pick(X, Y, 0.0, CurrentRenderer);
	path2 = m_YAxisPicker->GetPath();

	m_ZAxisPicker->Pick(X, Y, 0.0, CurrentRenderer);
	path3 = m_ZAxisPicker->GetPath();
	if (path1 != NULL)
	{
		prop = path1->GetFirstNode()->GetViewProp();
		m_CurrentAxis = XAxis;
		counter++;
	}

	if (path2 != NULL)
	{
		prop = path2->GetFirstNode()->GetViewProp();
		m_CurrentAxis = YAxis;
		counter++;
	}
	if (path3 != NULL)
	{
		prop = path3->GetFirstNode()->GetViewProp();
		m_CurrentAxis = ZAxis;
		counter++;
	}
	if ((path1 == NULL) && (path2 == NULL) && (path3 == NULL))
	{
		m_WidgetState = Outside;
		Highlight(0);
		ConstraintAxis = -1;
		return;
	}

	if ((counter == 1))
		m_Mode = 0;
	else
		m_Mode = 1;

	currentActor = dynamic_cast<vtkActor *>(prop);
	m_CurrentPicker->GetPickPosition(LastPickPosition);

	m_WidgetState = Moving;
	ConstraintAxis = DetermineConstraintAxis(-1, NULL);

	double d[3];
	GetPosition(d);

	EventCallbackCommand->SetAbortFlag(1);
	StartInteraction();
	InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	Interactor->Render();
}

void misColorPointWidget::OnLeftButtonUp()
{
	if (m_InteractionCaptured == false)
	{
		return;
	}
	if (m_WidgetState == Outside || m_WidgetState == Start)
	{
		return;
	}
	m_WidgetState = Start;
	Highlight(0);
	EventCallbackCommand->SetAbortFlag(1);
	EndInteraction();
	double d[3];
	GetPosition(d);
	InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	Interactor->Render();
}

void misColorPointWidget::OnMiddleButtonDown()
{
	if (m_InteractionCaptured == false)
	{
		return;
	}
	int x = Interactor->GetEventPosition()[0];
	int y = Interactor->GetEventPosition()[1];
	// Okay, make sure that the pick is in the current renderer
	if (!CurrentRenderer || !CurrentRenderer->IsInViewport(x, y))
	{
		m_WidgetState = Outside;
		return;
	}
	if (!m_XAxisPicker)
		return;

	m_XAxisPicker->Pick(x, y, 0.0, CurrentRenderer);
	vtkAssemblyPath *path = m_XAxisPicker->GetPath();
	if (!path)
	{
		m_WidgetState = Translating;
		Highlight(1);
	}
	else
	{
		m_WidgetState = Outside;
		ConstraintAxis = -1;
		return;
	}
	EventCallbackCommand->SetAbortFlag(1);
	StartInteraction();
	InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	Interactor->Render();
}

void misColorPointWidget::OnMiddleButtonUp()
{
	if (m_InteractionCaptured == false)
	{
		return;
	}
	if (m_WidgetState == Outside || m_WidgetState == Start)
	{
		return;
	}
	m_WidgetState = Start;
	Highlight(0);
	EventCallbackCommand->SetAbortFlag(1);
	EndInteraction();
	InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	Interactor->Render();
}

void misColorPointWidget::OnRightButtonDown()
{
	if (m_InteractionCaptured == false)
	{
		return;
	}
}

void misColorPointWidget::OnRightButtonUp()
{
	if (m_InteractionCaptured == false)
	{
		return;
	}
	if (m_WidgetState == Outside || m_WidgetState == Start)
	{
		return;
	}
}

void misColorPointWidget::OnMouseMove()
{
	if (m_InteractionCaptured == false)
		return;

	if (m_WidgetState == Outside || m_WidgetState == Start)
	{
		return;
	}

	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Do different things depending on m_WidgetState
	// Calculations everybody does
	double focalPoint[4], pickPoint[4], prevPickPoint[4];
	double z;

	vtkCamera *camera = CurrentRenderer->GetActiveCamera();
	if (!camera)
	{
		return;
	}

	// Compute the two points defining the motion vector
	ComputeWorldToDisplay(LastPickPosition[0], LastPickPosition[1], LastPickPosition[2], focalPoint);
	z = focalPoint[2];
	ComputeDisplayToWorld(double(Interactor->GetLastEventPosition()[0]), double(Interactor->GetLastEventPosition()[1]),
		z, prevPickPoint);
	ComputeDisplayToWorld(double(X), double(Y), z, pickPoint);

	// Process the motion
	if (m_WidgetState == Moving)
	{
		if (!WaitingForMotion || WaitCount++ > 3)
		{
			ConstraintAxis = DetermineConstraintAxis(ConstraintAxis, pickPoint);
			MoveFocus(prevPickPoint, pickPoint);
		}
		else
		{
			return; //avoid the extra render
		}
	}
	// Interact, if desired
	EventCallbackCommand->SetAbortFlag(1);
	InvokeEvent(vtkCommand::InteractionEvent, NULL);
	Interactor->Render();
}

void misColorPointWidget::MoveFocus(double *p1, double *p2)
{
	//Get the motion vector
	double v[3];
	v[0] = p2[0] - p1[0];
	v[1] = p2[1] - p1[1];
	v[2] = p2[2] - p1[2];

	double focus[3];

	m_Cursor3D->GetFocalPoint(focus);

	if (ConstraintAxis >= 0)
	{
		focus[ConstraintAxis] += v[ConstraintAxis];
	}
	else
	{
		focus[0] += v[0];
		focus[1] += v[1];
		focus[2] += v[2];
	}
	if (m_Mode == 0)
	{
		if (m_CurrentAxis == XAxis)

			focus[0] -= v[0];
		else if (m_CurrentAxis == YAxis)
			focus[1] -= v[1];
		else if (m_CurrentAxis == ZAxis)
			focus[2] -= v[2];
		m_Cursor3D->SetFocalPoint(focus);
	}
	else if (m_Mode == 1)
	{
		m_Cursor3D->SetFocalPoint(focus);
	}
}

void misColorPointWidget::PlaceWidget(double bds[6])
{
	int i;
	double bounds[6], center[3];

	AdjustBounds(bds, bounds, center);

	m_Cursor3D->SetModelBounds(bounds);
	//m_Cursor3D->SetFocalPoint(center);
	m_Cursor3D->Update(); 

	for (i = 0; i < 6; i++)
	{
		InitialBounds[i] = bounds[i];
	}

	InitialLength = sqrt((bounds[1] - bounds[0])*(bounds[1] - bounds[0]) +
		(bounds[3] - bounds[2])*(bounds[3] - bounds[2]) +
		(bounds[5] - bounds[4])*(bounds[5] - bounds[4]));

}

void misColorPointWidget::PlaceWidget(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
	//	Superclass::PlaceWidget(xmin,xmax,ymin,ymax,zmin,zmax);
}

void misColorPointWidget::GetPolyData(vtkPolyData *pd)
{
	m_Cursor3D->Update();
	if (!pd)
	{
		return;
	}
	pd->DeepCopy(m_Cursor3D->GetFocus());
}

misColorPointWidget * misColorPointWidget::New()
{
	return new misColorPointWidget();
}

void misColorPointWidget::SetCurrentCursorType(misCursorType cursorType)
{
	std::shared_ptr<ICornerProperties> tempCorner;
	if (m_Cursor3D)
	{
		if (m_CursorType == cursorType)
		{
			return;
		}
		tempCorner = m_Cursor3D->m_CornerPropreties;
		if (Interactor)
		{
			SetEnabled(0);
		}
		m_Cursor3D = 0;
	}

	SetCursorType(cursorType);

	m_Cursor3D = misCursorFactory::MakeNewCursor(cursorType);
	m_Cursor3D->SetColorsComposition(m_AxesColors);
	m_Cursor3D->SetLineWidth(m_LineWidth);
	m_Cursor3D->m_WidgetOrientation = m_WidgetOrientation;
	m_Cursor3D->Initialization();
	if (tempCorner)
		m_Cursor3D->SetCornerProperties(tempCorner);

	UpdateWidgetPosition();
	if (cursorType == CompleteCursor)
	{
		InitialCrossSetting();
	}
	else
		ResetCrossSetting();

	if (Interactor)
	{
		SetEnabled(1);
	}
}

void misColorPointWidget::InitialCrossSetting()
{
	if (!currentActor)
	{
		currentActor = vtkSmartPointer<vtkActor>::New();
	}
	
	if (!m_XAxisPicker)
	{
		m_XAxisPicker = vtkSmartPointer<vtkCellPicker>::New();
		m_XAxisPicker->PickFromListOn();
		m_XAxisPicker->AddPickList(GetActors()[0]);
		m_XAxisPicker->SetTolerance(m_PickingTolerance);
	}
	if (!m_YAxisPicker)
	{
 		m_YAxisPicker = vtkSmartPointer<vtkCellPicker>::New();
		m_YAxisPicker->PickFromListOn();
		m_YAxisPicker->AddPickList(GetActors()[1]);
		m_YAxisPicker->SetTolerance(m_PickingTolerance);
	}
	if (!m_ZAxisPicker)
	{
		m_ZAxisPicker = vtkSmartPointer<vtkCellPicker>::New();
		m_ZAxisPicker->PickFromListOn();
		m_ZAxisPicker->AddPickList(GetActors()[2]);
		m_ZAxisPicker->SetTolerance(m_PickingTolerance);
	}

	if (!m_CurrentPicker)
	{
		m_CurrentPicker = vtkSmartPointer<vtkCellPicker>::New();
		m_CurrentPicker->PickFromListOn();
		m_CurrentPicker->AddPickList(currentActor);
	}
}

void misColorPointWidget::ResetCrossSetting()
{
	currentActor = 0;
	m_XAxisPicker = 0;
	m_YAxisPicker = 0;
	m_ZAxisPicker = 0;
	m_CurrentPicker = 0;
}


void misColorPointWidget::AddActors()
{
 	for (auto actor : GetActors())
	{

		CurrentRenderer->AddActor(actor);
	}
}

void misColorPointWidget::RemoveActors()
{
	auto cursorActors = GetActors();
	for (auto cActor : cursorActors)
	{
		vtkActor* tempActor = cActor;
		CurrentRenderer->RemoveActor(tempActor);
	}
}

void misColorPointWidget::SetPosition(double x, double y, double z)
{
	m_Cursor3D->SetFocalPoint(x, y, z);
}

void misColorPointWidget::SetPosition(double x[3])
{
	SetPosition(x[0], x[1], x[2]);
}

double* misColorPointWidget::GetPosition()
{
	if (m_Cursor3D)
		return m_Cursor3D->GetFocalPoint();
	return 0;
}

void misColorPointWidget::GetPosition(double xyz[3])
{
	m_Cursor3D->GetFocalPoint(xyz);
}

bool misColorPointWidget::GetTorusVisibility()
{
	return m_TorusVisibility;
}

void misColorPointWidget::SetTorusVisibility(bool b)
{
	m_TorusVisibility = b;
}

double misColorPointWidget::GetDParam()
{
	return DParam;
}

void misColorPointWidget::SetDParam(double d)
{
	DParam = d;
}

void misColorPointWidget::SetCursorType(misCursorType cursorType)
{
	m_CursorType = cursorType;
}

IMAGEORIENTATION misColorPointWidget::GetWidgetOrientation()
{
	return m_WidgetOrientation;
}

void misColorPointWidget::SetWidgetOrientation(IMAGEORIENTATION orientation)
{
	m_WidgetOrientation = orientation;
	if (!m_Cursor3D)
	{
		return;
	}
	m_Cursor3D->m_WidgetOrientation = orientation;
}

std::vector<vtkSmartPointer<vtkActor>> misColorPointWidget::GetActors()
{
	return m_Cursor3D->GetActors();
}

void misColorPointWidget::SetCurrentActiveLandmark(int index)
{
	m_ActiveLandmark = index;
}

int misColorPointWidget::GetCurrentActiveLandmark()
{
	return m_ActiveLandmark;
}

void misColorPointWidget::SetInteractionCapturedFlag(bool val)
{
	m_InteractionCaptured = val;
}

void misColorPointWidget::SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProperties)
{
	if (!pCornerProperties)
	{
		return;
	}
	m_Cursor3D->SetCornerProperties(pCornerProperties);
}

void misColorPointWidget::UpdateWidgetPosition()
{
	if (!m_Cursor3D)
	{
		return;
	}
	m_Cursor3D->UpdateWidgetPosition();
}

void misColorPointWidget::SetAxesColors(parcast::AxesColors const& colors)
{
	m_AxesColors = colors;
	if (!m_Cursor3D)
	{
		return;
	}
	m_Cursor3D->SetColorsComposition(colors);
}

void misColorPointWidget::SetPickingTolerance(double pickingTolerance)
{
	m_PickingTolerance = pickingTolerance;
}

void misColorPointWidget::ModifyAxis()
{
	if (!m_Cursor3D)
	{
		return;
	}
	m_Cursor3D->ModifyAxis();
}

void misColorPointWidget::SetLineWidth(double width)
{
	m_LineWidth = width;
	if (!m_Cursor3D)
	{
		return;
	}
	m_Cursor3D->SetLineWidth(width);
	m_Cursor3D->ModifyAxis();
}