#pragma once

#include "mislandMarkPosAndStatusStr.h"

// The misRegistration class provides a wrapper around the IGSTK Landmark3DRegistration class to hide away the request/callback
// structure of IGSTK. It also provides a collinearity check (checked by IGSTK but not reported except as registration failure)
// that uses the same algorithm as used by IGSTK. Here, the moving coordinate system corresponds with the tracker and the fixed
// coordinates system with that of image.
class misLandmarkRegistration
{
public:
	typedef itk::Point<double, 3> PointType;	// Type of points used for registration.
	typedef std::vector<PointType> PointListType;	

	// Creates and initializes an misRegistration object.
	misLandmarkRegistration();	

	// Performs calculations if necessary and gets the provided fixed points all lie on the same line. It uses a tolerance value
	// predefined within the class to also include points that are only nearly on the same line. The larger the tolerance value,
	// rougher the algorithm. Collinear fixed points cannot be used in registration. This check is also performed during
	// the registration process by underlying IGSTK registration procedure (using the same algorithm). However IGSTK does not 
	// directly report the result of the check.
	bool ArePointsCollinear();

	// Gets the registration transform matrix that transforms from the fixed coordinate system to the moving coordinate system.
	vtkMatrix4x4* GetRegistrationTransform();

	// Sets the set of moving points as a list of points.
	void SetMovingPoints(const PointListType &movingPoint);

	// Extracts a list of points from a list of mislandMarkPosAndStatusStr objects and assigns it as the list of moving points.
	void SetMovingPoints(const std::vector<mislandMarkPosAndStatusStr> &movingPoint);

	// Sets the set of fixed points as a list of points.
	void SetFixedPoints(const PointListType &fixedPoints);

	// Extracts a list of points from a list of mislandMarkPosAndStatusStr objects and assigns it as the list of fixed points.
	void SetFixedPoints(const std::vector<mislandMarkPosAndStatusStr> &fixedPoints);

private:
	// Performs all the calculations necessary (if any of the input point sets are updated) and updates internal values for 
	// collinearity and registration transform matrix by calling CheckCollinearity and (if no collinearity is detected)
	// ComputeRegistrationMatrix().
	void PerformCalculations();

	// Checks the specified fixed points for collinearity and updates internally kept value: m_AreFixedPointsCollinear. It uses 
	// the same algorithm used internally by IGSTK (but not made public). The algorithm was directly retrieved from IGSTK 
	// Landmark3DRegistration source code.
	void CheckCollinearity();

	// Computes the registration matrix by creating an IGSTK Landmark3DRegistration object and sending respective requests and
	// handling the transform events.
	void ComputeRegistrationMatrix();

	// Replaces a list of points with those extracted from a list of mislandMarkPosAndStatusStr objects. Used by overloads of 
	// SetFixedPoints and SetMovingPoints.
	PointListType ReplacePointsWithSimpleLandmarkList(const std::vector<mislandMarkPosAndStatusStr> &landmarkList, PointListType &points);

	// Holds whether a recalculation of class outputs is necessary (if any of the set of input points are changed).
	bool m_IsCalculationNecessary;

	bool m_AreFixedPointsCollinear;	// Returned by ArePointsCollinear after being updated if necessary by CheckCollinearity.
	double m_CollinearityTolerance;	// The tolerance value for detecting collinearity of fixed points. Used in CheckCollinearity.
	PointListType m_MovingPoints;	// The set of moving points assigned by SetMovingPoints.
	PointListType m_FixedPoints;	// The set of fixed points assigned by SetFixedPoints.
	
	// Used by GetRegistrationTransform and updated if necessary by ComputeRegistrationMatrix()
	igstk::Transform m_RegistrationTransform;
};