#pragma once

#include "misCoaxialToriCollectionProperties.h"
#include "misTorus.h"

// The misCoaxialToriCollection class creates and maintains a collection of coaxial tori (misTorus objects) using the data from the
// properties object. It contains a specific number of tori all centred on a common axis, however with a fixed distance from each
// other. The first torus in the collection is created with a specified inner radius and distance from the base point. 
// Subsequent tori are created with the inner radius and the distance from the base point for each one larger than the last one 
// to a fixed amount. These values can be set through the object properties.
// Further, the collection is assigned a DestinationDirectionVector and a DestinationPosition. Each time UpdateRepresentation() 
// is called, DestinationDirectionVector and DestinationPosition are used respectively as the common axis of the tori 
// and the position of the base point.
class misCoaxialToriCollection 
{
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_DestinationDirectionVector, DestinationDirectionVector);
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_DestinationPosition, DestinationPosition);

public:
	misCoaxialToriCollection(void);
	~misCoaxialToriCollection(void);

	// Updates the position and orientation of the torus actors based on current DestinationDirectionVector and DestinationPosition.
	void UpdateRepresentation();

	// Sets new values for the object properties.
	// NOTE: This causes the underlying torus objects to be deleted and new ones to be created. Thus, references held to the old
	// objects should be discarded as those objects are not updated through calls to UpdateRepresentation() and holding references
	// to them will inhibit their disposal.
	void SetProperties(const misCoaxialToriCollectionProperties &newSettings);
	const misCoaxialToriCollectionProperties &GetProperties() const;

	// Gets the list of torus objects. This list will contain different misTorus object each time SetProperties() is called.
	const std::vector < std::shared_ptr<misTorus> > GetTori() const;

	//set the position instead of transform for viewing the torus
	void SetPosition(const double* position);

private:
	// Creates the misTorus objects using current properties. Called during construction and each time SetProperties is called.
	void CreateTori();

	double m_position[2];

	std::vector< std::shared_ptr<misTorus> > m_Tori;	// See GetTori().
	misCoaxialToriCollectionProperties m_Properties;	// Active settings. See SetProperties()
};

