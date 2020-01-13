#pragma once

#include "misCornerProperties.h"
#include "misSimplePointType.h"

class misQuadMapperBase:public vtkMapper
{
public:
	
	misQuadMapperBase(void);
	virtual void BuildPlane()=0;
	virtual void SetShaderVariables(vtkRenderer *ren, vtkActor *a)  = 0;
	typedef itk::Point<double, 3> PointType;
	tgt::vec3     GetCenter()    ;    
	virtual void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp) ;
	double * GetBounds();
	void	GeneratePlaneMesh(misTexturePropertyStruct prop);
	virtual void	UpdatePlaneAndTexturePoints()=0;
	virtual void	SetInitialSetting()=0;
	virtual void	InitializeCoorinatePoints()=0;

protected:

	std::shared_ptr<ICornerProperties> m_CornerProperties;
	misSimplePointType	m_P1;
	misSimplePointType	m_P2;
	misSimplePointType	m_P3;
	misSimplePointType	m_P4;
	misSimplePointType	m_Coordinate1;
	misSimplePointType	m_Coordinate2;
	misSimplePointType	m_Coordinate3;
	misSimplePointType	m_Coordinate4;

	struct  Point{
		float x;
		float y;
		float z;
	};

	struct PlaneCoordionatePropertiesStrct
	{
		tgt::mat4 Transform = tgt::mat4::identity;
		tgt::vec4 TransformedPoints[4];
	};
	std::vector<PlaneCoordionatePropertiesStrct> m_GroupCoordinateProperties;
	tgt::vec4		m_InitialPoints[4];
	IMAGEORIENTATION m_Orientation;
	misSimplePointType m_OrintationDir;
	tgt::mat4  m_OrientationTransform;
	double*  m_Bounds;
};

