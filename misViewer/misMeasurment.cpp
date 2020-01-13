#include "stdafx.h"
#include "misMeasurment.h"

#include "misCoreEvents.h"

#pragma warning (disable : 4503)

misMeasurment::misMeasurment()
{

}

misMeasurment::~misMeasurment()
{
}

misMeasurment::Pointer misMeasurment::New( void )
{
	Pointer smartPtr; 
	Self *rawPtr = new Self; 
	smartPtr = rawPtr; 
	rawPtr->UnRegister(); 
	return smartPtr;
}

void misMeasurment::SetMeasurmentWidget()
{
	m_Handle = vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
	m_Handle->GetProperty()->SetColor(1,0,0);
	m_Representation = vtkSmartPointer<misDistanceRepresentation2D>::New();
	m_Representation->SetHandleRepresentation(m_Handle);

	m_Representation->GetAxis()->SetNumberOfMinorTicks(4);
	m_Representation->GetAxis()->SetTickLength(9);
	m_Representation->GetAxis()->SetTitlePosition(0.2);
	m_Representation->GetAxis()->SetFontFactor(5);

	m_widget = vtkSmartPointer<misDistanceWidget>::New();
	m_widget->SetInteractor(m_RenderWindowInteractor);
	m_widget->CreateDefaultRepresentation();
	m_widget->SetRepresentation(m_Representation);
	m_widget->SetMeasurmentMode(NORMALMEASURMENT);
	m_widget->init();
	m_widget->On();

	SetControlToWidget();
}

void misMeasurment::ResetMeasurmentWidget()
{
	if(m_widget)
		m_widget->SetInteractor(0);
	if (m_InteractionStyleExtend)
		m_InteractionStyleExtend->SetSatateToRender();
}

void misMeasurment::SetControlToWidget()
{
	m_InteractionStyleExtend->SetStateToWidget();
}

void misMeasurment::SetInteractionStyleExtend( misInteractorSTyleImageExtend* pInteractionStyleExtend, IMAGEORIENTATION orientation)
{
	if (pInteractionStyleExtend)
	{
		m_InteractionStyleExtend = pInteractionStyleExtend;
		if(m_Representation)
			m_Representation->SetImageOrientation(orientation);
	} 
 
}

void misMeasurment::SetRenderWindowInteractor( vtkRenderWindowInteractor* pRenderWindowInteractor)
{
 
	m_RenderWindowInteractor = pRenderWindowInteractor;
 
}








