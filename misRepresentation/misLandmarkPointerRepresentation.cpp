#include "stdafx.h"
#include "misLandmarkPointerRepresentation.h"

#include "misSpherePointLandmark.h"
#include "misStrctColorData.h"
#include "misVisualizationResourceManager.h"
#include "vtkArrowSource.h"
#include "misLandMarkLabel.h"
#include "LandmarkColor.h"
#include "misSurfaceRepresentation.h"
#include "ILandMarkLabel.h"
#include "LandmarkLablePositionCalculator.h"
#include "misFollowerFixedArea.h"


using namespace std;

misLandmarkPointerRepresentation::misLandmarkPointerRepresentation(
	int index, LANDMARKLABELSTAUS stat, misLandmarkType category, const double position[3], LANDMARKLABLETYPE lndType, double radius, bool disabledepth)
	: m_Category(category), m_labelType(lndType), m_DisableDepth(disabledepth)
{
	auto landmarkColor = std::make_shared<parcast::LandmarkColor>();
	m_landMarkRep = std::make_shared<misSpherePointLandmark>(m_DisableDepth);
	m_Surface = std::make_shared<misSurfaceRepresentation>("misLandmarkPointerRepresentation");
	m_Label = std::make_shared<misLandMarkLabel>(landmarkColor, radius, m_DisableDepth);
	SetPosition(position);
	SetCategory(category);
	SetLabelData(index, NORMAL, lndType);
	m_LableActor = m_Label->GetActor();
	m_Surface->AddProp(m_LableActor);
	m_Surface->AddProp(m_landMarkRep->GetActor(0));
	CreateLink();
}

misLandmarkPointerRepresentation::misLandmarkPointerRepresentation(double radius, bool disabledepth)
	: m_DisableDepth(disabledepth)
{
	auto landmarkColor = std::make_shared<parcast::LandmarkColor>();
	m_Label = std::make_shared<misLandMarkLabel>(landmarkColor, radius, m_DisableDepth);
	m_landMarkRep = std::make_shared<misSpherePointLandmark>(m_DisableDepth);
	m_Surface = std::make_shared<misSurfaceRepresentation>("misLandmarkPointerRepresentation");
	m_Surface->AddProp(m_LableActor);
	m_Surface->AddProp(m_landMarkRep->GetActor(0));
	CreateLink();
}

void misLandmarkPointerRepresentation::Validate()
{
	m_Valid = true;
}

void misLandmarkPointerRepresentation::InValidate()
{
	m_Valid = false;
}

std::shared_ptr<misSpherePointLandmark> misLandmarkPointerRepresentation::GetLandMark()
{
	return m_landMarkRep;
}

std::shared_ptr<misSurfaceRepresentation> misLandmarkPointerRepresentation::GetLablel()
{
	return std::static_pointer_cast<misSurfaceRepresentation>(m_Label->GetSurface());
}

void misLandmarkPointerRepresentation::UpdateAsUnderCapture()
{
	UpdateData(UNDERCAPTURE);
}

void misLandmarkPointerRepresentation::UpdateNormal()
{
	UpdateData(NORMAL);
}

void misLandmarkPointerRepresentation::UpdateAsSelected()
{
	UpdateData(SELECTED);
}

void misLandmarkPointerRepresentation::UpdateData(LANDMARKLABELSTAUS landmarkStatus)
{
	if (m_landMarkRep)
	{
		SetLabelData(m_Id, landmarkStatus, m_labelType);
	}
}

void misLandmarkPointerRepresentation::SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType)
{
	m_Id = id;
	m_Label->SetLabelData(id, stat, lndType);
	const auto lastColor = m_Label->GetLastColor();
	SetColor(lastColor.Red, lastColor.Green, lastColor.Blue, lastColor.Alpha);
	m_landMarkRep->SetColor(lastColor.Red, lastColor.Green, lastColor.Blue);
	m_landMarkRep->SetOpacity(lastColor.Alpha);
}

void misLandmarkPointerRepresentation::GetPosition(double position[3])
{
	position[0] = m_LandmartkPosition[0];
	position[1] = m_LandmartkPosition[1];
	position[2] = m_LandmartkPosition[2];
}

shared_ptr<IRepresentation> misLandmarkPointerRepresentation::GetSurface() const
{
	return m_Surface;
}

void misLandmarkPointerRepresentation::SetVisibilityOn()
{
	m_Surface->SetVisibilityOn();
}

void misLandmarkPointerRepresentation::SetVisibility(bool value)
{
	m_Surface->SetVisibility(value);
}

void misLandmarkPointerRepresentation::SetVisibilityOff()
{
	m_Surface->SetVisibilityOff();
}

void misLandmarkPointerRepresentation::SetLandmartkPosition(misItkPointType val)
{
	m_LandmartkPosition = val;
	m_landMarkRep->SetPosition(val[0], val[1], val[2]);
}

void misLandmarkPointerRepresentation::SetPosition(const double position[3])
{
	if (position)
	{
		SetPosition(position[0], position[1], position[2]);
	}
}

void misLandmarkPointerRepresentation::SetPosition(double x, double y, double z)
{
	misItkPointType val;
	val[0] = x;
	val[1] = y;
	val[2] = z;
	auto oldPt = m_LandmartkPosition;
	SetLandmartkPosition(val);
	Validate();
	if (!m_generatedLabel)
	{
		return;
	}
	auto vec = m_LandmartkPosition - oldPt;
	auto pt = m_LabelPosition + vec;
	SetLabelPosition(pt[0], pt[1], pt[2]);
	UpdateLink();
}

void misLandmarkPointerRepresentation::SetColor(float r, float g, float b, float a)
{
	m_Surface->SetColor(r, g, b);
	m_Surface->SetOpacity(a);
}

void misLandmarkPointerRepresentation::SetCorrectionVectorForLandmarkRegistration(double mainPosition[3],
	double finalRegisteredPosition[3])
{
	auto arrowSource = vtkSmartPointer<vtkArrowSource>::New();
	// Compute a basis
	double normalizedX[3];
	double normalizedY[3];
	double normalizedZ[3];
	// The X axis is a vector from start to end
	vtkMath::Subtract(mainPosition, finalRegisteredPosition, normalizedX);
	double length = vtkMath::Norm(normalizedX);
	vtkMath::Normalize(normalizedX);
	// The Z axis is an arbitrary vector cross X
	double arbitrary[3];
	arbitrary[0] = vtkMath::Random(-10, 10);
	arbitrary[1] = vtkMath::Random(-10, 10);
	arbitrary[2] = vtkMath::Random(-10, 10);
	vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
	vtkMath::Normalize(normalizedZ);
	// The Y axis is Z cross X
	vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
	auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	// Create the direction cosine matrix
	matrix->Identity();
	for (unsigned int i = 0; i < 3; i++)
	{
		matrix->SetElement(i, 0, normalizedX[i]);
		matrix->SetElement(i, 1, normalizedY[i]);
		matrix->SetElement(i, 2, normalizedZ[i]);
	}
	// Apply the transforms
	auto transform = vtkSmartPointer<vtkTransform>::New();
	transform->Translate(finalRegisteredPosition);
	transform->Concatenate(matrix);
	transform->Scale(length, length, length);
	auto transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformPD->SetTransform(transform);
	transformPD->SetInputConnection(arrowSource->GetOutputPort());
	//Create a mapper and actor for the arrow
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	auto actor = vtkSmartPointer<misFollowerFixedArea>::New();
	actor->SetDisableDepth(m_DisableDepth);
	mapper->SetInputConnection(arrowSource->GetOutputPort());
	actor->SetUserMatrix(transform->GetMatrix());
	actor->GetProperty()->SetColor(0.0, 1.0, 1.0);
	actor->SetMapper(mapper);
	m_Surface->AddProp(actor);
}

void misLandmarkPointerRepresentation::SetLabelPosition(const double position[3])
{
	SetLabelPosition(position[0], position[1], position[2]);
}

void misLandmarkPointerRepresentation::SetLabelPosition(double x, double y, double z)
{
	m_LabelPosition[0] = x;
	m_LabelPosition[1] = y;
	m_LabelPosition[2] = z;
	m_Label->SetPosition(m_LabelPosition.GetDataPointer());
	UpdateLink();
	Validate();
	m_generatedLabel = true;
}

void misLandmarkPointerRepresentation::UpdateLink()
{
	m_plineSource->SetPoint1(m_LandmartkPosition[0], m_LandmartkPosition[1], m_LandmartkPosition[2]);
	m_plineSource->SetPoint2(m_LabelPosition[0], m_LabelPosition[1], m_LabelPosition[2]);
}

void misLandmarkPointerRepresentation::CreateLink()
{
	m_LineActor = vtkSmartPointer<vtkActor>::New();
	m_plineSource = vtkLineSource::New();
	auto pLineMapper = vtkPolyDataMapper::New();
	pLineMapper->SetInputConnection(m_plineSource->GetOutputPort());
	auto pactor = dynamic_cast<vtkActor*>(m_LineActor.GetPointer());
	if (pactor)
	{
		pactor->SetMapper(pLineMapper);
	}
	m_Surface->AddProp(m_LineActor);
}

bool misLandmarkPointerRepresentation::IsValid() const
{
	return m_Valid;
}

vector<misSurfaceRepresentation> misLandmarkPointerRepresentation::GetAlllRepresentations()
{
	vector<misSurfaceRepresentation>  repList;
	return  repList;
}

void misLandmarkPointerRepresentation::SetCategory(misLandmarkType val)
{
	m_Category = val;
	m_Label->SetCategory(val);
	auto lastColor = m_Label->GetLastColor();
	SetColor(lastColor.Red, lastColor.Green, lastColor.Blue, lastColor.Alpha);
}

void misLandmarkPointerRepresentation::UpdateColorWithCategory()
{
	SetCategory(m_Category);
}

misLandmarkType misLandmarkPointerRepresentation::GetCategory() const
{
	return m_Category;
}

void misLandmarkPointerRepresentation::HideLandmarkLable()
{
	auto actors = m_Surface->GetActors();
	actors.erase(std::remove(actors.begin(), actors.end(), m_LableActor), actors.end());
	actors.erase(std::remove(actors.begin(), actors.end(), m_LineActor), actors.end());
	m_Surface->Reset();
	for (auto prop : actors)
	{
		m_Surface->AddProp(prop);
	}
}