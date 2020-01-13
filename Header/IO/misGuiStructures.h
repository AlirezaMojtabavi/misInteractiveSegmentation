#pragma once
//use this struct to store event information  about a sub tab selection


#include "misColorStruct.h"
#include "misEnums.h"
#include "misImageViewingItemsStruct.h"
#include "misLandmarkenums.h"
#include "misWindowLevelStr.h"
#include "misobjectProperitiesEnums.h"
#include "ApproachAndModelInformationStrct.h"
#include "misShortImageViewingStrct.h"
#include "BusinessEntities/Vector.h"

//Image and Object information Struct

struct ImageInformationStrct
{
	misUID packegeUID;
	misUID objectUID;
	misTreeViewType treeViewType;

	ImageInformationStrct()
	{
		Reset();
	};

	void Reset()
	{
		packegeUID = "";
		objectUID = "";
		treeViewType = UnSetItem;
	};
};


struct ImageVisibilityInformation
{
	ImageInformationStrct imageInformation;
	bool                   visibility;

	void Reset()
	{
		imageInformation.Reset();
		visibility = false;
	};
	ImageVisibilityInformation()
	{
		Reset();
	};
};

struct ApproachAndModelVisibilityInformation
{
	ApproachAndModelInformationStrct objectInformation;
	bool                   visibility;

	void Reset()
	{
		objectInformation.Reset();
		visibility = false;
	};
	ApproachAndModelVisibilityInformation()
	{
		Reset();
	};
};

struct ApproachAndModelOpacityInformation
{
	ApproachAndModelInformationStrct objectInformation;
	double                   opacity;

	void Reset()
	{
		objectInformation.Reset();
		opacity = 0.0;
	};
	ApproachAndModelOpacityInformation()
	{
		Reset();
	};
};

struct ApproachAndModelColorInformation
{
	ApproachAndModelInformationStrct objectInformation;
	misColorStruct                   color;
	void Reset()
	{
		objectInformation.Reset();
		color.InVisible();
	};

	ApproachAndModelColorInformation()
	{
		Reset();
	};
};

struct ObjectInformationStrct
{
	misUID packegeUID;
	misUID objectUID;
	MisObjectType objectType;
	mis3DModelRenderingType renderingType;

	void Reset()
	{
		packegeUID = "";
		objectUID = "";
		objectType = misUnKnowObjectType;
		renderingType = UnSetRenderingType;
	};

	ObjectInformationStrct(void)
	{
		Reset();
	};

	bool IsValidData()
	{
		if (packegeUID == "")
		{
			return false;
		}
		if (objectUID == "")
		{
			return false;
		}
		if (objectType == misUnKnowObjectType)
		{
			return false;
		}
		if (renderingType == UnSetRenderingType)
		{
			return false;
		}
		return true;
	};
};


struct SubTabSelection
{
	std::string tabName;
	std::string subTabName;
	int   subTabIndex;
	int width[5];
	int  height[5];
};

struct SingleWrapperStrct
{
	int currentRendererIndex;
	void* currentRendererHandle;
	int  sliderValueChange;
	int  toolbarType;
};

struct wrapperStrct
{
	int currentRendererIndex;
	void* currentRendererHandle;
	void* AxialRendererHandle;
	void* CoronalRendererHandle;
	void* SagitalRendererHandle;
	void* PanoramicRendererHandle;
	int  sliderValueChange;
	int  toolbarType;
	misZoomState zoomState;
	misImageViewingType viewingType;

};
struct zoomStrct
{
	double percentage;
	double proportion;
	bool fromImageViewer;
};
struct MeasurmentWidgetstrct
{
	wrapperStrct wrpstrct;
	bool  activate;
};

struct misSliderStrc
{
	double SliderIndex;
	int minSliderValue;
	int maxSliderValue;

	void Reset()
	{
		SliderIndex = -1;
		minSliderValue = -1;
		maxSliderValue = -1;
	};
	misSliderStrc()
	{
		Reset();
	};
};


struct sliderInfoStruct
{
	int sliderIndex;
	int sliderValue;

	void Reset()
	{
		sliderIndex = -1;
		sliderValue = -1;
	};

	sliderInfoStruct()
	{
		Reset();
	}
};


struct misShortImageContainedPolydataViewingStrct
{
	misUID        objectUID;
	bool	      visibility;
};


struct misShortPlanningViewingStruct
{
	std::string						name;
	misUID						objectUID;
	bool						visibility;
	bool						useable;
	misColorStruct				color;
	double			TargetPoint[3];
	double			EntryPoint[3];
	std::string						TargetpointName;
	std::string						EntryPointName;
	unsigned char               Transparency;
};

typedef  std::vector< misImageViewingItemsStruct >		ImageViewingListTypedef;

struct misSimpleIndexType
{
	double  data[3];
	double& operator [](int index)
	{
		return data[index];
	}
};

typedef misSimpleIndexType        GUISeedType;
typedef std::vector<GUISeedType>  GUISeedListType;
typedef std::vector<float>        GUISeedListValueType;

struct misPolydataViewingItemsStruct
{
	std::string   name;
	misUID objectUID;
	misUID parentImageUID;
	misUID packageUID;
	bool   directionSataus;
	bool   correlationSatus;
	bool   visibilitySatus;
};

typedef  std::vector< misPolydataViewingItemsStruct >          PolyDataViewingListTypedef;

struct ImageViewingCorrelationStruct
{
	misImageViewingItemsStruct mainImage;
	misImageViewingItemsStruct OtherImages;
};

enum  misTextureEnum
{
	Texture_A = 0,
	Texture_P,
	Texture_S,
	Texture_I,
	Texture_R,
	Texture_L,
	Texture_Blank,
	Texture_Strip,
	none
};
struct misFaceInformation
{
	int            cellID;
	misTextureEnum textureName;

	void Reset()
	{
		cellID = -1;
		textureName = Texture_Blank;
	}

	misFaceInformation()
	{
		Reset();
	}
};

typedef std::vector<misFaceInformation> faceInformationListTypdef;

#pragma region StctImage Dat
//                               Structures used in GUI
struct misViewingPatientProperties
{
	std::string FamilyName;
	std::string Gender;
	std::string BirthData;
	int Weight;
	int Age;

	void Reset()
	{
		FamilyName = "";
		Gender = "";
		BirthData = "";
		Weight = 0;
		Age = 0;
	};

	misViewingPatientProperties()
	{
		Reset();
	}
};

struct misStudySerieViewingProperties
{
	std::string SeriesDescription;
	std::string SerieAcquisitionDate;
	std::string SerieAcquisitionTime;

	std::string StudyDescription;
	std::string StudyDate;

	void Reset()
	{
		SeriesDescription = "";
		SerieAcquisitionDate = "";
		SerieAcquisitionTime = "";

		StudyDescription = "";
		StudyDate = "";
	};

	misStudySerieViewingProperties()
	{
		Reset();
	}
};

struct misViewingImageProperties
{
	std::string   ImageModality;
	std::string   PatientPosition;
	std::string   ProtocolName;
	std::string   NumberofImages;
	std::string   ZResolution;
	std::string   Rows;
	std::string   Columns;

	void Reset()
	{
		ImageModality = "";
		PatientPosition = "";
		ProtocolName = "";

		NumberofImages = "";
		ZResolution = "";
		Rows = "";
		Columns = "";
	}

	misViewingImageProperties()
	{
		Reset();
	}
};

// Used in GUI for viewing
struct misDicomDataViewingProperties
{
	misViewingPatientProperties       patientProperties;
	misViewingImageProperties         imageProperties;
	misStudySerieViewingProperties    studySerieProperties;

	void Reset()
	{
		patientProperties.Reset();
		imageProperties.Reset();
		studySerieProperties.Reset();
	};
	misDicomDataViewingProperties()
	{
		Reset();
	}
};
#pragma endregion StctImage Dat

//////////////////////////////////////////////////////////////////////////
#pragma region dataProcedure
typedef  std::vector<ImageViewingCorrelationStruct> ImageCorrelationViewingListTypedef;
#pragma endregion dataProcedure

typedef std::vector<LandmarkStatus> LandmarkStateListTypdef;

struct misNearsetLandmarkStr
{
	int    nearestID;
	parcast::VectorD3 vectorToNearest = parcast::VectorD3(0.,0.,0.);
	double distanceToNearest;
	misNearsetLandmarkStr()
	{
		distanceToNearest = -1;
		nearestID = -1;
	};
};

struct misColorAndUID
{
	misUID objectUID;
	misColorStruct color;
};

struct misOpacityAndUID
{
	misUID objectUID;
	double opacity;
};

struct misCorrelationManualRegistrationStructure
{
	int LandmarkIndex;
	misCorrelationImageType ImageType;
};

struct misImageAnd3DModelPropertiesSettingStrct
{
	//TODO --barzegar
	//no-fly-zone and fly-zone distance must be set..
	enum misTypeOfSelectedObject
	{
		UnknownObjectType,
		ImageObjectType,
		ApproachAndModelObjectType
	};

	misWindowLevelStr WindowLevel;
	float opacity;
	bool visibility2D;
	bool visibility3D;
	misColorStruct color;
	misTypeOfSelectedObject objectType;

	bool objectMarginActive;
	bool objectMarginShow;
	double objectMarginValue;

	misImageAnd3DModelPropertiesSettingStrct()
	{
		opacity = 0;
		visibility2D = false;
		visibility3D = false;
		objectType = UnknownObjectType;
		color.Reset();
		objectMarginActive = false;
		objectMarginShow = false;
		objectMarginValue = -1.0;
	};
	void operator =(misImageAnd3DModelPropertiesSettingStrct right)
	{
		WindowLevel.SetWindowParams(right.WindowLevel.GetWindowCenter(), right.WindowLevel.GetWindowWidth());
		opacity = right.opacity;
		visibility2D = right.visibility2D;
		visibility3D = right.visibility3D;
		color = right.color;
		objectType = right.objectType;

		objectMarginActive = right.objectMarginActive;
		objectMarginShow = right.objectMarginShow;
		objectMarginValue = right.objectMarginValue;
	}
};
