#ifndef MISINTERACTORSTYLEIMAGEEXTEND
#define MISINTERACTORSTYLEIMAGEEXTEND

#include "misDataProdecureEnum.h"
#include "misImageGeoProperties.h"
#include "misSquareDataStructure.h"

class vtkRenderer;
class vtkActorCollection;
class vtkActor;
class vtkTransform;
class vtkInteractorStyleImage;
class vtkAbstractPropPicker;
class vtkAssemblyPath;
class vtkCallbackCommand;
class vtkMath;
class vtkObjectFactory;
class vtkRenderWindowInteractor;
class misVolumeSlicer;

enum INTERACTIONMODE
{
	MouseDownState  = 1050,    
	MouseUpState  ,     
	NoState	,		   
	SwitchRightToZoom  ,
	SwitchRightToPan ,  
	PanEvent_2d   ,
	ZoomEvent   ,
	NoEvent	 ,
	MouseDownevent	  ,
	ResetContrast  ,
	ZoomOutEvent  ,
	ZoomInEvent   ,
	ContrastEvent  ,
	MeasurmentWidget   ,
	AutoMeasurmentWidget 
};

enum INTERACTORMODE
{
	NormalMode,
	ContrastMode,
	MeasurmentMode,
	DrawingMode
};

enum  InteractionState
{
	ZoomState,
	ContrastState,
	WidgetInteractionState,
	MeasurmentInteractionState,
	AutoMeasurmentInteractionState,
	CorrelationWidgetOn
};

#define  misGoNextImageEvent  vtkCommand::UserEvent+33
#define  misSetMeasurmentWidgetEvent  vtkCommand::UserEvent+34
#define  misPanImageEvent vtkCommand::UserEvent+35

// The misInteractorSTyleImageExtend mange all mouse + keyboard interaction for misImage viewer
class  misInteractorSTyleImageExtend: public vtkInteractorStyleImage
{
public:
	enum KEYSTATE {Up, Down, None};

	static misInteractorSTyleImageExtend* New();
	void SetPrimitiveValue();
	void SetStateToWidget();
	void SetStateToAutoWidget();
	void SetSatateToRender();
	void SetStateToResetContrast();
	void SetStateToPan();
	vtkRenderWindowInteractor* GetRenderWindowInteractor();
	void OnChar();
	INTERACTIONMODE GetInteractionMode() const;
	void SetInteractionMode(INTERACTIONMODE val);
	 InteractionState GetInteractionState() const ;
	 void SetInteractionState(InteractionState val) ;

	int m_SwitchEvent;
	//int m_imageSize[2];
	int m_zoomPanEvent;
	double m_firstfocal[4],m_firstPosition[4],m_lastPosition[4],m_lastFocalPoint[4];
	int m_counter;
	vtkActorCollection * m_manActor;
	double m_lastViewPoint[4];

protected:

	void Render();
	void windowLevelMove(int x, int y);
	void  EventLUT();
	void viewToWorld(double x, double y, double z, double worldPt[4]);
	void displayToView(double x, double y, double z, double worldPt[4]);
	SquareDS SetViewSquareDS();
	SquareDS SetPlanSquareStr();
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnRightButtonDown();
	void UpdateState();
	virtual void OnLeftButtonUp();
	virtual void OnRightButtonUp();
	virtual void Pan();
	virtual void OnMouseWheelForward() ;
	virtual void OnMouseWheelBackward();
	virtual void Dolly(double factor);
	virtual void Dolly();
	void DisplayToView(double x, double y, double z, double worldPt[4]);
	void SetMeasurmentWidget();
	void SetAutoMeasurmentWidget();
	void GoNextImage(misCineDirection direction);

private:

	INTERACTIONMODE m_InteractionMode;
	misInteractorSTyleImageExtend();
	double  m_ParallelScaleDistance;
	double m_lastParallelScaleFactor;
	double m_CurrentParallelScaleFactor;
	double m_FirstParallelScaleFactor;
	IMAGEORIENTATION m_Orientation;
	InteractionState m_InteractionState;
};

#endif
