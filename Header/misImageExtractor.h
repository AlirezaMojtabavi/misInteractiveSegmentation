#pragma once
#include "misobject.h"

#include "misRepresentation.h"
#include "VTKImageExport.h"	
#include "misImage.h"

#include "vtkImageImport.h"
#include "vtkImageExport.h"

#include "misImageExtractor.h"
class vtkDataSetMapper;
class vtkTexture;
class vtkBMPReader;
class vtkimageviewer2;
class vtkTextureMapToPlane;
class vtkimageReslice;
class vtkMatrix4x4;
class vtkImageActor;
class vtkImageReslice;
class vtkImageMapToColors;
class vtkPlaneSource;
class vtkImageData;
class vtkActor;
class vtkMapper2D;
class vtkPolyDataMapper;



typedef itk::Point<float ,3>  PointType;
typedef itk::Point<int,3>  PointTypeInt;
typedef itk::Vector<float,3>  VectorType;

class MISDLLEXPORT misImageExtractor :
	public misObject
{
public:
	typedef misImageExtractor                         Self;  
		typedef misObject                    Superclass; 
		typedef ::itk::SmartPointer< Self >       Pointer; 
		typedef ::itk::SmartPointer< const Self > ConstPointer; 

		  static Pointer New();
		  typedef float PixelType;

		  vtkImageData* get_m_CurrentImage() const;

		  //##ModelId=4875B7F20245
		  virtual void set_m_CurrentImage(vtkImageData* left);
		  //##ModelId=4875B7F20248
	
		  virtual  void SetDirection(vtkMatrix4x4*  pMatrix);

		  vtkMatrix4x4*  GetDirection(void)
		  {
			  return this->m_pExtractDirection;
		  };


protected:

	vtkMatrix4x4*  m_pExtractDirection;
	vtkMatrix4x4*  m_pFinalExtractDirection;
	//TEMP
	//===============================================================================
	vtkImageData*            m_CurrentImage;
	vtkImageReslice*     m_pReslice;
 
	misImageExtractor(void);
	virtual ~misImageExtractor(void);
};
