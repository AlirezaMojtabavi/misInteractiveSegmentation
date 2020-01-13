#include "StdAfx.h"
#include "misToolShapeBuilder.h"

#include "misFileReader.h"
#include "misStrctColorData.h"
#include "misToolFileAddressUtility.h"
#include "misToolRepresentation.h"
#include "misToolRepresentationExtension.h"
#include "IVirtualTipBuilder.h"
#include "BiopsyVirtualTipBuilder.h"
#include "ExtLibWrappers/GeneralVirtualTipBuilder.h"
#include "ExtLibWrappers/misExtensionVirtualTipBuilder.h"
#include "misGenericToolShape.h"

misToolShapeBuilder::misToolShapeBuilder(misApplicationType appType)
	:m_AppType(appType)
{
}

vtkSmartPointer<vtkPolyData> misToolShapeBuilder::CreateToolPolyData(const std::string& toolName)

{
	const auto modelFileName = misToolFileAddressUtility::MakeStlFilePathAndName(toolName);
	auto toolPolyData = misFileReader::ReadPolydataFromSTLFile(modelFileName);
	if (!toolPolyData)
	{
		toolPolyData = misFileReader::ReadPolydataFromOBJFile(modelFileName);
	}
	return toolPolyData;
}

std::shared_ptr<IToolRepresentation> misToolShapeBuilder::GetToolRepresentation() const
{
	return m_ToolRepresentation;
}

void misToolShapeBuilder::Clear()
{
	m_ToolRepresentation = nullptr;
}

vtkSmartPointer<vtkPolyData> misToolShapeBuilder::CreateGenericToolShape(const misToolRepresentationType toolType,
                                                                const misToolProperties& toolProp)
{
	return misGenericToolShape::GenerateToolGeometry();
 }

void misToolShapeBuilder::InitializeToolShapeColor(const misToolProperties& toolProp)
{
	if (toolProp.HasApplicationFlag(misToolProperties::Calibration))
	{
		misDoubleColorStruct color;
		color.SetColorToBlue();
		m_ToolRepresentation->SetColor(color.Red, color.Green, color.Blue);
	}
	else if (toolProp.HasApplicationFlag(misToolProperties::Reference))
	{
		misDoubleColorStruct color;
		color.SetColorToGreen();
		m_ToolRepresentation->SetColor(color.Red, color.Green, color.Blue);
	}
	else
	{
		misDoubleColorStruct color;
		color.SetColorToRed();
		m_ToolRepresentation->SetColor(color.Red, color.Green, color.Blue);
	}
}

void misToolShapeBuilder::CreateToolRepresentation(const misToolProperties& toolProp, bool measurementVirtualTipEnabled)
{
	std::shared_ptr<parcast::IVirtualTipBuilder> virtualTipBuilder;
	if (measurementVirtualTipEnabled)
	{
		virtualTipBuilder = std::make_shared<parcast::misExtensionVirtualTipBuilder>();
		m_ToolRepresentation = std::make_shared<misToolRepresentationExtension>(toolProp, virtualTipBuilder);
	
	}
	else if (m_AppType == Biopsy)
	{
		virtualTipBuilder = std::make_shared<parcast::BiopsyVirtualTipBuilder>();
		m_ToolRepresentation = std::make_shared<misToolRepresentation>(toolProp, virtualTipBuilder);
	}
	else
	{
		virtualTipBuilder = std::make_shared<parcast::GeneralVirtualTipBuilder>();
		m_ToolRepresentation = std::make_shared<misToolRepresentation>(toolProp, virtualTipBuilder);
	}
	
	 

}

void misToolShapeBuilder::SetToolRepresentationParam(const misToolRepresentationType toolType,
	const misToolProperties& toolProp, bool measurementVirtualTipEnabled)
{
	CreateToolRepresentation(toolProp, measurementVirtualTipEnabled);

	if (toolProp.partNumber == "biopTool")
	{
		auto toolName = (BiopsySpatialObj2D == toolType || SpatialObj2D == toolType) ? "biopTool2D" : "biopTool";
		auto polyData = CreateToolPolyData(toolName);
		m_ToolRepresentation->SetPolyData(polyData, toolProp, toolType);
	}
	else if (SpatialObj2D == toolType || SpatialObj3D == toolType ||
		BiopsySpatialObj2D == toolType)
	{
		const auto genericToolShape = CreateGenericToolShape(toolType, toolProp);
		m_ToolRepresentation->SetPolyData(genericToolShape, toolProp, toolType);
	}
	else
	{
		const auto polyData = CreateToolPolyData(toolProp.partNumber);
		m_ToolRepresentation->SetPolyData(polyData, toolProp, toolType);
	}

	InitializeToolShapeColor(toolProp);
	m_ToolRepresentation->SetVisibilityOff();
	
}

