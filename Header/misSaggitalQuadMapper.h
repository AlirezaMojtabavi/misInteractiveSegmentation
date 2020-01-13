#pragma once
#include "misabstractquadmapper.h"
#include "matrix.h"

class misSaggitalQuadMapper :
	public misAbstractQuadMapper
{
private:
//	void UpdateSliderInMapper(float slide , int groupIndex);
public:
		
	//static misSaggitalQuadMapper*  New();

	//virtual  double *  GetBounds();
	//void SetMatrixTransform(tgt::mat4 transformMatrix,int groupIndex);
	//virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	//double*				GetDimention();

	misSaggitalQuadMapper(IMAGEORIENTATION imageOrientation);
	~misSaggitalQuadMapper(void);
	//void GeneratePlaneMesh(misTexturePropertyStruct prop );
	//PointType* GetPlaneCoord();
};
