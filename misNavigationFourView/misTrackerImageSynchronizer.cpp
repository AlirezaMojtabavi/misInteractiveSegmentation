#include "stdafx.h"
#include "misTrackerImageSynchronizer.h"

#include "IVolumeSlicer.h"
#include "ICornerProperties.h"
#include "IPanoramicViewer.h"
#include "IToolShapeBuilder.h"
#include "misMathUtils.h"
#include "misPanoramicToolCoordSysRenderer.h"
#include "misToolCoordinateSystemRenderer.h"
#include "misTransform.h"
#include "IToolRepresentationDecider.h"


using namespace parcast;


misTrackerImageSynchronizer::misTrackerImageSynchronizer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >
	correlation, std::shared_ptr<IToolShapeBuilder> toolBuidler, std::shared_ptr<IToolRepresentationDecider> toolRepDecider)
	:m_CSCorrelationManager(correlation), m_VirtualLenght(0), m_ToolShapeBuilder(toolBuidler), m_ToolRepDecider(toolRepDecider)
{
}


void misTrackerImageSynchronizer::SetToolPosition(double* center)
{

	for (auto viewer : m_Viewers)
	{
		viewer.first->SetToolPosition(center[0], center[1], center[2]);
		if (m_PanoramicCoordinateConverter)
			m_PanoramicCoordinateConverter->SetImageCoordinates(center[0], center[1], center[2]);
	}
}

void misTrackerImageSynchronizer::AddToolRepresentation(misToolProperties toolData, std::string toolCoordinate)
{

	// Transformation tool properties
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> toolRenderers;
	// Rendering tool properties
	std::vector<std::shared_ptr<misToolRepresentation>> toolRepresentators;

	std::vector<std::shared_ptr<IVolumeRenderer>> viewers;
	std::vector<ToolVisulizationProp> props;
	for (const auto viewer : m_Viewers)
	{
		viewers.push_back(viewer.first);
		props.push_back(viewer.second);
	}

	for (auto index = 0; index < viewers.size(); index++)
	{
		if (!toolData.HasApplicationFlag(misToolProperties::Navigation) ||
			viewers[index]->HasRepresentationByName(toolData.partNumber))
		{
			return;
		}

		const misToolRepresentationType toolType = m_ToolRepDecider->GetToolRepType(viewers[index]);
		m_ToolShapeBuilder->SetToolRepresentationParam(toolType, toolData, props[index].ShowToolExtenstion);
		auto newToolRep = m_ToolShapeBuilder->GetToolRepresentation();
		std::shared_ptr<ICoordinateSystemRenderer> toolRenderer =
			std::make_shared<misToolCoordinateSystemRenderer>(newToolRep, m_CSCorrelationManager);
		const auto typeDirection = viewers[index]->GetTypeDirection();
		if (typeDirection == PanormaicView)
		{
			std::shared_ptr<ICoordinateSystemRenderer> panoramicToolRenderer =
				std::make_shared<misPanoramicToolCoordSysRenderer>(newToolRep, m_CSCorrelationManager,
					m_PanoramicTransformConvertor);
			panoramicToolRenderer->SetCoordinateSystem(toolCoordinate);
			viewers[index]->AddRepresentation(newToolRep->GetSurface());
			viewers[index]->AddCoordinateSytemRenderer(panoramicToolRenderer);
			m_ToolRenderers.push_back(panoramicToolRenderer);
		}
		else
		{
			toolRenderer->SetCoordinateSystem(toolCoordinate);
			viewers[index]->AddRepresentation(newToolRep->GetSurface());
			viewers[index]->AddCoordinateSytemRenderer(toolRenderer);
			m_ToolRenderers.push_back(toolRenderer);
		}
		m_ToolRepresentators.push_back(newToolRep);
		m_ViewrToolsMap[viewers[index]].push_back(newToolRep);
	}
	for (auto& tool : m_ToolRepresentators)
	{
		tool->SetVirtualTipLength(m_VirtualLenght);
	}
}

void misTrackerImageSynchronizer::AddToolRepresentation(std::shared_ptr<ITrackingTool> toolData)
{
	if (toolData->GetAxisDynamicFeature())
		AddToolRepresentation(toolData->GetToolProperties(), toolData->GetAxisDynamicFeature()->GetUID());
	else
		AddToolRepresentation(toolData->GetToolProperties(), toolData->GetUID());
}

void misTrackerImageSynchronizer::SetRenderingToolSceneReference(std::string refernce)
{
	std::for_each(m_ToolRenderers.begin(), m_ToolRenderers.end(), [&](std::shared_ptr<ICoordinateSystemRenderer> toolRenderer)
	{
		toolRenderer->SetRefrenceCoordinate(refernce);
	});
}

void misTrackerImageSynchronizer::SetToolTransform(vtkMatrix4x4* toolTransform)
{
	for (auto viewer : m_Viewers)
	{
		auto virtualTransform = vtkSmartPointer<vtkTransform>::New();
		virtualTransform->Concatenate(toolTransform);
		if (viewer.second.UpdateByVirtualTip)
		{
			virtualTransform->Translate(0, 0, m_VirtualLenght);
			for (auto tool : m_ViewrToolsMap[viewer.first])
				tool->SetVirtualTipVisibility(true);
		}
		else
		{
			for (auto tool : m_ViewrToolsMap[viewer.first])
				tool->SetVirtualTipVisibility(false);
		}
		virtualTransform->Update();
		viewer.first->GetCornerProperties()->SetMatrix(virtualTransform->GetMatrix());
		viewer.first->SetToolTransform(misMathUtils::CreateTransform(virtualTransform->GetMatrix()));
		auto imageViewer = std::dynamic_pointer_cast<IVolumeSlicer>(viewer.first);
		if (imageViewer)
			imageViewer->UpdateImage(true);
	}
}

void misTrackerImageSynchronizer::UpdateVirtualTipLength(double lenght)
{
	m_VirtualLenght = lenght;
	std::for_each(m_ToolRepresentators.begin(), m_ToolRepresentators.end(), [&](auto toolRep)
	{
		toolRep->SetVirtualTipLength(lenght);
	});
}

void misTrackerImageSynchronizer::ShowTorus(bool visibility)
{

	std::for_each(m_ToolRepresentators.begin(), m_ToolRepresentators.end(), [visibility](auto toolRep)
	{
		toolRep->SetTorusVisibility(visibility);
	});
}

void misTrackerImageSynchronizer::SetViewers(std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp> val)
{
	ClearViewers();
	m_Viewers = val;
}

void misTrackerImageSynchronizer::ClearViewers()
{
	m_ViewrToolsMap.clear();
	m_Viewers.clear();
}

void misTrackerImageSynchronizer::SetPanoramicTransformConvertor(std::shared_ptr<IPanoramicTransformConverter> val)
{
	m_PanoramicTransformConvertor = val;
	for (auto rendererItr = m_ToolRenderers.begin(); rendererItr != m_ToolRenderers.end(); ++rendererItr)
	{
		auto panoramicToolRenderer = std::dynamic_pointer_cast<misPanoramicToolCoordSysRenderer>(*rendererItr);
		if (panoramicToolRenderer)
			panoramicToolRenderer->SetPanoramicTransformConverter(m_PanoramicTransformConvertor);
	}
}

void misTrackerImageSynchronizer::Freeze()
{

	for (const auto& toolRenderer : m_ToolRenderers)
	{
		toolRenderer->RenderingOff();
	}
}

void misTrackerImageSynchronizer::Unfreeze()
{
	for (const auto& toolRenderer : m_ToolRenderers)
	{
		toolRenderer->RenderingOn();
	}
}

void misTrackerImageSynchronizer::SetPanoramicCoordinateConverter(std::shared_ptr<IPanoramicCoordinatesConverter> val)
{
	m_PanoramicCoordinateConverter = val;
}

void misTrackerImageSynchronizer::AddExistingRepresentation()
{
	m_ToolRenderers.clear();
	m_ToolShapeBuilder->Clear();
	m_ToolRepresentators.clear();
	for (const auto& tool : m_AddedTool)
		AddToolRepresentation(tool);
}

void misTrackerImageSynchronizer::AddTool(std::shared_ptr<ITrackingTool> toolData)
{
	m_AddedTool.push_back(toolData);
	AddToolRepresentation(toolData);
}