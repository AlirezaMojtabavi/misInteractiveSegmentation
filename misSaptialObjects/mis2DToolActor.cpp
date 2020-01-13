#include "stdafx.h"
#include "mis2DToolActor.h"


vtkStandardNewMacro(mis2DToolActor);

 

vtkSmartPointer<vtkTransform> mis2DToolActor::ComputeShiftTransform(vtkCamera* camera)
{
	double position[3];
	camera->GetPosition(position);
	double focalPoint[3];
	camera->GetFocalPoint(focalPoint);
	double cameraDirection[3];
	for (int i = 0; i < 3; i++)
		cameraDirection[i] = position[i] - focalPoint[i];
	vtkMath::Normalize(cameraDirection);
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->PostMultiply();
	transform->SetMatrix(this->GetMatrix());
	for (int i = 0; i < 3; i++)
		cameraDirection[i] = cameraDirection[i] * distance2Plane;
	transform->Translate(cameraDirection[0], cameraDirection[1], cameraDirection[2]);
	return transform;
}

void mis2DToolActor::Render(vtkRenderer *ren, vtkMapper *mapper)
{
	auto transform = ComputeShiftTransform(ren->GetActiveCamera());
	// build transformation
	if (!this->IsIdentity)
	{
		// compute the transposed matrix
		double mat[16];
		vtkMatrix4x4::Transpose(*transform->GetMatrix()->Element, mat);

		// insert model transformation
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixd(mat);
	}

	// send a render to the mapper; update pipeline
	mapper->Render(ren, this);

	// pop transformation matrix
	if (!this->IsIdentity)
	{
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

}