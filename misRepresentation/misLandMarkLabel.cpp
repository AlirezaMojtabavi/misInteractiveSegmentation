#include "StdAfx.h"
#include "misLandMarkLabel.h"

#include "mis3DLabeRepresentationl.h"
#include "misFollowerFixedArea.h"
#include "misSurfaceRepresentation.h"
#include "ILandmarkColor.h"

misLandMarkLabel::misLandMarkLabel(std::shared_ptr<parcast::ILandmarkColor> landmarkColor, double radius, bool disabledepth) :
	m_LndStatus(NORMAL),
	m_LndType(NUMERICALLANDMARK),
	m_LandmarkColor(landmarkColor),
	m_Radious(radius),
	m_DisableDepth(disabledepth)
{
	m_Surface = std::make_shared<misSurfaceRepresentation>("lansmark");
	m_textActor = vtkSmartPointer<misFollowerFixedArea>::New();
	m_textActor->SetDisableDepth(m_DisableDepth);
	m_Plane = vtkSmartPointer<vtkPlaneSource>::New();
	SetLabelRadious(m_Radious);
	auto texturePlane = vtkTextureMapToPlane::New();
	texturePlane->SetInputConnection(m_Plane->GetOutputPort());
	texturePlane->AutomaticPlaneGenerationOn();
	auto pMapper = vtkPolyDataMapper::New();
	pMapper->SetInputConnection(texturePlane->GetOutputPort());
	m_textActor->SetMapper(pMapper);
	m_Surface->AddProp(m_textActor);
	m_Category = UnkownLandmarkType;
	m_CurrentColor.InVisible();
}

void misLandMarkLabel::SetPosition(double position[3])
{
	m_Surface->SetPosition(position);
}

vtkProp* misLandMarkLabel::GetActor()
{
	return m_textActor;
}

std::shared_ptr<misSurfaceRepresentation> misLandMarkLabel::GetSurface() const
{
	return m_Surface;
}

void misLandMarkLabel::SetLabelRadious(double radious)
{
	m_Plane->SetOrigin(-radious, -radious, 0);
	m_Plane->SetPoint1(-radious, radious, 0);
	m_Plane->SetPoint2(radious, -radious, 0);
}

void misLandMarkLabel::SetLabelData(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE lndType)
{
	if ((id == m_LabelId) && (stat == m_LndStatus) && (lndType == m_LndType))
	{
		return;
	}

	m_LabelId = id;
	m_LndStatus = stat;
	m_LndType = lndType;

	auto pResManeger = misVisualizationResourceManager::GetInstance();
	auto texture = pResManeger->GetLandmarkTexture(m_LabelId, m_LndType);
	if (texture)
	{
		m_textActor->SetTexture(texture);
	}
	else
	{
		cout << "Texture does not exist for landmark : " << m_LabelId << endl;
	}
	UpdateColor();
}

void misLandMarkLabel::SetTexture(vtkTexture* ptexture)
{
	m_textActor->SetTexture(ptexture);
}

bool misLandMarkLabel::IsValid() const
{
	return m_Valid;
}

void misLandMarkLabel::SetValidation(bool val)
{
	m_Valid = val;
}

misLandmarkType misLandMarkLabel::GetCategory() const
{
	return m_Category;
}

void misLandMarkLabel::SetCategory(misLandmarkType val)
{
	m_Category = val;
	UpdateColor();
}

void misLandMarkLabel::UpdateColor()
{
	m_CurrentColor = m_LandmarkColor->GetColor(m_Category, m_LndStatus);
	m_Surface->SetColor(m_CurrentColor.Red, m_CurrentColor.Green, m_CurrentColor.Blue);
	m_Surface->SetOpacity(m_CurrentColor.Alpha);
}

misDoubleColorStruct misLandMarkLabel::GetLastColor()
{
	return m_CurrentColor;
}