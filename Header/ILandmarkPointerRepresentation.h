#pragma once

#include "misLandmarkenums.h"
#include "misSurfaceRepresentation.h"
#include "misSpherePointLandmark.h"


class ILandmarkPointerRepresentation
{
public:
	virtual ~ILandmarkPointerRepresentation() = default;
	virtual bool IsValid() const = 0;
	virtual void UpdateNormal() = 0;
	virtual void UpdateAsSelected() = 0;
	virtual void UpdateAsUnderCapture() = 0;
	virtual void Validate() = 0;
	virtual void InValidate() = 0;
	virtual std::shared_ptr<misSpherePointLandmark> GetLandMark() = 0;
	virtual std::shared_ptr<misSurfaceRepresentation> GetLablel() = 0;
	virtual void SetLabelPosition(const double position[3]) = 0;
	virtual void SetLabelPosition(double x, double y, double z) = 0;
	virtual void HideLandmarkLable() = 0;
	virtual misLandmarkType GetCategory() const = 0;
	virtual std::vector<misSurfaceRepresentation> GetAlllRepresentations() = 0;
	virtual void UpdateData(LANDMARKLABELSTAUS landmarkStatus) = 0;
	virtual void SetCorrectionVectorForLandmarkRegistration(double mainPosition[3], double finalRegisteredPosition[3]) = 0;
	virtual void GetPosition(double position[3]) = 0;
	virtual std::shared_ptr<IRepresentation> GetSurface() const = 0;
	virtual void SetVisibilityOn() = 0;
	virtual void SetVisibilityOff() = 0;
	virtual void SetCategory(misLandmarkType val) = 0;
	virtual void SetPosition(const double position[3]) = 0;
	virtual void SetPosition(double x, double y, double z) = 0;
	virtual void SetVisibility(bool value) = 0;
	virtual void SetColor(float r, float g, float  b, float a) = 0;
	virtual void SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType = NUMERICALLANDMARK) = 0;
};
