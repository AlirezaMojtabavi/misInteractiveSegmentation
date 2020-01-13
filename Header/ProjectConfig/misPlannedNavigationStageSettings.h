#pragma once

#include "misCameraAutomaticZoomControllerProperties.h"
#include "misMacros.h"
#include "misOrientationNavigationGuideObjectSettings.h"
#include "misPlanAxisNavigationGuideObjectProperties.h"
#include "misToriBasedOrientationNavigationGuideObjectProperties.h"
#include "serializable.h"

// The misPlannedNavigationStageSettings class is a wrapper for the settings used by misPlannedNavigationStage objects. It is 
// serializable so it can be read from a file and set to the object.
class misPlannedNavigationStageSettings : public Serializable
{
	// The view coordinates of the orientation navigation guide arrow (arrow start point) on the stage
	misPrivate3VectorVariableWithPublicAccessorsMacro(
		double, m_OrientationGuideArrowViewPosition, OrientationGuideArrowViewPosition);

	// Visual scale factor of the orientation navigation guide arrow. Use this to enlarge or shrink the arrow regardless of 
	// current stage zoom (which is controlled automatically).
	misPrivateVariableWithPublicAccessorsMacro(double, m_OrientationGuideArrowVisualScale, OrientationGuideArrowVisualScale);

	// Distance, in world coordinates, of the stage camera focal point from the plan start point along the negative plan axis, 
	// that is, plan end point to plan start point.
	misPrivateVariableWithPublicAccessorsMacro(double, m_CameraFocalPointDistanceFromPlan, CameraFocalPointDistanceFromPlan);

	// Initial distance, in world coordinates, of the stage camera position from the plan start point along the negative plan axis, 
	// that is, plan end point to plan start point. The camera distance is subsequently modified by the automatic zoom controller.
	misPrivateVariableWithPublicAccessorsMacro(double, m_CameraPositionDistanceFromPlan, CameraPositionDistanceFromPlan);

	// The length, in world measures, of the tracking tool used for navigation. This is used to place the orientation navigation 
	// guide mark near the tail end of the tool.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ToolLength, ToolLength);

	// The properties object for the orientation navigation guide.
	misPrivateVariableWithPublicAccessorsMacro(
		misOrientationNavigationGuideObjectSettings, m_OrientationNavigationGuideProperties, OrientationNavigationGuideProperties);

	// The properties object for the tori based navigation guide.
	misPrivateVariableWithPublicAccessorsMacro(
		misToriBasedOrientationNavigationGuideObjectProperties, m_ToriBasedOrientationNavigationGuideProperties, 
		ToriBasedOrientationNavigationGuideProperties);

	// The properties object for the plan axis guide.
	misPrivateVariableWithPublicAccessorsMacro(
		misPlanAxisNavigationGuideObjectProperties, m_PlanAxisNavigationGuideProperties, PlanAxisNavigationGuideProperties);

	// The properties object for the automatic camera zoom controller.
	misPrivateVariableWithPublicAccessorsMacro(
		misCameraAutomaticZoomControllerProperties, m_ZoomControllerProperties, ZoomControllerProperties);

public:
	misPlannedNavigationStageSettings(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );

	double GetRadiusGrayZoneThreshold();
	double GetRadiusYellowZoneThreshold();
	double GetRadiusGreenZoneThreshold();
	double GetHeightGrayZoneThreshold();
	double GetHeightYellowZoneThreshold();
	double GetHeightGreenZoneThreshold();

private:
	double m_RadiusGrayZoneThreshold;
	double m_RadiusYellowZoneThreshold;
	double m_RadiusGreenZoneThreshold;
	double m_HeightGrayZoneThreshold;
	double m_HeightYellowZoneThreshold;
	double m_HeightGreenZoneThreshold;
};


	