#include "stdafx.h"

#include <vtkPolyDataMapper.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include "ExtLibWrappers/GeneralVirtualTipBuilder.h"

using namespace parcast;

GeneralVirtualTipBuilder::GeneralVirtualTipBuilder()
 {
}

vtkSmartPointer<vtkPolyData> GeneralVirtualTipBuilder::CreateVirtualTip(const double length)
{
 	return CreateStraightLinePolyData(length);
}


vtkSmartPointer<vtkPolyData> GeneralVirtualTipBuilder::CreateStraightLinePolyData(double length)
{
	auto virtualTipLineSource = vtkSmartPointer<vtkLineSource>::New();
	virtualTipLineSource->SetPoint1(0, 0, 0);
	virtualTipLineSource->SetPoint2(0, 0, length);
	const auto linePolyData = virtualTipLineSource->GetOutputPort();
	auto edgesTuber = vtkSmartPointer<vtkTubeFilter>::New();
	edgesTuber->SetInputConnection(linePolyData);
	edgesTuber->SetNumberOfSides(18);
	edgesTuber->SetRadius(.30);
	edgesTuber->Update();
	auto polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->DeepCopy(edgesTuber->GetOutput());
	return polydata;
}
