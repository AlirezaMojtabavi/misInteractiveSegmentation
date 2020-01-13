#pragma once

#include "misToolTypeEnum.h"

class  OrientationCalibrationData
{
public:
	//x, y, z :axis
	//w :angle
	tgt::Vector4<double>		quaternion;
	misToolApplicationType toolBodyType;
};
