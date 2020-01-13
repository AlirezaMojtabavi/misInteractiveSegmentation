#pragma once

#include "misNavigationState.h"
#include "misSpatialObject.h"

// The misNavigationGuideObject class is the base for all navigation guide spatial objects. It provides a simple interface for 
// setting the misNavigationState object and updating navigation guide representation. Each type of navigation guide provides 
// different correction guides such as orientation, distance, and position.
class misNavigationGuideObject : public misSpatialObject
{	
	misObjectMacro(misNavigationGuideObject, misSpatialObject);

public:
	virtual ~misNavigationGuideObject() { }

	// This signals the navigation guide spatial object that navigation state has changed and that should readjust its 
	// representation accordingly.
	virtual void UpdateRepresentation() = 0;

	// The navigation state object used by derived objects to adjust their representations in terms of guiding marks.
	misPrivateVariableWithPublicAccessorsMacro(misNavigationState::Pointer, m_NavigationState, NavigationState);
	
protected:
	misNavigationGuideObject() : m_NavigationState(NULL) { }
};

