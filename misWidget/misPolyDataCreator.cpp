#include "stdafx.h"
#include "..\Header\misPolyDataCreator.h"


misPolyDataCreator::misPolyDataCreator(int numLines, int numPoints): m_Lines(vtkSmartPointer<vtkCellArray>::New()),
                                                                     m_Points(vtkSmartPointer<vtkPoints>::New())
{
	m_Points->Allocate(numPoints);
	const auto lineCount = m_Lines->EstimateSize(numLines, 2);
	m_Lines->Allocate(lineCount);
}

void misPolyDataCreator::InsertLine(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double pt1[3] = {x1, y1, z1}, pt2[3] = {x2, y2, z2};
	vtkIdType ptIds[2] = {m_Points->InsertNextPoint(pt1), m_Points->InsertNextPoint(pt2)};
	m_Lines->InsertNextCell(2, ptIds);
}

void misPolyDataCreator::ApplyToPolyData(vtkPolyData* polyData) const
{
	polyData->SetPoints(m_Points);
	polyData->SetLines(m_Lines);
}
