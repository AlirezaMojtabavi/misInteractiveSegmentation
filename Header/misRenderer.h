#pragma once

#include "misObject.h"
#include "misSpatialObject.h"

// The misRenderer class is used aggregate different spatial objects and representations into a single container and display them
// on a common renderer object. Call Initialize() to prepare the viewer before use. 
class misRenderer : 	public misObject
{
	misObjectMacro(misRenderer, misObject);
	misObjectNewMacro(misRenderer);

public:
	// Used to specify the type of internal renderer used.
	enum RendererType
	{
		RT_IMAGE_RENDERER,
		RT_VOLUME_RENDERER,
		RT_DEFAULT_RENDERER
	};

	misRenderer(void);
	virtual ~misRenderer(void);

	// Must be called before using the renderer to create the underlying vtkRenderer object of the specified type.
	void Initialize(RendererType rendererType);

	// Adds a spatial object to the viewer. The next call to Render() will display the object.
	virtual void AddSpatialObject(misSpatialObject::Pointer spatialObject);

	// Removes a previously added spatial object from the viewer. It will disappear on the next call to render().
	virtual void RemoveSpatialObject(misSpatialObject::Pointer spatialObject);

	// Reset the renderer state to its initial state and removes all the spatial objects.
	virtual void Reset();

	// Get the internal vtkRender object used for rendering. It must be used by the misWindow object to which this renderer is 
	// added.
	vtkRenderer* GetRenderer();

	// Asks the underlying renderer object to render and display all the contained spatial objects.
	void Render();

	double* GetBounding();

	// Checks whether a spatial object is fit for being added to the viewer (not empty and not already added).
	bool CheckNewSpatialObjectValidity(misSpatialObject::Pointer spatialObject);

private:
	void UpdateBoundingBox(void);

	vtkSmartPointer<vtkRenderer> m_Renderer;	// The renderer object in charge of rendering the spatial objects, etc.
	misSpatialObjectListType m_SpatialObjects;	// List of contained spatial objects that are viewed and managed by this viewer.
	double m_BoundingBox[6];
};

