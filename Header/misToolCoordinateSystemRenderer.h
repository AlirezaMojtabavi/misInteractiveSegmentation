#pragma once

#include "ICoordinateSystem.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRenderer.h"
#include "misToolRepresentation.h"

// Implementation class for rendering misTooldata of ICoordinateSystemRenderer - uses an instance of
// ICoordinateSystemCorrelationManager to obtain transform between the rendered and the reference coordinate systems.
class misToolCoordinateSystemRenderer :	public ICoordinateSystemRenderer
{
public:
	misToolCoordinateSystemRenderer(
		std::shared_ptr<IToolRepresentation>, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > coordinateSystemManager);

	virtual void Render();
	virtual void SetCoordinateSystem( const std::string& coordinateSytem );
	virtual void SetRefrenceCoordinate( const std::string& coordinateSytem );
	virtual void RenderingOn();
	virtual void RenderingOff();
	virtual void SetColor(float r, float g, float b );

private:
	std::string m_CoordinateSystem;
	std::string m_ReferenceCoordinateSystem;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<IToolRepresentation> m_ToolRepresentation;
	bool m_Render;
};

