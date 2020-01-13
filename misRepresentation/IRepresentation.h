#pragma once
#pragma once 

#include "misObject.h"
#include "misPolyDatasSpecifications.h"
 

class vtkActor;
class misApplicationSetting;
class vtkActorCollection;
class vtkAxes;
class vtkProp3D;
class vtkRenderer;
class vtkTransform;
class vtkProp;
// This class is the base for all spatial objects and the visual properties. These 

class IRepresentation
{
public:
	typedef std::vector< vtkSmartPointer<vtkProp> >   ActorsListType;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;

	virtual std::string GetObjectName() const = 0;
	virtual void SetObjectName(std::string val) = 0;
	virtual void SetRepresentationName(std::string name) = 0;
	virtual void AddProp(vtkProp*) = 0;

	//Sets the visibility of all actors of the list
	virtual void SetVisibilityOff(void) = 0;
	virtual void SetVisibility(bool value) = 0;
	virtual void SetVisibilityOn(void) = 0;

	//Returns the number of actors
	virtual int GetNumberOfActors() = 0;

	//Clears the list of actors. NOTICE this func may need to reset other things of the class???
	virtual void Reset() = 0;

	//Calls calculatedBoundingBox and then sets the position to all actors exist in list
	virtual void SetPosition(double position[3]) = 0;
	virtual void SetPosition(double x, double y, double z) = 0;

	//This method is virtual and may be overridden in derived class. Hence may
	//does some more actions rather than simply returning the position
	virtual double* GetPosition() const = 0;

	//Returns the position of the object and nothing more
	virtual void GetPosition(double position[3]) = 0;

	//Gets a vtkTransform and calls TransformDoublePoint(0,0,0) and then sets the result transform to all actors
	virtual void SetUserTransform(vtkTransform *transform) = 0;

	//returns actor located in i`th place of list. if index exceeds the valid index of actors, the function returns NULL
	virtual vtkProp* GetActor(int index) = 0;

 
 

	//calculates bounding box and sets it to m_BoundingBox class member. returning true means all things OK.
	virtual bool CalculatedBoundingBox() = 0;

	//Calls CalculatedBoundingBox and returns the calculated bounding box based on version of function used.
	//NOTICE: calling GetBoundingBox() method will not update m_BoundingBoxSimpleArray method.
	virtual itk::BoundingBox<double, 3, double>::Pointer GetBoundingBox() = 0;
	virtual bool GetBoundingBox(double *boundingBox) = 0;
	virtual ActorsListType GetActors() const = 0;
};

