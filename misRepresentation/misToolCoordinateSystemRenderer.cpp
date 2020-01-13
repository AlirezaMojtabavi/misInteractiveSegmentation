#include "StdAfx.h"
#include "misToolCoordinateSystemRenderer.h"

#include "misMathUtils.h"
#include "misDebug.h"

misToolCoordinateSystemRenderer::misToolCoordinateSystemRenderer(std::shared_ptr<IToolRepresentation> toolRepe,
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > coordinateSystemManager)
	: m_CorrelationManager(coordinateSystemManager), m_ToolRepresentation(toolRepe), m_Render(true)
{
}

void misToolCoordinateSystemRenderer::Render()
{
	if (!m_Render)
	{
		m_ToolRepresentation->SetVisibilityOff();
		return;
	}
	auto correlation = m_CorrelationManager->GetTransform(m_CoordinateSystem, m_ReferenceCoordinateSystem);
	if (correlation->IsValid())
	{
		auto vtkTransform = misMathUtils::CreateVtkTransform(correlation->GetTransform());
		m_ToolRepresentation->SetVisibilityOn();
		m_ToolRepresentation->SetUserTransform(vtkTransform);
	}
	else
		m_ToolRepresentation->SetVisibilityOff();
}

void misToolCoordinateSystemRenderer::SetCoordinateSystem( const  std::string& coordinateSytem )
{
	m_CoordinateSystem = coordinateSytem;
}

void misToolCoordinateSystemRenderer::SetRefrenceCoordinate( const  std::string& coordinateSytem )
{
	m_ReferenceCoordinateSystem = coordinateSytem;
}

 
void misToolCoordinateSystemRenderer::SetColor( float r, float g, float b )
{
	m_ToolRepresentation->SetColor(r, g , b);
}

void misToolCoordinateSystemRenderer::RenderingOn()
{
	m_Render = true;
}

void misToolCoordinateSystemRenderer::RenderingOff()
{
	m_Render = false;
}

 
