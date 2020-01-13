#include "stdafx.h"


#include "BiopsyVirtualTipBuilder.h"


using namespace parcast;

BiopsyVirtualTipBuilder::BiopsyVirtualTipBuilder()
{
}

vtkSmartPointer<vtkPolyData> BiopsyVirtualTipBuilder::CreateVirtualTip(const double length)
{
	vtkSmartPointer<vtkLineSource> m_VirtualTipLineSource = vtkSmartPointer<vtkLineSource>::New();
	m_VirtualTipLineSource->SetPoint1(0, 0, 0);
	m_VirtualTipLineSource->SetPoint2(0, 0, length);
	const auto linePolyData = m_VirtualTipLineSource->GetOutputPort();
	auto edgesTuber = vtkSmartPointer<vtkTubeFilter>::New();
	edgesTuber->SetInputConnection(linePolyData);
	edgesTuber->SetNumberOfSides(18);
	edgesTuber->SetRadius(.30);
	edgesTuber->Update();
	auto polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->DeepCopy(edgesTuber->GetOutput());
	return polydata;
}

