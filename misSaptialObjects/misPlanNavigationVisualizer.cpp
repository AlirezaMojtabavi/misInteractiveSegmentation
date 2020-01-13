#include "StdAfx.h"
#include "misPlanNavigationVisualizer.h"

#include "misFileReader.h"
#include "misMathUtils.h"
#include "ITransform.h"
#include "misApplicationSetting.h"

using namespace parcast;

misPlanNavigationVisualizer::misPlanNavigationVisualizer(
	std::shared_ptr<IAdaptiveZoomCalculator> adaptiveZoomCalculator,
	std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
	std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
	std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier,
	std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator) noexcept:
m_AdaptiveZoomCalculator(adaptiveZoomCalculator),
m_CrossIndicatorColorSpecifier(crossIndicatorColorSpecifier),
m_CircleIndicatorColorSpecifier(circleIndicatorColorSpecifier),
m_DepthIndicatorColorSpecifier(depthIndicatorColorSpecifier),
m_PositionInPlanCoordinateSystemCalculator(positionInPlanCoordinateSystemCalculator)
{
}

void misPlanNavigationVisualizer::UpdateVisualScaleFactor()
{
	if (const auto window = m_Renderer->GetRenderWindow())
		if (const auto windowSize = window->GetSize())
			m_VisualScaleFactor = std::min(windowSize[0] / 100, windowSize[1] / 80);
}

void misPlanNavigationVisualizer::Render()
{
	if (!m_IsInitialized)
	{
		return;
	}
	UpdateVisualElements();
	if (const auto window = m_Renderer->GetRenderWindow())
		window->Render();
}

void misPlanNavigationVisualizer::UpdateCamera()
{
	auto activeCamera = m_Renderer->GetActiveCamera();
	activeCamera->SetPosition(0, 0, -100);
	activeCamera->SetFocalPoint(0, 0, 100);
}

void misPlanNavigationVisualizer::UpdateCrosshairActor()
{
	if (!m_PositionInPlanCoordinateSystemCalculator->IsToolValid())
	{
		return;
	}

	auto verticalTransform = vtkSmartPointer<vtkTransform>::New();
	auto horizontalTransform = vtkSmartPointer<vtkTransform>::New();
	verticalTransform->PostMultiply();
	horizontalTransform->PostMultiply();
	verticalTransform->RotateZ(90);
	double tipPos[3];

	auto tooltipPosition = m_PositionInPlanCoordinateSystemCalculator->GetToolTip();
	tipPos[0] = m_VisualScaleFactor * tooltipPosition[0] / m_GrayZoneThreshold.radius;
	tipPos[1] = m_VisualScaleFactor * tooltipPosition[1] / m_GrayZoneThreshold.radius;
	tipPos[2] = tooltipPosition[2];
	verticalTransform->Translate(tipPos[0], tipPos[1], 0);
	horizontalTransform->Translate(tipPos[0], tipPos[1], 0);
	verticalTransform->Update();
	horizontalTransform->Update();

	m_VerticalMovingLineActor->SetUserTransform(verticalTransform);
	m_HorizontalLineActor->SetUserTransform(horizontalTransform);
}

void misPlanNavigationVisualizer::UpdateCircleActor()
{
	if (!m_PositionInPlanCoordinateSystemCalculator->IsToolValid())
	{
		return;
	}

	auto toolHandlePosition = m_PositionInPlanCoordinateSystemCalculator->GetPredictedTarget();
	double handlePos[2];
	handlePos[0] = -m_VisualScaleFactor * toolHandlePosition[0] / m_GrayZoneThreshold.radius;
	handlePos[1] = -m_VisualScaleFactor * toolHandlePosition[1] / m_GrayZoneThreshold.radius;
	auto handleTransform = vtkSmartPointer<vtkTransform>::New();
	handleTransform->Translate(handlePos[0], handlePos[1], 0);
	handleTransform->Update();
	m_HandleCircleActor->SetUserTransform(handleTransform);
}

void misPlanNavigationVisualizer::Update3DHeadActor()
{
	const auto image2PlanTrans = m_PositionInPlanCoordinateSystemCalculator->GetImageToPlanTransform();
	if (!image2PlanTrans)
	{
		return;
	}

	double transMat[16];
	image2PlanTrans->GetMarixElements(transMat);
	transMat[3] = 0;
	transMat[7] = 0;
	transMat[11] = +50;
	const auto vtkTrans = misMathUtils::CreateTransformFromMatrixElements(transMat);
	m_HumanHeadActor->SetUserTransform(vtkTrans);
}

void misPlanNavigationVisualizer::UpdateDepthActor()
{
	if (!m_PositionInPlanCoordinateSystemCalculator->IsToolValid())
	{
		return;
	}

	const auto currentZoneColor = m_DepthIndicatorColorSpecifier->GetColor();
	auto tooltipPosition = m_PositionInPlanCoordinateSystemCalculator->GetToolTip();

	if (currentZoneColor == IPilotIndicatorColorSpecifier::IndicatorColor::Green ||
		currentZoneColor == IPilotIndicatorColorSpecifier::IndicatorColor::Red)
	{
		auto depthActorTransform = vtkSmartPointer<vtkPlaneSource>::New();
		m_DepthPlaneActor->VisibilityOn();

		if (auto plan = m_CurrentPlannedScrew.lock())
		{
			const double planDepthIndicatorHeight = (m_DepthPlanePoint2[1] - m_DepthPlanePoint1[1]) * (1.0 - tooltipPosition[2] / plan->GetLength());
			depthActorTransform->SetPoint2(m_DepthPlanePoint2[0] + DepthIndicatorWidthDifference, m_DepthPlanePoint2[1], 0);
			depthActorTransform->SetOrigin(m_DepthPlaneOriginPoint[0] + DepthIndicatorWidthDifference, planDepthIndicatorHeight + m_DepthPlaneOriginPoint[1], 0);
			depthActorTransform->SetPoint1(m_DepthPlanePoint1[0] - DepthIndicatorWidthDifference, planDepthIndicatorHeight + m_DepthPlanePoint1[1], 0);

			if (planDepthIndicatorHeight + m_DepthPlanePoint1[1] <= m_DepthPlanePoint2[1] ||
				planDepthIndicatorHeight + m_DepthPlaneOriginPoint[1] <= m_DepthPlanePoint2[1])
			{
				auto planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
				planeMapper->SetInputConnection(depthActorTransform->GetOutputPort());
				m_DepthPlaneActor->SetMapper(planeMapper);
			}
		}
	}
	else
		m_DepthPlaneActor->VisibilityOff();
}

void misPlanNavigationVisualizer::UpdateTextActors()
{
	if (!m_PositionInPlanCoordinateSystemCalculator->IsToolValid())
	{
		return;
	}
	SetCaptionPosition();
	auto tooltipPosition = m_PositionInPlanCoordinateSystemCalculator->GetToolTip();
	if (auto plan = m_CurrentPlannedScrew.lock())
	{
		SetText(m_DepthCaption, plan->GetLength() - tooltipPosition[2]);
	}
	SetText(m_DistanceCaption, Distance2D(tooltipPosition[0], tooltipPosition[1]));
	auto toolHandlePosition = m_PositionInPlanCoordinateSystemCalculator->GetPredictedTarget();
	SetText(m_ToolHandleCaption, Distance2D(toolHandlePosition[0], toolHandlePosition[1]));
	SetText(m_DistanceCaptionSymbol, "+");
	SetText(m_ToolHandleCaptionSymbol, "o");
}

void misPlanNavigationVisualizer::UpdateActorColor(
	vtkSmartPointer<vtkActor> actor, IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	if (color == IPilotIndicatorColorSpecifier::IndicatorColor::Black)
	{
		actor->SetVisibility(false);
		return;
	}

	actor->SetVisibility(true);
	auto rgbColor = ConvertIndicatorColorEnum(color).GetNormRgb();
	actor->GetProperty()->SetColor(std::get<0>(rgbColor), std::get<1>(rgbColor), std::get<2>(rgbColor));
}

void misPlanNavigationVisualizer::UpdateCaptionActorColor(vtkSmartPointer<vtkTextActor> actor,
	IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	if (color == IPilotIndicatorColorSpecifier::IndicatorColor::Black)
	{
		actor->SetVisibility(false);
		return;
	}

	actor->SetVisibility(true);
	auto rgbColor = ConvertIndicatorColorEnum(color).GetNormRgb();
	actor->GetProperty()->SetColor(std::get<0>(rgbColor), std::get<1>(rgbColor), std::get<2>(rgbColor));
}

void misPlanNavigationVisualizer::UpdateVisualElements()
{
	if (!m_FreezeState)
	{
		UpdateVisualScaleFactor();
		auto activeCamera = m_Renderer->GetActiveCamera();
		activeCamera->SetParallelScale(CameraParallelScale);
		UpdateCamera();
		Update3DHeadActor();
		UpdateCrosshairActor();
		UpdateCircleActor();
		UpdateDepthActor();
		UpdateTextActors();

		UpdateActorColor(m_HandleCircleActor, m_CircleIndicatorColorSpecifier->GetColor());
		UpdateCaptionActorColor(m_ToolHandleCaption, m_CircleIndicatorColorSpecifier->GetColor());

		UpdateActorColor(m_VerticalMovingLineActor, m_CrossIndicatorColorSpecifier->GetColor());
		UpdateActorColor(m_HorizontalLineActor, m_CrossIndicatorColorSpecifier->GetColor());
		UpdateCaptionActorColor(m_DistanceCaption, m_CrossIndicatorColorSpecifier->GetColor());
		UpdateCaptionActorColor(m_DepthCaption, m_DepthIndicatorColorSpecifier->GetColor());
		UpdateCaptionActorColor(m_ToolHandleCaptionSymbol, m_CircleIndicatorColorSpecifier->GetColor());
		UpdateCaptionActorColor(m_DistanceCaptionSymbol, m_CrossIndicatorColorSpecifier->GetColor());
		UpdateActorColor(m_DepthPlaneActor, m_DepthIndicatorColorSpecifier->GetColor());
	}
}

void misPlanNavigationVisualizer::Initialize(vtkSmartPointer<vtkRenderer> renderer, bool paralleProjecton)
{
	if (m_Renderer)
	{
		m_Renderer->Clear();
		if (m_Renderer != renderer)
			m_Renderer->ReleaseGraphicsResources(renderer->GetVTKWindow());
		m_Renderer->RemoveAllViewProps();
	}
	m_VisualScaleFactor = 4.;
	m_Renderer = renderer;
	m_IsInitialized = true;
	CreateBaseObjects(paralleProjecton);
}

void misPlanNavigationVisualizer::CreateGrayZoneCircleActor()
{
	const auto grayZoneCircleActor = vtkSmartPointer<vtkActor>::New();
	MakeCircleActorGeometry(grayZoneCircleActor, m_VisualScaleFactor, ScaffoldingWidth);
	m_Renderer->AddActor(grayZoneCircleActor);
}

void misPlanNavigationVisualizer::CreateYellowZoneCircleActor()
{
	const auto yellowZoneCircleActor = vtkSmartPointer<vtkActor>::New();
	MakeCircleActorGeometry(yellowZoneCircleActor, 2, ScaffoldingWidth);
	m_Renderer->AddActor(yellowZoneCircleActor);
}

void misPlanNavigationVisualizer::CreateGreenZoneCircleActor()
{
	const auto greenZoneCircleActor = vtkSmartPointer<vtkActor>::New();
	MakeCircleActorGeometry(greenZoneCircleActor, 1, ScaffoldingWidth);
	m_Renderer->AddActor(greenZoneCircleActor);
}

void misPlanNavigationVisualizer::CreateFixedCrosshairActor()
{
	const auto horizontalLine = vtkSmartPointer<vtkActor>::New();
	CreateLineActor(horizontalLine, m_VisualScaleFactor, ScaffoldingWidth);
	m_Renderer->AddActor(horizontalLine);

	const auto verticalLine = vtkSmartPointer<vtkActor>::New();
	auto lineTransform = vtkSmartPointer<vtkTransform>::New();
	lineTransform->RotateZ(90);
	lineTransform->Update();
	CreateLineActor(verticalLine, m_VisualScaleFactor, ScaffoldingWidth, lineTransform);
	m_Renderer->AddActor(verticalLine);
}

void misPlanNavigationVisualizer::CreateFixedDepthActor()
{
	auto solidDepth = vtkSmartPointer<vtkPlaneSource>::New();
	m_DepthPlanePoint1[0] = 1.5 * m_VisualScaleFactor;
	m_DepthPlanePoint1[1] = -m_VisualScaleFactor;
	solidDepth->SetPoint1(m_DepthPlanePoint1[0], m_DepthPlanePoint1[1], +10);
	m_DepthPlanePoint2[0] = 1.1 * m_VisualScaleFactor;
	m_DepthPlanePoint2[1] = m_VisualScaleFactor;
	solidDepth->SetPoint2(m_DepthPlanePoint2[0], m_DepthPlanePoint2[1], +10);
	m_DepthPlaneOriginPoint[0] = 1.1 * m_VisualScaleFactor;
	m_DepthPlaneOriginPoint[1] = -m_VisualScaleFactor;
	solidDepth->SetOrigin(m_DepthPlaneOriginPoint[0], m_DepthPlaneOriginPoint[1], +10);
	auto planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	planeMapper->SetInputConnection(solidDepth->GetOutputPort());
	auto planeActor = vtkSmartPointer<vtkActor>::New();
	planeActor->SetMapper(planeMapper);
	m_Renderer->AddActor(planeActor);
}

void misPlanNavigationVisualizer::CreateCaptionActors()
{
	m_Renderer->RemoveActor2D(m_DepthCaption);
	m_DepthCaption = CreateCaptionActor();
	
	m_Renderer->RemoveActor2D(m_DistanceCaption);
	m_DistanceCaption = CreateCaptionActor();
	

	m_Renderer->RemoveActor2D(m_DistanceCaptionSymbol);
	m_DistanceCaptionSymbol = CreateCaptionActor(50);


	m_Renderer->RemoveActor2D(m_ToolHandleCaption);
	m_ToolHandleCaption = CreateCaptionActor();
	

	m_Renderer->RemoveActor2D(m_ToolHandleCaptionSymbol);
	m_ToolHandleCaptionSymbol = CreateCaptionActor(50);
	
}

void misPlanNavigationVisualizer::CreateDynamicCrosshairActors()
{
	m_Renderer->RemoveActor(m_VerticalMovingLineActor);
	m_VerticalMovingLineActor = vtkSmartPointer<vtkActor>::New();
	CreateLineActor(m_VerticalMovingLineActor, 2.5*TipCrosshairLength, ScaffoldingWidth);
	m_VerticalMovingLineActor->GetProperty()->SetLineWidth(5);
	m_Renderer->AddActor(m_VerticalMovingLineActor);

	m_Renderer->RemoveActor(m_HorizontalLineActor);
	m_HorizontalLineActor = vtkSmartPointer<vtkActor>::New();
	CreateLineActor(m_HorizontalLineActor, 2.5*TipCrosshairLength, ScaffoldingWidth);
	m_HorizontalLineActor->GetProperty()->SetLineWidth(5);
	m_Renderer->AddActor(m_HorizontalLineActor);
}

void misPlanNavigationVisualizer::CreateCircleActor()
{
	m_Renderer->RemoveActor(m_HandleCircleActor);
	m_HandleCircleActor = vtkSmartPointer<vtkActor>::New();
	MakeCircleActorGeometry(m_HandleCircleActor, 1, ScaffoldingWidth);
	m_HandleCircleActor->GetProperty()->SetLineWidth(5);
	m_Renderer->AddActor(m_HandleCircleActor);
}

void misPlanNavigationVisualizer::CreateDepthActor()
{
	m_Renderer->RemoveActor(m_DepthPlaneActor);
	m_DepthPlaneActor = vtkSmartPointer<vtkActor>::New();
	m_Renderer->AddActor(m_DepthPlaneActor);
}

void misPlanNavigationVisualizer::Create3DHeadActor()
{
	auto fileStlPath = "";
	if (misApplicationSetting::GetInstance()->m_WorkflowButtonSet == Spine)
		fileStlPath = "Resources\\3d Model\\Man\\Body.stl";
	else
		fileStlPath= "Resources\\3d Model\\HumanHead\\Head.stl";
	const auto headPolyData = misFileReader::ReadPolydataFromSTLFile(fileStlPath);
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(headPolyData);
	m_Renderer->RemoveActor(m_HumanHeadActor);
	m_HumanHeadActor = vtkSmartPointer<vtkActor>::New();
	m_HumanHeadActor->GetProperty()->SetColor(0.7692, 0.6756, 0.57);
	m_HumanHeadActor->SetMapper(mapper);
	m_Renderer->AddActor(m_HumanHeadActor);
}

void misPlanNavigationVisualizer::AdjustCameraParallelProjection(bool paralleProjecton)
{
	auto activeCamera = m_Renderer->GetActiveCamera();
	if (paralleProjecton)
	{
		activeCamera->ParallelProjectionOn();
		m_Renderer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(nullptr);
	}
	else
	{
		activeCamera->ParallelProjectionOff();
	}
	activeCamera->SetParallelScale(CameraParallelScale);
}

void misPlanNavigationVisualizer::CreateBaseObjects(bool paralleProjecton)
{
	Create3DHeadActor();
	CreateGrayZoneCircleActor();
	CreateYellowZoneCircleActor();
	CreateGreenZoneCircleActor();
	CreateFixedCrosshairActor();
	CreateFixedDepthActor();
	CreateCaptionActors();
	CreateDynamicCrosshairActors();
	CreateCircleActor();
	CreateDepthActor();
	AdjustCameraParallelProjection(paralleProjecton);
}

void misPlanNavigationVisualizer::SetGrayZoneThreshold(double height, double radius)
{
	m_GrayZoneThreshold.height = height;
	m_GrayZoneThreshold.radius = radius;
}

void misPlanNavigationVisualizer::SetPlan(std::weak_ptr<IPlan> plan)
{
	m_CurrentPlannedScrew = plan;
}

void misPlanNavigationVisualizer::SetFreezeState(bool state)
{
	m_FreezeState = state;
}

std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> misPlanNavigationVisualizer::
GetPositionInPlanCoordinate()
{
	return m_PositionInPlanCoordinateSystemCalculator;
}

IPilotIndicatorColorSpecifier::IndicatorColor misPlanNavigationVisualizer::GetIndicatorColor(std::string name)
{
	if (name == "DepthIndicatorColorSpecifier")
	{
		return m_DepthIndicatorColorSpecifier->GetColor();
	}
	else if(name == "CircleIndicatorColorSpecifier")
	{
		return m_CircleIndicatorColorSpecifier->GetColor();
	}
}

double misPlanNavigationVisualizer::Distance2D(double x, double y) const
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

parcast::Color misPlanNavigationVisualizer::ConvertIndicatorColorEnum(IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	switch (color)
	{
	case IPilotIndicatorColorSpecifier::IndicatorColor::Gray:
	{
		return parcast::Color::FromRgb(127, 127, 127);
	}
	case IPilotIndicatorColorSpecifier::IndicatorColor::Green:
	{
		return parcast::Color::FromRgb(0, 255, 0);
	}
	case IPilotIndicatorColorSpecifier::IndicatorColor::Red:
	{
		return parcast::Color::FromRgb(255, 0, 0);
	}
	case IPilotIndicatorColorSpecifier::IndicatorColor::Yellow:
	{
		return parcast::Color::FromRgb(255, 255, 0);
	}
	case IPilotIndicatorColorSpecifier::IndicatorColor::Black:
	{
		return parcast::Color::FromRgb(0, 0, 0);
	}

	}
}

void  misPlanNavigationVisualizer::CreateLineActor(vtkSmartPointer<vtkActor> actor, double length, double lineWidth)
{
	auto lineSource = vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(-length, 0, 0);
	lineSource->SetPoint2(length, 0, 0);
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(lineSource->GetOutputPort());
	actor->SetMapper(mapper);
}

void misPlanNavigationVisualizer::CreateLineActor(vtkSmartPointer<vtkActor> actor, double length, double lineWidth,
	vtkSmartPointer<vtkTransform> transform)
{
	auto lineSource = vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(-length, 0, 0);
	lineSource->SetPoint2(length, 0, 0);
	auto polydataTransform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	polydataTransform->SetInputConnection(lineSource->GetOutputPort());
	polydataTransform->SetTransform(transform);
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(polydataTransform->GetOutputPort());
	actor->SetMapper(mapper);
}

void misPlanNavigationVisualizer::MakeCircleActorGeometry(vtkSmartPointer<vtkActor> actor, double radius, double lineWidth)
{
	auto polygonSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
	polygonSource->GeneratePolygonOff();
	polygonSource->SetNumberOfSides(100);
	polygonSource->SetRadius(radius);
	polygonSource->SetCenter(0, 0, 0);
	auto circleMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	circleMapper->SetInputConnection(polygonSource->GetOutputPort());
	actor->SetMapper(circleMapper);
	actor->GetProperty()->SetLineWidth(lineWidth);
}

vtkSmartPointer<vtkTextActor> misPlanNavigationVisualizer::CreateCaptionActor(int fontSize)
{
	auto caption = vtkSmartPointer<vtkTextActor>::New();
	caption->SetTextScaleModeToNone();
	caption->SetNonLinearFontScale(fontSize, fontSize);
	m_Renderer->AddActor2D(caption);
	return caption;
}

double* misPlanNavigationVisualizer::CalculateNewCaptionPosition(double x, double y)
{
	
	m_Renderer->SetViewPoint(x, y, 0);
	m_Renderer->ViewToDisplay();
	double display[3];
	m_Renderer->GetDisplayPoint(display);
	
	return  display;
}

void misPlanNavigationVisualizer::SetCaptionPosition()
{
	auto position = CalculateNewCaptionPosition(-0.8, 0.8);
	m_DepthCaption->SetDisplayPosition(position[0], position[1]);
	position = CalculateNewCaptionPosition(0.7, 0.8);
	m_DistanceCaption->SetDisplayPosition(position[0], position[1]);
	position = CalculateNewCaptionPosition(0.6, 0.77);
	m_DistanceCaptionSymbol->SetDisplayPosition(position[0], position[1]);
	position = CalculateNewCaptionPosition(0.7, 0.65);
	m_ToolHandleCaption->SetDisplayPosition(position[0], position[1]);
	position = CalculateNewCaptionPosition(0.6, 0.62);
	m_ToolHandleCaptionSymbol->SetDisplayPosition(position[0], position[1]);
}

void misPlanNavigationVisualizer::SetText(vtkSmartPointer<vtkTextActor> actor, double variable)
{
	std::ostringstream depthFormatterStream;
	depthFormatterStream << std::fixed << std::setprecision(1) << variable << " mm";
	std::string captionString = depthFormatterStream.str();
	actor->SetInput(captionString.c_str());
}

void misPlanNavigationVisualizer::SetText(vtkSmartPointer<vtkTextActor> actor, std::string variable)
{
	std::ostringstream depthFormatterStream;
	depthFormatterStream << variable;
	std::string captionString = depthFormatterStream.str();
	actor->SetInput(captionString.c_str());
}

void misPlanNavigationVisualizer::SetVisibility(bool visibilityStatus)
{
	const int visInt = visibilityStatus ? 1 : 0;
	m_HandleCircleActor->SetVisibility(visInt);
	m_VerticalMovingLineActor->SetVisibility(visInt);
	m_HorizontalLineActor->SetVisibility(visInt);
	m_DistanceCaption->SetVisibility(visInt);
	m_DepthCaption->SetVisibility(visInt);
	m_DepthPlaneActor->SetVisibility(visInt);
	m_ToolHandleCaption->SetVisibility(visInt);
	m_ToolHandleCaptionSymbol->SetVisibility(true);
	m_DistanceCaptionSymbol->SetVisibility(true);
}