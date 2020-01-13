#ifndef __misPreciseCursor_h
#define __misPreciseCursor_h

#include "misCursor.h"

class  misPreciseCursor : public misCursor
{
public:

	static misPreciseCursor *New();

protected:
	misPreciseCursor();

	void UpdateCursorColor();
	void Initialization();
	void Initialization(IMAGEORIENTATION type);

private:
	void ModifyAxis();
	void ModifyXAxis();
	void ModifyMeasurmentXAxis();
	void ModifyYAxis();
	void ModifyMeasurmentYAxis();
	void ModifyZAxis();
	void ModifyMeasurmentZAxis();
	vtkSmartPointer <vtkPolyData> Get_X() const;
	vtkSmartPointer <vtkPolyData> Get_Y() const;
	vtkSmartPointer <vtkPolyData> Get_Z() const;
	vtkSmartPointer <vtkPolyData> Get_MX() const;
	vtkSmartPointer <vtkPolyData> Get_MY() const;
	vtkSmartPointer <vtkPolyData> Get_MZ() const;
	const double FarEndPos;
	const double NearEndPos;
	const double HalfNearEnd;
	const double MajorMarkingLength;
	const double MinorMarkingLength;
	vtkSmartPointer<vtkPolyDataMapper> m_XMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_YMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_ZMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_MxMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_MyMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_MzMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkConeSource> m_XCone = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkConeSource> m_YCone = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkConeSource> m_ZCone = vtkSmartPointer<vtkConeSource>::New();
	vtkSmartPointer<vtkActor> m_XActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> m_YActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> m_ZActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> m_MxActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> m_MyActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> m_MzActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer <vtkPolyData> x_output = vtkSmartPointer <vtkPolyData>::New();
	vtkSmartPointer <vtkPolyData> y_output = vtkSmartPointer <vtkPolyData>::New();
	vtkSmartPointer <vtkPolyData> z_output = vtkSmartPointer <vtkPolyData>::New();
	vtkSmartPointer <vtkPolyData> Mx_output = vtkSmartPointer <vtkPolyData>::New();
	vtkSmartPointer <vtkPolyData> My_output = vtkSmartPointer <vtkPolyData>::New();
	vtkSmartPointer <vtkPolyData> Mz_output = vtkSmartPointer <vtkPolyData>::New();
};

#endif


