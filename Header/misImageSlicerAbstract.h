#pragma once
#include "VisualizationGeneralTypes.h"
//#include "misInteractorSTyleImageExtend.h"
#include "misImageGeoProperties.h"
#include "igstkevents.h"
#include "misEvent.h"
//#include "misSettingStrct.h"
#include "matrix.h"
#include "misPlaneContrast.h"
class misInteractorSTyleImageExtend;


class misImageSlicerAbstract
{


protected:

	misInteractorSTyleImageExtend*  pImageStyle;
	//vector<misImageSpecification> m_ImageSpecification;


public:

	

	 

	misImageGeoProperties *m_ImageGeoProp;

 misImageSlicerAbstract();
	virtual double* GetDimention()=0;
	virtual double* GetDimention(int planeIndex)=0;

	virtual void GrayscaleOff()=0;
	virtual void GrayscaleOn()=0;
	virtual void GrayscaleOff(int index)=0;
	virtual void GrayscaleOn(int index)=0;


	virtual void  RemoveLayer(int layerIndex)=0;
	virtual void SetCurrentImagePos( double currentImagePosition )=0;

	virtual void SetSliceNumber(int slice)=0;
	/*virtual void SetSliceNumberForSecondImage(int slice)=0;*/

	virtual IMAGEORIENTATION  GetOrientation()=0;
	/*virtual void Update(void)=0; */
	virtual void SetWindowLevel(misWindowLevelStr winlevStr)=0;
	virtual void SetWindowLevelForSelectedPlane(misWindowLevelStr winlevStr )=0;

	virtual void  SetTextureTransform(tgt::mat4  pTrans)=0;
	void SetImageStyle( misInteractorSTyleImageExtend* val );
	misInteractorSTyleImageExtend* GetImageStyle() const;

	virtual PointType* GetPlaneCoord()=0;
	virtual PointType* GetPlaneCoord(int planeIndex)=0;

	virtual PointType  GetCenter()=0;
	virtual PointType  GetCenter(int planeIndex)=0;
 

	//void SetNumberOfSliceInDirection(int planeIndex ,int val);
	//void SetNumberOfSliceInDirection(int val);
	 
	virtual vtkImageData*     GetImage()=0;
	virtual double   GetCurrentImagePositionInDr()=0 ;

	virtual 	vtkActor* GetQuadPlane()=0;
 

};
