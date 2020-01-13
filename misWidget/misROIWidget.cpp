#include "stdafx.h"
#include "misROIWidget.h"

#include "VisualizationGeneralTypes.h"
#include "misLogger.h"


misROIWidget::misROIWidget()
	:TranslationEnabled(1), RotationEnabled(1), ScalingEnabled(1), InsideOut(0), OutlineFaceWires(0), OutlineCursorWires(1), m_Activate(true)
{
	State = misROIWidget::Start;
	EventCallbackCommand->SetCallback(misROIWidget::ProcessEvents);


	// Construct the poly data representing the hex
	HexPolyData = vtkPolyData::New();
	HexMapper = vtkPolyDataMapper::New();
	HexMapper->SetInputData(HexPolyData);
	HexActor = vtkActor::New();
	HexActor->SetMapper(HexMapper);

	// Construct initial points
	Points = vtkPoints::New(VTK_DOUBLE);
	Points->SetNumberOfPoints(27);//8 corners; 6 faces;
	HexPolyData->SetPoints(Points);

	// Construct connectivity for the faces. These are used to perform
	// the picking.
	auto cells = CreateBoxCell();
	HexPolyData->SetPolys(cells);
	HexPolyData->BuildCells();

	// The face of the hexahedra
	auto HexFacePolyDatacells = vtkCellArray::New();
	HexFacePolyDatacells->Allocate(HexFacePolyDatacells->EstimateSize(1, 4));
	vtkIdType pts[4];
	pts[0] = 4; pts[1] = 5; pts[2] = 6; pts[3] = 7;
	HexFacePolyDatacells->InsertNextCell(4, pts); //temporary, replaced later

	HexFacePolyData = vtkPolyData::New();
	HexFacePolyData->SetPoints(Points);
	HexFacePolyData->SetPolys(HexFacePolyDatacells);
	HexFaceMapper = vtkPolyDataMapper::New();
	HexFaceMapper->SetInputData(HexFacePolyData);
	HexFace = vtkActor::New();
	HexFace->SetMapper(HexFaceMapper);

	// Create the outline for the hex
	OutlinePolyData = vtkPolyData::New();
	OutlinePolyData->SetPoints(Points);
	OutlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	OutlineMapper->SetInputData(OutlinePolyData);
	HexOutline = vtkActor::New();
	HexOutline->SetMapper(OutlineMapper);
	auto OutlineMappercells = vtkCellArray::New();
	OutlineMappercells->Allocate(OutlineMappercells->EstimateSize(15, 2));
	OutlinePolyData->SetLines(OutlineMappercells);
	
	// Set up the initial properties
	CreateDefaultProperties();

	// Create the outline
	GenerateOutline();

	// Create the handles
	m_SphereHandles.resize(numberOfHandel);
	for (auto& elemnt : m_SphereHandles)
		elemnt = vtkSmartPointer<vtkActor>::New();
	m_SphereHandlesMapper.resize(numberOfHandel);

	m_SphereHandlesGeometry.resize(numberOfHandel);
	for (auto& elem : m_SphereHandlesGeometry)
	{
		elem = vtkSmartPointer<vtkSphereSource>::New();
		elem->SetThetaResolution(16);
		elem->SetPhiResolution(8);
	}
	for (auto& elem : m_SphereHandlesMapper)
		elem = vtkSmartPointer<vtkPolyDataMapper>::New();
	for (int i = 0; i < numberOfHandel; i++)
	{
		m_SphereHandlesMapper[i]->SetInputConnection(m_SphereHandlesGeometry[i]->GetOutputPort());
		m_SphereHandles[i]->SetMapper(m_SphereHandlesMapper[i]);
	}

	// Define the point coordinates
	double bounds[6];
	bounds[0] = -0.5;
	bounds[1] = 0.5;
	bounds[2] = -0.5;
	bounds[3] = 0.5;
	bounds[4] = -0.5;
	bounds[5] = 0.5;
	// Points 8-14 are down by PositionHandles();
	PlaceWidget(bounds);

	//Manage the picking stuff
	HandlePicker = vtkCellPicker::New();
	HandlePicker->SetTolerance(0.001);
	for (int i = 0; i < numberOfHandel; i++)
		HandlePicker->AddPickList(m_SphereHandles[i]);
	HandlePicker->PickFromListOn();

	HexPicker = vtkCellPicker::New();
	HexPicker->SetTolerance(0.001);
	HexPicker->AddPickList(HexActor);
	HexPicker->PickFromListOn();

	CurrentHandle = 0;
	m_orientation = UNKnownDirection;
	Transform = vtkTransform::New();
	OnLeftButtonUp();

	m_centerTranslate[0] = 0;
	m_centerTranslate[1] = 0;
	m_cornerHandle[0] = 0;
	m_cornerHandle[1] = 0;
	for (int k = 0; k < 8; k++)
	{
		m_edgeHandle[k] = 0;
	}
}

vtkSmartPointer<vtkCellArray> misROIWidget::CreateBoxCell()
{
	vtkIdType pts[4];
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	cells->Allocate(cells->EstimateSize(6, 4));
	pts[0] = 3; pts[1] = 0; pts[2] = 4; pts[3] = 7;
	cells->InsertNextCell(4, pts);
	pts[0] = 1; pts[1] = 2; pts[2] = 6; pts[3] = 5;
	cells->InsertNextCell(4, pts);
	pts[0] = 0; pts[1] = 1; pts[2] = 5; pts[3] = 4;
	cells->InsertNextCell(4, pts);
	pts[0] = 2; pts[1] = 3; pts[2] = 7; pts[3] = 6;
	cells->InsertNextCell(4, pts);
	pts[0] = 0; pts[1] = 3; pts[2] = 2; pts[3] = 1;
	cells->InsertNextCell(4, pts);
	pts[0] = 4; pts[1] = 5; pts[2] = 6; pts[3] = 7;
	cells->InsertNextCell(4, pts);
	return cells;
}

misROIWidget::~misROIWidget()
{
	HexActor->Delete();
	HexMapper->Delete();
	HexPolyData->Delete();
	Points->Delete();
	HexFace->Delete();
	HexFaceMapper->Delete();
	HexFacePolyData->Delete();
	HexOutline->Delete();
	OutlinePolyData->Delete();
	HandlePicker->Delete();
	HexPicker->Delete();
	Transform->Delete();
	HandleProperty->Delete();
	SelectedHandleProperty->Delete();
	FaceProperty->Delete();
	SelectedFaceProperty->Delete();
	OutlineProperty->Delete();
	SelectedOutlineProperty->Delete();
}

void misROIWidget::SetEnabled(int enabling)
{


	if (!Interactor)
	{
		vtkErrorMacro(<< "The interactor must be set prior to enabling/disabling widget");
		return;
	}

	if (enabling) //------------------------------------------------------------
	{
		vtkDebugMacro(<< "Enabling widget");

		if (Enabled) //already enabled, just return
		{
			return;
		}

		if (!CurrentRenderer)
		{
			SetCurrentRenderer(Interactor->FindPokedRenderer(
				Interactor->GetLastEventPosition()[0],
				Interactor->GetLastEventPosition()[1]));
			if (CurrentRenderer == NULL)
			{
				return;
			}
		}

		Enabled = 1;

		//    listen to the following events
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

		//    Add the various actors
		//    Add the outline
		CurrentRenderer->AddActor(HexActor);
		CurrentRenderer->AddActor(HexOutline);
		HexActor->SetProperty(OutlineProperty);
		HexOutline->SetProperty(OutlineProperty);
		//   Add the hex face
		CurrentRenderer->AddActor(HexFace);
		HexFace->SetProperty(FaceProperty);
 		//   turn on the handles
		for (int j = 0; j < numberOfHandel; j++)
		{
			CurrentRenderer->AddActor(m_SphereHandles[j]);
			m_SphereHandles[j]->SetProperty(HandleProperty);
		}

 

		for (int i = m_cornerHandle[0]; i < m_cornerHandle[1]; i++)
			CurrentRenderer->RemoveActor(m_SphereHandles[i]);

		InvokeEvent(vtkCommand::EnableEvent, NULL);
	}

	else //disabling-------------------------------------------------------------
	{
		if (!Enabled) //already disabled, just return
		{
			return;
		}

		Enabled = 0;

		//don't listen for events any more
		Interactor->RemoveObserver(EventCallbackCommand);

		//turn off the outline
		CurrentRenderer->RemoveActor(HexActor);
		CurrentRenderer->RemoveActor(HexOutline);

		//turn off the hex face
		CurrentRenderer->RemoveActor(HexFace);

		// turn off the handles
		for (int i = 0; i < numberOfHandel; i++)
		{
			CurrentRenderer->RemoveActor(m_SphereHandles[i]);
		}

		CurrentHandle = 0;
		InvokeEvent(vtkCommand::DisableEvent, NULL);
		SetCurrentRenderer(NULL);
	}

	Interactor->Render();
}

void misROIWidget::ProcessEvents(vtkObject* vtkNotUsed(object), unsigned long event, void* clientdata, void* vtkNotUsed(calldata))
{
	misROIWidget* self = reinterpret_cast<misROIWidget *>(clientdata);

	//okay, let's do the right thing
	switch (event)
	{
	case vtkCommand::LeftButtonPressEvent:
		if (self->m_Activate == true)
		{
			self->OnLeftButtonDown();
		}

		break;
	case vtkCommand::LeftButtonReleaseEvent:
		if (self->m_Activate == true)
		{
			self->OnLeftButtonUp();
		}
		break;
	case vtkCommand::MiddleButtonPressEvent:
		if (self->m_Activate == true)
		{
			self->OnMiddleButtonDown();
		}
		break;
	case vtkCommand::MiddleButtonReleaseEvent:
		if (self->m_Activate == true)
		{
			self->OnMiddleButtonUp();
		}
		break;
	case vtkCommand::RightButtonPressEvent:
		if (self->m_Activate == true)
		{
			self->OnRightButtonDown();
		}
		break;
	case vtkCommand::RightButtonReleaseEvent:
		if (self->m_Activate == true)
		{
			self->OnRightButtonUp();
		}
		break;
	case vtkCommand::MouseMoveEvent:
		if (self->m_Activate == true)
		{
			self->OnMouseMove();
		}
		break;
	}
}

void misROIWidget::PrintSelf(ostream& os, vtkIndent indent)
{
	Superclass::PrintSelf(os, indent);

	double *bounds = InitialBounds;
	os << indent << "Initial Bounds: "
		<< "(" << bounds[0] << "," << bounds[1] << ") "
		<< "(" << bounds[2] << "," << bounds[3] << ") "
		<< "(" << bounds[4] << "," << bounds[5] << ")\n";

	if (HandleProperty)
	{
		os << indent << "m_SphereHandles Property: " << HandleProperty << "\n";
	}
	else
	{
		os << indent << "m_SphereHandles Property: (none)\n";
	}
	if (SelectedHandleProperty)
	{
		os << indent << "Selected m_SphereHandles Property: "
			<< SelectedHandleProperty << "\n";
	}
	else
	{
		os << indent << "SelectedHandle Property: (none)\n";
	}

	if (FaceProperty)
	{
		os << indent << "Face Property: " << FaceProperty << "\n";
	}
	else
	{
		os << indent << "Face Property: (none)\n";
	}
	if (SelectedFaceProperty)
	{
		os << indent << "Selected Face Property: "
			<< SelectedFaceProperty << "\n";
	}
	else
	{
		os << indent << "Selected Face Property: (none)\n";
	}

	if (OutlineProperty)
	{
		os << indent << "Outline Property: " << OutlineProperty << "\n";
	}
	else
	{
		os << indent << "Outline Property: (none)\n";
	}
	if (SelectedOutlineProperty)
	{
		os << indent << "Selected Outline Property: "
			<< SelectedOutlineProperty << "\n";
	}
	else
	{
		os << indent << "Selected Outline Property: (none)\n";
	}

	os << indent << "Outline Face Wires: " << (OutlineFaceWires ? "On\n" : "Off\n");
	os << indent << "Outline Cursor Wires: " << (OutlineCursorWires ? "On\n" : "Off\n");
	os << indent << "Inside Out: " << (InsideOut ? "On\n" : "Off\n");
	os << indent << "Translation Enabled: " << (TranslationEnabled ? "On\n" : "Off\n");
	os << indent << "Scaling Enabled: " << (ScalingEnabled ? "On\n" : "Off\n");
	os << indent << "Rotation Enabled: " << (RotationEnabled ? "On\n" : "Off\n");

}

#define VTK_AVERAGE(a,b,c) \
	c[0] = (a[0] + b[0])/2.0; \
	c[1] = (a[1] + b[1])/2.0; \
	c[2] = (a[2] + b[2])/2.0;

void misROIWidget::PositionHandles()
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double *p0 = pts;
	double *p1 = pts + 3 * 1;
	double *p2 = pts + 3 * 2;
	double *p3 = pts + 3 * 3;
	double *p4 = pts + 3 * 4;
	double *p5 = pts + 3 * 5;
	double *p6 = pts + 3 * 6;
	double *p7 = pts + 3 * 7;
	double x[3];

	VTK_AVERAGE(p0, p7, x);
	Points->SetPoint(8, x);
	VTK_AVERAGE(p1, p6, x);
	Points->SetPoint(9, x);
	VTK_AVERAGE(p0, p5, x);
	Points->SetPoint(10, x);
	VTK_AVERAGE(p2, p7, x);
	Points->SetPoint(11, x);
	VTK_AVERAGE(p1, p3, x);
	Points->SetPoint(12, x);
	VTK_AVERAGE(p5, p7, x);
	Points->SetPoint(13, x);
	VTK_AVERAGE(p0, p6, x);
	Points->SetPoint(14, x);
	//////////////////////////////////////////////////////////////////////////
	VTK_AVERAGE(p4, p7, x);
	Points->SetPoint(15, x);
	VTK_AVERAGE(p0, p3, x);
	Points->SetPoint(16, x);
	VTK_AVERAGE(p5, p6, x);
	Points->SetPoint(17, x);
	VTK_AVERAGE(p1, p2, x);
	Points->SetPoint(18, x);
	VTK_AVERAGE(p4, p5, x);
	Points->SetPoint(numberOfHandel, x);
	VTK_AVERAGE(p0, p1, x);
	Points->SetPoint(20, x);
	VTK_AVERAGE(p7, p6, x);
	Points->SetPoint(21, x);
	VTK_AVERAGE(p2, p3, x);
	Points->SetPoint(22, x);
	VTK_AVERAGE(p3, p7, x);
	Points->SetPoint(23, x);
	VTK_AVERAGE(p0, p4, x);
	Points->SetPoint(24, x);
	VTK_AVERAGE(p2, p6, x);
	Points->SetPoint(25, x);
	VTK_AVERAGE(p1, p5, x);
	Points->SetPoint(26, x);

	for (int i = 0; i < numberOfHandel; ++i)
		m_SphereHandlesGeometry[i]->SetCenter(Points->GetPoint(8 + i));
	m_HandleFaceMap[0] = 0;
	m_HandleFaceMap[15] = 0;
	m_HandleFaceMap[1] = 1;
	m_HandleFaceMap[6] = 1;
	m_HandleFaceMap[16] = 1;
	m_HandleFaceMap[8] = 1;
	m_HandleFaceMap[2] = 2;
	m_HandleFaceMap[17] = 2;
	m_HandleFaceMap[9] = 2;
	m_HandleFaceMap[3] = 3;
	m_HandleFaceMap[10] = 3;
	m_HandleFaceMap[18] = 3;
	m_HandleFaceMap[4] = 4;
	m_HandleFaceMap[11] = 4;
	m_HandleFaceMap[5] = 5;
	m_HandleFaceMap[12] = 5;
	m_HandleFaceMap[13] = 0;
	m_HandleFaceMap[14] = 7;
	m_HandleFaceMap[7] = 6;






	Points->GetData()->Modified();
	HexFacePolyData->Modified();
	HexPolyData->Modified();
	GenerateOutline();
}
#undef VTK_AVERAGE

void misROIWidget::HandlesOn()
{
	for (int i = 0; i < numberOfHandel; i++)
	{
		m_SphereHandles[i]->VisibilityOn();
	}

}

void misROIWidget::HandlesOff()
{
	for (int i = 0; i < numberOfHandel; i++)
	{
		m_SphereHandles[i]->VisibilityOff();
	}
}

void misROIWidget::SizeHandles()
{
	double radius = vtk3DWidget::SizeHandles(0.75);;
	for (int i = 0; i < numberOfHandel; i++)
	{
		m_SphereHandlesGeometry[i]->SetRadius(radius);
	}
}

int misROIWidget::HighlightHandle(vtkProp *prop)
{
	CurrentHandle = static_cast<vtkActor *>(prop);

	if (!CurrentHandle)
		return -1;
	CurrentHandle->SetProperty(HandleProperty);

	CurrentHandle->SetProperty(SelectedHandleProperty);
	for (int i = 0; i < 27; i++) //find attached face
		return m_HandleFaceMap[i];
return -1;

}

void misROIWidget::HighlightFace(int cellId)
{
	if (cellId >= 0)
	{
		vtkIdType npts;
		vtkIdType *pts;
		vtkCellArray *cells = HexFacePolyData->GetPolys();
		HexPolyData->GetCellPoints(cellId, npts, pts);
		HexFacePolyData->Modified();
		cells->ReplaceCell(0, npts, pts);
		CurrentHexFace = cellId;
		HexFace->SetProperty(SelectedFaceProperty);
		if (!CurrentHandle)
		{
			CurrentHandle = HexFace;
		}
	}
	else
	{
		HexFace->SetProperty(FaceProperty);
		CurrentHexFace = -1;
	}
}

void misROIWidget::HighlightOutline(int highlight)
{
	if (highlight)
	{
		HexActor->SetProperty(SelectedOutlineProperty);
		HexOutline->SetProperty(SelectedOutlineProperty);
	}
	else
	{
		HexActor->SetProperty(OutlineProperty);
		HexOutline->SetProperty(OutlineProperty);
	}
}

void misROIWidget::OnLeftButtonDown()
{
	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Okay, we can process this. Try to pick handles first;
	// if no handles picked, then pick the bounding box.
	if (!CurrentRenderer || !CurrentRenderer->IsInViewport(X, Y))
	{
		State = misROIWidget::Outside;
		return;
	}

	vtkAssemblyPath *path;
	HandlePicker->Pick(X, Y, 0.0, CurrentRenderer);
	path = HandlePicker->GetPath();
	if (path != NULL)
	{
		State = misROIWidget::Moving;
		HighlightFace(
			HighlightHandle(path->GetFirstNode()->GetViewProp()));
		HandlePicker->GetPickPosition(LastPickPosition);
		ValidPick = 1;
	}
	else
	{
		HexPicker->Pick(X, Y, 0.0, CurrentRenderer);
		path = HexPicker->GetPath();
		if (path != NULL)
		{
			State = misROIWidget::Moving;
			HexPicker->GetPickPosition(LastPickPosition);
			ValidPick = 1;
			if (!Interactor->GetShiftKey())
			{
				HighlightHandle(NULL);
				HighlightFace(HexPicker->GetCellId());
			}
			else
			{
				CurrentHandle = m_SphereHandles[6];
				HighlightOutline(1);
			}
		}
		else
		{
			HighlightFace(HighlightHandle(NULL));
			State = misROIWidget::Outside;
			return;
		}
	}

	EventCallbackCommand->SetAbortFlag(1);
	StartInteraction();
	InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	Interactor->Render();
}

void misROIWidget::OnLeftButtonUp()
{
	if (State == misROIWidget::Outside ||
		State == misROIWidget::Start)
	{
		return;
	}

	State = misROIWidget::Start;
	HighlightFace(HighlightHandle(NULL));
	SizeHandles();

	EventCallbackCommand->SetAbortFlag(1);
	EndInteraction();
	InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	Interactor->Render();

}

void misROIWidget::OnMiddleButtonDown()
{
	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Okay, we can process this. Try to pick handles first;
	// if no handles picked, then pick the bounding box.
	if (!CurrentRenderer || !CurrentRenderer->IsInViewport(X, Y))
	{
		State = misROIWidget::Outside;
		return;
	}

	vtkAssemblyPath *path;
	HandlePicker->Pick(X, Y, 0.0, CurrentRenderer);
	path = HandlePicker->GetPath();
	if (path != NULL)
	{
		State = misROIWidget::Moving;
		CurrentHandle = m_SphereHandles[6];
		HighlightOutline(1);
		HandlePicker->GetPickPosition(LastPickPosition);
		ValidPick = 1;
	}
	else
	{
		HexPicker->Pick(X, Y, 0.0, CurrentRenderer);
		path = HexPicker->GetPath();
		if (path != NULL)
		{
			State = misROIWidget::Moving;
			CurrentHandle = m_SphereHandles[6];
			HighlightOutline(1);
			HexPicker->GetPickPosition(LastPickPosition);
			ValidPick = 1;
		}
		else
		{
			HighlightFace(HighlightHandle(NULL));
			State = misROIWidget::Outside;
			return;
		}
	}

	EventCallbackCommand->SetAbortFlag(1);
	StartInteraction();
	InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	Interactor->Render();
}

void misROIWidget::OnMiddleButtonUp()
{
	if (State == misROIWidget::Outside ||
		State == misROIWidget::Start)
	{
		return;
	}

	State = misROIWidget::Start;
	HighlightFace(HighlightHandle(NULL));
	SizeHandles();

	EventCallbackCommand->SetAbortFlag(1);
	EndInteraction();
	InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	Interactor->Render();


}

void misROIWidget::OnRightButtonDown()
{
	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Okay, we can process this. Try to pick handles first;
	// if no handles picked, then pick the bounding box.
	if (!CurrentRenderer || !CurrentRenderer->IsInViewport(X, Y))
	{
		State = misROIWidget::Outside;
		return;
	}

	vtkAssemblyPath *path;
	HandlePicker->Pick(X, Y, 0.0, CurrentRenderer);
	path = HandlePicker->GetPath();
	if (path != NULL)
	{
		State = misROIWidget::Scaling;
		HighlightOutline(1);
		HandlePicker->GetPickPosition(LastPickPosition);
		ValidPick = 1;
	}
	else
	{
		HexPicker->Pick(X, Y, 0.0, CurrentRenderer);
		path = HexPicker->GetPath();
		if (path != NULL)
		{
			State = misROIWidget::Scaling;
			HighlightOutline(1);
			HexPicker->GetPickPosition(LastPickPosition);
			ValidPick = 1;
		}
		else
		{
			State = misROIWidget::Outside;
			return;
		}
	}

	EventCallbackCommand->SetAbortFlag(1);
	StartInteraction();
	InvokeEvent(vtkCommand::StartInteractionEvent, NULL);
	Interactor->Render();

	InvokeEvent(misROIWidgetChangeEvent, &m_orientation);
}

void misROIWidget::OnRightButtonUp()
{
	if (State == misROIWidget::Outside)
	{
		return;
	}

	State = misROIWidget::Start;
	HighlightOutline(0);
	SizeHandles();

	EventCallbackCommand->SetAbortFlag(1);
	EndInteraction();
	InvokeEvent(vtkCommand::EndInteractionEvent, NULL);
	Interactor->Render();
}

void misROIWidget::OnMouseMove()
{
	// See whether we're active
	if (State == misROIWidget::Outside || State == misROIWidget::Start)
		return;

	int X = Interactor->GetEventPosition()[0];
	int Y = Interactor->GetEventPosition()[1];

	// Do different things depending on state
	// Calculations everybody does
	double focalPoint[4], pickPoint[4], prevPickPoint[4];
	double z, vpn[3];

	vtkCamera *camera = CurrentRenderer->GetActiveCamera();
	if (!camera)
		return;

	// Compute the two points defining the motion vector
	ComputeWorldToDisplay(LastPickPosition[0], LastPickPosition[1], LastPickPosition[2], focalPoint);
	z = focalPoint[2];
	ComputeDisplayToWorld(double(Interactor->GetLastEventPosition()[0]), double(Interactor->GetLastEventPosition()[1]), z, prevPickPoint);
	ComputeDisplayToWorld(double(X), double(Y), z, pickPoint);

	// Process the motion
	if (State == misROIWidget::Moving)
	{
		if (m_orientation == UNKnownDirection)
			return;
		// Okay to process
		if (CurrentHandle)
		{
			if (RotationEnabled && CurrentHandle == HexFace)
			{
				camera->GetViewPlaneNormal(vpn);
				Rotate(X, Y, prevPickPoint, pickPoint, vpn);
			}



			else if (TranslationEnabled && (CurrentHandle == m_SphereHandles[6] ||
				CurrentHandle == m_SphereHandles[m_centerTranslate[0]] ||
				CurrentHandle == m_SphereHandles[m_centerTranslate[1]]))
			{

				Translate(prevPickPoint, pickPoint);
			}

			else if (TranslationEnabled && ScalingEnabled)
			{
				if (CurrentHandle == m_SphereHandles[0])
				{
					MoveMinusXFace(prevPickPoint, pickPoint);
				}
				else if (CurrentHandle == m_SphereHandles[1])
				{
					MovePlusXFace(prevPickPoint, pickPoint);
				}
				else if (CurrentHandle == m_SphereHandles[2])
				{
					MoveMinusYFace(prevPickPoint, pickPoint);
				}
				else if (CurrentHandle == m_SphereHandles[3])
				{
					MovePlusYFace(prevPickPoint, pickPoint);
				}
				else if (CurrentHandle == m_SphereHandles[4])
				{
					MoveMinusZFace(prevPickPoint, pickPoint);
				}
				else if (CurrentHandle == m_SphereHandles[5])
				{
					MovePlusZFace(prevPickPoint, pickPoint);
				}
				switch (m_orientation)
				{
				case AXIAL:
				{
					if ((CurrentHandle == m_SphereHandles[AXIAL_LEFT_FRONT]) || (CurrentHandle == m_SphereHandles[AXIAL_LEFT_BACK]))
					{
						MoveMinusXFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[AXIAL_RIGHT_FRONT]) || (CurrentHandle == m_SphereHandles[AXIAL_RIGHT_BACK]))
					{
						MovePlusXFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[AXIAL_BOTTOM_FRONT]) || (CurrentHandle == m_SphereHandles[AXIAL_BOTTOM_BACK]))
					{
						MoveMinusYFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[AXIAL_UP_FRONT]) || (CurrentHandle == m_SphereHandles[AXIAL_Up_BACK]))
					{
						MovePlusYFace(prevPickPoint, pickPoint);
					}

				}
				break;
				case CORONAL:
				{
					if ((CurrentHandle == m_SphereHandles[CORONAL_UP_FRONT]) || (CurrentHandle == m_SphereHandles[CORONAL_Up_BACK]))
					{
						MoveMinusZFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[CORONAL_BOTTOM_FRONT]) || (CurrentHandle == m_SphereHandles[CORONAL_BOTTOM_BACK]))
					{
						MovePlusZFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[CORONAL_LEFT_FRONT]) || (CurrentHandle == m_SphereHandles[CORONAL_LEFT_BACK]))
					{
						MoveMinusXFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[CORONAL_RIGHT_FRONT]) || (CurrentHandle == m_SphereHandles[CORONAL_RIGHT_BACK]))
					{
						MovePlusXFace(prevPickPoint, pickPoint);
					}
				}
				break;
				case SAGITTAL:
				{
					if ((CurrentHandle == m_SphereHandles[SAGITTAL_UP_FRONT]) || (CurrentHandle == m_SphereHandles[SAGITTAL_Up_BACK]))
					{
						MoveMinusZFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[SAGITTAL_BOTTOM_FRONT]) || (CurrentHandle == m_SphereHandles[SAGITTAL_BOTTOM_BACK]))
					{
						MovePlusZFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[SAGITTAL_LEFT_FRONT]) || (CurrentHandle == m_SphereHandles[SAGITTAL_LEFT_BACK]))
					{
						MoveMinusYFace(prevPickPoint, pickPoint);
					}
					else if ((CurrentHandle == m_SphereHandles[SAGITTAL_RIGHT_FRONT]) || (CurrentHandle == m_SphereHandles[SAGITTAL_RIGHT_BACK]))
					{
						MovePlusYFace(prevPickPoint, pickPoint);
					}
				}
				break;
				}
				/////////////////////////////////////////////////////////

			}
		}
	}
	// 	else if ( ScalingEnabled && State == misROIWidget::Scaling )
	// 	{
	// 		Scale(prevPickPoint, pickPoint, X, Y);
	// 	}

		// Interact, if desired
	EventCallbackCommand->SetAbortFlag(1);
	InvokeEvent(vtkCommand::InteractionEvent, NULL);
	Interactor->Render();
}

void misROIWidget::MoveFace(double *p1, double *p2, double *dir, double *x1, double *x2, double *x3, double *x4, double *x5)
{
	int i;
	double v[3], v2[3];

	for (i = 0; i < 3; i++)
	{
		v[i] = p2[i] - p1[i];
		v2[i] = dir[i];
	}

	vtkMath::Normalize(v2);
	double f = vtkMath::Dot(v, v2);

	for (i = 0; i < 3; i++)
	{
		v[i] = f*v2[i];

		x1[i] += v[i];
		x2[i] += v[i];
		x3[i] += v[i];
		x4[i] += v[i];
		x5[i] += v[i];
	}
	PositionHandles();
}

void misROIWidget::GetDirection(const double Nx[3], const double Ny[3], const double Nz[3], double dir[3])
{
	double dotNy, dotNz;
	double y[3];

	if (vtkMath::Dot(Nx, Nx) != 0)
	{
		dir[0] = Nx[0];
		dir[1] = Nx[1];
		dir[2] = Nx[2];
	}
	else
	{
		dotNy = vtkMath::Dot(Ny, Ny);
		dotNz = vtkMath::Dot(Nz, Nz);
		if (dotNy != 0 && dotNz != 0)
		{
			vtkMath::Cross(Ny, Nz, dir);
		}
		else if (dotNy != 0)
		{
			//dir must have been initialized to the 
			//corresponding coordinate direction before calling
			//this method
			vtkMath::Cross(Ny, dir, y);
			vtkMath::Cross(y, Ny, dir);
		}
		else if (dotNz != 0)
		{
			//dir must have been initialized to the 
			//corresponding coordinate direction before calling
			//this method
			vtkMath::Cross(Nz, dir, y);
			vtkMath::Cross(y, Nz, dir);
		}
	}
}

void misROIWidget::MovePlusXFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 9;

	double *x1 = pts + 3 * 1;
	double *x2 = pts + 3 * 2;
	double *x3 = pts + 3 * 5;
	double *x4 = pts + 3 * 6;

	double dir[3] = { 1 , 0 , 0 };
	ComputeNormals();
	GetDirection(N[1], N[3], N[5], dir);
	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

void misROIWidget::MoveMinusXFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 8;

	double *x1 = pts + 3 * 0;
	double *x2 = pts + 3 * 3;
	double *x3 = pts + 3 * 4;
	double *x4 = pts + 3 * 7;

	double dir[3] = { -1,0,0 };
	ComputeNormals();
	GetDirection(N[0], N[4], N[2], dir);

	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

void misROIWidget::MovePlusYFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 11;

	double *x1 = pts + 3 * 2;
	double *x2 = pts + 3 * 3;
	double *x3 = pts + 3 * 6;
	double *x4 = pts + 3 * 7;

	double dir[3] = { 0,1,0 };
	ComputeNormals();
	GetDirection(N[3], N[5], N[1], dir);

	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

void misROIWidget::MoveMinusYFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 10;

	double *x1 = pts + 3 * 0;
	double *x2 = pts + 3 * 1;
	double *x3 = pts + 3 * 4;
	double *x4 = pts + 3 * 5;

	double dir[3] = { 0, -1, 0 };
	ComputeNormals();
	GetDirection(N[2], N[0], N[4], dir);

	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

void misROIWidget::MovePlusZFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 13;

	double *x1 = pts + 3 * 4;
	double *x2 = pts + 3 * 5;
	double *x3 = pts + 3 * 6;
	double *x4 = pts + 3 * 7;

	double dir[3] = { 0,0,1 };
	ComputeNormals();
	GetDirection(N[5], N[1], N[3], dir);

	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

void misROIWidget::MoveMinusZFace(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);

	double *h1 = pts + 3 * 12;

	double *x1 = pts + 3 * 0;
	double *x2 = pts + 3 * 1;
	double *x3 = pts + 3 * 2;
	double *x4 = pts + 3 * 3;

	double dir[3] = { 0,0,-1 };
	ComputeNormals();
	GetDirection(N[4], N[2], N[0], dir);

	MoveFace(p1, p2, dir, x1, x2, x3, x4, h1);
}

// Loop through all points and translate them

void misROIWidget::Translate(double *p1, double *p2)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double v[3];

	v[0] = p2[0] - p1[0];
	v[1] = p2[1] - p1[1];
	v[2] = p2[2] - p1[2];

	// Move the corners
	for (int i = 0; i < 8; i++)
	{
		*pts++ += v[0];
		*pts++ += v[1];
		*pts++ += v[2];
	}
	PositionHandles();
}

void misROIWidget::Scale(double* vtkNotUsed(p1), double* vtkNotUsed(p2), int vtkNotUsed(X), int Y)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double *center
		= static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(3 * 14);
	double sf;

	if (Y > Interactor->GetLastEventPosition()[1])
	{
		sf = 1.03;
	}
	else
	{
		sf = 0.97;
	}

	// Move the corners
	for (int i = 0; i < 8; i++, pts += 3)
	{
		pts[0] = sf * (pts[0] - center[0]) + center[0];
		pts[1] = sf * (pts[1] - center[1]) + center[1];
		pts[2] = sf * (pts[2] - center[2]) + center[2];
	}
	PositionHandles();
}

void misROIWidget::ComputeNormals()
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double *p0 = pts;
	double *px = pts + 3 * 1;
	double *py = pts + 3 * 3;
	double *pz = pts + 3 * 4;
	int i;

	for (i = 0; i < 3; i++)
	{
		N[0][i] = p0[i] - px[i];
		N[2][i] = p0[i] - py[i];
		N[4][i] = p0[i] - pz[i];
	}
	vtkMath::Normalize(N[0]);
	vtkMath::Normalize(N[2]);
	vtkMath::Normalize(N[4]);
	for (i = 0; i < 3; i++)
	{
		N[1][i] = -N[0][i];
		N[3][i] = -N[2][i];
		N[5][i] = -N[4][i];
	}
}

void misROIWidget::GetPlanes(vtkPlanes *planes)
{
	if (!planes)
	{
		return;
	}

	ComputeNormals();

	vtkPoints *pts = vtkPoints::New(VTK_DOUBLE);
	pts->SetNumberOfPoints(6);

	vtkDoubleArray *normals = vtkDoubleArray::New();
	normals->SetNumberOfComponents(3);
	normals->SetNumberOfTuples(6);

	// Set the normals and coordinate values
	double factor = (InsideOut ? -1.0 : 1.0);
	for (int i = 0; i < 6; i++)
	{
		pts->SetPoint(i, Points->GetPoint(8 + i));
		normals->SetTuple3(i, factor*N[i][0], factor*N[i][1],
			factor*N[i][2]);
	}

	planes->SetPoints(pts);
	planes->SetNormals(normals);

	pts->Delete();
	normals->Delete();
}

void misROIWidget::Rotate(int X, int Y, double *p1, double *p2, double *vpn)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double *center =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(3 * 14);
	double v[3]; //vector of motion
	double axis[3]; //axis of rotation
	double theta; //rotation angle
	int i;

	v[0] = p2[0] - p1[0];
	v[1] = p2[1] - p1[1];
	v[2] = p2[2] - p1[2];

	// Create axis of rotation and angle of rotation
	vtkMath::Cross(vpn, v, axis);
	if (vtkMath::Normalize(axis) == 0.0)
	{
		return;
	}
	int *size = CurrentRenderer->GetSize();
	double l2 = (X - Interactor->GetLastEventPosition()[0])*(X - Interactor->GetLastEventPosition()[0]) + (Y - Interactor->GetLastEventPosition()[1])*(Y - Interactor->GetLastEventPosition()[1]);
	theta = 360.0 * sqrt(l2 / (size[0] * size[0] + size[1] * size[1]));

	//Manipulate the transform to reflect the rotation
	Transform->Identity();
	Transform->Translate(center[0], center[1], center[2]);
	Transform->RotateWXYZ(theta, axis);
	Transform->Translate(-center[0], -center[1], -center[2]);

	//Set the corners
	vtkPoints *newPts = vtkPoints::New(VTK_DOUBLE);
	Transform->TransformPoints(Points, newPts);

	for (i = 0; i < 8; i++, pts += 3)
	{
		Points->SetPoint(i, newPts->GetPoint(i));
	}

	newPts->Delete();
	PositionHandles();
}

void misROIWidget::CreateDefaultProperties()
{
	// m_SphereHandles properties
	HandleProperty = vtkProperty::New();
	HandleProperty->SetColor(1, 1, 1);

	SelectedHandleProperty = vtkProperty::New();
	SelectedHandleProperty->SetColor(1, 0, 0);

	// Face properties
	FaceProperty = vtkProperty::New();
	FaceProperty->SetColor(1, 1, 1);
	FaceProperty->SetOpacity(0.0);

	SelectedFaceProperty = vtkProperty::New();
	SelectedFaceProperty->SetColor(1, 1, 0);
	SelectedFaceProperty->SetOpacity(0.25);

	// Outline properties
	OutlineProperty = vtkProperty::New();
	OutlineProperty->SetRepresentationToWireframe();
	OutlineProperty->SetAmbient(1.0);
	OutlineProperty->SetColor(1.0, 1.0, 1.0);
	OutlineProperty->SetLineWidth(2.0);

	SelectedOutlineProperty = vtkProperty::New();
	SelectedOutlineProperty->SetRepresentationToWireframe();
	SelectedOutlineProperty->SetAmbient(1.0);
	SelectedOutlineProperty->SetColor(0.0, 1.0, 0.0);
	SelectedOutlineProperty->SetLineWidth(2.0);

	DeactivedOutLineProperty = vtkProperty::New();
	DeactivedOutLineProperty->SetRepresentationToWireframe();
	DeactivedOutLineProperty->SetAmbient(1.0);
	DeactivedOutLineProperty->SetColor(1.0, 0.0, 0.0);
	DeactivedOutLineProperty->SetLineWidth(2.0);
}

void misROIWidget::PlaceWidget(double bds[6])
{
	int i;
	double bounds[6], center[3];

	AdjustBounds(bds, bounds, center);

	Points->SetPoint(0, bounds[0], bounds[2], bounds[4]);
	Points->SetPoint(1, bounds[1], bounds[2], bounds[4]);
	Points->SetPoint(2, bounds[1], bounds[3], bounds[4]);
	Points->SetPoint(3, bounds[0], bounds[3], bounds[4]);
	Points->SetPoint(4, bounds[0], bounds[2], bounds[5]);
	Points->SetPoint(5, bounds[1], bounds[2], bounds[5]);
	Points->SetPoint(6, bounds[1], bounds[3], bounds[5]);
	Points->SetPoint(7, bounds[0], bounds[3], bounds[5]);

	for (i = 0; i < 6; i++)
	{
		InitialBounds[i] = bounds[i];
	}
	InitialLength = sqrt((bounds[1] - bounds[0])*(bounds[1] - bounds[0]) +
		(bounds[3] - bounds[2])*(bounds[3] - bounds[2]) +
		(bounds[5] - bounds[4])*(bounds[5] - bounds[4]));

	PositionHandles();
	ComputeNormals();
	SizeHandles();
}

void misROIWidget::GetTransform(vtkTransform *t)
{
	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double *p0 = pts;
	double *p1 = pts + 3 * 1;
	double *p3 = pts + 3 * 3;
	double *p4 = pts + 3 * 4;
	double *p14 = pts + 3 * 14;
	double center[3], translate[3], scale[3], scaleVec[3][3];
	double InitialCenter[3];
	int i;

	// The transformation is relative to the initial bounds.
	// Initial bounds are set when PlaceWidget() is invoked.
	t->Identity();

	// Translation
	for (i = 0; i < 3; i++)
	{
		InitialCenter[i] =
			(InitialBounds[2 * i + 1] + InitialBounds[2 * i]) / 2.0;
		center[i] = p14[i] - InitialCenter[i];
	}
	translate[0] = center[0] + InitialCenter[0];
	translate[1] = center[1] + InitialCenter[1];
	translate[2] = center[2] + InitialCenter[2];
	t->Translate(translate[0], translate[1], translate[2]);

	// Orientation
	vtkMatrix4x4 *matrix = vtkMatrix4x4::New();
	PositionHandles();
	ComputeNormals();
	for (i = 0; i < 3; i++)
	{
		matrix->SetElement(i, 0, N[1][i]);
		matrix->SetElement(i, 1, N[3][i]);
		matrix->SetElement(i, 2, N[5][i]);
	}
	t->Concatenate(matrix);
	matrix->Delete();

	// Scale
	for (i = 0; i < 3; i++)
	{
		scaleVec[0][i] = (p1[i] - p0[i]);
		scaleVec[1][i] = (p3[i] - p0[i]);
		scaleVec[2][i] = (p4[i] - p0[i]);
	}

	scale[0] = vtkMath::Norm(scaleVec[0]);
	if (InitialBounds[1] != InitialBounds[0])
	{
		scale[0] = scale[0] / (InitialBounds[1] - InitialBounds[0]);
	}
	scale[1] = vtkMath::Norm(scaleVec[1]);
	if (InitialBounds[3] != InitialBounds[2])
	{
		scale[1] = scale[1] / (InitialBounds[3] - InitialBounds[2]);
	}
	scale[2] = vtkMath::Norm(scaleVec[2]);
	if (InitialBounds[5] != InitialBounds[4])
	{
		scale[2] = scale[2] / (InitialBounds[5] - InitialBounds[4]);
	}
	t->Scale(scale[0], scale[1], scale[2]);

	// Add back in the contribution due to non-origin center
	t->Translate(-InitialCenter[0], -InitialCenter[1], -InitialCenter[2]);
}

void misROIWidget::SetTransform(vtkTransform* t)
{
	if (!t)
	{
		vtkErrorMacro(<< "vtkTransform t must be non-NULL");
		return;
	}

	double *pts =
		static_cast<vtkDoubleArray *>(Points->GetData())->GetPointer(0);
	double xIn[3];
	// make sure the transform is up-to-date before using it
	t->Update();

	// Position the eight points of the box and then update the
	// position of the other handles.
	double *bounds = InitialBounds;

	xIn[0] = bounds[0]; xIn[1] = bounds[2]; xIn[2] = bounds[4];
	t->InternalTransformPoint(xIn, pts);

	xIn[0] = bounds[1]; xIn[1] = bounds[2]; xIn[2] = bounds[4];
	t->InternalTransformPoint(xIn, pts + 3);

	xIn[0] = bounds[1]; xIn[1] = bounds[3]; xIn[2] = bounds[4];
	t->InternalTransformPoint(xIn, pts + 6);

	xIn[0] = bounds[0]; xIn[1] = bounds[3]; xIn[2] = bounds[4];
	t->InternalTransformPoint(xIn, pts + 9);

	xIn[0] = bounds[0]; xIn[1] = bounds[2]; xIn[2] = bounds[5];
	t->InternalTransformPoint(xIn, pts + 12);

	xIn[0] = bounds[1]; xIn[1] = bounds[2]; xIn[2] = bounds[5];
	t->InternalTransformPoint(xIn, pts + 15);

	xIn[0] = bounds[1]; xIn[1] = bounds[3]; xIn[2] = bounds[5];
	t->InternalTransformPoint(xIn, pts + 18);

	xIn[0] = bounds[0]; xIn[1] = bounds[3]; xIn[2] = bounds[5];
	t->InternalTransformPoint(xIn, pts + 21);

	PositionHandles();
}

void misROIWidget::GetPolyData(vtkPolyData *pd)

{
	pd->SetPoints(HexPolyData->GetPoints());
	pd->SetPolys(HexPolyData->GetPolys());
}

void misROIWidget::SetOutlineFaceWires(int newValue)
{
	if (OutlineFaceWires != newValue)
	{
		OutlineFaceWires = newValue;
		Modified();
		// the outline is dependent on this value, so we have to regen
		GenerateOutline();
	}
}

void misROIWidget::SetOutlineCursorWires(int newValue)
{
	if (OutlineCursorWires != newValue)
	{
		OutlineCursorWires = newValue;
		Modified();
		// the outline is dependent on this value, so we have to regen
		GenerateOutline();
	}
}

void misROIWidget::GenerateOutline()
{
	// Whatever the case may be, we have to reset the Lines of the
	// OutlinePolyData (i.e. nuke all current line data)
	vtkCellArray *cells = OutlinePolyData->GetLines();
	cells->Reset();

	// Now the outline lines
	if (!OutlineFaceWires && !OutlineCursorWires)
	{
		return;
	}

	vtkIdType pts[2];

	if (OutlineFaceWires)
	{
		pts[0] = 0; pts[1] = 7;       //the -x face
		cells->InsertNextCell(2, pts);
		pts[0] = 3; pts[1] = 4;
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 6;       //the +x face
		cells->InsertNextCell(2, pts);
		pts[0] = 2; pts[1] = 5;
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 4;       //the -y face
		cells->InsertNextCell(2, pts);
		pts[0] = 0; pts[1] = 5;
		cells->InsertNextCell(2, pts);
		pts[0] = 3; pts[1] = 6;       //the +y face
		cells->InsertNextCell(2, pts);
		pts[0] = 2; pts[1] = 7;
		cells->InsertNextCell(2, pts);
		pts[0] = 0; pts[1] = 2;       //the -z face
		cells->InsertNextCell(2, pts);
		pts[0] = 1; pts[1] = 3;
		cells->InsertNextCell(2, pts);
		pts[0] = 4; pts[1] = 6;       //the +Z face
		cells->InsertNextCell(2, pts);
		pts[0] = 5; pts[1] = 7;
		cells->InsertNextCell(2, pts);
	}
	if (OutlineCursorWires)
	{
		pts[0] = 8; pts[1] = 9;         //the x cursor line
		cells->InsertNextCell(2, pts);
		pts[0] = 10; pts[1] = 11;       //the y cursor line
		cells->InsertNextCell(2, pts);
		pts[0] = 12; pts[1] = 13;       //the z cursor line
		cells->InsertNextCell(2, pts);
	}
	OutlinePolyData->Modified();
	if (OutlineProperty)
	{
		OutlineProperty->SetRepresentationToWireframe();
		SelectedOutlineProperty->SetRepresentationToWireframe();
	}
}

vtkPoints* misROIWidget::GetPoints()
{
	vtkPoints* p = vtkPoints::New();
	p = Points;
	return p;
}

void misROIWidget::SetPoints(vtkPoints *p)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		Points->SetPoint(i, p->GetPoint(i));
	}
}

double * misROIWidget::GetCompressData(vtkPoints* p)
{
	int n = 0;
	int m = 0;
	double * compdata = new double[6];
	double temp[3];
	double min[3] = { 0 };
	double max[3] = { 0 };
	p->GetPoint(0, min);
	for (int i = 1; i < 8; i++)
	{
		p->GetPoint(i, temp);
		for (int j = 0; j < 3; j++)
		{
			if (min[j] > temp[j])
			{
				min[j] = temp[j];
			}
			if (temp[j] > max[j])
			{
				max[j] = temp[j];
			}
		}
	}
	for (int q = 0; q < 6; q++)
	{
		if (q % 2 == 0)
		{
			compdata[q] = min[n];
			n++;
		}
		else
		{
			compdata[q] = max[m];
			m++;
		}
	}
	return compdata;
}

void misROIWidget::OneHandleOff(int i)
{
	m_SphereHandles[i]->VisibilityOff();
}

misROIWidget* misROIWidget::New()
{
	return new misROIWidget;
}

void misROIWidget::SetBoxActive()
{
	m_Activate = true;
	HexActor->SetProperty(OutlineProperty);
	HexOutline->SetProperty(OutlineProperty);
	HexFace->SetProperty(OutlineProperty);
}

void misROIWidget::SetBoxDeactive()
{
	m_Activate = false;
	HexActor->SetProperty(DeactivedOutLineProperty);
	HexOutline->SetProperty(DeactivedOutLineProperty);
	HexFace->SetProperty(DeactivedOutLineProperty);
}

void misROIWidget::SetOrientation(IMAGEORIENTATION orientation)
{
	m_orientation = orientation;
	switch (m_orientation)
	{
	case AXIAL:
	{
		m_centerTranslate[0] = AXIAL_FACE_FRONT;
		m_centerTranslate[1] = AXIAL_FACE_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_edgeHandle[0] = AXIAL_LEFT_FRONT;
		m_edgeHandle[1] = AXIAL_LEFT_BACK;
		m_edgeHandle[2] = AXIAL_RIGHT_FRONT;
		m_edgeHandle[3] = AXIAL_RIGHT_BACK;
		m_edgeHandle[4] = AXIAL_BOTTOM_FRONT;
		m_edgeHandle[5] = AXIAL_BOTTOM_BACK;
		m_edgeHandle[6] = AXIAL_UP_FRONT;
		m_edgeHandle[7] = AXIAL_Up_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_cornerHandle[0] = 15;
		m_cornerHandle[1] = numberOfHandel;
	}
	break;
	case CORONAL:
	{
		m_centerTranslate[0] = CORONAL_FACE_FRONT;
		m_centerTranslate[1] = CORONAL_FACE_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_edgeHandle[0] = CORONAL_LEFT_FRONT;
		m_edgeHandle[1] = CORONAL_LEFT_BACK;
		m_edgeHandle[2] = CORONAL_RIGHT_FRONT;
		m_edgeHandle[3] = CORONAL_RIGHT_BACK;
		m_edgeHandle[4] = CORONAL_BOTTOM_FRONT;
		m_edgeHandle[5] = CORONAL_BOTTOM_BACK;
		m_edgeHandle[6] = CORONAL_UP_FRONT;
		m_edgeHandle[7] = CORONAL_Up_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_cornerHandle[0] = 7;
		m_cornerHandle[1] = 11;
	}
	break;
	case SAGITTAL:
	{
		m_centerTranslate[0] = SAGITTAL_FACE_FRONT;
		m_centerTranslate[1] = SAGITTAL_FACE_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_edgeHandle[0] = SAGITTAL_LEFT_FRONT;
		m_edgeHandle[1] = SAGITTAL_LEFT_BACK;
		m_edgeHandle[2] = SAGITTAL_RIGHT_FRONT;
		m_edgeHandle[3] = SAGITTAL_RIGHT_BACK;
		m_edgeHandle[4] = SAGITTAL_BOTTOM_FRONT;
		m_edgeHandle[5] = SAGITTAL_BOTTOM_BACK;
		m_edgeHandle[6] = SAGITTAL_UP_FRONT;
		m_edgeHandle[7] = SAGITTAL_Up_BACK;
		//////////////////////////////////////////////////////////////////////////
		m_cornerHandle[0] = 11;
		m_cornerHandle[1] = 15;
	}
	break;
	}
}


IMAGEORIENTATION misROIWidget::GetOrientation()
{
	return m_orientation;
}

double misROIWidget::GetHandlePosition()
{
	double handlePosision = 0;
	double x[] = { 0, 0, 0 };

	switch (m_orientation)
	{
	case AXIAL:
	{
		Points->GetPoint(13, x);
		handlePosision = x[2];
	}
	break;
	case CORONAL:
	{
		Points->GetPoint(11, x);
		handlePosision = x[1];
	}
	break;
	case SAGITTAL:
	{
		Points->GetPoint(9, x);
		handlePosision = x[0];
	}
	break;
	}
	return handlePosision;
}

double misROIWidget::GetThirdDimensionValue()
{
	double thirdPosision = 0;
	double x[] = { 0, 0, 0 };
	double y[] = { 0, 0, 0 };
	switch (m_orientation)
	{
	case AXIAL:
	{
		Points->GetPoint(13, x);
		Points->GetPoint(12, y);
		thirdPosision = abs(x[2] - y[2]);
	}
	break;
	case CORONAL:
	{
		Points->GetPoint(10, x);
		Points->GetPoint(11, y);
		thirdPosision = abs(x[1] - y[1]);
	}
	break;
	case SAGITTAL:
	{
		Points->GetPoint(8, x);
		Points->GetPoint(9, y);
		thirdPosision = abs(x[0] - y[0]);
	}
	break;
	}
	return thirdPosision;
}


void misROIWidget::On()
{
	if (Interactor)
	{
		SetEnabled(1);
	}
}

void misROIWidget::Off()
{
	if (Interactor)
	{
		SetEnabled(0);
	}
}

void MyCallback::Execute(vtkObject *caller, unsigned long, void*)
{
	/*if (eventId== vtkCommand::RightButtonPressEvent)
	{

	}*/
}

void misROIWidget::UpdateWidgetData()
{
	vtkPoints* p = GetPoints();
	double* data = GetCompressData(p);
	int temp;
	if (data[0] > data[1])
	{
		temp = data[0];
		data[0] = data[1];
		data[1] = temp;
	}

	if (data[2] > data[3])
	{
		temp = data[2];
		data[2] = data[3];
		data[3] = temp;
	}

	if (data[4] > data[5])
	{
		temp = data[4];
		data[4] = data[5];
		data[5] = temp;
	}
}
