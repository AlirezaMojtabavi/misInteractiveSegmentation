#pragma once
class misPolyDataCreator
{
public:
	misPolyDataCreator(int numLines, int numPoints);

misPolyDataCreator(const misPolyDataCreator&) = delete;	// No copy

void InsertLine(double x1, double y1, double z1, double x2, double y2, double z2);

	void ApplyToPolyData(vtkPolyData* polyData) const;

	private:
		vtkSmartPointer<vtkPoints> m_Points;
		vtkSmartPointer<vtkCellArray> m_Lines;
	};
 

