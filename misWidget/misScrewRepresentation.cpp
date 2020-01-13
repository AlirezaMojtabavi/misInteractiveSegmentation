#include "StdAfx.h"
#include "misScrewRepresentation.h"

#include "mis3DImplant.h"
#include "misScrewSource.h"
#include "misMathUtils.h"
#include "CylinderUtility.h"
#include "misPlanMapper.h"
#include  "misMathUtils.h"

using namespace std;

void misScrewRepresentation::CreateHandles()
{
	// Create the handles
	Handle = new vtkActor*[2];
	HandleMapper = new vtkPolyDataMapper*[2];
	HandleGeometry = new vtkSphereSource*[2];
	for (int i = 0; i < 2; i++)
	{
		//IMPORTANTNOTICE: HandleGeometry is the president of two ends of line.
		HandleGeometry[i] = vtkSphereSource::New();
		HandleGeometry[i]->SetThetaResolution(16);
		HandleGeometry[i]->SetPhiResolution(8.0);
		HandleMapper[i] = vtkPolyDataMapper::New();
		HandleMapper[i]->SetInputConnection(HandleGeometry[i]->GetOutputPort());
		Handle[i] = vtkActor::New();
		Handle[i]->SetMapper(HandleMapper[i]);
	}
}

misScrewRepresentation::misScrewRepresentation(
	std::shared_ptr<ICornerProperties> cornerProperties,
	std::shared_ptr<IImplantSource> implantSource) :
	m_ImplantSource(implantSource),
	m_CornerProperties(cornerProperties)
{
	// vtkWidgetRepresentation parameter initialization
	HandleSize = 5.0;
	Placed = 0;
	RepresentationState = Outside;

	InstantiateHandleRepresentation();
	CreateHandles();
	// Set up the initial properties
	CreateDefaultProperties();
	// This needs to be initialized before PlaceWidget is called.
	BoundingBox = vtkSmartPointer<vtkBox>::New();

	m_LineLenCaption->VisibilityOff();
	m_LineLenCaption->BorderOff();
	m_LineLenCaption->LeaderOff();

	LineActor->SetMapper(m_ImplantSource->GetMapper());
}

void misScrewRepresentation::SetScrewDiameter(double diameter)
{
	m_ImplantSource->SetRadius(diameter / 2.);
}



void misScrewRepresentation::UpdateLengthCaption(double x1[3], double x2[3]) const
{
	const auto dLineLen = (parcast::PointD3(x1) - parcast::PointD3(x2)).Length();
	std::ostringstream formatter;
	formatter << std::fixed << std::setprecision(1) << dLineLen;
	m_LineLenCaption->SetCaption(formatter.str().c_str());
	m_LineLenCaption->SetAttachmentPoint((x2[0] + x1[0]) / 2., (x2[1] + x1[1]) / 2., (x2[2] + x1[2]) / 2.);
	m_LineLenCaption->SetPosition(0.05, 0.05);
	m_LineLenCaption->GetCaptionTextProperty()->SetFontSize(42);
}

void misScrewRepresentation::BuildRepresentation()
{
	// Rebuild only if necessary
	if (GetMTime() > BuildTime ||
		Point1Representation->GetMTime() > BuildTime ||
		Point2Representation->GetMTime() > BuildTime ||
		LineHandleRepresentation->GetMTime() > BuildTime ||
		(Renderer && Renderer->GetVTKWindow() &&
		(Renderer->GetVTKWindow()->GetMTime() > BuildTime ||
			Renderer->GetActiveCamera()->GetMTime() > BuildTime)))
	{
		if (!InitializedDisplayPosition && Renderer)
		{

			double point1[3] = { m_ImplantSource->GetEntry()[0], m_ImplantSource->GetEntry()[1], m_ImplantSource->GetEntry()[2] };
			double point2[3] = { m_ImplantSource->GetTarget()[0], m_ImplantSource->GetTarget()[1] ,m_ImplantSource->GetTarget()[2] };
			SetPointsWorldPosition(point1, point2);

			ValidPick = 1;
			InitializedDisplayPosition = 1;
		};


	}

	double point1[3], point2[3];
	//IMPORTANTNOTICE: These methods return the position of the cross which is set at the end of line.
	GetPoint1WorldPosition(point1);
	GetPoint2WorldPosition(point2);
	UpdateLengthCaption(point1, point2);
	//IMPORTANTNOTICE: Control the position of cross according to type of mode movement and update line and sphere position(interaction style).
	SetCorrectWorldPositions(point1, point2);
	SizeHandles();
	BuildTime.Modified();
}


void misScrewRepresentation::SetCorrectWorldPositions(double x1[3], double x2[3])
{
	
	m_ImplantSource->SetEntry(parcast::PointD3(x1));
	m_ImplantSource->SetTarget(parcast::PointD3(x2));
	auto currentPosition = m_CornerProperties->GetCurrentPosition();
	m_ImplantSource->SetCurrentPoint(currentPosition);

	auto normalPlane = m_CornerProperties->GetPlaneNormal();
	auto normalPlaneITKVector = normalPlane.GetItkVector();
	auto normalplanevector3D = parcast::VectorD3(normalPlaneITKVector[0], normalPlaneITKVector[1], normalPlaneITKVector[2]);
	auto intersection = misMathUtils::GetIntersectionLineWithPlane(normalplanevector3D, parcast::PointD3(x1), parcast::PointD3(x2), currentPosition);
	m_ImplantSource->SetInterSectionPoint(intersection);
	m_ImplantSource->SetNormalPlane(normalplanevector3D);
	
	HandleGeometry[0]->SetCenter(x1); //the sphere
	HandleGeometry[1]->SetCenter(x2); //the sphere

	Point1Representation->SetWorldPosition(x1);
	Point2Representation->SetWorldPosition(x2);
}

void misScrewRepresentation::SetInteractionType(ScrewWidgetInteractionType type)
{
	m_InteractionState = type;
}

void misScrewRepresentation::SetMaxAllowedLineLen(double len)
{
}

ScrewWidgetInteractionType misScrewRepresentation::GetInteractionType()
{
	return m_InteractionState;
}


misScrewRepresentation::~misScrewRepresentation()
{
	if (HandleRepresentation)
	{
		HandleRepresentation->Delete();
	}
	if (Point1Representation)
	{
		Point1Representation->Delete();
	}
	if (Point2Representation)
	{
		Point2Representation->Delete();
	}
	if (LineHandleRepresentation)
	{
		LineHandleRepresentation->Delete();
	}

	for (int i = 0; i < 2; i++)
	{
		HandleGeometry[i]->Delete();
		HandleMapper[i]->Delete();
		Handle[i]->Delete();
	}
	delete[] Handle;
	delete[] HandleMapper;
	delete[] HandleGeometry;

	EndPointProperty->Delete();
	SelectedEndPointProperty->Delete();
	EndPoint2Property->Delete();
	SelectedEndPoint2Property->Delete();
	LineProperty->Delete();
	SelectedLineProperty->Delete();

}

void misScrewRepresentation::InstantiateHandleRepresentation()
{
	// By default, use one of these handles
	HandleRepresentation = vtkPointHandleRepresentation3D::New();
	//HandleRepresentation->AllOff(); //was not needed
	HandleRepresentation->SetHotSpotSize(1.0);
	HandleRepresentation->SetPlaceFactor(1.0);
	HandleRepresentation->TranslationModeOn();

	Point1Representation = HandleRepresentation->NewInstance();
	Point1Representation->ShallowCopy(HandleRepresentation);
	Point2Representation = HandleRepresentation->NewInstance();
	Point2Representation->ShallowCopy(HandleRepresentation);
	LineHandleRepresentation = HandleRepresentation->NewInstance();
	LineHandleRepresentation->ShallowCopy(HandleRepresentation);
}


void misScrewRepresentation::GetPoint1WorldPosition(double pos[3])
{
	Point1Representation->GetWorldPosition(pos);
}

double* misScrewRepresentation::GetPoint1WorldPosition()
{
	return Point1Representation->GetWorldPosition();
}

void misScrewRepresentation::GetPoint1DisplayPosition(double pos[3])
{
	Point1Representation->GetDisplayPosition(pos);
}

double* misScrewRepresentation::GetPoint1DisplayPosition()
{
	return Point1Representation->GetDisplayPosition();
}

void misScrewRepresentation::SetPointsWorldPosition(double x1[3], double x2[3])
{
	Point1Representation->SetWorldPosition(x1);
	Point2Representation->SetWorldPosition(x2);
	m_ImplantSource->SetEntry(parcast::PointD3(x1));
	m_ImplantSource->SetTarget(parcast::PointD3(x2));
	HandleGeometry[0]->SetCenter(x1); //the sphere
	HandleGeometry[1]->SetCenter(x2); //the sphere
}

void misScrewRepresentation::SetPoint1DisplayPosition(double x[3])
{
	Point1Representation->SetDisplayPosition(x);
	double p[3];
	Point1Representation->GetWorldPosition(p);
	Point1Representation->SetWorldPosition(p);
}

void misScrewRepresentation::GetPoint2WorldPosition(double pos[3])
{
	Point2Representation->GetWorldPosition(pos);
}

double* misScrewRepresentation::GetPoint2WorldPosition()
{
	return Point2Representation->GetWorldPosition();
}

void misScrewRepresentation::GetPoint2DisplayPosition(double pos[3])
{
	Point2Representation->GetDisplayPosition(pos);
}

double* misScrewRepresentation::GetPoint2DisplayPosition()
{
	return Point2Representation->GetDisplayPosition();
}

void misScrewRepresentation::SetPoint2DisplayPosition(double x[3])
{
	Point2Representation->SetDisplayPosition(x);
	double p[3];
	Point2Representation->GetWorldPosition(p);
	Point2Representation->SetWorldPosition(p);
}

void misScrewRepresentation::SetRenderer(vtkRenderer* ren)
{
	if (ren == Renderer)
	{
		return;
	}
	HandleRepresentation->SetRenderer(ren);
	Point1Representation->SetRenderer(ren);
	Point2Representation->SetRenderer(ren);
	LineHandleRepresentation->SetRenderer(ren);
	if(!ren->HasViewProp(m_LineLenCaption))
		ren->AddViewProp(m_LineLenCaption);
	UnRegisterPickers();
	Renderer = ren;
	PickersModified();
	Modified();
}

void misScrewRepresentation::StartWidgetInteraction(double e[2])
{
	if (m_Finalized)
	{
		return;
	}
	// Store the start position
	StartEventPosition[0] = e[0];
	StartEventPosition[1] = e[1];
	StartEventPosition[2] = 0.0;
	// Store the start position
	LastEventPosition[0] = e[0];
	LastEventPosition[1] = e[1];
	LastEventPosition[2] = 0.0;
	// Get the coordinates of the three handles
	Point1Representation->GetWorldPosition(StartP1);
	Point2Representation->GetWorldPosition(StartP2);
	LineHandleRepresentation->GetWorldPosition(StartLineHandle);

	if (InteractionState == misScrewRepresentation::Scaling)
	{
		double dp1[3], dp2[3];
		Point1Representation->GetDisplayPosition(dp1);
		Point2Representation->GetDisplayPosition(dp2);
		Length = sqrt((dp1[0] - dp2[0])*(dp1[0] - dp2[0]) + (dp1[1] - dp2[1])*(dp1[1] - dp2[1]));
	}
}

void misScrewRepresentation::WidgetInteraction(double e[2])
{
	if (m_Finalized)
	{
		return;
	}
	// Process the motion
	switch (InteractionState)
	{
	case misScrewRepresentation::OnLine:
	{
		double x[3] = { 0., 0., 0. }, p1[3] = { 0., 0., 0. }, p2[3] = { 0., 0., 0. }, delta[3]  = {0., 0., 0.};
		// Get the new position
		LineHandleRepresentation->GetWorldPosition(x);
		// Compute the delta from the previous position
		delta[0] = x[0] - StartLineHandle[0];
		delta[1] = x[1] - StartLineHandle[1];
		delta[2] = x[2] - StartLineHandle[2];

		//Is added for debug for plan jumps in panning state
		int a = 1;
		const double ln = parcast::VectorD3(delta).Length();
	
		for (auto i = 0; i < 3; i++)
		{
			p1[i] = StartP1[i] + delta[i];
			p2[i] = StartP2[i] + delta[i];
		}
		Point1Representation->SetWorldPosition(p1);
		Point2Representation->SetWorldPosition(p2);
	}
	case misScrewRepresentation::Scaling:
	{
		double p1[3], p2[3], center[3];

		Point1Representation->GetWorldPosition(p1);
		Point2Representation->GetWorldPosition(p2);

		double delta = sqrt((StartEventPosition[0] - e[0])*(StartEventPosition[0] - e[0]) +
			(StartEventPosition[1] - e[1])*(StartEventPosition[1] - e[1]));

		double sf = 1.0;
		if (Length != 0.0)
			sf = 1.0 + delta / Length;

		if ((e[1] - LastEventPosition[1]) < 0.0)
			sf = 1 / sf;

		for (int i = 0; i < 3; i++)
		{
			center[i] = (p1[i] + p2[i]) / 2.0;
			p1[i] = center[i] + (p1[i] - center[i])*sf;
			p2[i] = center[i] + (p2[i] - center[i])*sf;
		}
		Point1Representation->SetWorldPosition(p1);
		Point2Representation->SetWorldPosition(p2);
	}
	case misScrewRepresentation::TranslatingP1:
	{
		double x[3], p2[3];
		// Get the new position
		Point1Representation->GetWorldPosition(x);
		for (int i = 0; i < 3; i++)
		{
			p2[i] = StartP2[i] + (x[i] - StartP1[i]);
		}
		Point2Representation->SetWorldPosition(p2);
	}
	case misScrewRepresentation::TranslatingP2:
	{
		double x[3], p1[3];
		// Get the new position
		Point2Representation->GetWorldPosition(x);
		for (int i = 0; i < 3; i++)
			p1[i] = StartP1[i] + (x[i] - StartP2[i]);
		Point1Representation->SetWorldPosition(p1);
	}
	}


	// Store the start position
	LastEventPosition[0] = e[0];
	LastEventPosition[1] = e[1];
	LastEventPosition[2] = 0.0;
}

bool misScrewRepresentation::IsPointerOnPlan(int X, int Y)
{
	if (m_CornerProperties->GetPlanePoints(m_Orientation).empty())
		return false;

	Renderer->SetDisplayPoint(X, Y, 0);
	Renderer->DisplayToWorld();
	auto wordPos = Renderer->GetWorldPoint();
	mis3DPoint<double> wordpt(wordPos);
	auto planeNormal = mis3DVector<double>(m_CornerProperties->GetPlaneNormal().data);
	auto aPointOnPlane = mis3DPoint<double>(m_CornerProperties->GetPlanePoints(m_Orientation)[0].data);
	auto cornerIsValid = m_CornerProperties->GetValidity();
	auto projected = misMathUtils::GetProjectPointOnPlane(wordpt, aPointOnPlane, planeNormal);
	auto planCylinder =
		parcast::Cylinder{ m_ImplantSource->GetEntry(), m_ImplantSource->GetTarget(), m_ImplantSource->GetRadius() };
	auto util = parcast::CylinderUtility(planCylinder);
	return util.IsInCylinder(parcast::PointD3(projected.GetDataPointer()));
}

int misScrewRepresentation::ComputeInteractionState(int X, int Y, int vtkNotUsed(modify))
{

	if (m_Finalized)
		return misScrewRepresentation::Outside;

	// See if we are near one of the end points or outside
	double pos1[3], pos2[3];
	GetPoint1DisplayPosition(pos1);
	GetPoint2DisplayPosition(pos2);

	double p1[3], p2[3], xyz[3];
	double closest[3];
	xyz[0] = static_cast<double>(X);
	xyz[1] = static_cast<double>(Y);
	p1[0] = static_cast<double>(pos1[0]);
	p1[1] = static_cast<double>(pos1[1]);
	p2[0] = static_cast<double>(pos2[0]);
	p2[1] = static_cast<double>(pos2[1]);
	xyz[2] = p1[2] = p2[2] = 0.0;

	double tol2 = Tolerance*Tolerance;
	// Check if we are on end points
	if (vtkMath::Distance2BetweenPoints(xyz, p1) <= tol2)
	{
		InteractionState = misScrewRepresentation::OnP1;
		SetRepresentationState(misScrewRepresentation::OnP1);
		return InteractionState;
	}

	if (vtkMath::Distance2BetweenPoints(xyz, p2) <= tol2)
	{
		InteractionState = misScrewRepresentation::OnP2;
		SetRepresentationState(misScrewRepresentation::OnP2);
		return InteractionState;
	}


	if (IsPointerOnPlan(X, Y))
	{
		InteractionState = misScrewRepresentation::OnLine;
		SetRepresentationState(misScrewRepresentation::OnLine);
	}
	else
	{
		InteractionState = misScrewRepresentation::Outside;
		SetRepresentationState(misScrewRepresentation::Outside);
	}

	return InteractionState;
}

void misScrewRepresentation::SetRepresentationState(int state)
{
	if (RepresentationState == state)
		return;

	state = (state < misScrewRepresentation::Outside ?
		misScrewRepresentation::Outside :
		(state > misScrewRepresentation::Scaling ?
			misScrewRepresentation::Scaling : state));

	RepresentationState = state;
	Modified();
	m_LineLenCaption->VisibilityOn();
	if (state == misScrewRepresentation::Outside)
	{
		HighlightPoint(0, 0);
		HighlightPoint(1, 0);
		HighlightLine(0);
		m_LineLenCaption->VisibilityOff();
	}
	else if (state == misScrewRepresentation::OnP1)
	{
		HighlightPoint(0, 1);
		HighlightPoint(1, 0);
		HighlightLine(0);
	}
	else if (state == misScrewRepresentation::OnP2)
	{
		HighlightPoint(0, 0);
		HighlightPoint(1, 1);
		HighlightLine(0);
	}
	else if (state == misScrewRepresentation::OnLine)
	{
		HighlightPoint(0, 0);
		HighlightPoint(1, 0);
		HighlightLine(1);
	}
	else
	{
		HighlightPoint(0, 1);
		HighlightPoint(1, 1);
		HighlightLine(1);
	}
}

double *misScrewRepresentation::GetBounds()
{
	BuildRepresentation();
	BoundingBox->SetBounds(LineActor->GetBounds());
	BoundingBox->AddBounds(Handle[0]->GetBounds());
	BoundingBox->AddBounds(Handle[1]->GetBounds());

	return BoundingBox->GetBounds();
}

void misScrewRepresentation::CreateDefaultProperties()
{
	// Endpoint properties
	EndPointProperty = vtkProperty::New();
	EndPointProperty->SetColor(1.0, 0.0, 0.0);

	// Pass the initial properties to the actors.
	Handle[0]->SetProperty(EndPointProperty);
	//IMPORTANTNOTICE: Point1Representation is the president of the cross at the end of line.
	Point1Representation->SetProperty(EndPointProperty);
	LineHandleRepresentation->SetProperty(EndPointProperty);

	SelectedEndPointProperty = vtkProperty::New();
	SelectedEndPointProperty->SetColor(0, 1, 0);

	EndPoint2Property = vtkProperty::New();
	EndPoint2Property->SetColor(0.0, 1.0, 0.0);

	Handle[1]->SetProperty(EndPoint2Property);
	//IMPORTANTNOTICE: Point1Representation is the president of the cross at the end of line.
	Point2Representation->SetProperty(EndPoint2Property);

	SelectedEndPoint2Property = vtkProperty::New();
	SelectedEndPoint2Property->SetColor(0, 1, 0);

	// Line properties
	LineProperty = vtkProperty::New();
	//LineProperty->SetAmbientColor(0.1, 0.1, 0.1);
	//LineProperty->SetDiffuseColor(0.0, 0.0, 1.0);
	LineProperty->SetColor(0.0, 0.0, 1.0);
	LineProperty->SetLineWidth(2.0);
	LineActor->SetProperty(LineProperty);

	SelectedLineProperty = vtkProperty::New();
	SelectedLineProperty->SetAmbientColor(0.0, 1.0, 0.0);
	SelectedLineProperty->SetLineWidth(2.0);
}

void misScrewRepresentation::SizeHandles()
{
	// The SizeHandles() method depends on the LastPickPosition data member.
	auto p1 = m_ImplantSource->GetEntry();
	auto p2 = m_ImplantSource->GetTarget();
	double p1Array[3] = { p1[0], p1[1], p1[2] };
	double p2Array[3] = { p2[0], p2[1], p2[2] };

	auto radius = vtkWidgetRepresentation::SizeHandlesInPixels(2.35, p1Array);
	HandleGeometry[0]->SetRadius(radius);

	radius = vtkWidgetRepresentation::SizeHandlesInPixels(2.35, p2Array);
	HandleGeometry[1]->SetRadius(radius);
}

void misScrewRepresentation::HighlightPoint(int ptId, int highlight)
{
	if (ptId == 0)
	{
		if (highlight)
		{
			Handle[0]->SetProperty(SelectedEndPointProperty);
			Point1Representation->SetSelectedProperty(SelectedEndPointProperty);
		}
		else
		{
			Handle[0]->SetProperty(EndPointProperty);
			Point1Representation->SetProperty(EndPointProperty);
		}
	}
	else if (ptId == 1)
	{
		if (highlight)
		{
			Handle[1]->SetProperty(SelectedEndPoint2Property);
			Point2Representation->SetSelectedProperty(SelectedEndPoint2Property);
		}
		else
		{
			Handle[1]->SetProperty(EndPoint2Property);
			Point2Representation->SetProperty(EndPoint2Property);
		}
	}
	else //if ( ptId == 2 )
	{
		if (highlight)
			LineHandleRepresentation->SetSelectedProperty(SelectedEndPointProperty);
		else
			LineHandleRepresentation->SetProperty(EndPointProperty);
	}
}

void misScrewRepresentation::HighlightLine(bool highlight)
{
	if (highlight)
		LineActor->SetProperty(SelectedLineProperty);
	else
		LineActor->SetProperty(LineProperty);
}

void misScrewRepresentation::SetLineColor(double r, double g, double b)
{
	if (LineProperty)
		LineProperty->SetColor(r, g, b);
	auto plan2DMapper = dynamic_cast<misPlanMapper*>(m_ImplantSource->GetMapper().GetPointer());
	if (plan2DMapper)
		plan2DMapper->SetColor(tgt::vec3(r, g, b));

}


void misScrewRepresentation::GetActors(vtkPropCollection *pc)
{
	LineActor->GetActors(pc);
	Handle[0]->GetActors(pc);
	Handle[1]->GetActors(pc);
}

void misScrewRepresentation::ReleaseGraphicsResources(vtkWindow *w)
{
	LineActor->ReleaseGraphicsResources(w);
	Handle[0]->ReleaseGraphicsResources(w);
	Handle[1]->ReleaseGraphicsResources(w);
}

int misScrewRepresentation::RenderOpaqueGeometry(vtkViewport *v)
{
	int count = 0;
	BuildRepresentation();

	count += LineActor->RenderOpaqueGeometry(v);
	if (!m_Finalized)
	{
		count += Handle[0]->RenderOpaqueGeometry(v);
		count += Handle[1]->RenderOpaqueGeometry(v);
	}

	return count;
}

int misScrewRepresentation::RenderTranslucentPolygonalGeometry(vtkViewport *v)
{
	int count = 0;
	BuildRepresentation();
	count += LineActor->RenderTranslucentPolygonalGeometry(v);
	count += Handle[0]->RenderTranslucentPolygonalGeometry(v);
	count += Handle[1]->RenderTranslucentPolygonalGeometry(v);

	return count;
}

int misScrewRepresentation::HasTranslucentPolygonalGeometry()
{
	int result = 0;
	BuildRepresentation();
	result |= LineActor->HasTranslucentPolygonalGeometry();
	result |= Handle[0]->HasTranslucentPolygonalGeometry();
	result |= Handle[1]->HasTranslucentPolygonalGeometry();

	return result;
}

vtkMTimeType misScrewRepresentation::GetMTime()
{
	vtkMTimeType mTime = Superclass::GetMTime();
	vtkMTimeType mTime2 = Point1Representation->GetMTime();
	mTime = (mTime2 > mTime ? mTime2 : mTime);
	mTime2 = Point2Representation->GetMTime();
	mTime = (mTime2 > mTime ? mTime2 : mTime);
	mTime2 = LineHandleRepresentation->GetMTime();
	mTime = (mTime2 > mTime ? mTime2 : mTime);

	return mTime;
}


void misScrewRepresentation::SetScrewPlacementIsFinalized(bool finalized)
{
	m_Finalized = finalized;
}

bool misScrewRepresentation::GetScrewPlacementIsFinalized()
{
	return m_Finalized;
}
