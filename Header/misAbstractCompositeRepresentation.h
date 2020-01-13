//#pragma once
//#include "mis3drepresentation.h"
//#include "misCompositeImageMapper.h"
//#include "misStrctLayer.h"
//#include "misImageGeoProperties.h"
//#include "misImageSlicerAbstract.h"
//#include "vtkOpenGLTexture.h"
//#include "igstkMacros.h"
//#define   LayerCount  4
//
//
//class misAbstractCompositeRepresentation :	public mis3dRepresentation,public  misImageSlicerAbstract
//{
//protected:
//	vtkActor* m_CpActor;
//	misCompositeImageMapper* m_CpMapper;
//	GLuint textureID1,textureID2;
//	vector<misStrct3DLayer::Pointer>  m_Layers;
//	misImageViewingType m_ImageViewingType;
//
//
//	PointType  m_p1;
//	PointType  m_p2;
//	PointType  m_p3;
//	PointType  m_p4;
//	double m_PlaneWidth ;
//	double m_PlaneHeight;
//	double     m_ImagePosition[3];
//	IMAGEORIENTATION  m_Orientation;
//	double     m_CurrentImagePosition;
//	
//	void				Reset();
//	virtual void		SetLayerStatus(int index, LayerStatus status);
//	virtual LayerStatus GetLayerStatus(int index);
//	virtual void		SetLoadStatus(int index, bool status);
//	virtual bool		GetLoadStatus(int index);
//	virtual void		Update(void); 
//
//public:
//	misAbstractCompositeRepresentation(void);
//	~misAbstractCompositeRepresentation(void);
//
//	igstkStandardClassBasicTraitsMacro(misAbstractCompositeRepresentation,mis3dRepresentation);
//
//	virtual void		GeneartePlaneMesh(PointType  p1,PointType p2 ,PointType p3)=0;
//	virtual void		SetSlice(float  value)=0;
//	virtual void		SetTexture( vtkOpenGLTexture* pTexture,misPlanePoint  plane,misImageDataModality  modality);
//	virtual void		SetTexture( int layerIndex,vtkOpenGLTexture* pTexture,misPlanePoint  plane,misImageDataModality  modality);
//	virtual void		SetTextureTransform(vtkTransform*  pTrans);
//	virtual void		SetImageProperties(misImageGeoProperties   prop);
//	virtual void		SetImageData( int layerIndex, vtkImageData* pImage);
//	virtual void		CreatePlane( vtkImageData* pImage )=0;
//	virtual void		SetCurrentImagePos( double currentImagePosition )=0;
//	virtual void		SetSliceNumber(int slice)=0;
//	virtual void		SetWindowLevel( int layerIndex, double window,double  level);
//	virtual void		GrayscaleColorMappingOff();
//	virtual void		GrayscaleColorMappingOn();
//	virtual void		GrayscaleColorMappingOff(int index);
//	virtual void		GrayscaleColorMappingOn(int index);
//	virtual void		SetWindowLevel(double window, double level);
//
//	void	SetImageData( vtkImageData* pImage );
//	void	setID(int textureid, int index);
//	void	RemoveLayer(int layerIndex);
//	void	RemoveLayer(vtkImageData*  pSourceImage);
//	void	SetLookUpTable( int layerIndex, vtkLookupTable *lookupTable );
//	void	InitilizeLaers();
//	
//	
//	virtual PointType			GetCenter();
//	virtual double*				GetDimention();
//	virtual PointType*			GetPlaneCoord();
//	vtkActor*					GetQuadPlane();
//	double*						GetCurrentImagePosition(void);
//	double						GetCurrentImagePositionInDr() ;
//	misCompositeImageMapper*	GetMapper();
//	vtkImageData*				GetImage();
//	vtkTexture*					GetTexure(int index);
//	misAbstractCompositeRepresentation(string name);
//
//
//	
//	
//	
//	
//
//};
//
//
//
