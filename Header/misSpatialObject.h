#pragma once

#include "misObject.h"

// The misSpatialObject class is the base for all visual objects that can be rendered and displayed by a misViewer object. As such,
// the misViewer object can have an aggregate of misSpatialObject instances. This class is abstract and only its subclasses can be
// constructed. misSpatialObject's are different than igstk::SpatialObject's in that the former do not require a corresponding 
// representation in order to be displayed in an misViewer object.
class misSpatialObject : public misObject
{
	misObjectMacro(misSpatialObject, misObject)

public:
	typedef std::list< vtkSmartPointer<vtkProp> > PropsListType; 
	typedef itk::BoundingBox<double, 3> BoundingBoxType;

	// The visibility of the spatial object determines whether the viewer object will display the contained props.
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_Visibility, Visibility);

	// Gets a list of all the props contained within this spatial object.
	virtual const PropsListType &GetProps() const;

	// A user transform that the misSpatialObject must apply to all its contained props. Triggers call to CalculateBoundingBox().
	virtual void SetUserTransform(vtkSmartPointer<vtkTransform> transform);
	virtual vtkSmartPointer<vtkTransform> GetUserTransform() const;

	// Gets the bounding box enclosing all the props within the object and stores them within the given array. Can be used to 
	// determine camera parameters in such a way as to have all the props belonging to the spatial objects within the view.
	bool GetBoundingBox(double bounds[6]) const;

protected:
	misSpatialObject();
	virtual ~misSpatialObject();

	// AddProp is used by derived classes to add props to the list of contained props. Triggers call to CalculateBoundingBox().
	virtual void AddProp(vtkSmartPointer<vtkProp> prop);

	// DeleteProp is used by derived classes to delete props from the list of contained props. See AddProp()
	virtual void DeleteProp(vtkSmartPointer<vtkProp> prop);

	// Clears the list of props contained props. Used by subclasses to reset their state, etc. See AddProp()
	virtual void ClearProps();

	// CalculateBoundingBox calculates the bounding box of that encloses all the props within GetProps() and return true for success 
	// and false for failure. This method should called when either a user transform is applied to the object or a new prop object 
	// is added. In the latter case AddProp() automatically calls CalculateBoundingBox. The calculated bounding box is returned 
	// through the bounds parameter.  Deprecated.
	virtual bool CalculateBoundingBox( double bounds[6] );

private:
	// List of actors that constitute spatial representation of this spatial object
	PropsListType m_PropsList;

	// The bounding box enclosing all the props contained. See CalculateBoundingBox(), GetBoundingBox()
	double m_BoundingBox[6];

	bool m_IsBoundingBoxCalculated;	// Determines whether the value of m_BoundingBox is valid (CalculateBoundingBox succeeded)
	
	// The custom transform to be applied to all the props contained. See SetUserTransform()
	vtkSmartPointer<vtkTransform> m_Transform;
};

typedef std::list<misSpatialObject::Pointer> misSpatialObjectListType;