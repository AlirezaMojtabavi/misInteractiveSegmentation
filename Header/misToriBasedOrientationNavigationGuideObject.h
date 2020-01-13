#pragma once

#include "misCoaxialToriCollection.h"
#include "misNavigationGuideObject.h"
#include "misToriBasedOrientationNavigationGuideObjectProperties.h"

// The misToriBasedOrientationNavigationGuideObject class provides a 3D navigation guide in the form of two sets of coaxial 
// tori. The radius of the tori in each set is linearly increased with increasing distance from the torus collection base.
// One set of tori has its common axis fixed on the plan axis and its base on the plan start point. The other set has its axis
// aligned with the tracking tool orientation and its base fixed on the tracking tool tip position. As such, to place the tracking
// tool at the plan start point and orientate it according to the plan, the clinician must try to place the torus collection of 
// the tool on the torus collection of the plan.
class misToriBasedOrientationNavigationGuideObject : public misNavigationGuideObject
{
	misObjectMacro(misToriBasedOrientationNavigationGuideObject, misNavigationGuideObject);
	misObjectNewMacro(misToriBasedOrientationNavigationGuideObject);

public:
	// The properties of the object. Changing individual properties on the Properties object returned does not change the 
	// properties stored inside misOrientationNavigationGuideObject. You must create a misOrientationNavigationGideObjectSettings
	// object and pass it in as the new properties.
	void SetProperties(const misToriBasedOrientationNavigationGuideObjectProperties &newSettings);

	const misToriBasedOrientationNavigationGuideObjectProperties &GetProperties() const;

	virtual void UpdateRepresentation();

private:
	misToriBasedOrientationNavigationGuideObject(void);
	~misToriBasedOrientationNavigationGuideObject(void);

	// Adds the props for the two sets of tori to the list of props representing the spatial object. It is called at construction 
	// time and each time the properties are set. This is because setting properties on the two misCoaxialToriCollection objects 
	// causes their current actors to be invalidated and new torus actors to be created. Therefore, every time, the invalid props
	// must be cleared from the internal spatial object list and the new ones must be added.
	void AddTorusProps();

	// The collection of coaxial tori representing position and orientation of the tracking tool.
	misCoaxialToriCollection m_ToriCollectionForTool;

	// The collection of coaxial tori representing position and orientation of the planned screw.
	misCoaxialToriCollection m_ToriCollectionForPlan;

	misToriBasedOrientationNavigationGuideObjectProperties m_Properties;	// See SetProperties()
};

