#pragma once

#include "misMacros.h"
#include "serializable.h"

// The misCalibrationWorkflowManagerProperties class provides a serializable container for the settings and properties required
// for initialization of a misCalibrationWorkflowManager object. 
class misCalibrationWorkflowManagerProperties :	public Serializable
{
	// Type of the user performing calibration. Possible values are "Admin" and "User". For different user types, different 
	// calibration profiles are invoked. E.g., ordinary users are only allowed to perform validation on fixed tools whereas 
	// administrators can fully calibrate both detached and fixed tools.
	misPrivateVariableWithPublicAccessorsMacro(std::string, m_UserType, UserType);

	// Length of the data buffer used for calibration data gathering, that is, the number of consecutive instantaneous tool 
	// transform instances that should be analyzed for fixation (of orientation and/or position) and if found "roughly" fixed 
	// (based on the fixation threshold values), the data buffer is eligible for using in calibration processes.
	misPrivateVariableWithPublicAccessorsMacro(int, m_DataBufferLength, DataBufferLength);

	// The strategy used for calibration of the tool tip position. Possible values are "Fixed Tip Position Mean" (the tool tip
	// is held fixed at a previously known spatial position - on the calibration tool), and "Fixed Pivot Point Calculation" (the
	// tip of the tool is held fixed at any position while the stem of the tool is rotated.
	misPrivateVariableWithPublicAccessorsMacro(std::string, m_TipCalibrationStrategy, TipCalibrationStrategy);

	// Determines whether automatic calibration is by default enabled. 
	misPrivateVariableWithPublicAccessorsMacro(bool, m_AutomaticCalibration, AutomaticCalibration);

public:
	misCalibrationWorkflowManagerProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );
};