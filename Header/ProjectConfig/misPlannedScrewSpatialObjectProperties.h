#pragma once

#include "misMacros.h"
#include "serializable.h"

// The misPlannedScrewSpatialObjectProperties class provides a serializable container for the settings and properties required
// for initialization of a misPlannedScrewSpatialObject object. 
class misPlannedScrewSpatialObjectProperties : public Serializable
{
	// Radius of the sphere representing starting point of the plan.
	misPrivateVariableWithPublicAccessorsMacro(double, m_StartPointRadius, StartPointRadius);

	// Radius of the sphere representing starting point of the plan.
	misPrivateVariableWithPublicAccessorsMacro(double, m_EndPointRadius, EndPointRadius);
	
	// Radius of the cylinder representing the plan shaft.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ShaftRadius, ShaftRadius);

	// Colour of the plan start point marker
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_StartPointColour, StartPointColour);

	// Colour of the plan end point marker
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_EndPointColour, EndPointColour);

public:
	misPlannedScrewSpatialObjectProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );

};

