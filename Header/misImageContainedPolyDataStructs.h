#pragma once

#include "mis3DModelViewingProperties.h"
#include "misColorStruct.h"
#include "misEnums.h"
#include "misStringTools.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"

struct PropertiesOfPixelInImageStr
{
	misRGObjectType pixelType;
	misUID          PolyDataName;
	misUID          PolyDataUID;
};
typedef std::vector<PropertiesOfPixelInImageStr> PropertiesOfPixelInImageType;

class  ImagePolyDataContenStrct 
{
public:
	misUID  ParrentImageUID;
	misUID  PolyDataUID;
	std::string  PolyDataName;
	misColorStruct  PolyDataColor;
	int IndexRepresentObject; // between 0 to 7, the real indexs are (2*IndexRepresentObject) & (2*IndexRepresentObject+1)
	double ObjectVolume;
	mis3DModelObjectOpacityPropertiesStrct OpacityProp;
	int  extend[6];
	bool alarmMarging = false; 
	double marginValue = 0;
	int	numberOfMarginPixel = 0;
	int	maxIndex = 0;
	int	numberOfIndex = 0;
	mis3DModelTypes surfaceType = UnSetModelType;
	ImagePolyDataContenStrct(void);
	void WriteToFile(std::fstream& file);
	bool GetShowMargin() const;
	void SetShowMargin(const bool Showmargin);
private:
    bool m_ShowMargin = false;

};
typedef std::vector<ImagePolyDataContenStrct> PolyDatasPropertyByImageTypdef;