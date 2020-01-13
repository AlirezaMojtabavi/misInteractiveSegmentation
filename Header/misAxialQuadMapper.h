
#pragma once
#include "vtkmapper.h"
#include "misAbstractQuadMapper.h"
#include "vtktransform.h"
#include "itkPoint.h"
#include "matrix.h"

class misAxialQuadMapper :	public misAbstractQuadMapper
{

private:
	//void UpdateSliderInMapper( float slide , int groupIndex );
	//void UnBind();
public:

	//static misAxialQuadMapper*  New();

	//virtual void		Render(vtkRenderer *ren, vtkActor *a)  ;
	//virtual  double *	GetBounds();
	//double*				GetDimention();
	//void				GeneratePlaneMesh(misTexturePropertyStruct prop );
	//void				SetMatrixTransform( tgt::mat4 transformMatrix,int groupIndex);
	misAxialQuadMapper(IMAGEORIENTATION imageOrientation);
	~misAxialQuadMapper(void);
	//PointType* GetPlaneCoord();
	
};
