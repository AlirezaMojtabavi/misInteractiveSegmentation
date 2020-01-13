#include "stdafx.h"
#include "misInteractorSTyleImageExtend.h"

#include "misAutoMeasurment.h"
#include "misCoreEvents.h"


misInteractorSTyleImageExtend::misInteractorSTyleImageExtend()
	:m_InteractionMode(NoEvent) , m_InteractionState(WidgetInteractionState)
{ 
	 SetPrimitiveValue();
	 m_manActor=0;
}

misInteractorSTyleImageExtend* misInteractorSTyleImageExtend::New()
{
	return new misInteractorSTyleImageExtend;
}

void misInteractorSTyleImageExtend::SetPrimitiveValue()
{
	m_counter=0;
	for (int i=0;i<4;i++)
	{
		m_lastPosition[i]=0;
		m_lastFocalPoint[i]=0;
	}
	m_lastParallelScaleFactor=0;
	viewToWorld(-1,-1,1,m_lastViewPoint);
	m_manActor=NULL;
	State=VTKIS_NONE;
	
}

void misInteractorSTyleImageExtend::windowLevelMove(int x, int y)
{
	FindPokedRenderer(x, y);
	if (CurrentRenderer == NULL)
	{
		return;
	}
	WindowLevel();
	InvokeEvent(vtkCommand::InteractionEvent, NULL);
	
	if ( Interactor )
	{
		ReleaseFocus();
	}
	State=MouseDownState;
}

void misInteractorSTyleImageExtend::OnRightButtonDown() 
{
		State = None;
}
void misInteractorSTyleImageExtend::OnMouseMove()
{
	int x = Interactor->GetEventPosition()[0];
	int y = Interactor->GetEventPosition()[1];
	std::cout << "misInteractorSTyleImageExtend::OnMouseMove" << std::endl;
	switch (State) 
	{
	case MouseDownState:
		if (m_InteractionMode == ContrastEvent)
		{
			WindowLevelStartPosition[0] = x;
			WindowLevelStartPosition[1] = y;
			StartWindowLevel();
			State = VTKIS_WINDOW_LEVEL;

		}
		break;

	case VTKIS_WINDOW_LEVEL:
		windowLevelMove(x,y);
		break;

	case VTKIS_PICK:
		FindPokedRenderer(x, y);
		Pick();
		InvokeEvent(vtkCommand::InteractionEvent, NULL);
		break;

	case VTKIS_PAN:
		FindPokedRenderer(x,y);
		InvokeEvent(misPanImageEvent,NULL);
		InvokeEvent(vtkCommand::InteractionEvent, NULL);
		break;

	case VTKIS_DOLLY:
		FindPokedRenderer(x,y);
		Dolly();
		InvokeEvent(vtkCommand::InteractionEvent, NULL);
		break;
	}
}
	
void  misInteractorSTyleImageExtend::EventLUT()
{
	State=VTKIS_NONE;
}
	
void misInteractorSTyleImageExtend::OnLeftButtonDown()
{
	int x = Interactor->GetEventPosition()[0];
	int y = Interactor->GetEventPosition()[1];

	FindPokedRenderer(x,y);
	if (CurrentRenderer == NULL)
	{
		return;
	}
	
	EventLUT();
	UpdateState();
	State = MouseDownState;
}

 void misInteractorSTyleImageExtend::OnLeftButtonUp()
{
	switch (State) 
	{
	case VTKIS_WINDOW_LEVEL:
		EndWindowLevel();
		break;
	case VTKIS_DOLLY:
		EndDolly();
		break;

	case VTKIS_PAN:
		EndPan();
		State =NoState;
		break;

	case VTKIS_SPIN:
		EndSpin();
		break;
	}
	if (Interactor)
	{
		ReleaseFocus();
	}
	State = MouseUpState;
}


void misInteractorSTyleImageExtend::OnRightButtonUp() 
{
	switch (State) 
	{
	case VTKIS_WINDOW_LEVEL:
		EndWindowLevel();
		break;
	case VTKIS_DOLLY:
		EndDolly();
		break;

	case VTKIS_PAN:
		EndPan();
		State =NoState;
		break;

	case VTKIS_SPIN:
		EndSpin();
		break;
	}

	if (Interactor)
	{
		ReleaseFocus();
	}
}

 void misInteractorSTyleImageExtend::Dolly()
{
	
}

 void misInteractorSTyleImageExtend::Dolly(double factor)
{

}

void misInteractorSTyleImageExtend::viewToWorld(double x, double y, double z, double worldPt[4])
{
	if (CurrentRenderer == NULL)
	{
		return;
	}
	CurrentRenderer->SetViewPoint(x,y,z);
	CurrentRenderer->ViewToWorld();
	CurrentRenderer->GetWorldPoint(worldPt);
	if (worldPt[3])
	{
		worldPt[0] /= worldPt[3];
		worldPt[1] /= worldPt[3];
		worldPt[2] /= worldPt[3];
		worldPt[3] = 1.0;
	}
}

SquareDS misInteractorSTyleImageExtend::SetViewSquareDS()
{
	double PickPoint[4],PickPoint1[4],PickPoint2[4],PickPoint3[4];
	viewToWorld(-1,-1,1,PickPoint);
	viewToWorld(-1,1,1,PickPoint1);
	viewToWorld(1,1,1,PickPoint2);
	viewToWorld(1,-1,1,PickPoint3);

	SquareDS viewSquareStr;
	viewSquareStr.leftDownPointX=PickPoint[0];
	viewSquareStr.leftDownPointY=PickPoint[1];
	viewSquareStr.leftDownPointZ=PickPoint[2];

	viewSquareStr.leftUpPointX=PickPoint1[0];
	viewSquareStr.leftUpPointY=PickPoint1[1];
	viewSquareStr.leftUpPointZ=PickPoint1[2];

	viewSquareStr.rightDownPointX=PickPoint3[0];
	viewSquareStr.rightDownPointY=PickPoint3[1];
	viewSquareStr.rightDownPointZ=PickPoint3[2];

	viewSquareStr.rightUpPointX=PickPoint2[0];
	viewSquareStr.rightUpPointY=PickPoint2[1];
	viewSquareStr.rightUpPointZ=PickPoint2[2];

	return viewSquareStr;
}



 void misInteractorSTyleImageExtend::Pan()
{
	if (CurrentRenderer == NULL)
	{
		return;
	}
	
}

 void misInteractorSTyleImageExtend::OnMouseWheelForward() 
{
	GoNextImage(forwardDirection);
}

 void misInteractorSTyleImageExtend::OnMouseWheelBackward()
{
	GoNextImage(backwardDirection);
}

 void misInteractorSTyleImageExtend::GoNextImage(misCineDirection direction)
 {
	 if (CurrentRenderer == NULL)
	 {
		 return;
	 }

	 int step = 0;
	 if (forwardDirection == direction)
	 {
	   step = 1;
	 } 
	 else if (backwardDirection == direction)
	 {
	   step =-1;
	 }

	 FindPokedRenderer(Interactor->GetEventPosition()[0], 
	 Interactor->GetEventPosition()[1]);
	 
	 GrabFocus(EventCallbackCommand);
	 InvokeEvent(misGoNextImageEvent,&step);
	 ReleaseFocus();
 }

 void misInteractorSTyleImageExtend::UpdateState()
 {
	 switch (m_InteractionMode)
	 {

	 case MeasurmentWidget:
		 SetMeasurmentWidget();
		 break;

	 case AutoMeasurmentWidget:
		 SetAutoMeasurmentWidget();
		 break;
	 }
 }

 void misInteractorSTyleImageExtend::SetMeasurmentWidget()
 {
	 MEASURMENTMODE measurmentMode = NORMALMEASURMENT;
	 InvokeEvent(misSetMeasurmentWidgetEvent,&measurmentMode);
 }

 void misInteractorSTyleImageExtend::SetStateToWidget()
 {
	 m_InteractionMode = MeasurmentWidget;
 }

 void misInteractorSTyleImageExtend::SetSatateToRender()
 {
	m_InteractionMode = PanEvent_2d;
 }

 void misInteractorSTyleImageExtend::SetAutoMeasurmentWidget()
 {
	 MEASURMENTMODE measurmentMode = AUTOMEASURMENT;
	 InvokeEvent(misSetMeasurmentWidgetEvent,&measurmentMode);
 }

 void misInteractorSTyleImageExtend::SetStateToAutoWidget()
 {
	 m_InteractionMode = AutoMeasurmentWidget;
 }

 vtkRenderWindowInteractor * misInteractorSTyleImageExtend::GetRenderWindowInteractor()
 {
	return Interactor;
 }

 void misInteractorSTyleImageExtend::SetStateToResetContrast()
 {
	
	 InvokeEvent(vtkCommand::ResetWindowLevelEvent, this);

	 InvokeEvent(vtkCommand::EndWindowLevelEvent, this);
	 if ( Interactor )
	 {
		 ReleaseFocus();
	 }
 }

 void misInteractorSTyleImageExtend::OnChar()
 {

 }

 void misInteractorSTyleImageExtend::SetStateToPan()
 {
	 State = VTKIS_PAN;
 }

 INTERACTIONMODE misInteractorSTyleImageExtend::GetInteractionMode() const
 {
	 return m_InteractionMode;
 }

 void misInteractorSTyleImageExtend::SetInteractionMode( INTERACTIONMODE val )
 {
	 m_InteractionMode = val;
 }
  
 InteractionState misInteractorSTyleImageExtend::GetInteractionState() const 
 {
	 return m_InteractionState;
 }

 void misInteractorSTyleImageExtend::SetInteractionState(InteractionState val)
 {
	 m_InteractionState = val;
 }

