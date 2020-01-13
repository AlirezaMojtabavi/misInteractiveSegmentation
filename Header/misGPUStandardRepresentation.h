#pragma once
#include "misGpuRepresentation.h"
//#include "misTextureStrcts.h"
#include "misAbstractQuadMapper.h"

class misGPUStandardRepresentation : public misGpuRepresentation
{
public:
	igstkStandardClassBasicTraitsMacro(misGPUStandardRepresentation,misGpuRepresentation);
	static Pointer New(string name);
	////////////////////////////--Virtual--//////////////////////////////////////////////
	// 	void SetSliceNumber(int slice);
	// 	void SetSliceNumber(misPlaneEnum planeIndex , int slice);//2nd	

	// 	void SetSliceValueIn01Range(float slice);
	// 	void SetSliceValueIn01Range(misPlaneEnum planeIndex , float slice);//2nd
	// 	void SetCurrentImagePos( double currentImagePosition );
	// 	void SetCurrentImagePos( misPlaneEnum planeIndex , double currentImagePosition );//2nd
	IMAGEORIENTATION GetOrientation() ;

	void	SetTextureTransform(misPlaneEnum planeIndex, tgt::mat4 pTrans);
	//void	SetCorrelatedSlice();

	//	int		GetNumberOfSliceInDirection( misPlaneEnum planeIndex ) const;
	// 	int		GetCorrespondingInedx( double slice );
	// 	double	GetCorrespondingSliceNumber( int index );

	//	void SetOrientationTransform(vtkTransform* OrntTransform);
	void SetCornerProperties(misCornerProperties* pCornerProp);
	//	void DrawPlaneGeometry();

protected:
	misAbstractQuadMapper* m_Mapper;
	misCornerProperties*	m_CornerProperties;
	// 	void	SetSlice(float  value);
	// 	void	SetSlice(misPlaneEnum planeIndex , float value);//2nd

private:
	misGPUStandardRepresentation(string  name);
	~misGPUStandardRepresentation();

	// 	int m_ExtentMax;
	// 	int m_ExtentMin;
	// 	double m_spacing;

	void GeneratePlaneMesh( misTexturePropertyStruct prop);
	void GeneratePlaneMesh( misPlaneEnum planeIndex , misTexturePropertyStruct prop);
	// 	float GetSlice( misPlaneEnum planeIndex );
	// 	float GetSlice();

	void SetRepresentationType();
	void SetCornerProperties();
};