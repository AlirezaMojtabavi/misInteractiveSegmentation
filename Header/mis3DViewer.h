#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRenderer.h"
#include "MIS3DInteractionStyle.h"
#include "misAxisProperty.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "misImageAnnotation.h"
#include "misObject.h"
#include "misSimpleDataPackage.h"
#include "misSpatialObject.h"
#include "misTextRepresentation.h"
#include "misViewerTypeDirection.h"
#include "IWindows.h"
#include "I3DViewer.h"

//#include "misROIWidget.h"

#define  MAX_IMAGE_WIDTH 512.0

// The mis3DViewer class is used to aggregate different spatial objects and representations into a single container and display them
// within a common window.
class mis3DViewer :  public I3DViewer
{
 
	

public:
 
	mis3DViewer(vtkPicker* picker);
	virtual ~mis3DViewer();


	// Gets/sets whether the viewer should render contents to the underlying renderer; see m_Active.
	bool GetViewerActivity() const;	
	void SetViewerActivity(bool val);

	// Used only in tests to display a set of perpendicular axes.
	void AddAxis(misAxisProperty  axis);
	void AddAxis(double x, double y ,double z);
	
	// Adds/removes a representation object to the viewer to be displayed on the next call to render()
	virtual void AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation);
	// Adds/removes a representation object to the viewer to be displayed on the next call to render()
	virtual void AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer);

	virtual void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent);
	virtual void RemoveRepresentationByName(std::string name);
	
	// Return a list contains all representation by prvided name
	std::vector<std::shared_ptr<IRepresentation>> FindRepresentationByName(const std::string& name) override;

	// Adds a spatial object to the viewer. The next call to render() will display the object.
	virtual void AddSpatialObject(misSpatialObject::Pointer spatialObject);

	// Removes a previously added spatial object from the viewer. It will disappear on the next call to render().
	virtual void RemoveSpatialObject(misSpatialObject::Pointer spatialObject);
	
	// Adds the specified text as an annotationRepresentation to be displayed at the given coordinates on the render window.
	void AddAnnotation(char* Text, tgt::vec2 position);

	// Gets the vtkInteractionStyle object used by the underlying render window. It is an instance of MIS3DInteractionStyle created
	// on the first call to SetWindow().
	MIS3DInteractionStyle * Get3dStyleCamera();

	// Removes all representations and spatial objects from the viewer and resets the camera state.
	virtual void  Reset();
	// Resets the camera attached to the renderer to the state where all visible representations are in view.
	void ResetCamera();

	// Renders contained representation objects to the underlying render window if the viewer is active. See SetViewerActivity().
	virtual void Render();



	// Gets the underlying vtkRenderer object.
	vtkRenderer* GetRenderer();

	// Gets a list of representation objects contained within this viewer.
	RepresentionsListType GetRepresentation();

	// Gets the number of representation objects contained within this viewer.
	int GetNumberOfRepresentations();
	
	// Not used anywhere. Possible redundant code.
	//double*                GetBounding();

	// Ensures that all the vtkActor objects pertaining to all contained representation objects are added to the renderer (adds 
	// those that are not already added). Representation objects whose vtkActor's are not added to the renderer, are not displayed.
	void UpdateRepresentationActors();

	// Sets the render window which this viewer will occupy. It also configures the specified window for use with the viewer (sets
	// vtkInteractionStyle, attaches observers, ...)
	virtual void SetWindow(std::shared_ptr<Iwindows> pWindow, int index);
	std::shared_ptr<Iwindows> GetWindow() const;	// Gets the render window.
	misViewPort GetViewPort() const;
	void SetViewPort(const misViewPort& val);
	// Sets the cropping direction for volume rendering. This is in turn applied to all contained representations of type
	// misPartialVolumeBaseRepresentation.
	void SetCroppingDirection(misCroppingDirectionInVR croppingDirection);

	// Sets the focal point of the renderer camera to a default position. See UpdateFocalPoint()
	void SetDefaultFocalPoint(void);

	// Gets the default camera focal point position which might not be the same as current camera focal point. See UpdateFocalPoint.
	void GetDefaultFocalPoint( double focalPoint[3] );

 

	virtual bool ProcessRequest(const itk::EventObject* event) { return false; };
	
	// USED FOR DEBUGGING. Sets the frame rate to be displayed on the render window. See AddFPSRenderer()
	virtual void SetFPS(double fps);

	// USED FOR DEBUGGING. Adds a text representation to the renderer displaying the current frame rate. See SetFPS().
	void AddFPSRenderer();
	void ShowFPSOn();
	void ShowFPSOff();
	
	// USED FOR DEBUGGING. Gets the average amount of time that a single rendering operation takes.
	double GetAverageRenderTime(void);
	//Set coordinateSystemCorrelationManager for updating transform durin rendering 
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCoordianteSystemCorrelationManager() const;
	void SetCoordianteSystemCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val);
	
	virtual void UpdateWindowSize(misStrctWindowSize &size) ;

	bool IsWindowsSizeChanged() const override ;
	void GetWindowSize(int* size) const override ;
	RepresentionsListType GetRepresentations() const override;
	MIS3DInteractionStyle* Get3DStyle() const override;
	void Set3DStyle(MIS3DInteractionStyle* val) { m_3dStyle = val; }
	// Check the validity of the new representation object before adding so duplicates and empty pointers are not added.
	bool CheckNewRepresentationValidity(std::shared_ptr<IRepresentation> pRepresentation);
	auto GetWindowSizeUpdated() const { return m_WindowSizeUpdated; }
	void SetWindowSizeUpdated(int val0, int val1) override;
	const double* GetFocalPoint() const override;
	void SetFocalPoint(double val0, double val1, double val2);

	
	int GetIndexInGroup() const override;
	
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> GetCoordinateRenderers() const override;
	void SetCoordinateRenderers(std::vector<std::shared_ptr<ICoordinateSystemRenderer>> val) { m_CoordinateRenderers = val; }
	const double* GetBoundingBox() const;
	double GetScaleCameraPosition() const override;
	void SetScaleCameraPosition(double val);

	virtual MIS3DInteractionStyle* GetM_3dStyle() const override;


	virtual void SetM_3dStyle(MIS3DInteractionStyle* val) override;


	virtual void SetBoundingBox(double* val) override;

protected:

	// Handles WindowSizeChaged event from the viewer render window. Default implementation simply ignores this event. Subclasses 
	// might override this method to alter default behaviour.
	void WindowSizeChanged(itk::Object *caller, const itk::EventObject & event);
	
	// Check the validity of the new spatial object before adding so duplicates and empty pointers are not added.
	bool CheckNewSpatialObjectValidity(misSpatialObject::Pointer spatialObject);

	RepresentionsListType m_Representations;	// Contained representation objects.
	// call render of each ICoordinateSystemRenderer to update transform and set needed properties
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> m_CoordinateRenderers;
	vtkSmartPointer<vtkRenderer> m_Renderer;	// The renderer object in charge of rendering the spatial objects, etc.
	std::shared_ptr<Iwindows> m_Window;	// Window occupied by this viewer. See SetWindow().
	misViewPort m_ViewPort;
	int m_IndexInGroup;
	MIS3DInteractionStyle* m_3dStyle;	// vtkInteractionStyle object used by the render window. See Get3dStyleCamera().
	double m_BoundingBox[6];	// The coordinates of the smallest box bounding contained representation objects.
	//bool m_BoundingBoxUpdated;	
	double m_FocalPoint[3];	// Current default camera focal point. See UpdateFocalPoint()
	int	m_WindowSizeUpdated[2];

	
private:
	void UpdateAverageRenderTime( double elpsedTime );
	void UpdateBoundingBox();	// Update m_BoundingBox based on spatial geometry of contained representations.

	void UpdateFocalPoint();	// Updates default focal point position to be placed at the center of the bounding box.
	
	// check the last OpenGL error by glGetError and log results
	void LogOpenGLError();
	
	// Updates ICoordinateSystemRenderer  transforms for rendering 
	void UpdateCoordinateTransforms();

	misSpatialObjectListType m_SpatialObjects;	// List of contained spatial objects that are viewed and managed by this viewer.
	bool m_GlExtensionLoaded;	// Determines whether GL extensions have been already loaded. See LoadExtensions().
	std::shared_ptr<misTextRepresentation> m_pFpsReprsentation;	// Used to display frame rate on the viewer. See SetFPS().
	long m_RenderCount;	// Number of times rendering has been performed; used for computing average render time.
	double m_AverageRenderTime;	// Average amount of time that each render process takes in milliseconds.
	vtkTimerLog* m_Timer;	// Used for debugging and calculating average rendering time.
	bool m_Active;	// See SetViewerActivity().
	vtkCamera* m_pDiagonal;
	std::map<vtkCamera*, std::string> m_Camera;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CoordianteSystemCorrelationManager;
	bool m_ShowFPS;
 	double  m_ScaleCameraPosition;
	vtkPicker* m_Picker;
};



