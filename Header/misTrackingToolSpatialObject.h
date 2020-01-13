#pragma once

#include "misSpatialObject.h"
#include "misToolData.h"

// The misTrackingToolSpatialObject provides a spatial representation of a tracking tool that can be added to a misRenderer object
// and have it displayed and its spatial configuration constantly updated.
class misTrackingToolSpatialObject : public misSpatialObject
{
	misObjectMacro(misTrackingToolSpatialObject, misSpatialObject);
	misObjectNewMacro(misTrackingToolSpatialObject);

	// The length, in world measures, of the tracking tool used for navigation. This is used to place the guide mark near the tail 
	// end of the tool.
	void SetToolLength(double length);
	double GetToolLength();

public:
	virtual ~misTrackingToolSpatialObject(void);


	// Updates the representation of this spatial object based on the current tracking tool position and orientation.
	void UpdateRepresentation(vtkSmartPointer<vtkTransform> toolFinalTransform);

protected:
	misTrackingToolSpatialObject(void);

private:

	// Creates the polydata used to represent the tool body. The polydata is assumed to be a representation of the tool orientated
	// along the Z axis and placed at (0, 0, 0). It is transformed according to current tool transform.
	void CreateRepresentation();


	// The final tool transform is stored here on every navigation update. It is declared globally so we won't have to create it 
	// every time.
	vtkSmartPointer<vtkTransform> m_ToolFinalTransform;

	// The prop3d object that is used to represent the spatial position and orientation of the tracking tool. Its position and 
	// orientation is updated by UpdateRepresentation(). It is created by CreateRepresentation().
	vtkSmartPointer<vtkProp3D> m_RepresentationProp;

	// Length of the tool representation in world coordinates scale.
	double m_ToolLength;
};
