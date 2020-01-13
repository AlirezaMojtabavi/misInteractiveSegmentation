#include "misGeoActor.h"
#include "misMacros.h"

class misTorus
{
	misPrivateVariableWithPublicAccessorsMacro(vtkSmartPointer<vtkActor2D>, m_TorusActor, TorusActor);

public:
	misTorus(double CrossSectionRadius, double RingRadius, double zElement);

	void TranslateTorus(double* position);

	vtkMatrix4x4*	GetTransformMatrix()
	{
		return transformMatrix;
	};

private:
	vtkMatrix4x4* transformMatrix;
	void CreateTorus(double CrossSectionRadius, double RingRadius, double zElement);
};
