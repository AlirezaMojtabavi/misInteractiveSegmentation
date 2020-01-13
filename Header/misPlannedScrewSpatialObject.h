#pragma once

#include "misPlannedScrewSpatialObjectProperties.h"
#include "misSpatialObject.h"

// The misPlannedScrewSpatialObject provides a spatial representation of a planned screw. The spatial object can be subsequently 
// added to a (planned navigation) stage to be displayed. 
class misPlannedScrewSpatialObject : public misSpatialObject
{
	misObjectMacro(misPlannedScrewSpatialObject, misSpatialObject);
	misObjectNewMacro(misPlannedScrewSpatialObject);

	// The scale used to enlarge or shrink the representation of the object. This can be used to keep the visible size of the object
	// relatively fixed amongst different zoom levels.
	misPrivateVariableWithPublicAccessorsMacro(double, m_Scale, Scale);

	// The position, in world coordinates, of the plan start point.
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_PlanStartPoint, PlanStartPoint);

	// The position, in world coordinates, of the plan end point.
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_PlanEndPoint, PlanEndPoint);

public:
	// Updates the representation of this spatial object by translating it to plan start and end point positions and performing the
	// required scaling.
	void UpdateRepresentation();

	// The object holding the properties (settings) for screw representation object. To modify the settings, the properties object 
	// must be set rather than modifying its attributes.
	void SetProperties(const misPlannedScrewSpatialObjectProperties &newSettings);
	const misPlannedScrewSpatialObjectProperties &GetProperties() const;

	misPlannedScrewSpatialObject(void);
	virtual ~misPlannedScrewSpatialObject(void);

private:
	// Creates the planned screw representation at the origin.
	void CreateRepresentation();

	vtkSmartPointer<vtkActor> m_StartPointActor;	// The actor used to represent the start (entry) point of the planned screw.
	vtkSmartPointer<vtkActor> m_EndPointActor;	// The actor used to represent the end point of the planned screw.
	vtkSmartPointer<vtkActor> m_ShaftActor;	// The actor used to represent the line connecting start and end points.

	misPlannedScrewSpatialObjectProperties m_Properties;	// See SetProperties().
};