#pragma once

#include "misObject.h"
#include "misRenderer.h"
#include "misWindow.h"

// The misStageBase class provides the basic implementation for all stage classes. Stage classes contain a window, a viewer, 
// subclass specific spatial objects, and widgets for controlling the view. The stage base provides the window, viewer, and some
// basic configuration.
class misStageBase : public misObject
{
	misObjectMacro(misStageBase, misObject);

public:
	misStageBase(void);
	~misStageBase(void);

	// Asks the underlying window object to render its display area. Must be called after some internal stage parameters have been
	// altered to update the view.
	void Render();

	// Sets the camera clipping planes (normal to the camera axis).
	void SetClippingPlanes(double nearPlane, double farPlane);

	// Gets the active camera in use by the renderer object. This can be used by subclasses to customize their view. Client objects
	// may use this method to customize camera behaviour and also get current camera configuration of the stage.
	virtual vtkCamera* GetActiveCamera();

protected:
	// Adds a spatial object to the underlying renderer. The next call to Render() will display the object.
	virtual void AddSpatialObject(misSpatialObject::Pointer spatialObject);

	// After a change to internal state of the derived class, spatial objects must be updated before they can be rendered to the 
	// display. Therefore UpdateSpatialObjects() is called by the Render() method before performing the rendering. This must be 
	// overridden by subclasses to reflect changes to their internal state on their spatial objects.
	virtual void UpdateSpatialObjects();

	// Gets the length, in view port measures, of a unit vector at the given world point that is perpendicular to the perspective 
	// line, i.e., the line connecting camera position to the given point. It can be used get the displayed proportions of a world 
	// spatial object so the stage might be able to scale it to a certain size no matter what the camera position is.
	double GetWorldPointDifferentialInViewCoordinates(const double *worldPoint);

	void ConvertViewToWorldCoordinates(const double *viewPoint, double *worldPoint);

	// Initializes the stage by creating the underlying misWindow object, initializing the underlying misRenderer object 
	// and embedding the misWindow within the native window with the specified handle.
	// It must be called by deriving classes (possibly within a specialized initialization method).
	virtual void Initialize(misRenderer::RendererType rendererType, HWND nativeWindowHandle);

	// Initializes the stage by creating the underlying misWindow object, initializing the underlying misRenderer object 
	// and embedding the misWindow within the native window specified by the given misWindowModel.
	// It must be called by deriving classes (possibly within a specialized initialization method).
	virtual void Initialize(misRenderer::RendererType rendererType, const misWindowModel &windowModel);

private:
	// Creates and initializes the renderer of the specified type and adds it to the stage misWindow. It is called by both overloads
	// of Initialize().
	virtual void InitializeRenderer(misRenderer::RendererType rendererType);

	misRenderer::Pointer m_Renderer;	// The whole stage will be set in this renderer.

	misWindow m_Window;	// The windows containing the stage view, interactor, etc.

	bool m_IsInitialized;	// Determines whether the stage object has been initialized
};

