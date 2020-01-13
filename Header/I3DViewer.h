#pragma once
#include "misViewerTypeDirection.h"
#include "ICoordinateSystemRenderer.h"
#include "MIS3DInteractionStyle.h"
#include "misAxisProperty.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "IRepresentation.h"
#include "misSpatialObject.h"
#include "IWindows.h"


typedef std::vector<std::shared_ptr<IRepresentation>> RepresentionsListType;
template < typename CST >
class ICoordinateSystemCorrelationManager;

class I3DViewer
{
public:
	// igstkStandardClassBasicTraitsMacro(mis3DViewer,misOldObject);
	// static Pointer New(void); 

	virtual ~I3DViewer() {};

	//void SetIntersectionSelectionStatus(bool status);
	//bool GetIntersectionSelectionStatus(void);

	// Gets/sets whether the viewer should render contents to the underlying renderer; see m_Active.
	virtual bool GetViewerActivity() const = 0;
	virtual void SetViewerActivity(bool val) = 0;

	// Used only in tests to display a set of perpendicular axes.
	virtual void AddAxis(misAxisProperty  axis) = 0;
	virtual void AddAxis(double x, double y, double z) = 0;

	// Adds/removes a representation object to the viewer to be displayed on the next call to render()
	virtual void AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation) = 0;
	// Adds/removes a representation object to the viewer to be displayed on the next call to render()
	virtual void AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer) = 0;

	virtual void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent) = 0;
	virtual void RemoveRepresentationByName(std::string name) = 0;

	// Return a list contains all representation by provided name
	virtual std::vector<std::shared_ptr<IRepresentation>> FindRepresentationByName(const std::string& name) = 0;

	// Adds a spatial object to the viewer. The next call to render() will display the object.
	virtual void AddSpatialObject(misSpatialObject::Pointer spatialObject) = 0;

	// Removes a previously added spatial object from the viewer. It will disappear on the next call to render().
	virtual void RemoveSpatialObject(misSpatialObject::Pointer spatialObject) = 0;

	// Adds the specified text as an annotationRepresentation to be displayed at the given coordinates on the render window.
	virtual void AddAnnotation(char* Text, tgt::vec2 position) = 0;

	// Gets the vtkInteractionStyle object used by the underlying render window. It is an instance of MIS3DInteractionStyle created
	// on the first call to SetWindow().
	virtual MIS3DInteractionStyle * Get3dStyleCamera() = 0;

	// Removes all representations and spatial objects from the viewer and resets the camera state.
	virtual void  Reset() = 0;


	// Resets the camera attached to the renderer to the state where all visible representations are in view.
	virtual void ResetCamera() = 0;

	// Renders contained representation objects to the underlying render window if the viewer is active. See SetViewerActivity().
	virtual void Render() = 0;

	// Gets the underlying vtkRenderer object.
	virtual vtkRenderer* GetRenderer() = 0;

	// Gets a list of representation objects contained within this viewer.
	virtual RepresentionsListType GetRepresentation() = 0;

	// Gets the number of representation objects contained within this viewer.
	virtual int GetNumberOfRepresentations() = 0;

	// Not used anywhere. Possible redundant code.
	//double*                GetBounding();

	// Ensures that all the vtkActor objects pertaining to all contained representation objects are added to the renderer (adds 
	// those that are not already added). Representation objects whose vtkActor's are not added to the renderer, are not displayed.
	virtual void UpdateRepresentationActors() = 0;

	// Sets the render window which this viewer will occupy. It also configures the specified window for use with the viewer (sets
	// vtkInteractionStyle, attaches observers, ...)
	virtual void SetWindow(std::shared_ptr<Iwindows> pWindow, int index) = 0;
	virtual std::shared_ptr<Iwindows> GetWindow() const = 0;	// Gets the render window = 0.
	virtual misViewPort GetViewPort() const = 0;
	virtual void SetViewPort(const misViewPort& val) = 0;
	// Sets the cropping direction for volume rendering. This is in turn applied to all contained representations of type
	// misPartialVolumeBaseRepresentation.
	virtual void SetCroppingDirection(misCroppingDirectionInVR croppingDirection) = 0;

	// Sets the focal point of the renderer camera to a default position. See UpdateFocalPoint()
	virtual void SetDefaultFocalPoint(void) = 0;

	// Gets the default camera focal point position which might not be the same as current camera focal point. See UpdateFocalPoint.
	virtual void GetDefaultFocalPoint(double focalPoint[3]) = 0;

	virtual bool ProcessRequest(const itk::EventObject* event) = 0;

	// USED FOR DEBUGGING. Sets the frame rate to be displayed on the render window. See AddFPSRenderer()
	virtual void SetFPS(double fps) = 0;

	// USED FOR DEBUGGING. Adds a text representation to the renderer displaying the current frame rate. See SetFPS().
	virtual void AddFPSRenderer() = 0;
	virtual void ShowFPSOn() = 0;
	virtual void ShowFPSOff() = 0;

	// USED FOR DEBUGGING. Gets the average amount of time that a single rendering operation takes.
	virtual double GetAverageRenderTime(void) = 0;
	//Set coordinateSystemCorrelationManager for updating transform durin rendering 
	virtual std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCoordianteSystemCorrelationManager() const = 0;
	virtual void SetCoordianteSystemCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val) = 0;

	virtual void UpdateWindowSize(misStrctWindowSize &size) = 0;


	virtual bool CheckNewRepresentationValidity(std::shared_ptr<IRepresentation> pRepresentation) = 0;

	virtual MIS3DInteractionStyle* GetM_3dStyle() const = 0;
	virtual void SetM_3dStyle(MIS3DInteractionStyle* val) = 0;
	virtual const double* GetBoundingBox() const = 0;
	virtual void SetBoundingBox(double* val) = 0;
	virtual void SetWindowSizeUpdated(int val0, int val1) = 0;
	virtual double GetScaleCameraPosition() const = 0;
	virtual RepresentionsListType GetRepresentations() const = 0;
	virtual const double* GetFocalPoint() const = 0;
	virtual int GetIndexInGroup() const = 0;
	virtual MIS3DInteractionStyle* Get3DStyle() const = 0;
	virtual std::vector<std::shared_ptr<ICoordinateSystemRenderer>> GetCoordinateRenderers() const = 0;
	virtual bool IsWindowsSizeChanged() const = 0;
	virtual void GetWindowSize(int* size) const = 0;
};
