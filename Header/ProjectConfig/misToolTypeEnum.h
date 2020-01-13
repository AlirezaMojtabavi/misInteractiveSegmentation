#pragma once

enum misToolApplicationType
{
	ReferenceTool,
	CalibrationTool,
	RefandCalibrationTool,
	FixedNavigationTool,
	DetachableNavigationTool,
	unKnownToolAppType
};

enum misToolStatus
{
	MIS_New       =0, //useable
	MIS_TrackingOk,   //useable
	MIS_Missing	  ,   //useable
	MIS_CalibrationProgress,
	MIS_MissingDuringCalibrationProgress,
	MIS_CalibrationFinished,
	MIS_POV		  ,
	MIS_ERROR	  ,
	MIS_Deactive  ,   //useable
	MIS_UnKnown
};

enum misToolCategory
{
	Reference,
	BrainGeneral,
	ENTGeneral,
	BiopsyTool,
	UnSetCategory
};

typedef std::vector<misToolCategory>    misToolCategoryListTypdef;

enum misTooltipStyle
{
	Straight,
	Bended,
	unkownToolType
};
