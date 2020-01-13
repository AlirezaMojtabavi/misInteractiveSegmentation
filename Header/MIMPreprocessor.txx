
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: MIMPreprocessor.txx,v $
  Language:  C++
  Date:      $Date: 2002/11/16 20:14:28 $
  Version:   $Revision: 1.3 $

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MIMPreprocessor_txx
#define _MIMPreprocessor_txx

#include "MIMPreprocessor.h"
#include "itkChangeInformationImageFilter.h"
#include "itkNormalizeImageFilter.h"

namespace itk
{

template <typename TInputImage, typename TOutputImage>
MIMPreprocessor<TInputImage,TOutputImage>
::MIMPreprocessor()
{
  m_InputFixedImage   = NULL;
  m_InputMovingImage  = NULL;
  m_OutputFixedImage  = NULL;
  m_OutputMovingImage = NULL;

  for ( unsigned int j = 0; j < ImageDimension; j++ )
    {
    m_PermuteOrder[j] = j;
    }

  m_FlipAxes.Fill( false );
 
  m_PostTransform = Rigid3DTransformType::New();
  m_PreTransform  = Rigid3DTransformType::New();

}


template <typename TInputImage, typename TOutputImage>
void
MIMPreprocessor<TInputImage,TOutputImage>
::Execute()
{

  typedef ChangeInformationImageFilter<TInputImage>
    CentererType;
  typedef NormalizeImageFilter<TInputImage,TOutputImage>
    NormalizerType;

  Rigid3DTransformType::MatrixType matrix;
  Rigid3DTransformType::OffsetType offset;

  CentererType::Pointer   centerer;
  CentererType::Pointer   centerer2;
  NormalizerType::Pointer normalizer;
  NormalizerType::Pointer normalizer2;
  PermuterType::Pointer   permuter;
  FlipperType::Pointer    flipper;

  // Process the fixed image
  centerer =  CentererType::New();
  normalizer = NormalizerType::New();

  centerer->CenterImageOff();
  centerer->SetInput( m_InputFixedImage );
  
  normalizer->SetInput( centerer->GetOutput() );
  normalizer->Update();
  m_OutputFixedImage = normalizer->GetOutput();

  m_PreTransform->SetIdentity();
  for ( unsigned int j = 0; j < ImageDimension; j++ )
    {
    offset[j] = centerer->GetOutput()->GetOrigin()[j];
    }
  m_PreTransform->SetOffset( offset );


  // Process the moving image
  centerer2   = CentererType::New();
  normalizer2 = NormalizerType::New();
  permuter   = PermuterType::New();
  flipper    = FlipperType::New();

  centerer2->CenterImageOff();
  centerer2->SetInput( m_InputMovingImage );

  bool needToPermute = this->NeedToPermute();
  bool needToFlip    = this->NeedToFlip();

  if ( needToPermute )
    {
    std::cout << "Need to permute: " << m_PermuteOrder;
    permuter->SetInput( centerer2->GetOutput() );
    permuter->SetOrder( m_PermuteOrder );
    }
  else if ( needToFlip )
    {
    flipper->SetInput( centerer2->GetOutput() );
    }

  if ( needToFlip )
    {
    std::cout << "Need to flip: " << m_FlipAxes;
    flipper->SetFlipAxes( m_FlipAxes );
    normalizer2->SetInput( flipper->GetOutput() );
    }
  else if ( needToPermute )
    {
    normalizer2->SetInput( permuter->GetOutput() );
    }
  else
    {
    normalizer2->SetInput( centerer2->GetOutput() );
    }

  if ( needToPermute && needToFlip )
    {
    flipper->SetInput( permuter->GetOutput() );
    }

  normalizer2->Update();
  m_OutputMovingImage = normalizer2->GetOutput();

  // Compute the affine transform

  m_PostTransform->SetIdentity();
  for ( unsigned int j = 0; j < ImageDimension; j++ )
    {
    offset[j] = - 1.0 * centerer->GetOutput()->GetOrigin()[j];
    }
  m_PostTransform->SetOffset( offset );

  if ( needToPermute )
    {
    matrix.Fill( 0.0 );
    offset.Fill( 0.0 );

    typename Rigid3DTransformType::Pointer transform = Rigid3DTransformType::New();
 
    PermuteOrderArrayType invOrder = permuter->GetInverseOrder();

    for ( unsigned int j = 0; j < ImageDimension; j++ )
      {
      matrix[j][invOrder[j]] = 1.0;
      }    

    transform->SetMatrix( matrix );
    transform->SetOffset( offset );

    m_PostTransform->Compose( transform, true );

    }

  if ( needToFlip )
    {

    typename Rigid3DTransformType::Pointer transform = Rigid3DTransformType::New();
    matrix.SetIdentity();
    offset.Fill( 0.0 );

    for ( unsigned int j = 0; j < ImageDimension; j++ )
      {
      if ( m_FlipAxes[j] )
          {
          matrix[j][j] *= -1.0;
          }
      }

    transform->SetMatrix( matrix );
    transform->SetOffset( offset );

    m_PostTransform->Compose( transform, true );

    }
  
}


} // namespace itk

#endif
