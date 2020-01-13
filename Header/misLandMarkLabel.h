#pragma once

#include "ILandMarkLabel.h"

class vtkPlaneSource;
class mis3DLabeRepresentationl;
class misFollowerFixedArea;

namespace parcast
{
	class ILandmarkColor;
}

class misLandMarkLabel :public ILandMarkLabel
{

public:
	misLandMarkLabel(std::shared_ptr<parcast::ILandmarkColor> landmarkColor, double radius, bool disabledepth);
	bool IsValid() const override;
	void SetValidation(bool val) override;
	void SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType) override;
	void SetTexture(vtkTexture* ptexture) override;
	void SetLabelRadious(double radious) override;
	void SetCategory(misLandmarkType val) override;
	void SetPosition(double position[3]) override;
	misLandmarkType GetCategory() const override;
	misDoubleColorStruct GetLastColor() override;
	vtkProp* GetActor() override;
	std::shared_ptr<misSurfaceRepresentation> GetSurface() const override;

private:

	void UpdateColor();

	vtkSmartPointer<misFollowerFixedArea> m_textActor;
	vtkSmartPointer<vtkPlaneSource> m_Plane;
	std::shared_ptr<mis3DLabeRepresentationl> m_LabelRep;
	std::shared_ptr<parcast::ILandmarkColor> m_LandmarkColor;
	std::shared_ptr<misSurfaceRepresentation> m_Surface;
	misLandmarkType m_Category;
	LANDMARKLABELSTAUS m_LndStatus;
	LANDMARKLABLETYPE m_LndType;
	misDoubleColorStruct m_CurrentColor;
	bool m_Valid;
	double m_Radious = 5.5;
	int m_LabelId = 0;
	bool m_DisableDepth = true;
};