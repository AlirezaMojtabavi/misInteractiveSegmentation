#pragma once

class vtkTransformPolyDataFilter;
class IImplantSource;

class misImplantPlan3D
{
public:
	misImplantPlan3D(std::shared_ptr<IImplantSource> implantSource);
	vtkAlgorithmOutput* GetOutputPort();

private:
	const double LineRadius = 0.2;
	const double LineHeight = 1000;
	const double LineResolution = 10;

	void UpdateTransform();
	bool IsTransformChanged();
	void Update();
	void AppendMiddleLine();

	vtkSmartPointer<vtkCylinderSource> m_LineSource = vtkSmartPointer<vtkCylinderSource>::New();
	std::shared_ptr<IImplantSource> m_SimpleLineImplant;
	vtkSmartPointer<vtkTransformPolyDataFilter> m_Transform = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	vtkSmartPointer<vtkAppendPolyData> m_AppendFilter;
};

