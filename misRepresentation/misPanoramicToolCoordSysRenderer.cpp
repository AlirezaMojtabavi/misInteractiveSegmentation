#include "StdAfx.h"
#include "misPanoramicToolCoordSysRenderer.h"
#include "misMathUtils.h"
#include "misToolRepresentation.h"

misPanoramicToolCoordSysRenderer::misPanoramicToolCoordSysRenderer(
	std::shared_ptr<IToolRepresentation> toolRep, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > coordinateSystemManager,
	std::shared_ptr<IPanoramicTransformConverter> transformConverter)
	: m_CorrelationManager(coordinateSystemManager), m_ToolRepresentation(toolRep), m_Render(true), 
	m_PanoramicTransformConverter(transformConverter)
{
}

void misPanoramicToolCoordSysRenderer::Render()
{
	if (!m_Render)
	{
		m_ToolRepresentation->SetVisibilityOff();
		return;
	}
	auto correlation = m_CorrelationManager->GetTransform(m_CoordinateSystem, m_ReferenceCoordinateSystem);
	if (correlation->IsValid() && m_PanoramicTransformConverter)
	{
		m_PanoramicTransformConverter->SetTransformInImageSpace(correlation->GetTransform());
		auto vtkTrans = misMathUtils::CreateVtkTransform(m_PanoramicTransformConverter->GetTransformInPanoramicSpace());
		m_ToolRepresentation->SetVisibilityOn();
		m_ToolRepresentation->SetUserTransform(vtkTrans);
	}
	else
		m_ToolRepresentation->SetVisibilityOff();
}

void misPanoramicToolCoordSysRenderer::SetCoordinateSystem( const std::string& coordinateSytem )
{
	m_CoordinateSystem = coordinateSytem;
}

void misPanoramicToolCoordSysRenderer::SetRefrenceCoordinate( const std::string& coordinateSytem )
{
	m_ReferenceCoordinateSystem = coordinateSytem;
}

void misPanoramicToolCoordSysRenderer::SetPanoramicTransformConverter( std::shared_ptr<IPanoramicTransformConverter> converter )
{
	m_PanoramicTransformConverter = converter;
}

void misPanoramicToolCoordSysRenderer::RenderingOn()
{
	m_Render = true;
}

void misPanoramicToolCoordSysRenderer::RenderingOff()
{
	m_Render = false;
}



void misPanoramicToolCoordSysRenderer::SetColor( float r, float g, float b )
{
	m_ToolRepresentation->SetColor(r, g , b);
}
