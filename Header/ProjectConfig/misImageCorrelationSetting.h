#pragma once

#include "LevelInformation.h"
#include "misColorStruct.h"
#include "serializable.h"

class ImageCorrelationSetting:public Serializable
{

public:

	bool					  LoggerEnabled;

	int						  MultiResolutionLevelNumber;
	bool					  usedPrimeryCorrelationVlaue;
	int						  defaultIterationNumberForEachLevel;
	bool					  useThreadInPyramidCreation;
	int						  UpdateResultInterval;

	double					  fixedImageOpacity;
	double					  movingImageOpacity;

	misColorStruct			  fixedImageColor;
	misColorStruct			  movingImageColor;

	bool					  AutomaticRegistration;
	int						  MinimumLandmarkNumberForManualRegistartion;

	bool					  IsPyramidCalculatedInMultiThreadProcedure;
	//NOTE: the following variables are related to correlation procedure
	//unsigned int			  permute[3];
	tgt::Vector3ui				  permute;
	tgt::bvec3					  flip;
	//bool					  flip[3];
	int						  numberOfLevel;
	std::vector<levelInformation > levelInfo;
	double					  translationScale;

	double					  freeTranslationStep;
	double					  freeRotationStep;
	
	ImageCorrelationSetting();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	void SetDefaultImageCorrelation( void );

};
