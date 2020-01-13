#pragma once

#include "AxesColors.h"
#include "misEnums.h"
#include "VisualizationGeneralTypes.h"

class ICornerProperties;
class misCursor;

enum AxisType
{
	XAxis = 0,
	YAxis,
	ZAxis
};

enum misWidgetState
{
	Start=0,
	Moving,
	Scaling,
	Translating,
	Outside
};

// The misColorPointWidget represents a set of three mutually perpendicular lines placed in the scene at the specified position
// and with the specified orientation.
class misColorPointWidget : public vtk3DWidget
{
	friend class vtkLineWidget;
public:
	static misColorPointWidget *New();
//	vtkTypeRevisionMacro(misColorPointWidget,vtk3DWidget);
	virtual void SetEnabled(int);
	virtual void PlaceWidget(double bounds[6]);
	void PlaceWidget(){/*this->Superclass::PlaceWidget();*/}
	void PlaceWidget(double xmin, double xmax, double ymin, double ymax,double zmin, double zmax);
	void GetPolyData(vtkPolyData *pd);

	// Sets the relative weight of the line used in drawing the widget.
	void SetLineWidth(double width);

	// Description:
	// Set/Get the position of the point. Note that if the position is set
	// outside of the bounding box, it will be clamped to the boundary of
	// the bounding box.
	void SetPosition(double x, double y, double z);	
	void SetPosition(double x[3]);
	double* GetPosition();
	void GetPosition(double xyz[3]);
	IMAGEORIENTATION GetWidgetOrientation();
	void SetWidgetOrientation(IMAGEORIENTATION  orientation);
	bool GetTorusVisibility();
	void SetTorusVisibility(bool b);
	double GetDParam();
	void SetDParam(double d);
	void SetCursorType(misCursorType cursorType);
	void Init();
	void SetCurrentCursorType(misCursorType cursorName);
	void ResetCrossSetting();
	void InitialCrossSetting();
	void ModifyAxis() ;
	void SetCurrentActiveLandmark(int index);
	int GetCurrentActiveLandmark();
	void SetInteractionCapturedFlag(bool val);
	std::vector < vtkSmartPointer<vtkActor>> GetActors();
	void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProperties);
	void UpdateWidgetPosition();
	void SetAxesColors(parcast::AxesColors const& colors);
	void SetPickingTolerance(double pickingTolerance);
	vtkSetClampMacro(HotSpotSize,double,0.0,1.0);
	vtkGetMacro(HotSpotSize,double);

protected:
	misColorPointWidget( );
	~misColorPointWidget() = default;
	// ProcessEvents() dispatches to these methods.
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	virtual void OnMiddleButtonDown();
	virtual void OnMiddleButtonUp();
	virtual void OnRightButtonDown();
	virtual void OnRightButtonUp();
	void AddActors();
	void RemoveActors();
	// Handles the events
	static void ProcessEvents(vtkObject* object, 
	unsigned long event,
	void* clientdata, 
	void* calldata);
	int DetermineConstraintAxis(int constraint, double *x);
	void Highlight(int highlight);

	vtkSmartPointer<vtkProp> currentActor;
	int    m_Mode; //if m_Mode ==0 -> line is selected else focal point is selected
	IMAGEORIENTATION     m_WidgetOrientation;
	misWidgetState m_WidgetState;
	misCursorType  m_CursorType;
	AxisType    m_CurrentAxis;
	bool		m_InteractionCaptured;
	// Do the picking
	vtkSmartPointer<vtkCellPicker> m_XAxisPicker;
	vtkSmartPointer<vtkCellPicker> m_YAxisPicker;
	vtkSmartPointer<vtkCellPicker> m_ZAxisPicker;
	vtkSmartPointer<vtkCellPicker> m_CurrentPicker;

	// Methods to manipulate the cursor
	int ConstraintAxis;
	//void Translate(double *p1, double *p2);
	//  void Scale(double *p1, double *p2, int X, int Y);
	void MoveFocus(double *p1, double *p2);
	int TranslationMode;

	// The size of the hot spot.
	double HotSpotSize;
	int WaitingForMotion;
	int WaitCount;

	bool m_TorusVisibility;
	double DParam;
	vtkSmartPointer<misCursor> m_Cursor3D ;

private:
	misColorPointWidget(const misColorPointWidget&);  //Not implemented
	void operator=(const misColorPointWidget&);  //Not implemented
	int m_ActiveLandmark;
	parcast::AxesColors m_AxesColors;
	double m_LineWidth;	// See SetLineWidth()
	double m_PickingTolerance = 0.005;
};

