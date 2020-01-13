#include "misNavigationGuideObject.h"
#include "misPlanAxisNavigationGuideObjectProperties.h"
#include "misnavigationguideobject.h"

// The misPlanAxisNavigationGuideObject class provides a navigation guide to help the clinician position the tool tip on the 
// plan axis. It displays a guiding arrow indicating the corrective translational movement that must be applied to the tool 
// tip. The arrow indicates the shortest path (perpendicular) that meets the plan axis.
class misPlanAxisNavigationGuideObject : public misNavigationGuideObject
{
	misObjectMacro(misPlanAxisNavigationGuideObject, misNavigationGuideObject);
	misObjectNewMacro(misPlanAxisNavigationGuideObject);

public:
	~misPlanAxisNavigationGuideObject(void);

	// Overrides abstract base. It calculates the vector that maps current position of the tool tip to the plan start point, and 
	// applies such a transform to the navigator guide prop (a guiding arrow) to demonstrate the required corrective translative 
	// movement of the tool tip. Calls to UpdateRepresentation() will fail if the NavigationState has not been set.
	virtual void UpdateRepresentation();

	// The object holding the properties (settings) for this guide object. To modify the settings, the properties object must be
	// set rather than modifying its attributes.
	void SetProperties(const misPlanAxisNavigationGuideObjectProperties &newSettings);
	const misPlanAxisNavigationGuideObjectProperties &GetProperties() const;

	void GetGuideStartPoint(double *startPoint);
	void GetGuideEndPoint(double *endPoint);

protected:
	// Creates and initializes the navigation guide spatial object. It creates, initializes and adds the guiding arrow to the list 
	// of props and sets the default settings.
	misPlanAxisNavigationGuideObject(void);

private:
	vtkSmartPointer<vtkActor> m_ArrowActor;	// The actor used to represent the guiding arrow on the renderer

	// The actor used to display the magnitude of angular displacement in degrees
	vtkSmartPointer<vtkCaptionActor2D> m_CaptionActor;

	// The string representation of the required angular displacement in degrees. It's kept here so the ASCIIZ pointer passed to the
	// caption actor is not invalidated during the life-time of the object.
	std::string m_CaptionString;

	// Keeps track of the distance from tool tip position (length of the nearest path to) the plan axis
	double m_DistanceFromPlanAxis;

	// Current position of the guide arrow actor. Used by GetSpatialPosition().
	double m_GuideStartPoint[3];

	// Current start position of the guide arrow actor. 
	double m_GuideEndPoint[3];

	misPlanAxisNavigationGuideObjectProperties m_Properties;	// See SetProperties().
};

