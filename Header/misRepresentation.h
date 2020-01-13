#pragma once 

#include "misObject.h"
#include "misPolyDatasSpecifications.h"
#include "IRepresentation.h"
#include "misRepresentationContainer.h"

class vtkActor;
class misApplicationSetting;
class vtkActorCollection;
class vtkAxes;
class vtkProp3D;
class vtkRenderer;
class vtkTransform;

// This class is the base for all spatial objects and the visual properties. These 

class misRepresentation : public IRepresentation, public std::enable_shared_from_this<misRepresentation>
{
public:
	misRepresentation(std::string name);
	virtual ~misRepresentation() = default;

	typedef std::vector< vtkSmartPointer<vtkProp> >   ActorsListType; 

	std::string GetObjectName() const { return m_ObjectName; }
	void SetObjectName(std::string val) { m_ObjectName = val; }

	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *) override;


	virtual void InvokeEvent(const itk::EventObject& event) override;


	virtual bool HasObserver(const itk::EventObject & event) const override;

	misRepresentation::ActorsListType GetActors() const override;
	
 	//2 class members containing bounding box of the object. NOTICE that 
	//when you call some methods to get these values only one of them will be updated and the other one is not. Hence,
	//use appropriate function when you want to get bounding box
	itk::BoundingBox<double, 3, double>::Pointer m_BoundingBox;
	double m_BoundingBoxSimpleArray[6];
	//Sets the name of object
	void SetRepresentationName(std::string name);
	void AddProp(vtkProp*);

	//Sets the visibility of all actors of the list
	virtual void SetVisibilityOff(void);
	virtual void SetVisibility(bool value);
	virtual void SetVisibilityOn(void);
	//Returns the number of actors
	int GetNumberOfActors();


	//Clears the list of actors. NOTICE this func may need to reset other things of the class???
	virtual void Reset();

	//Calls calculatedBoundingBox and then sets the position to all actors exist in list
	virtual void SetPosition(double position[3]);
	virtual void SetPosition(double x, double y, double z);

	//This method is virtual and may be overridden in derived class. Hence may
	//does some more actions rather than simply returning the position
	virtual double* GetPosition() const;

	//Returns the position of the object and nothing more
	void GetPosition(double position[3]);

	//Gets a vtkTransform and calls TransformDoublePoint(0,0,0) and then sets the result transform to all actors
	virtual void SetUserTransform(vtkTransform *transform);

	//returns actor located in i`th place of list. if index exceeds the valid index of actors, the function returns NULL
	vtkProp* GetActor(int index);

	//Gets all actors of prep object and pushes them into the list containing actors of current object. This
	//means after calling this method, we have actors of ours and also actors of prep object in one list
	void AttachRepresentation(misRepresentation* prep);

	//calculates bounding box and sets it to m_BoundingBox class member. returning true means all things OK.
	bool CalculatedBoundingBox();

	//Calls CalculatedBoundingBox and returns the calculated bounding box based on version of function used.
	//NOTICE: calling GetBoundingBox() method will not update m_BoundingBoxSimpleArray method.
	itk::BoundingBox<double, 3, double>::Pointer GetBoundingBox();
	virtual bool GetBoundingBox(double *boundingBox);



	//represents a user transform and will be set by calling SetUserTransform
	vtkTransform*  m_pUserTramsform;
	//misApplicationSetting* m_AppSetting;

 protected:

	//Name
	std::string m_ObjectName;

	//List of actors embedded in this representation
	ActorsListType  m_Actors;
 

	//refer to position of (0,0,0) of  this object in new  world coordinates??????????
	double          m_Position[3];
	
	//more than a flag!
	int   m_BoundingActorsUpdated;
	void AddActors(vtkActorCollection* pActorCollection);



private:

	misRepresentationContainer::Pointer m_DummyObject = misRepresentationContainer::New();
};

