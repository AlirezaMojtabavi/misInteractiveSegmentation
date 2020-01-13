#ifndef misSurfaceRepresentation_H_HEADER_INCLUDED_B7FB56C9
#define misSurfaceRepresentation_H_HEADER_INCLUDED_B7FB56C9

#include "misRepresentation.h"

class vtkFollower;
class vtkLineSource;
class vtkTextSource;
class vtkmapper;
class vtkActor;
class vtkProperty;

//This class provides some convenient methods to help programmers change properties of actors and
//also set a camera to actors of type misFollowerFixedArea to face the camera all of the time
class   misSurfaceRepresentation : public misRepresentation
{

public:

 
	//Set the color to all actors of the class. r,g and b values must be between 0~1
	virtual void SetColor(float r,float g,float  b);

	//Sets opacity to all actors of the object
	virtual void SetOpacity(double opacity);

	//connects the input polyData to a new actor and pushes the new actor into the list of actors. the 
	//property represents the property of polyData and also puts the number of actors into m_BoundingActorsUpdated
	virtual vtkActor* AddPolyData(vtkPolyData* polyData, vtkProperty* property = 0);

	//connects the input polyData to a new actor and pushes the new actor into the list of actors. the 
	//property represents the property of polyData and also puts the number of actors into m_BoundingActorsUpdated
	virtual vtkActor* AddPolyData(vtkAlgorithmOutput* polyData, vtkProperty* property = 0);


	//Makes a new instance of misSurfaceRepresentation and replicates and 
	//adds all actors to the newly generated object
	std::shared_ptr<misSurfaceRepresentation> CreateInstance();

	//Sets camera to object of type misFollowerFixedArea if exist in the list of actors
	void SetCamera(vtkCamera* pCamera);


	misSurfaceRepresentation(std::string name ):misRepresentation(name) 
	{
	}

	virtual ~misSurfaceRepresentation()
	{
	}
};

#endif /* misSurfaceRepresentation_H_HEADER_INCLUDED_B7FB56C9 */
