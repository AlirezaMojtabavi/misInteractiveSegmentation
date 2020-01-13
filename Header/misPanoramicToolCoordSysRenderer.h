#pragma once

#include "ICoordinateSystem.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRenderer.h"
#include "IPanoramicTransformConverter.h"
class IToolRepresentation;

class misPanoramicToolCoordSysRenderer : public ICoordinateSystemRenderer
{
public:
	misPanoramicToolCoordSysRenderer(
		std::shared_ptr<IToolRepresentation> toolRep, 
			std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > coordinateSystemManager,
		std::shared_ptr<IPanoramicTransformConverter> transformConverter);

	virtual void Render();

	virtual void SetCoordinateSystem( const std::string& coordinateSytem );

	virtual void SetRefrenceCoordinate( const std::string& coordinateSytem );
	virtual void SetPanoramicTransformConverter( std::shared_ptr<IPanoramicTransformConverter> converter );

	virtual void RenderingOn();

	virtual void RenderingOff();


	virtual void SetColor( float r, float g, float b );

private:
	std::string m_CoordinateSystem;
	std::string m_ReferenceCoordinateSystem;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<IToolRepresentation> m_ToolRepresentation;
	bool m_Render;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicTransformConverter;
};

