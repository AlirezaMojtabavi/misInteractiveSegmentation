#pragma once
#include "ILandmarkPointerRepresentation.h"

#include "misitkTypdef.h"
#include "IRepresentation.h"
#include "misFollowerFixedArea.h"

class vtkSphereSource;
class misSpherePointLandmark;
class misSurfaceRepresentation;
class ILandMarkLabel;

class misLandmarkPointerRepresentation : public ILandmarkPointerRepresentation
{

public:
	misLandmarkPointerRepresentation(double radius, bool disabledepth);
	misLandmarkPointerRepresentation(int index, LANDMARKLABELSTAUS stat, misLandmarkType category,
		const double position[3], LANDMARKLABLETYPE lndType , double radius, bool disabledepth);
	bool IsValid() const override;
	void UpdateNormal() override;
	void UpdateAsSelected() override;
	void UpdateAsUnderCapture() override;
	void Validate() override;
	void InValidate() override;
	void SetLabelPosition(const double position[3]) override;
	void SetLabelPosition(double x, double y, double z) override;
	void HideLandmarkLable();
	void UpdateData(LANDMARKLABELSTAUS landmarkStatus) override;
	void SetCorrectionVectorForLandmarkRegistration(double mainPosition[3], double finalRegisteredPosition[3]) override;
	void GetPosition(double position[3]) override;
	void SetVisibilityOn() override;
	void SetVisibility(bool value) override;
	void SetVisibilityOff() override;
	void SetCategory(misLandmarkType val) override;
	void SetPosition(const double position[3]) override;
	void SetPosition(double x, double y, double z) override;
	void SetColor(float r, float g, float b, float a) override;
	void SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType) override;
	std::vector<misSurfaceRepresentation> GetAlllRepresentations() override;
	std::shared_ptr<misSpherePointLandmark> GetLandMark() override;
	std::shared_ptr<misSurfaceRepresentation> GetLablel() override;
	std::shared_ptr<IRepresentation> GetSurface() const override;
	misLandmarkType GetCategory() const override;

private:

	void SetLandmartkPosition(misItkPointType val);
	void UpdateColorWithCategory(void);
	void UpdateLink();
	void CreateLink();

	std::shared_ptr<ILandMarkLabel> m_Label;
	std::shared_ptr<misSpherePointLandmark> m_landMarkRep;
	std::shared_ptr<misSurfaceRepresentation> m_Surface;
	vtkSmartPointer<vtkActor> m_LineActor;
	vtkSmartPointer<vtkProp> m_LableActor;
	vtkSmartPointer<vtkLineSource>  m_plineSource;
	misItkPointType m_LandmartkPosition;
	misItkPointType m_LabelPosition;
	misLandmarkType m_Category = UnkownLandmarkType;
	bool m_Valid = false;
	bool m_generatedLabel = false;
	int  m_Id = -1;
	LANDMARKLABLETYPE m_labelType;
	bool m_DisableDepth = true;
};