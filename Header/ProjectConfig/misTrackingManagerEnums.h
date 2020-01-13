#pragma once

enum TrackerType
{
	NoneTracker,
	Polaris,
	BiopsyPolaris,
	Micron,
	Simulated,
	Ascension,
	Aurora
};

enum CallibratorType
{
	NoneCallibrator,
	HeadBandRef,
	MicronTTBlock,
	SimulatedCalib,
	AscensionCallibrator,
	AuroraCalibrator
};

enum misTrackingVolumeType
{
	PyramidVolume	= 0, // Standard Measurement Volume
	ExtendedVolume  = 5  // Extended Measurement Volume
};

enum TrackerToolType
{
	PolarisTool,
	MicronTool,
	Ascension3DGTool,
	SimulatedTool,
	AuroraTool
};

enum misToolVisibilityStateEnum
{
	RealVisibility,
	CurrentVisibility,
};

enum misAccuracyCheckingStatus
{
	//MIS_OFF_ForAllTools	=	0,
	MIS_ON_ForAnotherTool	=	0,
	MIS_ON_ForThisTool
};


// The Status enumeration holds all the possible statuses which the workflow manager can assume at any time.
enum misCalibrationWorkflowStatus
{
	// The workflow manager object has been created but it has not engaged in any activity yet. Idle.
	ST_INITIAL, 

	// The workflow manager object has started the tool tip position validation process (data gathering, analyzes, etc).
	ST_TIP_VALIDATION_IN_PROGRESS,

	// The last tip position validation process was successfully completed and calibration data set on the subject tool. Idle.
	ST_TIP_VALIDATION_SUCCESSFUL,

	// The last tip validation process failed due (calibration point is too far from the original tool tip to be allowed). Idle.
	ST_TIP_VALIDATION_FAILED,

	// The workflow manager object has started the tool tip position calibration process (data gathering, analyzes, etc).
	ST_TIP_CALIBRATION_IN_PROGRESS,

	// The last tool tip position calibration process is done. Idle.
	ST_TIP_CALIBRATION_SUCCESSFUL,

	// The last  tool tip position calibration process is failed.
	ST_TIP_CALIBRATION_FAILED,

	// The last tool tip position calibration process is done (in the manual mode) and user has requested performing of
	// orientation calibration. Idle.
	ST_ORIENTATION_CALIBRATION_STANDBY,

	// The workflow manager object has started the tool orientation calibration process (data gathering, analyzes, etc).
	ST_ORIENTATION_CALIBRATION_IN_PROGRESS,

	// The last tool orientation calibration process is done. Idle.
	ST_ORIENTATION_CALIBRATION_DONE

};

enum misToolAccuracySteps
{
	ToolValidation,//ToolValidation tab
	TipCalibration,//TipCalibration tab
	OrientationCalibration//OrientationCalibration tab
};

enum ToolVisibilityStatus
{
	ToolsVisible,
	NavigationToolInvisible,
	ReferenceToolInvisible,
	CalibratorToolInvisible
	/*ToolValidated,
	ToolInvalid,
	WhileToolFixation,
	LetTipRecalibration,
	LetOrientationRecalibration,
	ResetColibration,
	UpdateMsgToRepeatTipCalibration,
	EnableAllForTest*/
};

//enum 
enum misToolTrackingEnum
{
	// the order is important and must not be changed
	AbsoluteCoordinate,
	RelativeCoordinate,
	RegistratedCoordinate,
	AnotherImageRegistratedCoordinate
};

//Added by -M.A-
//An enum to control which type of tip calibration should be used
enum TipCalibrationApproach
{
	OnePointWithPrecalculatedPivotPoint=0,//Represents the traditional single point calibration approach to find offset
	//The value of line below commented to don`t allow user to use this value because we never want to use this approach
	//ManyPointsWithPrecalculatedPivotPoint,//Represents Offset calibration with pre-calculated pivot which is read from xml file of reference (NOTICE: NEVER USE THIS APPROACH)
	ManyPointsAndCalculatePivotPoint,//Represents pivot calibration which calculates offset and pivot simultaneously (NOTE:ALWAYS USE THIS APPROACH)
	
	//this means the tip of tool is steady on pivot point and we get some data and calculate an average of data
	FixedTipWithManyDataBySteadyTool
};


//added by -M.A- 
//An enum to show Quality Of NDI tracker Spheres
enum NDItoolSpheresQuality
{
	VeryGood=0,
	Acceptable,
	Inappropriate
};

//added by -M.A-
//This enum is used to specify this property of tool if that is Reference, Calibrator and so on...
enum KindOfTool
{
	ToolIsReference=0,
	ToolIsCalibrator,

	//This is used for polaris that its calibrator is a reference too
	ToolIsReferenceAndCalinratorSimultaneously,
	ToolIsNavigationTool,
	ToolIsRegistrationTool

};