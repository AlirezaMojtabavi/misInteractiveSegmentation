#pragma once

#include "misSelectionElement.h"
#include "misTransferFunctionSelecting.h"

class vtkImageData;
class vtkMath;
class vtkImageGradientMagnitude;
class vtkAbstractVolumeMapper;
class vtkObjectFactory;
class vtkLODProp3D;
class vtkImageActor;
class vtkRenderer;
class vtkMapper;
class vtkAssemblyPath;
class vtkActorCollection;
class vtkTransform;
class vtkProperty;
class vtkRenderWindow;
class vtkProp3DCollection;
class vtkCommand;
class vtkPoints;
class vtkBox;
class vtkIdList;
class misImage;
class TransFuncIntensity;

class   misVolumePointPicker : public vtkPicker
{
public:
	misVolumePointPicker(void);
	virtual	~misVolumePointPicker(void);
	
	 
	
	float m_SurfaceValue;
public:
	static misVolumePointPicker *New();
	void PrintSelf(ostream& os, vtkIndent indent);
	vtkGetMacro(PointId, vtkIdType);
	int Pick(double selectionX, double selectionY, double selectionZ,vtkRenderer *renderer);
	void SetVolumeMapper(vtkMapper* val);
protected:
	vtkIdType PointId; //picked point
	double IntersectWithLine(double p1[3], double p2[3], double tol, vtkAssemblyPath *path, vtkProp3D *p,	vtkAbstractMapper3D *m);
	

	
	void Initialize();
	
private:
	vtkMapper*  m_VolumeMapper;
	
	
};
