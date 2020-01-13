#include "stdafx.h"
#include "misExtensionVirtualTipBuilder.h"


 

vtkSmartPointer<vtkPolyData> parcast::misExtensionVirtualTipBuilder::CreateVirtualTip(double length)
{
 	const double minorMarkLength = 1, majorMarkLength = 5;

		auto majorIntervalMultiple = static_cast<int>(majorMarkLength / minorMarkLength);
		if (majorIntervalMultiple < 1)
			majorIntervalMultiple = 2;
		auto linePoints = vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkCellArray> polyLineCells = vtkSmartPointer<vtkCellArray>::New();
		auto lastCenterPointId = linePoints->InsertNextPoint(0, 0, 0);
		for (auto i = 1; i * minorMarkLength < length; ++i)
		{
			const auto z = i * minorMarkLength;
			const auto markLength = i % majorIntervalMultiple == 0 ? majorMarkLength/2.0 : minorMarkLength;
			const auto markCenterPointId = linePoints->InsertNextPoint(0, 0, z);
			const auto markEndPoint1Id = linePoints->InsertNextPoint(markLength, 0, z);
			const auto markEndPoint2Id = linePoints->InsertNextPoint(-markLength, 0, z);
			const auto markEndPoint3Id = linePoints->InsertNextPoint(0, markLength / 2.0, z);
			const auto markEndPoint4Id = linePoints->InsertNextPoint(0, -markLength / 2.0, z);
			polyLineCells->InsertNextCell(10);
			polyLineCells->InsertCellPoint(lastCenterPointId);
			polyLineCells->InsertCellPoint(markCenterPointId);
			polyLineCells->InsertCellPoint(markEndPoint1Id);
			polyLineCells->InsertCellPoint(markCenterPointId);
			polyLineCells->InsertCellPoint(markEndPoint2Id);
			polyLineCells->InsertCellPoint(markCenterPointId);
			polyLineCells->InsertCellPoint(markEndPoint3Id);
			polyLineCells->InsertCellPoint(markCenterPointId);
			polyLineCells->InsertCellPoint(markEndPoint4Id);
			polyLineCells->InsertCellPoint(markCenterPointId);
			lastCenterPointId = markCenterPointId;
		}
		polyLineCells->InsertNextCell(2);
		const auto lastLinePoint = linePoints->InsertNextPoint(0, 0, length);
		polyLineCells->InsertCellPoint(lastCenterPointId);
		polyLineCells->InsertCellPoint(lastLinePoint);
		auto linePolyData = vtkSmartPointer<vtkPolyData>::New();
		linePolyData->SetPoints(linePoints);
		linePolyData->SetLines(polyLineCells);
		return linePolyData;
	}
 
