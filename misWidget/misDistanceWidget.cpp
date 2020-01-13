#include "stdafx.h"
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDistanceWidget.cxx,v

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

	 This software is distributed WITHOUT ANY WARRANTY; without even
	 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "misDistanceWidget.h"

#include "misDistanceRepresentation2D.h"
 
vtkStandardNewMacro(misDistanceWidget);


// The distance widget observes its two handles.
// Here we create the command/observer classes to respond to the 
// handle widgets.
class misDistanceWidgetCallback : public vtkCommand
{
public:
  static misDistanceWidgetCallback *New() 
	{ return new misDistanceWidgetCallback; }
  virtual void Execute(vtkObject*, unsigned long eventId, void*)
	{
	  switch (eventId)
		{
		case vtkCommand::StartInteractionEvent:
		  this->DistanceWidget->StartDistanceInteraction(this->HandleNumber);
		  break;
		case vtkCommand::InteractionEvent:
		  this->DistanceWidget->DistanceInteraction(this->HandleNumber);
		  break;
		case vtkCommand::EndInteractionEvent:
		  this->DistanceWidget->EndDistanceInteraction(this->HandleNumber);
		  break;
		}
	}
  int HandleNumber;
  misDistanceWidget *DistanceWidget;
};


//----------------------------------------------------------------------
misDistanceWidget::misDistanceWidget()
{
	this->ManagesCursor = 0;
	this->m_Orientation = UNKnownDirection;

	this->WidgetState = vtkDistanceWidget::Start;
	this->CurrentHandle = 0;

	// The widgets for moving the end points. They observe this widget (i.e.,
	// this widget is the parent to the handles).
	this->Point1Widget = vtkHandleWidget::New();
	this->Point1Widget->SetParent(this);
	this->Point2Widget = vtkHandleWidget::New();
	this->Point2Widget->SetParent(this);

	// Set up the callbacks on the two handles
	this->DistanceWidgetCallback1 = misDistanceWidgetCallback::New();
	this->DistanceWidgetCallback1->HandleNumber = 0;
	this->DistanceWidgetCallback1->DistanceWidget = this;
	this->Point1Widget->AddObserver(vtkCommand::StartInteractionEvent, this->DistanceWidgetCallback1, this->Priority);
	this->Point1Widget->AddObserver(vtkCommand::InteractionEvent, this->DistanceWidgetCallback1,this->Priority);
	this->Point1Widget->AddObserver(vtkCommand::EndInteractionEvent, this->DistanceWidgetCallback1,this->Priority);

	this->DistanceWidgetCallback2 = misDistanceWidgetCallback::New();
	this->DistanceWidgetCallback2->HandleNumber = 1;
	this->DistanceWidgetCallback2->DistanceWidget = this;
	this->Point2Widget->AddObserver(vtkCommand::StartInteractionEvent, this->DistanceWidgetCallback2, 
		this->Priority);
	this->Point2Widget->AddObserver(vtkCommand::InteractionEvent, this->DistanceWidgetCallback2,
		this->Priority);
	this->Point2Widget->AddObserver(vtkCommand::EndInteractionEvent, this->DistanceWidgetCallback2,
		this->Priority);


	// These are the event callbacks supported by this widget
	this->CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonPressEvent,
		vtkWidgetEvent::AddPoint,
		this, misDistanceWidget::AddPointAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::MouseMoveEvent,
		vtkWidgetEvent::Move,
		this, misDistanceWidget::MoveAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonReleaseEvent,
		vtkWidgetEvent::EndSelect,
		this, misDistanceWidget::EndSelectAction);
}

//----------------------------------------------------------------------
misDistanceWidget::~misDistanceWidget()
{
 
}

//----------------------------------------------------------------------
void misDistanceWidget::CreateDefaultRepresentation()
{
  if ( ! this->WidgetRep )
	{
	this->WidgetRep = misDistanceRepresentation2D::New();
	}
  reinterpret_cast<misDistanceRepresentation2D*>(this->WidgetRep)->
	InstantiateHandleRepresentation();
}

//----------------------------------------------------------------------

// The following methods are the callbacks that the measure widget responds to
//-------------------------------------------------------------------------
void misDistanceWidget::AddPointAction(vtkAbstractWidget *w)
{
  misDistanceWidget *self = reinterpret_cast<misDistanceWidget*>(w);
  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];

  // Freshly enabled and placing the first point
  if ( self->WidgetState == misDistanceWidget::Start )
	{
	self->GrabFocus(self->EventCallbackCommand);
	self->WidgetState = misDistanceWidget::Define;
	self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
	reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->VisibilityOn();
	double autoposition[3];
	double displayPosition[4];
	self->GetAutoPoint1(autoposition);
	self->ComputeWorldToDisplay(autoposition[0] ,autoposition[1] , autoposition[2] ,displayPosition);
	double e[2];
	e[0] = static_cast<double>(X);
	e[1] = static_cast<double>(Y);
	if (AUTOMEASURMENT == self->GetMeasurmentMode())
	{
		reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->SetPoint1ToFocalPoint(displayPosition);
		reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->setRepresentationMode(false);
	}
	else
		reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->setRepresentationMode(true);
	
	reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->StartWidgetInteraction(e);
	

	self->CurrentHandle = 0;
	self->InvokeEvent(vtkCommand::PlacePointEvent,&(self->CurrentHandle));
	}

  // Placing the second point is easy
  else if ( self->WidgetState == misDistanceWidget::Define )
	{
	self->CurrentHandle = 1;
	self->InvokeEvent(vtkCommand::PlacePointEvent,&(self->CurrentHandle));
	self->WidgetState = misDistanceWidget::Manipulate;
	self->Point1Widget->SetEnabled(1);
	self->Point2Widget->SetEnabled(1);
	self->CurrentHandle = -1;
	self->ReleaseFocus();
	self->InvokeEvent(vtkCommand::EndInteractionEvent,NULL);
	}

  // Maybe we are trying to manipulate the widget handles
  else //if ( self->WidgetState == misDistanceWidget::Manipulate )
	{
	int state = self->WidgetRep->ComputeInteractionState(X,Y);
	if ( state == vtkDistanceRepresentation::Outside )
	  {
	  self->CurrentHandle = -1;
	  return;
	  }

	self->GrabFocus(self->EventCallbackCommand);
	if ( state == vtkDistanceRepresentation::NearP1 )
	  {
	  self->CurrentHandle = 0;
	  }
	else if ( state == vtkDistanceRepresentation::NearP2 )
	  {
	  self->CurrentHandle = 1;
	  }
	self->InvokeEvent(vtkCommand::LeftButtonPressEvent,NULL);
	}

  // Clean up
  self->EventCallbackCommand->SetAbortFlag(1);
  self->Render();
}

//-------------------------------------------------------------------------
void misDistanceWidget::MoveAction(vtkAbstractWidget *w)
{
  misDistanceWidget *self = reinterpret_cast<misDistanceWidget*>(w);

  // Do nothing if in start mode or valid handle not selected
  if ( self->WidgetState == misDistanceWidget::Start )
	{
	return;
	}

  // Delegate the event consistent with the state
  if ( self->WidgetState == misDistanceWidget::Define )
	{
	int X = self->Interactor->GetEventPosition()[0];
	int Y = self->Interactor->GetEventPosition()[1];
	double e[2];
	e[0] = static_cast<double>(X);
	e[1] = static_cast<double>(Y);
	reinterpret_cast<misDistanceRepresentation2D*>(self->WidgetRep)->WidgetInteraction(e);
	self->InvokeEvent(vtkCommand::InteractionEvent,NULL);
	self->EventCallbackCommand->SetAbortFlag(1);
	}
  else //must be moving a handle, invoke a event for the handle widgets
	{
	self->InvokeEvent(vtkCommand::MouseMoveEvent, NULL);
	}
  misDistanceRepresentation2D*  pmisWidge=dynamic_cast<misDistanceRepresentation2D*>(self->WidgetRep); 
  pmisWidge->SetImageOrientation(self->GetImageOrientation());
  self->WidgetRep->BuildRepresentation();
  self->Render();
}

//-------------------------------------------------------------------------
void misDistanceWidget::EndSelectAction(vtkAbstractWidget *w)
{
  misDistanceWidget *self = reinterpret_cast<misDistanceWidget*>(w);

  // Do nothing if outside
  if ( self->WidgetState == misDistanceWidget::Start ||
	   self->WidgetState == misDistanceWidget::Define ||
	   self->CurrentHandle < 0 )
	{
	return;
	}

  self->ReleaseFocus();
  self->InvokeEvent(vtkCommand::LeftButtonReleaseEvent,NULL);
  self->CurrentHandle = -1;
  misDistanceRepresentation2D*  pmisWidge=dynamic_cast<misDistanceRepresentation2D*>(self->WidgetRep); 
  pmisWidge->SetImageOrientation(self->GetImageOrientation());
  self->WidgetRep->BuildRepresentation();
  self->EventCallbackCommand->SetAbortFlag(1);
  self->Render();
}

// These are callbacks that are active when the user is manipulating the
// handles of the measure widget.
//----------------------------------------------------------------------
void misDistanceWidget::StartDistanceInteraction(int)
{
  this->Superclass::StartInteraction();
  this->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
}

//----------------------------------------------------------------------
void misDistanceWidget::DistanceInteraction(int handle)
{
  double pos[3];
  double displayPos[4];
  if ( handle == 0 )
	{
		if (this->GetMeasurmentMode())
		{
			this->GetAutoPoint1(pos);
			this->ComputeWorldToDisplay(pos[0] , pos[1] , pos[2] , displayPos);
			reinterpret_cast<misDistanceRepresentation2D*>(this->WidgetRep)->SetPoint1ToFocalPoint(displayPos);
		}
		else
		{
			reinterpret_cast<vtkDistanceRepresentation*>(this->WidgetRep)->
				GetPoint1Representation()->GetDisplayPosition(pos);
			reinterpret_cast<vtkDistanceRepresentation*>(this->WidgetRep)->
				SetPoint1DisplayPosition(pos);
		}
	}
  else
	{
	reinterpret_cast<vtkDistanceRepresentation*>(this->WidgetRep)->
	  GetPoint2Representation()->GetDisplayPosition(pos);
	reinterpret_cast<vtkDistanceRepresentation*>(this->WidgetRep)->
	  SetPoint2DisplayPosition(pos);
	}
  this->InvokeEvent(vtkCommand::InteractionEvent,NULL);
}

////----------------------------------------------------------------------
void misDistanceWidget::EndDistanceInteraction(int)
{
  EndInteraction();
  this->InvokeEvent(vtkCommand::EndInteractionEvent,NULL);
}

MEASURMENTMODE misDistanceWidget::GetMeasurmentMode()
{
	return  this->m_MeasurmentMode;

}

void misDistanceWidget::SetMeasurmentMode( MEASURMENTMODE type )
{
	this->m_MeasurmentMode = type;

}

void misDistanceWidget::init()
{
	this->SetMeasurmentMode(this->GetMeasurmentMode());
}

void misDistanceWidget::SetAutoPoint1( double pos[3] )
{
	this->AutoPoint1[0] = pos[0];
	this->AutoPoint1[1] = pos[1];
	this->AutoPoint1[2] = pos[2];
}

void misDistanceWidget::GetAutoPoint1( double pos[3] )
{
	pos[0] = this->AutoPoint1[0];
	pos[1] = this->AutoPoint1[1];
	pos[2] = this->AutoPoint1[2];
}

void misDistanceWidget::SetImageOrientation( IMAGEORIENTATION ImgOrn)
{
	this->m_Orientation = ImgOrn;
}

IMAGEORIENTATION misDistanceWidget::GetImageOrientation()
{
	return this->m_Orientation;
}

//----------------------------------------------------------------------
