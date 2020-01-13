#pragma once
#include "misStrctColorData.h"
#include "misLandmarkenums.h"

class misSurfaceRepresentation;

class ILandMarkLabel
{

public:
	virtual ~ILandMarkLabel() = default;

	virtual bool IsValid() const = 0;
	virtual void SetValidation(bool val) = 0;
	virtual void SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType) = 0;
	virtual void SetTexture(vtkTexture* ptexture) = 0;
	virtual void SetLabelRadious(double radious) = 0;
	virtual void SetCategory(misLandmarkType val) = 0;
	virtual misLandmarkType GetCategory() const = 0;
	virtual misDoubleColorStruct GetLastColor() = 0;
	virtual void SetPosition(double position[3]) = 0;
	virtual vtkProp* GetActor() = 0;
	virtual std::shared_ptr<misSurfaceRepresentation> GetSurface() const = 0;
};