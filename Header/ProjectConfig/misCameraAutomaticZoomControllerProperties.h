#pragma once

#include "misMacros.h"
#include "serializable.h"

// The misCameraAutomaticZoomControllerProperties class provides a serializable container for the settings and properties required
// for initialization of a misCameraAutomaticZoomController object. 
class misCameraAutomaticZoomControllerProperties : public Serializable
{
	// The ratio used to increase (or decrease) the view angle of the camera after it has been determined by coverage points. If
	// the ratio is set to 1, one of the coverage points will fall on the border of the view port. To bring it further in, the ratio
	// must be set to a value slightly greater than 1.
	misPrivateVariableWithPublicAccessorsMacro(double, m_AngleRatio, AngleRatio);

	// The ratio of the threshold distance and the camera focal distance. The threshold distance is the distance that determines
	// if the distance of the camera should be increased. If any of the points fall behind the threshold plane (normal to the camera
	// axis) looking from the focal point, the camera is moved away from the focal point (kept fixed) to increase the distance and
	// fit the point within the threshold range.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ThresholdRatio, ThresholdRatio);

	// The factor by which the camera distance is increased or decreased when the view angle is below the minimum or above the 
	// maximum angle.
	misPrivateVariableWithPublicAccessorsMacro(double, m_DistanceModificationFactor, DistanceModificationFactor);

	// The minimum view angle of the camera. If the calculated view angle is below this measure, the camera is moved toward the
	// focal point using DistanceModificationFactor and calculation is performed again (up to three times).
	misPrivateVariableWithPublicAccessorsMacro(double, m_MinimumAngle, MinimumAngle);

	// The maximum view angle of the camera. If the calculated view angle is above this measure, the camera is moved away from the
	// focal point using DistanceModificationFactor and calculation is performed again (up to three times).
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumAngle, MaximumAngle);

	// The minimum focal distance of the camera. No matter how small the calculated view angle, the focal point will not be moved 
	// closer than this measure to the camera.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MinimumDistance, MinimumDistance);

	// The maximum focal distance of the camera. No matter how great the calculated view angle, the focal point will not be moved 
	// further than this measure away from the focal point.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumDistance, MaximumDistance);

	// The maximum number of times the calculation of the view angle is performed if it is not within the acceptable range.
	misPrivateVariableWithPublicAccessorsMacro(int, m_MaximumAngleCalculationPasses, MaximumAngleCalculationPasses);

public:
	misCameraAutomaticZoomControllerProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );

};

