#include "stdafx.h"
#include "misToolRepresentation.h"
#include "misToolProperties.h"


misToolRepresentation::misToolRepresentation(const std::string& name,
	std::shared_ptr<parcast::IVirtualTipBuilder> virtualTipBuilder)
	: m_VirtualTipBuilder(virtualTipBuilder)
{
	m_ToolProperties.showTorus = false;
	m_ToolProperties.SetShowVirtualTip(false);
	m_ToolProperties.SetShowVirtualTipTorus(false);
}

misToolRepresentation::misToolRepresentation(const misToolProperties& tool,
	std::shared_ptr<parcast::IVirtualTipBuilder> virtualTipBuilder)
	:m_ToolProperties(tool), m_VirtualTipBuilder(virtualTipBuilder)
{
}



bool misToolRepresentation::operator==(misToolRepresentation& right)
{
	return GetToolProperties().toolName == right.GetToolProperties().toolName;
}

void misToolRepresentation::UpdateVirtualTipParameters(void) const
{
	if (!m_VirtualTipActor )
	{
		return;
	}
	auto const toolVisibility = static_cast<bool>(m_Surface->GetActors()[0]->GetVisibility());
	const auto virtualTipPolyData = m_VirtualTipBuilder->CreateVirtualTip(m_ToolProperties.GetVirtualToolLength());
	m_VirtualPolyDataMapper->SetInputData(virtualTipPolyData);
	UpdateVirtualTipTorus();
}

void misToolRepresentation::UpdateTorusParameters(void) const
{
	if (!m_Torus || !m_TorusActor)
	{
		return;
	}

	m_Torus->SetCrossSectionRadius(m_ToolProperties.torusCrossSectionDiameter);
	m_Torus->SetRingRadius(m_ToolProperties.torusDiameter);
	auto torusTransform = vtkSmartPointer<vtkTransform>::New();
	torusTransform->Identity();
	torusTransform->Translate(0, 0, -m_ToolProperties.torusDistanceToToolTip);
	m_Torus->Modified();
	auto parametricFunctionSource = vtkParametricFunctionSource::New();
	parametricFunctionSource->SetParametricFunction(m_Torus);
	auto torousPolyTransform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	torousPolyTransform->SetTransform(torusTransform);
	torousPolyTransform->SetInputConnection(parametricFunctionSource->GetOutputPort());
	auto torusMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	torusMapper->SetInputConnection(torousPolyTransform->GetOutputPort());
	torusMapper->Modified();
	m_TorusActor->SetMapper(torusMapper);
	m_TorusActor->Modified();
	m_TorusActor->SetVisibility(true);
}

void misToolRepresentation::UpdateVirtualTipTorus(void) const
{
	if (!m_VirtualTipTorusActor)
	{
		return;
	}
	m_VirtualTipTorusActor->SetVisibility(false);
	if (m_ToolProperties.GetVirtualToolLength() > 0)
	{
		if (m_ToolProperties.GetShowVirtualTipTorus())
		{
			m_VirtualTipTorus->SetCrossSectionRadius(m_ToolProperties.virtualTipTorusCrossSectionDiameter);
			m_VirtualTipTorus->SetRingRadius(m_ToolProperties.virtualTipTorusDiameter);
			vtkSmartPointer<vtkTransform> virtualTipTorusTransform = vtkSmartPointer<vtkTransform>::New();
			// Z distance
			virtualTipTorusTransform->Translate(0, 0, m_ToolProperties.GetVirtualToolLength() / 2);
			m_VirtualTipTorus->Modified();
			vtkParametricFunctionSource*  parametricFunctionSource = vtkParametricFunctionSource::New();
			parametricFunctionSource->SetParametricFunction(m_VirtualTipTorus);
			auto torusPolyData = parametricFunctionSource->GetOutputPort();
			torusPolyData->Modified();
			auto torusMapper = vtkPolyDataMapper::New();
			auto polyDataTransformer = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
			polyDataTransformer->SetTransform(virtualTipTorusTransform);
			polyDataTransformer->SetInputConnection(torusPolyData);
			torusMapper->SetInputConnection(polyDataTransformer->GetOutputPort());
			torusMapper->Modified();

			m_VirtualTipTorusActor->SetMapper(torusMapper);
			m_VirtualTipTorusActor->Modified();
			m_VirtualTipTorusActor->SetVisibility(true);
		}
	}
}

void misToolRepresentation::UpdateToolProperties()
{
	UpdateVirtualTipParameters();
	UpdateShowExtraPartStatus();
}

void misToolRepresentation::SetToolRepresentationType(misToolRepresentationType toolRepType)
{
	m_ToolRepType = toolRepType;
	UpdateShowExtraPartStatus();
}

void misToolRepresentation::UpdateShowExtraPartStatus(void)
{
	m_ShowExtraActors = (
		RealModel2D == m_ToolRepType ||
		RealModel3D == m_ToolRepType ||
		SpatialObj2D == m_ToolRepType||
		SpatialObj3D == m_ToolRepType ||
		BiopsySpatialObj2D== m_ToolRepType ||
		BiopsySpatialObj3D == m_ToolRepType );

 
}

void misToolRepresentation::SetToolProperties(misToolProperties  toolProperties, misToolRepresentationType  currentToolRepType)
{
	m_ToolRepType = currentToolRepType;
	m_ToolProperties = toolProperties;
	UpdateToolProperties();
}

void misToolRepresentation::SetColor(float r, float g, float b)
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
		if (pActor == dynamic_cast<vtkActor*>(m_TorusActor.GetPointer()))
		{
			pActor->GetProperty()->SetColor(m_ToolProperties.virtaulToolColor[0], m_ToolProperties.virtaulToolColor[1],
				m_ToolProperties.virtaulToolColor[2]);
		}
		else if (pActor == m_VirtualTipActor.GetPointer())
		{
			pActor->GetProperty()->SetColor(m_ToolProperties.virtaulToolColor[0], m_ToolProperties.virtaulToolColor[1],
				m_ToolProperties.virtaulToolColor[2]);
		}
		else if (pActor == m_VirtualTipTorusActor.GetPointer())
		{
			pActor->GetProperty()->SetColor(m_ToolProperties.virtaulToolColor[0], m_ToolProperties.virtaulToolColor[1],
				m_ToolProperties.virtaulToolColor[2]);
			//pActor->GetProperty()->SetOpacity(m_ToolProperties.vrtualToolTorusOpacity);
		}
		else
		{
			pActor->GetProperty()->SetColor(r, g, b);
			pActor->GetProperty()->SetAmbient(0.2);
		}
	}
}


void misToolRepresentation::SetTorusRadious(const double radius)
{
	if (radius > 0)
	{
		m_ToolProperties.torusDiameter = radius;
	}
}

void misToolRepresentation::SetVirtualTipLength(double length)
{
	const auto mustapppliedVirtualTip = (
		RealModel2D == m_ToolRepType ||
		RealModel3D == m_ToolRepType ||
		SpatialObj2D == m_ToolRepType ||
		SpatialObj3D == m_ToolRepType ||
		BiopsySpatialObj2D == m_ToolRepType ||
		BiopsySpatialObj3D == m_ToolRepType);
	if (!mustapppliedVirtualTip)
		return;
	m_ToolProperties.SetVirtualToolLength(length);
	UpdateVirtualTipParameters();
}

vtkSmartPointer<vtkActor> misToolRepresentation::CreateActor(
	misToolRepresentationType currentToolRepTypemisToolProperties)
{
	if (currentToolRepTypemisToolProperties == RealModel2D ||
		currentToolRepTypemisToolProperties == SpatialObj2D ||
		currentToolRepTypemisToolProperties == BiopsySpatialObj2D)
		return vtkSmartPointer<mis2DToolActor>::New();
	return vtkSmartPointer<vtkActor>::New();
}

vtkSmartPointer<vtkActor> misToolRepresentation::SetPolyData(vtkSmartPointer<vtkPolyData> polyData, misToolProperties toolProperties,
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

	if (!m_TorusActor)
	{
		m_TorusActor = vtkSmartPointer<vtkActor>::New();
		m_Surface->AddProp(m_TorusActor);
		UpdateTorusParameters();
	}

	if (!m_VirtualTipActor)
	{
		m_VirtualTipActor = CreateActor(currentToolRepTypemisToolProperties);
		m_Surface->AddProp(m_VirtualTipActor);
		m_VirtualTipActor->SetVisibility(true);
		m_VirtualTipActor->SetMapper(m_VirtualPolyDataMapper);
		m_VirtualTipActor->Modified();
	}

	if (!m_VirtualTipTorusActor)
	{
		m_VirtualTipTorusActor = CreateActor(currentToolRepTypemisToolProperties);
		m_Surface->AddProp(m_VirtualTipTorusActor);
	}
	return actor;
}

void misToolRepresentation::SetVisibilityOff(void)
{
	SetVisibility(false);
}

void misToolRepresentation::SetVisibilityOn(void)
{
	SetVisibility(true);
}

void misToolRepresentation::UpdateTrousVisibility(const bool visibility) const
{
	const auto torusVisibilty = m_ShowExtraActors && m_ToolProperties.showTorus;
	if (torusVisibilty)
		m_TorusActor->SetVisibility(visibility);
	else
		m_TorusActor->VisibilityOff();
}

void misToolRepresentation::SetVisibility(bool visibility)
{
	auto actors = m_Surface->GetActors();
	for (const auto& actor : actors)
		actor->SetVisibility(visibility);
	UpdateTrousVisibility(visibility);
	UpdateVirtualTipVisibilty(visibility);

	const bool virtualTipTorusVisibilty = (m_ShowExtraActors && m_ToolProperties.GetShowVirtualTip()) &&
		(m_ToolProperties.GetShowVirtualTipTorus() && (m_ToolProperties.GetVirtualToolLength() > 0));
	if (virtualTipTorusVisibilty)
		m_VirtualTipTorusActor->SetVisibility(visibility);
	else
		m_VirtualTipTorusActor->VisibilityOff();
}

void misToolRepresentation::UpdateVirtualTipVisibilty(const bool visibility) const
{
	const auto virtualTipVisibilty = (m_ShowExtraActors && m_ToolProperties.GetShowVirtualTip() &&
		(m_ToolProperties.GetVirtualToolLength() > 0));

	if (virtualTipVisibilty )
	{
		m_VirtualTipActor->SetVisibility(visibility);
	}
	else
	{
		m_VirtualTipActor->VisibilityOff();
	}
}

misToolProperties misToolRepresentation::GetToolProperties(void)
{
	return this->m_ToolProperties;
}

void misToolRepresentation::SetTorusVisibility(const bool value)
{
	// for the reference and calibration tool, the torus must be invisible
	if ((m_ToolProperties.HasApplicationFlag(misToolProperties::Calibration) ||
		m_ToolProperties.HasApplicationFlag(misToolProperties::Reference)) && value)
	{
		m_ToolProperties.showTorus = false;
		return;
	}
	m_ToolProperties.showTorus = value;
}

void misToolRepresentation::SetVirtualTipVisibility(bool value)
{
	// for the reference and calibration tool, the torus must be invisible
	if ((m_ToolProperties.HasApplicationFlag(misToolProperties::Calibration) ||
		m_ToolProperties.HasApplicationFlag(misToolProperties::Reference)) && value)
	{
		m_ToolProperties.SetShowVirtualTip(false);
		return;
	}

	m_ToolProperties.SetShowVirtualTip(value);
}

std::shared_ptr<IRepresentation> misToolRepresentation::GetSurface() const
{
	return m_Surface;
}

void misToolRepresentation::SetUserTransform(vtkTransform *transform)
{
	m_Surface->SetUserTransform(transform);
}
