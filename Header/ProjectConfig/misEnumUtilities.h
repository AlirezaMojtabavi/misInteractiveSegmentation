#pragma once


#include "misEnums.h"
#include "misobjectProperitiesEnums.h"
#include "misSubSequenseGeneralStateEnums.h"
#include "misResultMessageEnums.h"
#include "misToolTypeEnum.h"
#include "misImageModalityEnum.h"
#include "misRegistrationEnums.h"
#include "VisualizationGeneralTypes.h"
//#include "misGroupViewerSetting.h"
#include "misViewerTypeDirection.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "misColorStruct.h"
#include "misPointPropertiesOnReferenceEnum.h"
#include "misTrackingManagerEnums.h"
#include "misCaptureDevices.h"
#include "misVolumeViewingTypes.h"

//#include "misPointPropertiesOnReferenceEnum.h"

class misEnumUtilities
{
public:

	//static std::string					ConvertMessageBoxButtonEnumToString(misMessageBoxButtons messageBoxButton);
	//static misMessageBoxButtons			ConvertMessageBoxButtonStringToEnum(string enumInStringFormat)
	
	static std::string					ConvertImageViewingEnumToString(misImageViewingType imageViewingType);
	static misImageViewingType			ConvertImageViewingStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertImageModalityEnumToString(misImageDataModality imageModalityType);
	static misImageDataModality			ConvertImageModalityStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertRegistarationResultEnumToString(misRegistationStatus registartionType);
	static misRegistationStatus			ConvertRegistarationResultStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertObjectTypeEnumToString(MisObjectType objectType);
	static MisObjectType				ConvertObjectTypeStringToEnum(std::string enumInStringFormat);

	static std::string					Convert3DModelTypeEnumToString(mis3DModelTypes modelType3D);
	static mis3DModelTypes				Convert3DModelTypeStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertPatientPositionEnumToString(misPatientPosition patientPosition);
	static misPatientPosition			ConvertPatientPositionStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertImageColorTableEnumToString(ImageColorTableType colorTableName);
	static ImageColorTableType			ConvertImageColorTableStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertVolumeViewingEnumToString(misVolumeViewingTypes volumeViewingTypes);
	static misVolumeViewingTypes		ConvertVolumeViewingStringToEnum(std::string enumInStringFormat);

	static std::string                  ConvertSequenseStateEnumToString(subSequenseGeneralStateEnums sequenseState);
	static subSequenseGeneralStateEnums ConvertSequenseStateStringToEnum(std::string enumInStringFormat);
	
	static std::string					ConvertGenderEnumToString(GenderEnum genderEnum);
	static GenderEnum					ConvertGenderStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertCursorTypeEnumToString(misCursorType cursorEnum);
	static misCursorType				ConvertCursorTypeStringToEnum(std::string enumInStringFormat);

	static std::string		ConvertImageOrientationTypeEnumToString(IMAGEORIENTATION imgOrientation,  bool isObliqe);
	static IMAGEORIENTATION				ConvertImageOrientationTypeStringToEnum(std::string enumInStringFormat);

	static IMAGEORIENTATION				ConvertViewTypeDirectionToEnum(misViewerTypeDirection typeDirection);
	static int							ConvertImageOrientationToInt(IMAGEORIENTATION ornt);

	static std::string					ConvertToolAppTypeEnumToString(misToolApplicationType toolAppType);
	static misToolApplicationType		ConvertToolAppTypeStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertToolCategoryEnumToString(misToolCategory toolCategory);
	static misToolCategory				ConvertToolCategoryStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertSaveSolutionModeEnumToString(misSaveSolutionMode saveSolutionMode);
	static misSaveSolutionMode			ConvertSaveSolutionModeStringToEnum(std::string enumInStringFormat);
	static std::string					ConvertToolStatusToString(misToolStatus toolStatus);
	static misToolStatus				ConvertToolStatusStringToEnum(std::string enumInStringFormat);
	static misColorStruct    		    ConvertToolStatusEnumToColor(misToolStatus toolStatus);
	static std::string				    ConvertToolStatusEnumToImagePathString(misToolStatus toolStatus);

	static std::string					ConvertToolApplicationTypeEnumToString(misToolApplicationType toolApplicationType);

	static std::string					ConvertApplicationTypeEnumToString(misApplicationType appType);
	static misApplicationType			ConvertApplicationTypeStringToEnum(std::string enumInStringFormat);

	static std::string								ConvertLandmarkRegistarationPlaySoundStatusEnumToString(misLandmarkRegistarationPlaySoundStatus landmarkRegPlaySound);
	static misLandmarkRegistarationPlaySoundStatus	ConvertLandmarkRegistarationPlaySoundStatusStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertCroppingDirectionInVREnumToString(misCroppingDirectionInVR landmarkRegPlaySound);
	static misCroppingDirectionInVR	    ConvertCroppingDirectionInVRStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertPointUsecaseEnumToString(misPointUsecase pointUsecase);
	static misPointUsecase				ConvertPointUsecaseStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertPointStructureEnumToString(misPointStructure pointStructure);
	static misPointStructure			ConvertPointStructureStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertTooltipStyleEnumToString(misTooltipStyle tooltipStyle);
	static misTooltipStyle				ConvertTooltipStyleStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertLandmarkTypeEnumToString(misLandmarkType landmarkType);
	static misLandmarkType				ConvertLandmarkTypeStringToEnum(std::string enumInStringFormat);

	static std::string					ConvertTrackerTypeEnumToString(TrackerType CurrentTracker);//Added by -M.A-
	static TrackerType					ConvertTrackerTypeStringToEnum(std::string enumInStringFormat);//Added by -M.A-

	static std::string					ConvertCallibratorTypeEnumToString(CallibratorType CurrentTracker);//Added by -S.M-
	static CallibratorType				ConvertCallibratorTypeStringToEnum(std::string enumInStringFormat);//Added by -S.M-

	static std::string					ConvertTipCalibrationApproachEnumToString(TipCalibrationApproach CurrentTipCalibrationApproach);//Added by -M.A-
	static TipCalibrationApproach		ConvertTipCalibrationApproachStringToEnum(std::string enumInStringFormat);//Added by -M.A-

	static std::string					ConvertNDItoolSpheresQualityEnumToString(NDItoolSpheresQuality SphereQuality);//Added by -M.A-
	static NDItoolSpheresQuality		ConvertNDItoolSpheresQualityStringToEnum(std::string enumInStringFormat);//Added by -M.A-

	static std::string	 				ConvertAppModeEnumToString(AppMode appMode);
	static AppMode						ConvertAppModeStringToEnum(std::string appModeInStringFormat);

	static std::string					ConvertFlyZoneTypeEnumToString(misRGObjectType zoneStat);
	static misRGObjectType				ConvertFlyZoneTypeStringToEnum(std::string enumZoneStat);
	
	static videoInputType				ConvertvideoInputTypeStringToEnum(std::string input);
	static std::string						ConvertvideoInputTypeEnumTostring(videoInputType input);

	static std::string						ConvertDoubleToString(double iarg);

	//This function gets the double value and an int number showing number of significant digits required after floating point
	static std::string						ConvertDoubleToString(double iarg, int NumSignificantDigitsAfterFloatingPoint);
public:
	 misEnumUtilities();
	~misEnumUtilities();
};
