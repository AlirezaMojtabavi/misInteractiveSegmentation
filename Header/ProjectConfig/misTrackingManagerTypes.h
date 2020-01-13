#ifndef __MISTRACKINGMANGERTYPES__
#define __MISTRACKINGMANGERTYPES__

#include "misExtraToolInformation.h"
#include "misToolImageStrct.h"
#include "misToolTypeEnum.h"
#include "misTrackingManagerEnums.h"
#include "misTryCatchDeserializationMACRO.h"

using namespace Gdiplus;
//============================================================================
//typedef enum
//{
//	Data_Manager	=	0,
//	Analysis_Studio,
//	Planning,
//	Tracking_Activation,
//	Registration,
//	Navigation
//} ActiveTabsType;
//=========================================================================

//==========================================================================

/** Available parity settings. */

typedef std::map<std::string,std::string>	misToolNameIDMapTypedef;

typedef  std::vector<misToolStatus>			    misToolStatusListtypedef;

typedef std::vector<double>					misDoubleValueListTypdef;

typedef std::vector<int>					misIntValueListTypdef;

struct misStrctInputCalibrationData
{  
	int index;
	double time;
	std::string toolName;
};

struct misStrctInputSaveToolData
{
	int index;
	std::string Address;

	misStrctInputSaveToolData()
	{
		index = -1;
	}
};

struct misStrctSimpleToolProperties:public  Serializable
{
	bool					IsLoaded;
	std::string				ToolName;
	std::string				PartNumber;
	std::string				ToolSerialNumber;
	unsigned				ShaftLength;
	unsigned				ShaftDiameter;
	unsigned				NumberOfMarkers;
	unsigned				MinOfMarkers;
	unsigned				ToolWeight;
	misTooltipStyle			TooltipStyle;
	std::shared_ptr<Gdiplus::Image>			ToolImage;
	misToolApplicationType	ToolApplicationType;
	
	bool operator <(misStrctSimpleToolProperties& right)
	{
		return PartNumber < right.PartNumber;
	}
	
	bool operator ==(misStrctSimpleToolProperties& right)
	{
		return PartNumber == right.PartNumber;
	}
	
	misStrctSimpleToolProperties()
	{
		ShaftLength   = 0;
		ShaftDiameter = 0;
		ToolImage     = 0;
		IsLoaded  = false;
	};

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("toolName",this->ToolName);
		s.serialize("partNumber",this->PartNumber);
	};

	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("toolName", ToolName);
		TRYCATCHDESERILIZE("partNumber", PartNumber);
	};
};

typedef std::vector<misStrctSimpleToolProperties>    misSimpleToolNameListTypdef;

struct misStrctListPointer 
{
	misSimpleToolNameListTypdef* pAllToolList;
	misSimpleToolNameListTypdef* pUploadedList;
};



//typedef std::map<std::string,misToolStatusToGUI> misToolToGUI;

struct misStrctSCUInformation
{
	bool SCU;
	bool STB;
};

struct  misStrctTrackerInformation
{
	bool tracker;
	bool bump;
	bool Tempretaure;
};

struct misStrctOutputCalibrationData
{
	double translation[3];
	double error;
	int numberofsample;
};

//=============================================================

struct misStructPivotData
{
	std::string Address;
	double VectorTranslation[3];
	int index;
};

struct misStrctInputCalibrationDataInThread
{
	misStrctInputCalibrationData data;
	void* trkManager;
};

struct ToolValidationStatusData
{
	bool							isAutomatic;
	double							progressValue;
	misCalibrationWorkflowStatus	toolAccuracyState;
};

struct TrackerStateRawData
{
	bool							isAutomatic;
	double							progressValue;
	ToolVisibilityStatus			toolVisibilityState;
	misCalibrationWorkflowStatus	toolAccuracyState;
};


struct simpleMessage
{
	int state;
	std::string messageText;
};

struct misStrctSettingPolaris
{
	int		PGFrequency;
	int		IRFrequency;
	int		Volume;
	int     IlluminationRate;
};

struct misStrctSettingSimulatedTracker
{
	double		RadiusInMillimeters;
	double		SpeedInDegreesPerSecond;
};

struct misStrctSettingPivot
{
	float delayTime;
	float calibrartionDuration;    
};

struct ResultFlags
{
	bool SuccessFlag;
	bool FailureFlag;
};

struct ObserverHandles
{
	unsigned long SuccessObserverHandle;
	unsigned long FailureObserverHandle;
};

struct QuadResult
{
	ResultFlags ResFlag;
	ObserverHandles ObsHandle;
};

enum CameraImageType
{
	FullSize,
	FullSize24Bit,
	HalfSize,
	HalfSize24Bit
};

struct CameraImageData
{
	bool							isAvailable;
	CameraImageType					ImageType;
	unsigned char					*leftImage;
	unsigned char					*rightImage;
	unsigned char					*middletImage;
	int								lenLimage;
	int								lenRimage;
	int								lenMimage;
	int								width;
	int								height;
	std::vector<misDoubleValueListTypdef> rPoints;
	std::vector<misDoubleValueListTypdef> lPoints;
};

//struct misStrctSettingConnect
//{
//	int ComPort;
//	int BaudRate;
//	int DataBit;
//	int StopBit;
//	int Parity;
//	int HandShake;
//};

//=============================================================
#endif
