#pragma once

class  mis2DToolActor : public vtkActor
{
	const int distance2Plane = 20;
public:
	static mis2DToolActor* New();
	void Render(vtkRenderer *, vtkMapper *) override;

private:

	vtkSmartPointer<vtkTransform> ComputeShiftTransform(vtkCamera* camera);

};

