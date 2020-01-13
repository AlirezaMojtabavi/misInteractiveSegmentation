#pragma once
#include "IPlanNavigationVisualizer.h"
#include "BusinessEntities\Point.h"
#include "IAdaptiveZoomCalculator.h"
#include "IPositionInPlanCoordinateSystemCalculatorGetter.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "Color.h"
#include "vtkTextActor.h"



class vtkImageActor;

namespace parcast
{
	// The misPlanNavigationVisualizer class provides visual elements to guide the surgeon in positioning the tip of a surgical tool
	// in a previously planned position and align the tool axis in the direction of the same plan. These visual guide comprise of a
	// stationary cross-hair placed at the centre of a number of circles which denotes the axial view of the plan. The circles serve 
	// to demonstrate the radial distance of the tool tip (projected point of impact) from the axis of the plan. Apart from the 
	// stationary elements, there is a moving cross-hair that represents the tool tip and a moving circle the represents the tool
	// virtual handle. The circles around the plan axis distinguish four zones (black, grey, yellow, green) which signify how
	// accurately the tool is currently positioned and oriented with respect to the plan. For the navigation to fall within a certain
	// zone, the tool tip (cross-hair) and the virtual handle (circle centre) must fall within the circle pertaining to that zone and
	// the height of the tool tip (axial distance from the plan start) must also be within thresholds of the zone.
	// The virtual handle of the tool is the point along the tool axis whose distance from the tool tip is equal to plan length.
	// Thus, the position of the tool handle in the plan axial view is a measure of how far the impact point of the current tool
	// orientation might be if it is extended to a length equal to that of the plan.
	// When the tool position/orientation enters the green zone (signifying that the surgeon could safely proceed with drilling), the
	// plan depth indicator appears that informs at any time how much further the tool must be advance along its current orientation.
	class misPlanNavigationVisualizer :public IPlanNavigationVisualizer
	{
	public:
		misPlanNavigationVisualizer(
			std::shared_ptr<IAdaptiveZoomCalculator> adaptiveZoomCalculator,
			std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
			std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
			std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier,
			std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator) noexcept;

		void Render() override;
		void Initialize(vtkSmartPointer<vtkRenderer> renderer, bool paralleProjecton) override;
		void SetGrayZoneThreshold(double height, double radius) override;
		void SetPlan(std::weak_ptr<IPlan> plan) override;
		void SetFreezeState(bool state) override;
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> GetPositionInPlanCoordinate() override;
		IPilotIndicatorColorSpecifier::IndicatorColor GetIndicatorColor(std::string name) override;

	private:
		struct Threshold
		{
			double height;
			double radius;
		};

		const double ScaffoldingWidth = 3;
		const double TipCrosshairLength = 1;
		const double CameraParallelScale = 5.5;
		const double DepthIndicatorWidthDifference = 0.25;

		void CreateGrayZoneCircleActor();
		void CreateYellowZoneCircleActor();
		void CreateGreenZoneCircleActor();
		void CreateFixedCrosshairActor();
		void CreateFixedDepthActor();
		void CreateCaptionActors();
		void CreateDynamicCrosshairActors();
		void CreateCircleActor();
		void CreateDepthActor();
		void Create3DHeadActor();
		void AdjustCameraParallelProjection(bool paralleProjecton);
		void UpdateVisualScaleFactor();
		void UpdateVisualElements();
		void SetVisibility(bool visibilityStatus);
		void UpdateCamera();
		void UpdateCrosshairActor();
		void UpdateCircleActor();
		void Update3DHeadActor();
		void UpdateDepthActor();
		void UpdateTextActors();
		void UpdateActorColor(vtkSmartPointer<vtkActor> actor, IPilotIndicatorColorSpecifier::IndicatorColor color);
		void UpdateCaptionActorColor(vtkSmartPointer<vtkTextActor> actor, IPilotIndicatorColorSpecifier::IndicatorColor color);
		void SetText(vtkSmartPointer<vtkTextActor> actor, double variable);
		void SetText(vtkSmartPointer<vtkTextActor> actor, std::string variable);
		void CreateLineActor(vtkSmartPointer<vtkActor> actor, double length, double lineWidth);
		void CreateLineActor(vtkSmartPointer<vtkActor> actor, double length, double lineWidth, vtkSmartPointer<vtkTransform> transform);
		void MakeCircleActorGeometry(vtkSmartPointer<vtkActor> actor, double radius, double lineWidth);
		void CreateBaseObjects(bool paralleProjecton);
		double Distance2D(double x, double y) const;
		parcast::Color ConvertIndicatorColorEnum(IPilotIndicatorColorSpecifier::IndicatorColor color);
		vtkSmartPointer<vtkTextActor> CreateCaptionActor(int fontSize = 25);
		double* CalculateNewCaptionPosition(double x, double y);
		void SetCaptionPosition();

		std::shared_ptr<IAdaptiveZoomCalculator> m_AdaptiveZoomCalculator;
		std::shared_ptr<IPilotIndicatorColorSpecifier> m_CrossIndicatorColorSpecifier;
		std::shared_ptr<IPilotIndicatorColorSpecifier> m_CircleIndicatorColorSpecifier;
		std::shared_ptr<IPilotIndicatorColorSpecifier> m_DepthIndicatorColorSpecifier;
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> m_PositionInPlanCoordinateSystemCalculator;
		vtkSmartPointer<vtkTextActor> m_ToolHandleCaptionSymbol;
		vtkSmartPointer<vtkTextActor> m_DistanceCaptionSymbol;
		vtkSmartPointer<vtkTextActor> m_DepthCaption;
		vtkSmartPointer<vtkTextActor> m_DistanceCaption;
		vtkSmartPointer<vtkTextActor> m_ToolHandleCaption;
		vtkSmartPointer<vtkActorCollection> m_StaticActors;
		vtkSmartPointer<vtkRenderer> m_Renderer;

		vtkSmartPointer<vtkActor> m_VerticalMovingLineActor;
		vtkSmartPointer<vtkActor> m_HorizontalLineActor;
		vtkSmartPointer<vtkActor> m_HandleCircleActor;
		vtkSmartPointer<vtkActor> m_DepthPlaneActor;
		vtkSmartPointer<vtkActor> m_HumanHeadActor;

		Threshold m_GrayZoneThreshold;

		Point<double, 3> m_DepthPlanePoint1;
		Point<double, 3> m_DepthPlanePoint2;
		Point<double, 3> m_DepthPlaneOriginPoint;

		std::weak_ptr<IPlan> m_CurrentPlannedScrew;

		double m_VisualScaleFactor = 4.;
		bool m_IsInitialized = false;
		bool m_FreezeState = false;
	};
}
