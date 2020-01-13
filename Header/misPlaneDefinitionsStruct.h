#pragma once

#include "VisualizationGeneralTypes.h"
#include "misApplicationSetting.h"
#include "misEventFromGUIUnLoaded.h"
#include "misSimplePointType.h"

class misPlaneDefinitionsStruct
{
private:
	misSimplePointType AxialPlaneNormal;
	misSimplePointType CoronalPlaneNormal;
	misSimplePointType SagittalPlaneNormal;

	misSimplePointType AxialViewUp;
	misSimplePointType CoronalViewUp;
	misSimplePointType SagittalViewUp;
	misSimplePointType AxialPlanePoints[4];
	misSimplePointType CoronalPlanePoints[4];
	misSimplePointType SagittalPlanePoints[4];

	misSimplePointType AxialPlaneOffset;
	misSimplePointType CoronalPlaneOffset;
	misSimplePointType SagittalPlaneOffset;

	int AxialCameraPositionDir;
	int CoronalCameraPositionDir;
	int SagittalCameraPositionDir;

public:

	misPlaneDefinitionsStruct();

	misSimplePointType ViewUp(IMAGEORIENTATION pOrientation);

	//Returns the predefined plane normals. To see the values take a look at constructor of misPlaneDefinitionsStruct
	 misSimplePointType PlaneNormal(IMAGEORIENTATION pOrientation);

	 double CameraPositionDir(IMAGEORIENTATION pOrientation);
	 
	 //returns predefined offsets. To see the values take a look at constructor of misPlaneDefinitionsStruct
	 misSimplePointType GetPlaneDefaultOffset(IMAGEORIENTATION pOrientation);

	 std::vector<misSimplePointType> GetCoordinatePoints(IMAGEORIENTATION pOrientation);
};