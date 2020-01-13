#include "stdafx.h"
#include "misAutoMeasurment.h"

#include "misCoreEvents.h"

#pragma warning (disable : 4503)

misAutoMeasurment::misAutoMeasurment()
{

}

misAutoMeasurment::~misAutoMeasurment()
{

}

misAutoMeasurment::Pointer misAutoMeasurment::New( void )
{
	Pointer smartPtr; 
	Self *rawPtr = new Self; 
	smartPtr = rawPtr; 
	rawPtr->UnRegister(); 
	return smartPtr;
}

void misAutoMeasurment::SetMeasurmentWidget()
{
	this->m_Handle = vtkPointHandleRepresentation2D::New();
	this->m_Handle->GetProperty()->SetColor(1,0,0);
	this->m_Representation = misDistanceRepresentation2D::New();
	this->m_Representation->SetHandleRepresentation(this->m_Handle);

	this->m_Representation->GetAxis()->SetNumberOfMinorTicks(4);
	this->m_Representation->GetAxis()->SetTickLength(9);
	this->m_Representation->GetAxis()->SetTitlePosition(0.2);
	m_Representation->GetAxis()->SetFontFactor(5);

	this->m_widget = misDistanceWidget::New();
	this->m_widget->SetInteractor(this->m_RenderWindowInteractor);
	this->m_widget->CreateDefaultRepresentation();
	this->m_widget->SetRepresentation(this->m_Representation);
	this->m_widget->SetMeasurmentMode(AUTOMEASURMENT);
	this->m_widget->SetAutoPoint1(this->m_FirstPoint);
	this->m_widget->SetImageOrientation(this->m_ImageOrientation);
	this->m_widget->init();
	this->m_widget->On();

	this->SetControlToWidget();
}



void misAutoMeasurment::SetControlToWidget()
{
	this->m_InteractionStyleExtend->SetStateToAutoWidget();
}

void misAutoMeasurment::SetImageOrientation( IMAGEORIENTATION pOrientation)
{
	this->m_ImageOrientation = pOrientation;
}

void misAutoMeasurment::SetWidgetFirstPoint( double pFirstPosition [3])
{
	this->m_FirstPoint[0] = pFirstPosition[0];
	this->m_FirstPoint[1] = pFirstPosition[1];
	this->m_FirstPoint[2] = pFirstPosition[2];
}

