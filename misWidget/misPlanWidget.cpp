#include "StdAfx.h"
#include "misPlanWidget.h"
 
 
#include "IPlanWidgetRepresentation.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkHandleWidget.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkObjectFactory.h"
#include "vtkWidgetEventTranslator.h"
#include "vtkWidgetCallbackMapper.h"
#include "vtkEvent.h"
#include "vtkWidgetEvent.h"
#include "vtkRenderWindow.h"
 
 
void misPlanWidget::SetLineWidgetUID( misUID uid )
{
	this->m_LineWidgetUID = uid;
}

misUID misPlanWidget::GetLineWidgetUID()
{
	return this->m_LineWidgetUID;
}

misPlanWidget * misPlanWidget::New()
{
	return new misPlanWidget;
}
 

void misPlanWidget::CreateDefaultRepresentation()
{
 
}


//----------------------------------------------------------------------------
misPlanWidget::misPlanWidget()
{
	this->WidgetState = misPlanWidget::Start;
	this->ManagesCursor = 1;
	this->CurrentHandle = 0;

	// The widgets for moving the end points. They observe this widget (i.e.,
	// this widget is the parent to the handles).
	this->Point1Widget = vtkHandleWidget::New();
	this->Point1Widget->SetPriority(this->Priority - 0.01);
	this->Point1Widget->SetParent(this);
	this->Point1Widget->ManagesCursorOff();

	this->Point2Widget = vtkHandleWidget::New();
	this->Point2Widget->SetPriority(this->Priority - 0.01);
	this->Point2Widget->SetParent(this);
	this->Point2Widget->ManagesCursorOff();

	this->LineHandle = vtkHandleWidget::New();
	this->LineHandle->SetPriority(this->Priority - 0.01);
	this->LineHandle->SetParent(this);
	this->LineHandle->ManagesCursorOff();

	// Define widget events
	this->CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonPressEvent,
		vtkWidgetEvent::Select,
		this, misPlanWidget::SelectAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonReleaseEvent,
		vtkWidgetEvent::EndSelect,
		this, misPlanWidget::EndSelectAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::MiddleButtonPressEvent,
		vtkWidgetEvent::Translate,
		this, misPlanWidget::TranslateAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::MiddleButtonReleaseEvent,
		vtkWidgetEvent::EndTranslate,
		this, misPlanWidget::EndSelectAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::RightButtonPressEvent,
		vtkWidgetEvent::Scale,
		this, misPlanWidget::ScaleAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::RightButtonReleaseEvent,
		vtkWidgetEvent::EndScale,
		this, misPlanWidget::EndSelectAction);
	this->CallbackMapper->SetCallbackMethod(vtkCommand::MouseMoveEvent,
		vtkWidgetEvent::Move,
		this, misPlanWidget::MoveAction);

	this->ActiveKeyCode = 0;
	this->KeyEventCallbackCommand = vtkCallbackCommand::New();
	this->KeyEventCallbackCommand->SetClientData(this);
	this->KeyEventCallbackCommand->SetCallback(misPlanWidget::ProcessKeyEvents);
}

//----------------------------------------------------------------------------
misPlanWidget::~misPlanWidget()
{
	this->Point1Widget->Delete();
	this->Point2Widget->Delete();
	this->LineHandle->Delete();
	this->KeyEventCallbackCommand->Delete();
}

//----------------------------------------------------------------------
void misPlanWidget::SetEnabled(int enabling)
{
	int enabled = this->Enabled;

	// We do this step first because it sets the CurrentRenderer
	this->Superclass::SetEnabled(enabling);

	// We defer enabling the handles until the selection process begins
	if (enabling && !enabled)
	{
		// Don't actually turn these on until cursor is near the end points or the line.
		this->CreateDefaultRepresentation();
		this->Point1Widget->SetRepresentation(reinterpret_cast<IPlanWidgetRepresentation*>
			(this->WidgetRep)->GetPoint1Representation());
		this->Point1Widget->SetInteractor(this->Interactor);
		this->Point1Widget->GetRepresentation()->SetRenderer(this->CurrentRenderer);

		this->Point2Widget->SetRepresentation(reinterpret_cast<IPlanWidgetRepresentation*>
			(this->WidgetRep)->GetPoint2Representation());
		this->Point2Widget->SetInteractor(this->Interactor);
		this->Point2Widget->GetRepresentation()->SetRenderer(this->CurrentRenderer);

 
		this->LineHandle->SetInteractor(this->Interactor);
		this->LineHandle->GetRepresentation()->SetRenderer(this->CurrentRenderer);

		if (this->Parent)
		{
			this->Parent->AddObserver(vtkCommand::KeyPressEvent,
				this->KeyEventCallbackCommand,
				this->Priority);
			this->Parent->AddObserver(vtkCommand::KeyReleaseEvent,
				this->KeyEventCallbackCommand,
				this->Priority);
		}
		else
		{
			this->Interactor->AddObserver(vtkCommand::KeyPressEvent,
				this->KeyEventCallbackCommand,
				this->Priority);
			this->Interactor->AddObserver(vtkCommand::KeyReleaseEvent,
				this->KeyEventCallbackCommand,
				this->Priority);
		}
	}
	else if (!enabling && enabled)
	{
		this->Point1Widget->SetEnabled(0);
		this->Point2Widget->SetEnabled(0);
		this->LineHandle->SetEnabled(0);

		if (this->Parent)
		{
			this->Parent->RemoveObserver(this->KeyEventCallbackCommand);
		}
		else
		{
			this->Interactor->RemoveObserver(this->KeyEventCallbackCommand);
		}
	}
}

//----------------------------------------------------------------------
void misPlanWidget::SelectAction(vtkAbstractWidget *w)
{
	misPlanWidget *self = reinterpret_cast<misPlanWidget*>(w);
	if (self->WidgetRep->GetInteractionState() == IPlanWidgetRepresentation::Outside)
	{
		return;
	}

	// Get the event position
	int X = self->Interactor->GetEventPosition()[0];
	int Y = self->Interactor->GetEventPosition()[1];

	// We are definitely selected
	self->WidgetState = misPlanWidget::Active;
	self->GrabFocus(self->EventCallbackCommand);
	double e[2];
	e[0] = static_cast<double>(X);
	e[1] = static_cast<double>(Y);
	reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
		StartWidgetInteraction(e);
	self->InvokeEvent(vtkCommand::LeftButtonPressEvent, nullptr); //for the handles
	self->StartInteraction();
	self->InvokeEvent(vtkCommand::StartInteractionEvent, nullptr);
	self->EventCallbackCommand->SetAbortFlag(1);
}

//----------------------------------------------------------------------
void misPlanWidget::TranslateAction(vtkAbstractWidget *w)
{
	misPlanWidget *self = reinterpret_cast<misPlanWidget*>(w);
	if (self->WidgetRep->GetInteractionState() == IPlanWidgetRepresentation::Outside)
	{
		return;
	}

	// Modify the state, we are selected
	int state = self->WidgetRep->GetInteractionState();
	if (state == IPlanWidgetRepresentation::OnP1)
	{
		reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
			SetInteractionState(IPlanWidgetRepresentation::TranslatingP1);
	}
	else if (state == IPlanWidgetRepresentation::OnP2)
	{
		reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
			SetInteractionState(IPlanWidgetRepresentation::TranslatingP2);
	}
	else
	{
		reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
			SetInteractionState(IPlanWidgetRepresentation::OnLine);
	}

	// Get the event position
	int X = self->Interactor->GetEventPosition()[0];
	int Y = self->Interactor->GetEventPosition()[1];

	// We are definitely selected
	self->WidgetState = misPlanWidget::Active;
	self->GrabFocus(self->EventCallbackCommand);
	double eventPos[2];
	eventPos[0] = static_cast<double>(X);
	eventPos[1] = static_cast<double>(Y);
	reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
		StartWidgetInteraction(eventPos);
	self->InvokeEvent(vtkCommand::LeftButtonPressEvent, nullptr); //for the handles
	self->EventCallbackCommand->SetAbortFlag(1);
	self->StartInteraction();
	self->InvokeEvent(vtkCommand::StartInteractionEvent, nullptr);
}

//----------------------------------------------------------------------
void misPlanWidget::ScaleAction(vtkAbstractWidget *w)
{
	misPlanWidget *self = reinterpret_cast<misPlanWidget*>(w);
	if (self->WidgetRep->GetInteractionState() == IPlanWidgetRepresentation::Outside)
	{
		return;
	}

	reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
		SetInteractionState(IPlanWidgetRepresentation::Scaling);
	self->Interactor->Disable();
	self->LineHandle->SetEnabled(0);
	self->Interactor->Enable();

	// Get the event position
	int X = self->Interactor->GetEventPosition()[0];
	int Y = self->Interactor->GetEventPosition()[1];

	// We are definitely selected
	self->WidgetState = misPlanWidget::Active;
	self->GrabFocus(self->EventCallbackCommand);
	double eventPos[2];
	eventPos[0] = static_cast<double>(X);
	eventPos[1] = static_cast<double>(Y);
	reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
		StartWidgetInteraction(eventPos);
	self->EventCallbackCommand->SetAbortFlag(1);
	self->StartInteraction();
	self->InvokeEvent(vtkCommand::StartInteractionEvent, nullptr);
}

//----------------------------------------------------------------------
void misPlanWidget::MoveAction(vtkAbstractWidget *w)
{
	misPlanWidget *self = reinterpret_cast<misPlanWidget*>(w);
	// compute some info we need for all cases
	int X = self->Interactor->GetEventPosition()[0];
	int Y = self->Interactor->GetEventPosition()[1];

	// See whether we're active
	if (self->WidgetState == misPlanWidget::Start)
	{
		self->Interactor->Disable(); //avoid extra renders
		self->Point1Widget->SetEnabled(0);
		self->Point2Widget->SetEnabled(0);
		self->LineHandle->SetEnabled(0);

		int oldState = self->WidgetRep->GetInteractionState();
		int state = self->WidgetRep->ComputeInteractionState(X, Y);
		int changed;
		// Determine if we are near the end points or the line
		if (state == IPlanWidgetRepresentation::Outside)
		{
			changed = self->RequestCursorShape(VTK_CURSOR_DEFAULT);
		}
		else //must be near something
		{
			changed = self->RequestCursorShape(VTK_CURSOR_HAND);
			if (state == IPlanWidgetRepresentation::OnP1)
			{
				self->Point1Widget->SetEnabled(1);
			}
			else if (state == IPlanWidgetRepresentation::OnP2)
			{
				self->Point2Widget->SetEnabled(1);
			}
			else //if ( state == IPlanWidgetRepresentation::OnLine )
			{
				self->LineHandle->SetEnabled(1);
				changed = 1; //movement along the line always needs render
			}
		}
		self->Interactor->Enable(); //avoid extra renders
		if (changed || oldState != state)
		{
			self->Render();
		}
	}
	else //if ( self->WidgetState == misPlanWidget::Active )
	{
		// moving something
		double e[2];
		e[0] = static_cast<double>(X);
		e[1] = static_cast<double>(Y);
		self->InvokeEvent(vtkCommand::MouseMoveEvent, nullptr); //handles observe this
		reinterpret_cast<IPlanWidgetRepresentation*>(self->WidgetRep)->
			WidgetInteraction(e);
		self->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
		self->EventCallbackCommand->SetAbortFlag(1);
		self->Render();
	}
}

//----------------------------------------------------------------------
void misPlanWidget::EndSelectAction(vtkAbstractWidget *w)
{
	misPlanWidget *self = reinterpret_cast<misPlanWidget*>(w);
	if (self->WidgetState == misPlanWidget::Start)
	{
		return;
	}

	// Return state to not active
	self->WidgetState = misPlanWidget::Start;
	self->ReleaseFocus();
	self->InvokeEvent(vtkCommand::LeftButtonReleaseEvent, nullptr); //handles observe this
	self->EventCallbackCommand->SetAbortFlag(1);
	self->InvokeEvent(vtkCommand::EndInteractionEvent, nullptr);
	self->Superclass::EndInteraction();
	self->Render();
}

 

//----------------------------------------------------------------------------
void misPlanWidget::SetProcessEvents(int pe)
{
	this->Superclass::SetProcessEvents(pe);

	this->Point1Widget->SetProcessEvents(pe);
	this->Point2Widget->SetProcessEvents(pe);
	this->LineHandle->SetProcessEvents(pe);
}

//----------------------------------------------------------------------------
void misPlanWidget::ProcessKeyEvents(vtkObject*, unsigned long event,
	void* clientdata, void*)
{
 	 
}

//----------------------------------------------------------------------------
void misPlanWidget::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);

}


