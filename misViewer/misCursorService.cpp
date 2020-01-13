#include "StdAfx.h"
#include "misCursorService.h"

#include "misColorPointWidget.h"

misCursorService::misCursorService()
	: m_WidgetType(SimpleCursor), m_WidgetLineWidth(1)
{
	for (int i=0;i<6;i++)
		m_Bounds[i]=0;
	m_ImageOrientation = UNKnownDirection;
}

 

misCursorService::~misCursorService()
{
}

void misCursorService::SetWidgetInteractor( vtkRenderWindowInteractor* pInteractor )
{
	if (pInteractor)
		m_WidgetInteractor = pInteractor;
}

void misCursorService::ApplyWidget(vtkProp3D* actor)
{
	if (!actor)
		return;

	m_ColorPointWidget->SetProp3D(actor);
  	
	m_ColorPointWidget->SetInteractor(m_WidgetInteractor);
  	
	m_ColorPointWidget->SetCurrentCursorType(m_WidgetType);
  	if (m_Bounds)
  	{	
  		m_ColorPointWidget->PlaceWidget(m_Bounds);
  		m_ColorPointWidget->ModifyAxis();
  	}
	
	m_ColorPointWidget->Init();
	m_ColorPointWidget->EnabledOn();

}

void misCursorService::CreateWidget(double pickingTolerance)
{
	if (!m_ColorPointWidget)
		m_ColorPointWidget =  vtkSmartPointer<misColorPointWidget>::New();
	m_ColorPointWidget->SetPickingTolerance(pickingTolerance);
	m_ColorPointWidget->SetLineWidth(m_WidgetLineWidth);
	m_ColorPointWidget->SetAxesColors(m_AxesColors);
	m_ColorPointWidget->SetWidgetOrientation(m_ImageOrientation);
	m_ColorPointWidget->SetTorusVisibility(false);
	m_ColorPointWidget->SetDParam(5);
	m_ColorPointWidget->SetCurrentCursorType(m_WidgetType);
}

void misCursorService::SetImageOrientation( IMAGEORIENTATION imgOrintation )
{
	m_ImageOrientation = imgOrintation;
	if (m_ColorPointWidget)
	{
		m_ColorPointWidget->SetWidgetOrientation(m_ImageOrientation);
		m_ColorPointWidget->Init();
	}
}

void misCursorService::SetWidgetType( misCursorType widgetType )
{
	m_WidgetType = widgetType;
	if(m_ColorPointWidget)
		m_ColorPointWidget->SetCursorType(widgetType);
}

void misCursorService::EnableWidget()
{
	if (m_ColorPointWidget)
	{
		m_ColorPointWidget->EnabledOn();
	}
	else 
		_ASSERT( 0 == 1);
}

void misCursorService::DisableWidget()
{
	if (m_ColorPointWidget)
	{
		m_ColorPointWidget->EnabledOff();
	}
	else 
		_ASSERT( 0 == 1);
}

void misCursorService::ReleaseWidget()
{
	if(m_ColorPointWidget)
	{
		m_ColorPointWidget->SetInteractor(0);
		m_ColorPointWidget=0;
	}
}

void misCursorService::ChangeWidgetType(misCursorType cursorType)
{
	if (!m_ColorPointWidget)
		m_ColorPointWidget = vtkSmartPointer<misColorPointWidget>::New();
	if(m_CurrentRenderer)
		m_ColorPointWidget->SetCurrentRenderer(m_CurrentRenderer);
	double position[3] = {0,0,0};
	m_ColorPointWidget->SetWidgetOrientation(m_ImageOrientation);
	m_ColorPointWidget->SetCurrentCursorType(cursorType);
	m_ColorPointWidget->GetPosition(position);
	m_ColorPointWidget->SetLineWidth(m_WidgetLineWidth);
	m_ColorPointWidget->SetAxesColors(m_AxesColors);
	m_ColorPointWidget->PlaceWidget(m_Bounds);
	m_ColorPointWidget->SetPosition(position);
	m_ColorPointWidget->Init();
}

void misCursorService::SetWidgetBounds( double* pBounds )
{
	if (pBounds)
	{
		for (int i = 0 ; i < 6; i++)
			m_Bounds[i]=pBounds[i];
	}
	
}

void misCursorService::AddObserver( vtkCommand* pWdgObserver )
{
	if (m_ColorPointWidget)
	{
		m_ColorPointWidget->AddObserver(vtkCommand::EndInteractionEvent,pWdgObserver);
	}
	else
		_ASSERT( 0 == 1);
}

void misCursorService::Set3DInteractionCapturedFlag(bool val)
{
	if(m_ColorPointWidget)
		m_ColorPointWidget->SetInteractionCapturedFlag(val);
}

void misCursorService::UpdateWidgetPosition()
{
	if (m_ColorPointWidget)
	{
		m_ColorPointWidget->UpdateWidgetPosition();
	}
}

void misCursorService::SetCornerProperties( std::shared_ptr<ICornerProperties> pCornerProperties )
{
	if (pCornerProperties)
	{
		if(m_ColorPointWidget)
			m_ColorPointWidget->SetCornerProperties(pCornerProperties);
		else
			_ASSERT( 0 == 1);
	}
	else
		_ASSERT(0 == 1);
}

void misCursorService::SetAxesColors(const parcast::AxesColors& colors)
{
	m_AxesColors = colors;
	if (m_ColorPointWidget)
		m_ColorPointWidget->SetAxesColors(colors);
}

void misCursorService::SetRenderer( vtkRenderer* renderer )
{
	m_CurrentRenderer = renderer;
	if(m_ColorPointWidget)
		m_ColorPointWidget->SetCurrentRenderer(renderer);
}

void misCursorService::SetWidgetLineWeight( double weight )
{
	m_WidgetLineWidth = weight;
	if (m_ColorPointWidget)
		m_ColorPointWidget->SetLineWidth(m_WidgetLineWidth);
}
