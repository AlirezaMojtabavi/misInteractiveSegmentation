#include "StdAfx.h"
#include "misUpviewChangesButtonWidget.h"

vtkStandardNewMacro(misUpviewChangesButtonWidget);

//-------------------------------------------------------------------------
misUpviewChangesButtonWidget::misUpviewChangesButtonWidget()
{
}

//-------------------------------------------------------------------------
misUpviewChangesButtonWidget::~misUpviewChangesButtonWidget()
{
}

//----------------------------------------------------------------------
void misUpviewChangesButtonWidget::CreateDefaultRepresentation()
{
  if ( ! this->WidgetRep )
    {
    this->WidgetRep = misUpviewChangesButtonRepresentation::New();
    }
}

//-------------------------------------------------------------------------
void misUpviewChangesButtonWidget::SelectRegion(double eventPos[2])
{
  if ( ! this->WidgetRep )
    {
    return;
    }

  double x = eventPos[0];
  if ( x <= 0.45 && x >= 0.00000000000000000) //Turn left
    {
    reinterpret_cast<misUpviewChangesButtonRepresentation*>(this->WidgetRep)->TurnCameraToTheLeft();
    }
  else if ( x <= 0.99 && x >= 0.55 )
    {
    reinterpret_cast<misUpviewChangesButtonRepresentation*>(this->WidgetRep)->TurnCameraToTheRight();
    }
  
  this->WidgetState = vtkBorderWidget::Start;
  this->Superclass::SelectRegion(eventPos);
}

//-------------------------------------------------------------------------
void misUpviewChangesButtonWidget::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  
}
