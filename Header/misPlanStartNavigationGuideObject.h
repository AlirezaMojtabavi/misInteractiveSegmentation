#pragma once

#include "misNavigationGuideObject.h"

// The misPlanStartNavigationGuideObject class provides a navigation guide to help the clinician position the tool tip on the 
// plan start point. It displays a guiding arrow indicating the corrective translational movement that must be applied to the tool 
// tip. 

class misPlanStartNavigationGuideObject : public misNavigationGuideObject
{
	misObjectMacro(misPlanStartNavigationGuideObject, misNavigationGuideObject);
	misObjectNewMacro(misPlanStartNavigationGuideObject);

	// The threshold distance, in degrees, for scaling the guide. Distances greater than or equal to this will identically scale 
	// the guide, while smaller angles scale down the guide to the tool tip to start point distance and the threshold angle.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ThresholdDistance, ThresholdDistance);

	// The minimum scale of the guide mark. The guide mark shrinks linearly with the decreasing distance between tool tip and the
	// plan start point. This minimum keeps the guide mark from shrinking out of sight.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MinimumGuideScale, MinimumGuideScale);

	// The maximum scale of the guide mark. The guide mark grows linearly with the increasing distance between tool tip and the
	// plan start point. This maximum keeps the guide mark from growing out of convenience.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumGuideScale, MaximumGuideScale);

public:
	~misPlanStartNavigationGuideObject(void);

	// Overrides abstract base. It calculates the vector that maps current position of the tool tip to the plan start point, and 
	// applies such a transform to the navigator guide prop (a guiding arrow) to demonstrate the required corrective translative 
	// movement of the tool tip. Calls to UpdateRepresentation() will fail if the NavigationState has not been set.
	virtual void UpdateRepresentation();

	// Gets the property object of the actor used for representing the navigator object.
	virtual vtkProperty* GetActorProperty();
	
protected:
	// Creates and initializes the navigation guide spatial object. It creates, initializes and adds the guiding arrow to the list 
	// of props and sets the default settings.
	misPlanStartNavigationGuideObject(void);

private:
	vtkSmartPointer<vtkActor> m_Actor;	// The actor used to represent the guiding arrow on the renderer
	
	// The actor used to display the magnitude of angular displacement in degrees
	vtkSmartPointer<vtkCaptionActor2D> m_CaptionActor;

	// The string representation of the required angular displacement in degrees. It's kept here so the ASCIIZ pointer passed to the
	// caption actor is not invalidated during the life-time of the object.
	std::string m_CaptionString;
};

