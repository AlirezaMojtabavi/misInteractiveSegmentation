#pragma once

#include "misNavigationGuideObject.h"
#include "misOrientationNavigationGuideObjectSettings.h"

// The misOrientationNavigationGuideObject class provides a navigation guide to help the clinician orientate the tool along the 
// axis joining plan start to plan end, assuming that the tool tip is spatially fixed. It displays a guiding arrow indicating the 
// corrective angular displacement that must be applied to the tool handle (while keeping the tip fixed in place). The 
// scale of the arrow is a measure of the angular displacement required.
class misOrientationNavigationGuideObject : public misNavigationGuideObject
{
	misObjectMacro(misOrientationNavigationGuideObject, misNavigationGuideObject);
	misObjectNewMacro(misOrientationNavigationGuideObject);

	// The length, in world measures, of the tracking tool used for navigation. This is used to place the guide mark near the tail 
	// end of the tool.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ToolLength, ToolLength);

	// The scale of the guide arrow regardless of current angular deviation. Could be used to keep the visual size of the 
	// guide arrow relatively fixed at fixed angular deviations even though the camera zoom might change.
	misPrivateVariableWithPublicAccessorsMacro(double, m_Scale, Scale);

	// Gets/sets the world position of the the guide arrow tip (could be used by the owning stage to control the view position 
	// of the guide object or keep it fixed in the view).
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_GuideStartPoint, GuideStartPoint)

public:
	// Overrides abstract base. It calculates deviation of the tool from the orientation of the planned arrow and applies such a 
	// transform to the navigator guide prop (a guiding arrow) to demonstrate the required corrective angular movement of the tool 
	// handle. Calls to UpdateRepresentation() will fail if the NavigationState has not been set.
	virtual void UpdateRepresentation();

	// Gets the property object of the actor used for representing the navigator object.
	virtual vtkProperty* GetActorProperty();

	// Gets the caption actor used to display the magnitude of angular displacement in degrees.
	virtual vtkSmartPointer<vtkCaptionActor2D> GetCaptionActor();

	// Gets the world position of the the guide arrow tip
	void GetGuideEndPoint(double *endPoint);

	// The properties of the object. Changing individual properties on the Properties object returned does not change the 
	// properties stored inside misOrientationNavigationGuideObject. You must create a misOrientationNavigationGideObjectSettings
	// object and pass it in as the new properties.
	void SetProperties(const misOrientationNavigationGuideObjectSettings &newSettings);
	const misOrientationNavigationGuideObjectSettings &GetProperties() const;

	virtual ~misOrientationNavigationGuideObject() { }

protected:
	// Creates and initializes the navigation guide spatial object. It creates, initializes and adds the guiding arrow to the list 
	// of props and sets the default ThresholdAngle to 90.
	misOrientationNavigationGuideObject();

private:
	vtkSmartPointer<vtkActor> m_ArrowActor;	// The actor used to represent the guiding arrow on the viewer

	// The actor used to display the magnitude of angular displacement in degrees
	vtkSmartPointer<vtkCaptionActor2D> m_CaptionActor;

	// The string representation of the required angular displacement in degrees. It's kept here so the ASCIIZ pointer passed to the
	// caption actor is not invalidated during the life-time of the object.
	std::string m_CaptionString;

	// Current start position of the guide arrow actor. 
	double m_GuideEndPoint[3];

	misOrientationNavigationGuideObjectSettings m_Properties;	// Active settings. See SetProperties()
};
