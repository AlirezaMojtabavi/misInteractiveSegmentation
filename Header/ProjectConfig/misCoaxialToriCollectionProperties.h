#pragma once

#include "misMacros.h"
#include "serializable.h"

// The misToriBasedOrientationNavigationGuideObjectProperties class is a wrapper for the settings used by 
// misToriBasedOrientationNavigationGuideObject objects. It is serializable so it can be read from a file and set to the object.
class misCoaxialToriCollectionProperties : public Serializable
{
	// Number of tori to be displayed.
	misPrivateVariableWithPublicAccessorsMacro(int, m_NumberOfTori, NumberOfTori);

	// Cross section radius of all the tori.
	misPrivateVariableWithPublicAccessorsMacro(double, m_CrossSectionRadius, CrossSectionRadius);

	// Inner radius of the smallest torus in the collection.
	misPrivateVariableWithPublicAccessorsMacro(double, m_SmallestRingRadius, SmallestRingRadius);

	// Amount of increment applied to the radius of every next torus in the collection with respect to the one 
	// immediately before it.
	misPrivateVariableWithPublicAccessorsMacro(double, m_RingRadiusIncrementSize, RingRadiusIncrementSize);

	// Distance from the smallest torus to the XY plane (assuming the axis of the tori is parallel to the Z axis).
	misPrivateVariableWithPublicAccessorsMacro(double, m_XYPlaneDisplacement, XYPlaneDisplacement);

	// Distance between the planes containing each two adjacent tori within the collection.
	misPrivateVariableWithPublicAccessorsMacro(double, m_RingsSeparation, RingsSeparation);

	// Color of the tori using the R/G/B color scheme
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_ToriColour, ToriColour);

public:
	misCoaxialToriCollectionProperties(void);
	~misCoaxialToriCollectionProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );
};

