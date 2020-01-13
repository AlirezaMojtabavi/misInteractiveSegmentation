#include "misTypes.h"
#include "serializable.h"

struct misMatrixElement
{
	vtkSmartPointer<vtkTransform> transform;
	misUID                        objectUID;
};

