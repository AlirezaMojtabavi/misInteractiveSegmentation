//#pragma once
//#include "misAbstractCompositeRepresentation.h"
//#include "vtkActor.h"
//#include "igstkMacros.h"
//
//
//class misCompositePlaneRepresentation :public misAbstractCompositeRepresentation
//{
//protected:
//
//public:
//	
//	misCompositePlaneRepresentation(string name);
//	~misCompositePlaneRepresentation(void);
//
//	igstkStandardClassBasicTraitsMacro(misCompositePlaneRepresentation, misAbstractCompositeRepresentation);
//
//	static Pointer New(string name);
//	virtual void GeneartePlaneMesh(PointType  p1,PointType p2 ,PointType p3);
//	
//	void			SetSlice(float  value);
//	virtual void	CreatePlane( vtkImageData* pImage );
//	virtual void	SetSliceNumber(int slice);
//	virtual void	SetCurrentImagePos( double currentImagePosition );
//	virtual  IMAGEORIENTATION	GetOrientation() ;
//	virtual void	SetImageProperties(misImageGeoProperties  prop );
//	void SetTextureID( int index,int id );
//	void PassSliceNumberToMapper(int index,float val);
//};
