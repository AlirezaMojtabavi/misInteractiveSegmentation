#pragma once

#include "VisualizationGeneralTypes.h"
#include "misLandmarkenums.h"
#include "misitkTypdef.h"

struct misLandmarkInfoStruct
{
	int landmarkIndex;
	bool validity;
	misItkPointType CurrentPosition;
	misLandmarkType Landmarktype;
	LANDMARKLABLETYPE landmarkLableType;

	misLandmarkInfoStruct():validity(false), landmarkIndex(-1){};
};

struct misUpdatePositionInfoStruct
{
	vtkSmartPointer<vtkMatrix4x4> CornerTransform;
	bool          IsCameraUpdate = false;
	bool          ForceToRender = false;
	misUpdatePositionInfoStruct()
		:CornerTransform(vtkSmartPointer<vtkMatrix4x4>::New())
	{

	}
};