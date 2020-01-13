#pragma once

#include "IPlanWidgetRepresentation.h"
#include "ICornerProperties.h"
#include "IImplantSource.h"
#include "VisualizationGeneralTypes.h"
#include "misScrewWidgetData.h"

class misScrewRepresentation : public IPlanWidgetRepresentation
{
public:
	typedef itk::Vector<double, 3> VectorType;
	misScrewRepresentation(
		std::shared_ptr<ICornerProperties> cornerProperties,
		std::shared_ptr<IImplantSource> implantSource);
	~misScrewRepresentation(void);

	void BuildRepresentation() override;
	int ComputeInteractionState(int X, int Y, int modify = 0) override;
	void StartWidgetInteraction(double e[2]) override;
	void WidgetInteraction(double e[2]) override;
	double *GetBounds() override;
	void GetActors(vtkPropCollection *pc) override;
	void ReleaseGraphicsResources(vtkWindow*) override;
	int RenderOpaqueGeometry(vtkViewport*) override;
	int RenderTranslucentPolygonalGeometry(vtkViewport*) override;
	int HasTranslucentPolygonalGeometry() override;
	// Description:
	// Overload the superclasses' GetMTime() because internal classes
	// are used to keep the state of the representation.
	vtkMTimeType GetMTime() override;
	// Description:
	// Overridden to set the rendererer on the internal representations.
	void SetRenderer(vtkRenderer *ren) override;

	bool IsPointerOnPlan(int X, int Y);
	void SetScrewDiameter(double diameter);
	void SetInteractionType(ScrewWidgetInteractionType type);
	void SetMaxAllowedLineLen(double len);
	ScrewWidgetInteractionType GetInteractionType();

	//vtkMatrix4x4*	GetTransformMatrix();
	void SetCorrectWorldPositions(double x1[3], double x2[3]);
	// Description:
	// Methods to Set/Get the coordinates of the two points defining
	// this representation. Note that methods are available for both
	// display and world coordinates.
	void GetPoint1WorldPosition(double pos[3]);
	double* GetPoint1WorldPosition();
	void GetPoint1DisplayPosition(double pos[3]);
	double* GetPoint1DisplayPosition();
	//void SetPoint1WorldPosition(double pos[3]);
	void SetPoint1DisplayPosition(double pos[3]);
	void GetPoint2DisplayPosition(double pos[3]);
	double* GetPoint2DisplayPosition();
	void GetPoint2WorldPosition(double pos[3]);
	double* GetPoint2WorldPosition();
	//void SetPoint2WorldPosition(double pos[3]);
	void SetPoint2DisplayPosition(double pos[3]);
	void SetPointsWorldPosition(double x1[3], double x2[3]);

	// Get the end-point (sphere) properties. The properties of the end-points 
	// when selected and unselected can be manipulated.
	vtkGetObjectMacro(EndPointProperty, vtkProperty);
	vtkGetObjectMacro(SelectedEndPointProperty, vtkProperty);
	// Description:
	// Get the end-point (sphere) properties. The properties of the end-points 
	// when selected and unselected can be manipulated.
	vtkGetObjectMacro(EndPoint2Property, vtkProperty);
	vtkGetObjectMacro(SelectedEndPoint2Property, vtkProperty);
	// Description:
	// Get the line properties. The properties of the line when selected
	// and unselected can be manipulated.
	vtkGetObjectMacro(LineProperty, vtkProperty);
	vtkGetObjectMacro(SelectedLineProperty, vtkProperty);
	// Description:
	// The tolerance representing the distance to the widget (in pixels) in
	// which the cursor is considered near enough to the line or end point 
	// to be active.
	vtkSetClampMacro(Tolerance, int, 1, 100);
	vtkGetMacro(Tolerance, int);
	// Description:
	// This method is used to specify the type of handle representation to
	// use for the three internal vtkHandleWidgets within vtkLineWidget2.
	// To use this method, create a dummy vtkHandleWidget (or subclass),
	// and then invoke this method with this dummy. Then the 
	// vtkLineRepresentation uses this dummy to clone three vtkHandleWidgets
	// of the same type. Make sure you set the handle representation before
	// the widget is enabled. (The method InstantiateHandleRepresentation()
	// is invoked by the vtkLineWidget2.)
	void InstantiateHandleRepresentation();
	
	//BTX - manage the state of the widget
	enum InteractionPos { Outside = 0, OnP1, OnP2, TranslatingP1, TranslatingP2, OnLine, Scaling };
	//ETX

	// Description:
	// The interaction state may be set from a widget (e.g., vtkLineWidget2) or
	// other object. This controls how the interaction with the widget
	// proceeds. Normally this method is used as part of a handshaking
	// process with the widget: First ComputeInteractionState() is invoked that
	// returns a state based on geometric considerations (i.e., cursor near a
	// widget feature), then based on events, the widget may modify this
	// further.
	vtkSetClampMacro(InteractionState, int, Outside, Scaling);

	// Description:
	// Sets the visual appearance of the representation based on the
	// state it is in. This state is usually the same as InteractionState.
	virtual void SetRepresentationState(int);
	vtkGetMacro(RepresentationState, int);


	// Description:
	// Convenience method to set the line color.
	// Ideally one should use GetLineProperty()->SetColor().
	void SetLineColor(double r, double g, double b);


	void	HighlightLine(bool highlight);
	void	SetScrewPlacementIsFinalized(bool finalized);
	bool	GetScrewPlacementIsFinalized();

protected:
	// The handle and the rep used to close the handles
	vtkPointHandleRepresentation3D *HandleRepresentation;

	vtkSmartPointer<vtkActor>  LineActor = vtkSmartPointer<vtkActor>::New();

	int RepresentationState = 0;


	// glyphs representing hot spots (e.g., handles)
	vtkActor          **Handle;
	vtkPolyDataMapper **HandleMapper;
	vtkSphereSource   **HandleGeometry;

	// Properties used to control the appearance of selected objects and
	// the manipulator in general.
	vtkProperty *EndPointProperty;
	vtkProperty *SelectedEndPointProperty;
	vtkProperty *EndPoint2Property;
	vtkProperty *SelectedEndPoint2Property;
	vtkProperty *LineProperty;
	vtkProperty *SelectedLineProperty;
	void         CreateDefaultProperties();

	// Selection tolerance for the handles and the line
	int Tolerance = 5;

	// Helper members
	int  ClampToBounds = 0;
	void HighlightPoint(int ptId, int highlight);
	void SizeHandles();
	// Ivars used during widget interaction to hold initial positions
	double StartP1[3] = { 0., 0., 0. };
	double StartP2[3] = { 0., 0., 0. };

	double StartLineHandle[3] = {0., 0., 0.};
	double Length = 0.;
	double LastEventPosition[3] = { 0., 0., 0. };

	// Support GetBounds() method
	vtkSmartPointer<vtkBox>  BoundingBox;

	// Need to keep track if we have successfully initialized the display position. 
	// The widget tends to do stuff in world coordinates, put if the renderer has
	// not been assigned, then certain operations do not properly update the display
	// position.
	int InitializedDisplayPosition = 0;

	IMAGEORIENTATION m_Orientation = AXIAL;
	std::shared_ptr<ICornerProperties> m_CornerProperties;

private:
	ScrewWidgetInteractionType	m_InteractionState = Free;
	vtkSmartPointer<vtkCaptionActor2D> m_LineLenCaption = vtkSmartPointer<vtkCaptionActor2D>::New();
	std::shared_ptr<IImplantSource>	m_ImplantSource;
	bool m_Finalized = false;
	double m_TubeRadius = 1.0;
	void CreateHandles();
	void CreatePlanBody(misScrewWidgetData widegtParam,
		std::shared_ptr<ICornerProperties> cornerProperties,
		std::string shaderFileName,
		std::shared_ptr<parcast::I3DPlanCrossSectionFunction> crossSectionFunction);
	void UpdateLengthCaption(double x1[3], double x2[3]) const;
};

