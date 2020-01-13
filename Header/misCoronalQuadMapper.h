#pragma once
#include "misabstractquadmapper.h"

class misCoronalQuadMapper :
	public misAbstractQuadMapper
{
private:
//	void UpdateSliderInMapper(float slide, int groupIndex);
public:

	//static misCoronalQuadMapper*  New();
	//virtual  double *  GetBounds();


	//virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	//void SetMatrixTransform( tgt::mat4 transformMatrix, int groupIndex);
	//double*				GetDimention();

	misCoronalQuadMapper(IMAGEORIENTATION imageOrientation);
	~misCoronalQuadMapper(void);
	//PointType* GetPlaneCoord();
	//void GeneratePlaneMesh(misTexturePropertyStruct prop );
};
