#include "stdafx.h"
#include "misBiopsyPlanRepresentation.h"
#include "mis3DImplant.h"
#include "misScrewSource.h"
#include "misMathUtils.h"
#include "CylinderUtility.h"
#include "misPlanMapper.h"
#include  "misMathUtils.h"
#include "misScrewRepresentation.h"

using namespace std;

misBiopsyPlanRepresentation::misBiopsyPlanRepresentation(
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
	// Set up the initial properties
	CreateDefaultProperties();
	// This needs to be initialized before PlaceWidget is called.
	BoundingBox = vtkSmartPointer<vtkBox>::New();

	m_LineLenCaption->VisibilityOff();
	m_LineLenCaption->BorderOff();
	m_LineLenCaption->LeaderOff();
	LineActor->SetMapper(m_ImplantSource->GetMapper());

}

misBiopsyPlanRepresentation::~misBiopsyPlanRepresentation()
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


	EndPointProperty->Delete();
	SelectedEndPointProperty->Delete();
	EndPoint2Property->Delete();
	SelectedEndPoint2Property->Delete();
	LineProperty->Delete();
	SelectedLineProperty->Delete();

}

 
void misBiopsyPlanRepresentation::SetScrewDiameter(double diameter)
{
	m_ImplantSource->SetRadius(diameter / 2.);
}



void misBiopsyPlanRepresentation::UpdateLengthCaption(double x1[3], double x2[3]) const
{
	const auto dLineLen = (parcast::PointD3(x1) - parcast::PointD3(x2)).Length();
	std::ostringstream formatter;
	formatter << std::fixed << std::setprecision(1) << dLineLen;
	m_LineLenCaption->SetCaption(formatter.str().c_str());
	m_LineLenCaption->SetAttachmentPoint((x2[0] + x1[0]) / 2., (x2[1] + x1[1]) / 2., (x2[2] + x1[2]) / 2.);
	m_LineLenCaption->SetPosition(0.05, 0.05);
	m_LineLenCaption->GetCaptionTextProperty()->SetFontSize(42);
}

void misBiopsyPlanRepresentation::BuildRepresentation()
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
	BuildTime.Modified();
}


void misBiopsyPlanRepresentation::SetCorrectWorldPositions(double x1[3], double x2[3])
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

	Point1Representation->SetWorldPosition(x1);
	Point2Representation->SetWorldPosition(x2);
}

void misBiopsyPlanRepresentation::SetInteractionType(ScrewWidgetInteractionType type)
{
	m_InteractionState = type;
}

void misBiopsyPlanRepresentation::SetMaxAllowedLineLen(double len)
{
}

ScrewWidgetInteractionType misBiopsyPlanRepresentation::GetInteractionType()
{
	return m_InteractionState;
}

void misBiopsyPlanRepresentation::InstantiateHandleRepresentation()
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


void misBiopsyPlanRepresentation::GetPoint1WorldPosition(double pos[3])
{
	Point1Representation->GetWorldPosition(pos);
}

double* misBiopsyPlanRepresentation::GetPoint1WorldPosition()
{
	return Point1Representation->GetWorldPosition();
}

void misBiopsyPlanRepresentation::GetPoint1DisplayPosition(double pos[3])
{
	Point1Representation->GetDisplayPosition(pos);
}

double* misBiopsyPlanRepresentation::GetPoint1DisplayPosition()
{
	return Point1Representation->GetDisplayPosition();
}

void misBiopsyPlanRepresentation::SetPointsWorldPosition(double x1[3], double x2[3])
{
	Point1Representation->SetWorldPosition(x1);
	Point2Representation->SetWorldPosition(x2);
	m_ImplantSource->SetEntry(parcast::PointD3(x1));
	m_ImplantSource->SetTarget(parcast::PointD3(x2));

}

void misBiopsyPlanRepresentation::SetPoint1DisplayPosition(double x[3])
{
	Point1Representation->SetDisplayPosition(x);
	double p[3];
	Point1Representation->GetWorldPosition(p);
	Point1Representation->SetWorldPosition(p);
}

void misBiopsyPlanRepresentation::GetPoint2WorldPosition(double pos[3])
{
	Point2Representation->GetWorldPosition(pos);
}

double* misBiopsyPlanRepresentation::GetPoint2WorldPosition()
{
	return Point2Representation->GetWorldPosition();
}

void misBiopsyPlanRepresentation::GetPoint2DisplayPosition(double pos[3])
{
	Point2Representation->GetDisplayPosition(pos);
}

double* misBiopsyPlanRepresentation::GetPoint2DisplayPosition()
{
	return Point2Representation->GetDisplayPosition();
}

void misBiopsyPlanRepresentation::SetPoint2DisplayPosition(double x[3])
{
	Point2Representation->SetDisplayPosition(x);
	double p[3];
	Point2Representation->GetWorldPosition(p);
	Point2Representation->SetWorldPosition(p);
}

void misBiopsyPlanRepresentation::SetRenderer(vtkRenderer* ren)
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

void misBiopsyPlanRepresentation::StartWidgetInteraction(double e[2])
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

void misBiopsyPlanRepresentation::WidgetInteraction(double e[2])
{
	if (m_Finalized)
	{
		return;
	}
	// Process the motion
	switch (InteractionState)
	{
	case misBiopsyPlanRepresentation::OnLine:
	{
		double x[3] = { 0., 0., 0. }, p1[3] = { 0., 0., 0. }, p2[3] = { 0., 0., 0. }, delta[3] = { 0., 0., 0. };
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
	case misBiopsyPlanRepresentation::Scaling:
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
	case misBiopsyPlanRepresentation::TranslatingP1:
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
	case misBiopsyPlanRepresentation::TranslatingP2:
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

bool misBiopsyPlanRepresentation::IsPointerOnPlan(int X, int Y)
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

int misBiopsyPlanRepresentation::ComputeInteractionState(int X, int Y, int vtkNotUsed(modify))
{

	if (m_Finalized)
		return misBiopsyPlanRepresentation::Outside;

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

	double tol2 = Tolerance * Tolerance;
	// Check if we are on end points
	if (vtkMath::Distance2BetweenPoints(xyz, p1) <= tol2)
	{
		InteractionState = misBiopsyPlanRepresentation::OnP1;
		SetRepresentationState(misBiopsyPlanRepresentation::OnP1);
		return InteractionState;
	}

	if (vtkMath::Distance2BetweenPoints(xyz, p2) <= tol2)
	{
		InteractionState = misBiopsyPlanRepresentation::OnP2;
		SetRepresentationState(misBiopsyPlanRepresentation::OnP2);
		return InteractionState;
	}


	if (IsPointerOnPlan(X, Y))
	{
		InteractionState = misBiopsyPlanRepresentation::OnLine;
		SetRepresentationState(misBiopsyPlanRepresentation::OnLine);
	 
	}
	else
	{
		InteractionState = misBiopsyPlanRepresentation::Outside;
		SetRepresentationState(misBiopsyPlanRepresentation::Outside);
	}

	return InteractionState;
}

void misBiopsyPlanRepresentation::SetRepresentationState(int state)
{
	if (RepresentationState == state)
		return;

	state = (state < misBiopsyPlanRepresentation::Outside ?
		misBiopsyPlanRepresentation::Outside :
		(state > misBiopsyPlanRepresentation::Scaling ?
			misBiopsyPlanRepresentation::Scaling : state));

	RepresentationState = state;
	Modified();
	m_LineLenCaption->VisibilityOn();
	if (state == misBiopsyPlanRepresentation::Outside)
	{

		HighlightLine(0);
		m_LineLenCaption->VisibilityOff();
	}
	else if (state == misBiopsyPlanRepresentation::OnP1)
	{

		HighlightLine(0);
	}
	else if (state == misBiopsyPlanRepresentation::OnP2)
	{

		HighlightLine(0);
	}
	else if (state == misBiopsyPlanRepresentation::OnLine)
	{

		HighlightLine(1);
	}
	else
	{

		HighlightLine(1);
	}
}

double *misBiopsyPlanRepresentation::GetBounds()
{
	BuildRepresentation();
	BoundingBox->SetBounds(LineActor->GetBounds());

	return BoundingBox->GetBounds();
}

void misBiopsyPlanRepresentation::CreateDefaultProperties()
{
	// Endpoint properties
	EndPointProperty = vtkProperty::New();
	EndPointProperty->SetColor(1.0, 0.0, 0.0);

	//IMPORTANTNOTICE: Point1Representation is the president of the cross at the end of line.
	Point1Representation->SetProperty(EndPointProperty);
	LineHandleRepresentation->SetProperty(EndPointProperty);

	SelectedEndPointProperty = vtkProperty::New();
	SelectedEndPointProperty->SetColor(0, 1, 0);

	EndPoint2Property = vtkProperty::New();
	EndPoint2Property->SetColor(0.0, 1.0, 0.0);

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

void misBiopsyPlanRepresentation::HighlightLine(bool highlight)
{
	if (highlight)
		LineActor->SetProperty(SelectedLineProperty);
	else
		LineActor->SetProperty(LineProperty);
}

void misBiopsyPlanRepresentation::SetLineColor(double r, double g, double b)
{
	if (LineProperty)
		LineProperty->SetColor(r, g, b);
	auto plan2DMapper = dynamic_cast<misPlanMapper*>(m_ImplantSource->GetMapper().GetPointer());
	if (plan2DMapper)
		plan2DMapper->SetColor(tgt::vec3(r, g, b));

}


void misBiopsyPlanRepresentation::GetActors(vtkPropCollection *pc)
{
	LineActor->GetActors(pc);
}

void misBiopsyPlanRepresentation::ReleaseGraphicsResources(vtkWindow *w)
{
	LineActor->ReleaseGraphicsResources(w);
}

int misBiopsyPlanRepresentation::RenderOpaqueGeometry(vtkViewport *v)
{
	int count = 0;
	BuildRepresentation();

	count += LineActor->RenderOpaqueGeometry(v);

	return count;
}

int misBiopsyPlanRepresentation::RenderTranslucentPolygonalGeometry(vtkViewport *v)
{
	int count = 0;
	BuildRepresentation();
	count += LineActor->RenderTranslucentPolygonalGeometry(v);

	return count;
}

int misBiopsyPlanRepresentation::HasTranslucentPolygonalGeometry()
{
	int result = 0;
	BuildRepresentation();
	result |= LineActor->HasTranslucentPolygonalGeometry();

	return result;
}

vtkMTimeType misBiopsyPlanRepresentation::GetMTime()
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


void misBiopsyPlanRepresentation::SetScrewPlacementIsFinalized(bool finalized)
{
	m_Finalized = finalized;
}

bool misBiopsyPlanRepresentation::GetScrewPlacementIsFinalized()
{
	return m_Finalized;
}
