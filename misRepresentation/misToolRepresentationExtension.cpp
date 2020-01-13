#include "stdafx.h"

#include "misToolRepresentationExtension.h"
#include "misToolProperties.h"


misToolRepresentationExtension::misToolRepresentationExtension(const std::string& name,
	std::shared_ptr<parcast::IVirtualTipBuilder> virtualTipBuilder)
	: m_VirtualTipBuilder(virtualTipBuilder)
{
	m_ToolProperties.SetShowVirtualTip(false);
}

misToolRepresentationExtension::misToolRepresentationExtension(const misToolProperties& tool,
	std::shared_ptr<parcast::IVirtualTipBuilder> virtualTipBuilder)
	:m_ToolProperties(tool), m_VirtualTipBuilder(virtualTipBuilder)
{
}


bool misToolRepresentationExtension::operator==(misToolRepresentationExtension& right)
{
	return GetToolProperties().toolName == right.GetToolProperties().toolName;
}

void misToolRepresentationExtension::UpdateVirtualTipParameters(double length) const
{
	if (!m_VirtualTipActor)
	{
		return;
	}
	const auto virtualTipPolyData = m_VirtualTipBuilder->CreateVirtualTip(length);
	m_VirtualPolyDataMapper->SetInputData(virtualTipPolyData);
}



void misToolRepresentationExtension::SetToolRepresentationType(misToolRepresentationType toolRepType)
{
	m_ToolRepType = toolRepType;
	 
}

 
void misToolRepresentationExtension::SetToolProperties(misToolProperties  toolProperties, misToolRepresentationType  currentToolRepType)
{
	m_ToolRepType = currentToolRepType;
	m_ToolProperties = toolProperties;
}

void misToolRepresentationExtension::SetColor(float r, float g, float b)
{

	if (r < 0)
	{
		r = 0;
	}
	else if (r > 1)
	{
		r = 1;
	}

	if (g < 0)
	{
		g = 0;
	}
	else if (g > 1)
	{
		g = 1;
	}

	if (b < 0)
	{
		b = 0;
	}
	else if (b > 1)
	{
		b = 1;
	}

	tgt::vec3 torusColor;

	///      torus color
	if (m_ToolProperties.useSameColorOfToolForTorus)
	{
		torusColor[0] = r;
		torusColor[1] = g;
		torusColor[2] = b;
	}
	else  // use opposite color
	{
		torusColor[0] = abs(1 - r);
		torusColor[1] = abs(1 - g);
		torusColor[2] = abs(1 - b);
	}
	tgt::vec3 virtaulToolColor;
	///              virtaul tool color
	if (m_ToolProperties.useSameColorOfToolForVirtualTool)
	{
		virtaulToolColor[0] = r;
		virtaulToolColor[1] = g;
		virtaulToolColor[2] = b;
	}
	else  // use opposite color
	{
		virtaulToolColor[0] = abs(1 - r);
		virtaulToolColor[1] = abs(1 - g);
		virtaulToolColor[2] = abs(1 - b);
	}

	for (const auto& actor : m_Surface->GetActors())
	{
		auto pActor = dynamic_cast<vtkActor*>(actor.GetPointer());
		if (!pActor)
			continue;
		
		 if (pActor == m_VirtualTipActor.GetPointer())
		{
			pActor->GetProperty()->SetColor(m_ToolProperties.virtaulToolColor[0], m_ToolProperties.virtaulToolColor[1],
				m_ToolProperties.virtaulToolColor[2]);
		}
		else
		{
			pActor->GetProperty()->SetColor(r, g, b);
			pActor->GetProperty()->SetAmbient(0.2);
		}
	}
}

 

void misToolRepresentationExtension::SetVirtualTipLength(double length)
{
	UpdateVirtualTipParameters(length);
}

vtkSmartPointer<vtkActor> misToolRepresentationExtension::CreateActor(
	misToolRepresentationType currentToolRepTypemisToolProperties)
{
	if (currentToolRepTypemisToolProperties == RealModel2D ||
		currentToolRepTypemisToolProperties == SpatialObj2D ||
		currentToolRepTypemisToolProperties == BiopsySpatialObj2D)
		return vtkSmartPointer<mis2DToolActor>::New();
	return vtkSmartPointer<vtkActor>::New();
}

vtkSmartPointer<vtkActor> misToolRepresentationExtension::SetPolyData(vtkSmartPointer<vtkPolyData> polyData, misToolProperties toolProperties,
	misToolRepresentationType currentToolRepTypemisToolProperties)
{
	if (!polyData)
		return nullptr;
	SetToolProperties(toolProperties, currentToolRepTypemisToolProperties);
	auto  mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);
	mapper->ScalarVisibilityOff();
	auto actor = CreateActor(currentToolRepTypemisToolProperties);
	actor->SetMapper(mapper);
	m_Surface->AddProp(actor);
	if (actor)
	{
		actor->GetProperty()->SetOpacity(1.0);
	}
	m_MainActor = actor;



	if (!m_VirtualTipActor)
	{
		m_VirtualTipActor = CreateActor(currentToolRepTypemisToolProperties);
		m_Surface->AddProp(m_VirtualTipActor);
		m_VirtualTipActor->SetVisibility(true);
		m_VirtualTipActor->SetMapper(m_VirtualPolyDataMapper);
		m_VirtualTipActor->Modified();
	}

	return actor;
}

void misToolRepresentationExtension::SetVisibilityOff(void)
{
	SetVisibility(false);
}

void misToolRepresentationExtension::SetVisibilityOn(void)
{
	SetVisibility(true);
}


void misToolRepresentationExtension::SetVisibility(bool visibility)
{
	auto actors = m_Surface->GetActors();
	for (const auto& actor : actors)
		actor->SetVisibility(visibility);
}
 

misToolProperties misToolRepresentationExtension::GetToolProperties(void)
{
	return this->m_ToolProperties;
}

 
void misToolRepresentationExtension::SetVirtualTipVisibility(bool value)
{
	m_ToolProperties.SetShowVirtualTip(true);
}

std::shared_ptr<IRepresentation> misToolRepresentationExtension::GetSurface() const
{
	return m_Surface;
}

void misToolRepresentationExtension::SetUserTransform(vtkTransform *transform)
{
	m_Surface->SetUserTransform(transform);
}
