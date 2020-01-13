/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkImageResliceObjectRepresentation.h,v $
  Language:  C++
  Date:      $Date: 2009-06-15 20:29:05 $
  Version:   $Revision: 1.2 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __igstkImageResliceObjectRepresentation_h
#define __igstkImageResliceObjectRepresentation_h

#include "igstkMacros.h"
#include "igstkObjectRepresentation.h"
#include "igstkImageSpatialObject.h"
#include "igstkStateMachine.h"
#include "igstkReslicerPlaneSpatialObject.h"

class vtkLookupTable;
class vtkImageMapToColors;
class vtkImageReslice;
class vtkTexture;
class vtkActor;
class vtkPlaneSource;
class vtkOutlineFilter;
class vtkPlane;
class vtkPolyData;
class vtkCutter;
class vtkSphereSource;
class vtkProperty;
class vtkImageMapToColors;


namespace igstk
{
 
#define VTK_NEAREST_RESLICE 0
#define VTK_LINEAR_RESLICE  1
#define VTK_CUBIC_RESLICE   2

/** \class ImageResliceObjectRepresentation
 * 
 * \brief This class represents an oblique image object. 
 * 
 * \ingroup ObjectRepresentation
 */
template < class TImageSpatialObject >
class ImageResliceObjectRepresentation : public ObjectRepresentation
{

public:

  /** Macro with standard traits declarations. */
  igstkStandardTemplatedClassTraitsMacro( 
                ImageResliceObjectRepresentation,ObjectRepresentation )

public:

  typedef TImageSpatialObject                  ImageSpatialObjectType;

  typedef typename ImageSpatialObjectType::ConstPointer 
                                               ImageSpatialObjectConstPointer;

  typedef typename ImageSpatialObjectType::PointType  PointType;

  typedef ReslicerPlaneSpatialObject           ReslicerPlaneType;

  typedef ReslicerPlaneType::Pointer           ReslicerPlanePointerType;  

  typedef ReslicerPlaneType::VectorType        VectorType;

  /** Return a copy of the current object representation */
  Pointer Copy() const;

  void RequestSetReslicePlaneSpatialObject( const ReslicerPlaneType *
                                                    planeSpatialObject);

  /** Connect this representation class to the spatial object */
  void RequestSetImageSpatialObject( const ImageSpatialObjectType * 
                                                 ImageSpatialObject );

  /** Set the Window Level for the representation */
  void SetWindowLevel( double window, double level );

  /** Set the color */
  void SetFrameColor(ColorScalarType r, ColorScalarType g, ColorScalarType b);

  /** Print the object information in a stream. */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const; 


protected:

  /** Constructor */
  ImageResliceObjectRepresentation();
  
  /** Destructor */
  ~ImageResliceObjectRepresentation();

  /** Overloaded function to delete actors */
  void DeleteActors();

  /** Create the VTK actors for displaying geometry */
  void CreateActors();

  /** Get each frame color component */
  ColorScalarType GetFrameRed() const; 
  ColorScalarType GetFrameGreen() const;
  ColorScalarType GetFrameBlue() const;

  /** Verify time stamp. Use the reslicing tool transform to verify 
  * the time stamp */
  virtual bool VerifyTimeStamp() const;

private:

  ImageResliceObjectRepresentation(const Self&);
  void operator=(const Self&);   //purposely not implemented

  /** Internal itkSpatialObject */
  ImageSpatialObjectConstPointer         m_ImageSpatialObject;
  ImageSpatialObjectConstPointer         m_ImageSpatialObjectToAdd;

  /** Variables for maanging reslice plane spatial object */
  ReslicerPlanePointerType               m_ReslicePlaneSpatialObjectToBeSet;
  ReslicerPlanePointerType               m_ReslicePlaneSpatialObject;
    
  /** VTK classes that support display of an image */
  vtkImageData         *m_ImageData;
  vtkImageReslice      *m_ImageReslicer;
  vtkMatrix4x4         *m_ResliceAxes;
  vtkActor             *m_ImageActor;
  vtkProperty          *m_PlaneProperty;
  vtkImageMapToColors  *m_ColorMap;
  vtkTexture           *m_Texture;
  vtkLookupTable       *m_LookupTable;
  vtkPlaneSource       *m_PlaneSource;
  vtkPlane             *m_Plane;
  vtkImageData         *m_Box;
  vtkCutter            *m_Cutter;
  

  /** Main color of the representation. This should be RGB components, each one
   * in the range 0.0 to 1.0 */
  ColorScalarType                         m_FrameColor[3];

  int    m_ResliceInterpolate;
  int    m_TextureInterpolate;
  int    m_RestrictPlaneToVolume;

  /** Variables that store window and level values for 2D image display */
  double                                 m_Level;
  double                                 m_Window;

  /** Variables that store image information, that not change */
  double                                 m_ImageSpacing[3];
  double                                 m_ImageOrigin[3];
  int                                    m_ImageExtent[6];
  double                                 m_xbounds[2];
  double                                 m_ybounds[2];
  double                                 m_zbounds[2];

  /** Update the visual representation with changes in the geometry */
  virtual void UpdateRepresentationProcessing();

  /** Null operation for State Machine transition */
  void NoProcessing(); 

  /** Set the reslice plane spatial object */
  void SetReslicePlaneSpatialObjectProcessing();

  /** Connect this representation class to the spatial object. Only to be
   * called by the State Machine. */
  void SetImageSpatialObjectProcessing();

  /** Report invalid image spatial object type */
  void ReportInvalidImageSpatialObjectProcessing( void );

  /** Report invalid tool spatial object type */
  void ReportInvalidReslicePlaneSpatialObjectProcessing( void );

  /** Report invalid request */
  void ReportInvalidRequestProcessing( void );

  /** Sets reslice interpolation type */
  void SetResliceInterpolate(int i);

  /** Builds the plane geometry */
  void UpdatePlane();

  /** Internal function to get a vector from point1 to the origin*/
  void GetVector1(double v1[3]);

  /** Internal function to get a vector from point2 to the origin*/
  void GetVector2(double v1[3]);

  /** Sets the vtkImageData from the ImageSpatialObject. This method MUST be
   * private in order to prevent unsafe access from the VTK image layer. */
  void SetImage( const vtkImageData * image );
  
  /** Connect VTK pipeline */
  void ConnectVTKPipelineProcessing();
    
  /** Declare the observer that will receive a VTK image from the
   * ImageSpatialObject */
  igstkObserverMacro( VTKImage, VTKImageModifiedEvent,
                      EventHelperType::VTKImagePointerType);

  /** Declare the observers that will receive the reslicing plane parameters 
   * from the ReslicerPlaneSpatialObject */

  igstkObserverMacro( ReslicerPlaneCenter, 
                                    ReslicerPlaneType::ReslicerPlaneCenterEvent,
                                                 ReslicerPlaneType::VectorType);

  typename ReslicerPlaneCenterObserver::Pointer  m_ReslicerPlaneCenterObserver;

  igstkObserverMacro( ReslicerPlaneNormal, 
                                    ReslicerPlaneType::ReslicerPlaneNormalEvent,
                                                 ReslicerPlaneType::VectorType);

  typename ReslicerPlaneNormalObserver::Pointer  m_ReslicerPlaneNormalObserver;


  /** todo: see if we need this observer*/
  igstkObserverMacro( ImageTransform, CoordinateSystemTransformToEvent, 
     CoordinateSystemTransformToResult );

  typename VTKImageObserver::Pointer  m_VTKImageObserver;

private:

  /** Inputs to the State Machine */
  igstkDeclareInputMacro( ValidImageSpatialObject );
  igstkDeclareInputMacro( InValidImageSpatialObject );
  igstkDeclareInputMacro( ValidReslicePlaneSpatialObject );
  igstkDeclareInputMacro( InValidReslicePlaneSpatialObject );
  igstkDeclareInputMacro( ConnectVTKPipeline );

  /** States for the State Machine */
  igstkDeclareStateMacro( Initial );
  igstkDeclareStateMacro( ImageSpatialObjectSet );
  igstkDeclareStateMacro( ReslicePlaneSpatialObjectSet );
};

} // end namespace igstk

#ifndef IGSTK_MANUAL_INSTANTIATION
#include "igstkImageResliceObjectRepresentation.txx"
#endif


#endif // __igstkImageResliceObjectRepresentation_h
