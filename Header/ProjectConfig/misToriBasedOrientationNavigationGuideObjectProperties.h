#pragma once

#include "misMacros.h"
#include "misCoaxialToriCollectionProperties.h"
#include "serializable.h"

// The misToriBasedOrientationNavigationGuideObjectProperties class is a wrapper for the settings used by 
// misToriBasedOrientationNavigationGuideObject objects. It is serializable so it can be read from a file and set to the object.
// It contains two similar sets of settings, one for each of the torus collections that the tori based navigation guide object has.
class misToriBasedOrientationNavigationGuideObjectProperties : public Serializable
{
	// The properties used by the torus collection displaying position and orientation of the tracking tool.
	misPrivateVariableWithPublicAccessorsMacro(misCoaxialToriCollectionProperties, 
		m_ToriCollectionPropertiesForTool, ToriCollectionPropertiesForTool);

	// The properties used by the torus collection displaying position and orientation of the plan.
	misPrivateVariableWithPublicAccessorsMacro(misCoaxialToriCollectionProperties, 
		m_ToriCollectionPropertiesForPlan, ToriCollectionPropertiesForPlan);

public:
	misToriBasedOrientationNavigationGuideObjectProperties(void);
	~misToriBasedOrientationNavigationGuideObjectProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );
};