/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: SimpleAppOutput.h,v $
  Language:  C++
  Date:      $Date: 2004-02-06 22:38:15 $
  Version:   $Revision: 1.4 $

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _SimpleAppOutput_h
#define _SimpleAppOutput_h

#include "itkObject.h"
#include "itkRigid3DTransform.h"
#include <string>

namespace itk
{

/** \class SimpleAppOutput
 *
 * This component resamples the moving image using the user
 * specified transform. This class then writes out the 
 * fixed, moving and resampled image as PGM files.
 *
 * This class is activated by method Execute().
 *
 * Inputs:
 *  - pointer to the fixed image
 *  - pointer to the moving image
 *  - pointer to an affine tranform
 *  - name of output file
 *
 * Outputs:
 *  - pointer to the resampled image
 */
template <typename TImage>
class ITK_EXPORT SimpleAppOutput : public Object
{
public:

  /** Standard class typedefs. */
  typedef SimpleAppOutput Self;
  typedef Object Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(SimpleAppOutput, Object);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Image Type. */
  typedef TImage ImageType;

  /** Image dimension enumeration. */
  itkStaticConstMacro(ImageDimension, unsigned int, TImage::ImageDimension);

  /** Rigid 3D transform type. */
    typedef Rigid3DTransform<double> Rigid3DTransformType;
  typedef typename Rigid3DTransformType::Pointer Rigid3DTransformPointer;

  /** Set the fixed image. */
  itkSetObjectMacro( FixedImage, ImageType );

  /** Set the moving image. */
  itkSetObjectMacro( MovingImage, ImageType );

  /** Set the transform. */
  itkSetObjectMacro( Transform, Rigid3DTransformType );

  /** Set the output filename. */
  itkSetStringMacro( OutputFileName );

  /** Activiate the process. */
  void Execute();

  itk::Image< float,3>::Pointer GetOutImage();
  

protected:
  SimpleAppOutput();
  ~SimpleAppOutput(){};

private:
  SimpleAppOutput( const Self& ); //purposely not implemented
  void operator=( const Self& ); //purposely not implemented

  typename ImageType::Pointer  m_FixedImage;
  typename ImageType::Pointer  m_MovingImage;
  typename ImageType::Pointer  m_ResampledImage;

  Rigid3DTransformPointer  m_Transform;

  std::string m_OutputFileName;


};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "SimpleAppOutput.txx"
#endif

#endif
