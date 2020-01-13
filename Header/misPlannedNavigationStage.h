#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ITrackingTool.h"
#include "misCameraAutomaticZoomController.h"
#include "misCoaxialToriCollection.h"
#include "misNavigationState.h"
#include "misOrientationNavigationGuideObject.h"
#include "misPlanAxisNavigationGuideObject.h"
#include "misPlanDepthNavigationGuideObject.h"
#include "misPlanStartNavigationGuideObject.h"
#include "misPlannedNavigationStageSettings.h"
#include "misPlannedScrewSpatialObject.h"
#include "misStageBase.h"
#include "misToriBasedOrientationNavigationGuideObject.h"
#include "misTrackingToolSpatialObject.h"

// The misPlannedNavigationStage class sets the stage for planned navigation. It contains a viewer, navigational spatial objects, 
// and widgets for controlling the view. In planned navigation, the position of the starting and ending point of a plan is first 
// specified. Afterwards, setting the tracker tool position and orientation will update the spatial objects.
// When the surgeon plans a screw within the bone structure, the starting point is where the penetrating end of the screw is placed
// and the ending point is the other.
// The viewer does not have a default interaction style set for the renderer. The viewer camera is positioned along the plan axis
// looking from the plan start to plan end. The camera zoom is automatically controlled to fit all the navigational objects on the
// screen and the view-up is set using a dedicated CameraConfig tracking tool.
class misPlannedNavigationStage : public misStageBase
{
	misObjectMacro(misPlannedNavigationStage, misStageBase);
	misObjectNewMacro(misPlannedNavigationStage);

public:
	// The CameraParameters specifies the rendering camera configuration at a certain time. This can be used by the owner of this
	// to synchronize other viewers and renderers with this one. The definition of each of these parameters is equivalent to 
	// their synonymous parameters in a vtkCamera object.
	struct CameraParameters
	{
		CameraParameters() { }

		CameraParameters(const CameraParameters& other)
		{
			std::copy(other.m_CameraPosition, other.m_CameraPosition + 3, m_CameraPosition);
			std::copy(other.m_FocalPoint, other.m_FocalPoint + 3, m_FocalPoint);
			std::copy(other.m_ViewUp, other.m_ViewUp + 3, m_ViewUp);
		}

		double m_FocalPoint[3];
		double m_CameraPosition[3];
		double m_ViewUp[3];
	};

	// Sets the navigation tracking tool UID. At all times, the planned navigation involves updating guides that demonstrate 
	// how this tracking tool could be brought to the position of the plan.
	void SetNavigationToolTipUid(const std::string& toolUid);

	// Sets the UID of the tracking tool that will be used for camera view up configuration. The direction from the specified
	// tracking tool towards the plan axis is taken as the view-up vector of the camera, that is the vector standing upright 
	// within the 2D display.
	void SetViewConfigToolUid(const std::string& toolUid);

	void SetPlanCoordinateSystemUid(const std::string& coordSysUid);

	~misPlannedNavigationStage(void);
	
	// Gets the object holding the collection of properties and settings of the stage and its composite objects.
	void SetProperties(const misPlannedNavigationStageSettings &newProperties);
	const misPlannedNavigationStageSettings &GetProperties() const;

	// Set the planned start point (screw tip) in Cartesian world coordinates.
	void SetPlanStartPoint(double startPoint[3]);

	// Set the planned end point (screw bottom) in Cartesian world coordinates.
	void SetPlanEndPoint(double endPoint[3]);

	// Initializes the navigation stage by actually creating the underlying rendering pipeline and embedding it within the native
	// window with the specified handle. A correlation manager must also be provided for the initialization to be completed.
	virtual void Initialize(
		HWND nativeWindowHandle, std::shared_ptr<const  ICoordinateSystemCorrelationManager<std::string> > correlationManager);

	// Initializes the navigation stage by actually creating the underlying rendering pipeline and embedding it within the window
	// with the native handle and other data encapsulated within the specified misWindowModel. A correlation manager must 
	// also be provided for the initialization to be completed.
	virtual void Initialize(const misWindowModel &windowModel, 
		std::shared_ptr<const  ICoordinateSystemCorrelationManager<std::string> > correlationManager);

	// Rotates navigation stage camera view to the specified extent around the plan axis. Use negative values for clockwise and
	// positive values for counter-clockwise rotation.
	virtual void RotateView(double degrees);

	// Gets current render camera parameters as determined by zoom controller, camera config tool, etc.
	CameraParameters GetCameraParameters() const ;
	
protected:
	// Creates a misPlannedNavigationStage object in uninitialized state.
	misPlannedNavigationStage();

	// After a change to navigation state, UpdateSpatialObjects() is called by superclass to have all navigational spatial objects 
	// recalculate their current position and reform their representation accordingly.
	virtual void UpdateSpatialObjects() override;

	// Should be called whenever the plan coordinates are changed so the stage attributes related to the plan are updated.
	void ReconsiderPlan();

private:
	// Adds navigation stage specific spatial objects to the underlying stage as a part of stage initialization. It is called by 
	// different overloads of Initialize(). A correlation manager must also be provided for the initialization to be completed.
	void PerformInitialization(std::shared_ptr<const  ICoordinateSystemCorrelationManager<std::string> > correlationManager);

	// Updates the navigations state based on the tracking tool coordinates.
	void UpdateNavigationState();

	// Computes the camera position so that the view is normal to the plan axis, the plan start point being near the camera and
	// the plan end point far from it. It is called whenever any of the plan points or the camera config tool are modified in order 
	// to update the view.
	void ComputeCameraParameters();

	// Sets current coverage points for the camera zoom controller and updates it. It is called by ComputeCameraParameters().
	void UpdateZoomController();

	// Justifies the scale and position of abstract spatial objects so their sizes and positions remain visually fixed even 
	// though the camera position and zoom is constantly changing. 
	void JustifySpatialObjectsInView();

	// Navigation state (planned points and tool position and orientation) is referenced and used by navigation spatial objects.
	misNavigationState::Pointer m_NavigationState;

	// This guide spatial object provides a visual representation of the angular correction required to be performed by the surgeon.
	misOrientationNavigationGuideObject::Pointer m_OrientationNavigationGuide;

	// The navigation guide object that uses tori for navigation (auxiliary to the guiding arrows).
	misToriBasedOrientationNavigationGuideObject::Pointer m_ToriBasedOrientationGuide;

	// This guide object provides a visual representation of the spatial translation required to be performed on the tool to place
	// the tool tip position of the plan axis. This guide, at any time, provides a direction perpendicular to the plan axis, that
	// is, the nearest path to the plan axis.
	misPlanAxisNavigationGuideObject::Pointer m_PlanAxisNavigationGuide;

	// This guide object provides a visual representation of the projected position of the tool tip along the plan axis and
	// informs the clinician how far the tool is from the entry point, and when entered, how further to advance before the end
	// is reached. It also informs the clinician whether the tool has gone beyond plan end point and how far.
	misPlanDepthNavigationGuideObject::Pointer m_PlanDepthNavigationGuide;

	// The spatial object representing the planned screw in space. Current configuration places the plan at the center of the view
	// and the camera axis is parallel to plan axis. So, not much is seen.
	misPlannedScrewSpatialObject::Pointer m_ScrewObject;

	// Used to automatically control the zoom level of the stage active camera to optimally fit all the spatial objects.
	misCameraAutomaticZoomController::Pointer m_ZoomController;

	std::shared_ptr<const  ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;

	bool m_IsInitialized;	// Determines whether the stage has been properly initialized
	std::string m_NavigationToolTipUid, m_ViewConfigToolUid, m_PlanCoordinateSystemUid;

	misPlannedNavigationStageSettings m_Properties;	// See SetProperties()
	
	CameraParameters m_CameraParameters;	// See GetCameraParameters
};

