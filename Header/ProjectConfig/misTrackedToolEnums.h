#pragma once

enum misRequiredToolsStatusEnum
{
	OKStatus,
	NoTools,
	NoRefTools,
	NoCalibrationTool,
	NoNavTool,
	NoTrackingDevice,
	NoRobotDevice,
	NoPlanDevice,
	NotSetToolStatus,
};

enum misMarkerStatus
{
	MARKER_USED                = 0,
	MARKER_ButIsOutOfVolume    = 1,

	MARKER_MISSING             = 10,
	MARKER_EXCEEDED_MAX_ANGLE  = 11,
	MARKER_EXCEEDED_MAX_ERROR  = 12,
	MARKER_Outside_Charecterized_Volume = 13,

	Unset_MarkerStatus = 255,
};