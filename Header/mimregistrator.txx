
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: MIMRegistrator.txx,v $
  Language:  C++
  Date:      $Date: 2002-10-01 01:36:06 $
  Version:   $Revision: 1.3 $

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

	 This software is distributed WITHOUT ANY WARRANTY; without even 
	 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
	 PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MIMRegistrator_txx
#define _MIMRegistrator_txx

#include "MIMRegistrator.h"
#include "itkCommand.h"

#pragma warning (push, 0)

namespace itk
{

template <typename TFixedImage, typename TMovingImage>
MIMRegistrator<TFixedImage,TMovingImage>
::~MIMRegistrator()
{
  m_Registration->RemoveObserver( m_Tag );

}


template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>
::Execute()
{
	//TODO-- Barzegar
	//Test
// 	FixedImageType::IndexType  ind;
// 	ind[0]=20;
// 	ind[1]=20;
// 	ind[2]=5;

	//FixedImageType::PixelType  pt= m_Metric->GetFixedImage()->GetPixel(ind);
// 	FixedImageType::PixelType  pt2= this->m_FixedImage->GetPixel(ind);
// 	FixedImageType::PixelType	pt4 = this->m_MovingImage->GetPixel(ind);
// 	FixedImageType::PixelType	pt5;// = this->m_MovingImagePyramid->GetOutput(0)->GetPixel(ind);
	//EndTest


  // Setup the optimizer
  typename OptimizerType::ScalesType scales( 
	m_Transform->GetNumberOfParameters() );
  scales.Fill( 1.0);
  
  for ( int j = 4; j < 7; j++ )
	{
	scales[j] = m_TranslationScale;
	}

  m_Optimizer->SetScales( scales );
  m_Optimizer->MaximizeOn();
  //m_Optimizer->SetMinimumStepLength( 0.01 );

  // Setup the metric
  m_Metric->SetMovingImageStandardDeviation( m_MovingImageStandardDeviation );
  m_Metric->SetFixedImageStandardDeviation( m_FixedImageStandardDeviation );
  m_Metric->SetNumberOfSpatialSamples( m_NumberOfSpatialSamples );

  // Setup the image pyramids
  m_FixedImagePyramid->SetNumberOfLevels( m_NumberOfLevels );
  m_FixedImagePyramid->SetStartingShrinkFactors( 
	m_FixedImageShrinkFactors.GetDataPointer() );

  m_MovingImagePyramid->SetNumberOfLevels( m_NumberOfLevels );
  m_MovingImagePyramid->SetStartingShrinkFactors(
	m_MovingImageShrinkFactors.GetDataPointer() );

  // Setup the registrator
  m_Registration->SetFixedImage( m_FixedImage );
  m_Registration->SetMovingImage( m_MovingImage );
  m_Registration->SetNumberOfLevels( m_NumberOfLevels );
 
  m_Registration->SetInitialTransformParameters( m_InitialParameters );

  m_Registration->SetFixedImageRegion( m_FixedImage->GetBufferedRegion() );
  
  //TODO-- Barzegar
  //Test
// 	ind[0]=43;
// 	ind[1]=33;
// 	ind[2]=12;

	//pt= m_Metric->GetFixedImage()->GetPixel(ind);
	//pt2= this->m_FixedImage->GetPixel(ind);
	//pt3 = this->m_FixedImagePyramid->GetOutput(0)->GetPixel(ind);
	//pt4 = this->m_MovingImage->GetPixel(ind);
	//pt5 = this->m_MovingImagePyramid->GetOutput(0)->GetPixel(ind);
  //EndTest
  try
	{
	m_Registration->StartRegistration();
	}
  catch( itk::ExceptionObject & err )
	{
	std::cout << "Caught an exception: " << std::endl;
	std::cout << err << std::endl;
	throw err;
	}
}

template <typename TFixedImage, typename TMovingImage>
const 
typename MIMRegistrator<TFixedImage,TMovingImage>
::ParametersType &
MIMRegistrator<TFixedImage,TMovingImage>
::GetTransformParameters()
{
  return m_Registration->GetLastTransformParameters();
}


template <typename TFixedImage, typename TMovingImage>
typename MIMRegistrator<TFixedImage,TMovingImage>
::Rigid3DTransformPointer
MIMRegistrator<TFixedImage,TMovingImage>
::GetRigid3DTransform()
{
	/*std::cout<<"GetLastTransformParameters:\n";
	std::cout<<m_Registration->GetLastTransformParameters()<<std::endl;

	std::cout<<"Get Affine Transform:\n";
	std::cout<<"Rotation Matrix:\n";
	std::cout<<m_Transform->GetRotationMatrix()<<std::endl;
	std::cout<<"Offset:\n";
	std::cout<<m_Transform->GetOffset()<<std::endl;*/

  m_Transform->SetIdentity();
 /* std::cout<<"Trnasform Parameters = "<<m_Optimizer->GetCurrentPosition()
	  <<std::endl;*/
  //m_Transform->SetParameters( m_Registration->GetLastTransformParameters() );
  m_Transform->SetParameters( m_Optimizer->GetCurrentPosition() );

  /*std::cout<<"Rotation Matrix:\n";
	std::cout<<m_Transform->GetRotationMatrix()<<std::endl;
	std::cout<<"Offset:\n";
	std::cout<<m_Transform->GetOffset()<<std::endl;*/

  
  m_Rigid3DTransform->SetMatrix( m_Transform->GetRotationMatrix() );
  m_Rigid3DTransform->SetOffset( m_Transform->GetOffset() );

  return m_Rigid3DTransform;
}



template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>
::StartNewLevel()
{
	//RAMA added
	//bool m_stop;
	EnterCriticalSection(&section);
	//m_stop = m_stopOptimization;
	if (m_stopOptimization)
	{
		m_Registration->StopRegistration();
		m_Optimizer->StopOptimization();
	}
	LeaveCriticalSection(&section);
	/*EnterCriticalSection(&section);
	m_stopOptimization = false;
	LeaveCriticalSection(&section);*/

	//if (!m_stop)
	if (!m_stopOptimization)
	{

	std::cout << "--- Starting level " << m_Registration->GetCurrentLevel()
			<< std::endl;

	  unsigned int level = m_Registration->GetCurrentLevel();
	  if ( m_NumberOfIterations.Size() >= level + 1 )
		{
		m_Optimizer->SetNumberOfIterations( m_NumberOfIterations[level] );
		}

	  if ( m_LearningRates.Size() >= level + 1 )
		{
		m_Optimizer->SetLearningRate( m_LearningRates[level] );
		}

	  std::cout << " No. Iterations: " 
				<< m_Optimizer->GetNumberOfIterations()
				<< " Learning rate: "
				<< m_Optimizer->GetLearningRate()
				<< std::endl;
	}
}

//RAMA added, function is called after each iteration
template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>
::StartNewIteration()
{
		
	EnterCriticalSection(&section);
	//m_stop = m_stopOptimization;
	if (m_stopOptimization)
	{
		m_Registration->StopRegistration();
		m_Optimizer->StopOptimization();
		return;
	}
	LeaveCriticalSection(&section);

	unsigned int CurrentLevel = m_Registration->GetCurrentLevel();
	unsigned int ite = m_Optimizer->GetCurrentIteration();

	if ((ite>0) && (ite % NumberOfIterationsForMean == 0))
	{
		m_CostArray[CurrentPart] = m_CostArray[CurrentPart] / 
			NumberOfIterationsForMean;

		CostValueInformation CVInfo;
		CVInfo.IterationsNumber = ite;
		CVInfo.LevelIndex = CurrentLevel;
		CVInfo.CostValue = m_CostArray[CurrentPart];
		CostValueQueue.push(CVInfo);

		CurrentPart++;
		if (CurrentPart >= NumberOfPartsForCompare)
		{
			CurrentPart = 0;
		}
	}

	if ((CurrentLevel != (m_NumberOfLevels - 1)) && (ite > 0 ) && 
			(ite % (NumberOfPartsForCompare * NumberOfIterationsForMean) == 0))
	{
		double maxCostValue = m_CostArray[1];
		for (int jdx=2;jdx<=NumberOfPartsForCompare;jdx++)
		{
			if (maxCostValue<m_CostArray[jdx])
			{
				maxCostValue = m_CostArray[jdx];
			}
		}

		if ((maxCostValue / m_CostArray[0]) < m_ErrorStopRate)
		{
			//EnterCriticalSection(&section);
			//m_stopOptimization = true;
			//LeaveCriticalSection(&section);
		}

		m_CostArray.Fill(0.0);	
	}

	m_CostArray[CurrentPart] +=  m_Optimizer->
		GetCostFunction()->GetValue(m_Optimizer->GetCurrentPosition());

	//bool m_stop;
	//EnterCriticalSection(&section);
	//m_stop = m_stopOptimization;	

	
	if ((ite % 100) == 0)
	{
		EnterCriticalSection(&m_updateTransformMatrix);

		 std::cout<<"Iteration #"<<m_Optimizer->GetCurrentIteration()<<std::endl;
		 
		 m_CurrentTransform->SetIdentity();
		 m_CurrentTransform->Compose(m_PostTransform, true);
		 m_CurrentTransform->Compose(this->GetRigid3DTransform(), true);
		 m_CurrentTransform->Compose(m_PreTransform, true);

		 std::cout<<"Cutrrent Offset = "<<m_CurrentTransform->GetOffset()
			 <<std::endl;
		 std::cout<<"Cutrrent Rotation = "<<m_CurrentTransform->GetMatrix()
			 <<std::endl;

		 LeaveCriticalSection(&m_updateTransformMatrix);

		/* EnterCriticalSection(&m_ModifiedSection);
		 m_Modified = true;
		 LeaveCriticalSection(&m_ModifiedSection);*/

		
		
	}

	//LeaveCriticalSection(&section);

	EnterCriticalSection(&section);
	if (m_stopOptimization)
	{
		this->m_Optimizer->StopOptimization();
	}
	LeaveCriticalSection(&section);
	
	//std::cout<<"A new Iteration has started\n"<<std::endl;
}

//template <typename TFixedImage, typename TMovingImage>
//bool MIMRegistrator<TFixedImage,TMovingImage>
//::IsModified()
//{
//	bool returnValue;
//	EnterCriticalSection(&m_ModifiedSection);
//	returnValue = m_Modified;
//	LeaveCriticalSection(&m_ModifiedSection);
//	
//	return returnValue;
//}

template <typename TFixedImage, typename TMovingImage>
typename MIMRegistrator<TFixedImage,TMovingImage>
::Rigid3DTransformPointer MIMRegistrator<TFixedImage,TMovingImage>
::GetCurrentTransformMatrix()
{
	itk::Rigid3DTransform<double>::Pointer p_Transform;
	EnterCriticalSection(&m_updateTransformMatrix);
	p_Transform = m_CurrentTransform;
	LeaveCriticalSection(&m_updateTransformMatrix);
	
	return p_Transform;
}

template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>
::set_m_stopOptimization(bool m_stop)
{
	EnterCriticalSection(&section);
	m_stopOptimization = m_stop;
	if(m_stop == true)
	{
		this->m_Registration->StopRegistration();
		this->m_Optimizer->StopOptimization();
	}
	LeaveCriticalSection(&section);
}

template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>
::setCriticalSection(CRITICAL_SECTION *CRsection)
{
	section = CRsection;
}

template <typename TFixedImage, typename TMovingImage>
void itk::MIMRegistrator<TFixedImage, TMovingImage>::SetInitialTransform( Rigid3DTransformPointer pTransform )
{
	this->m_CurrentTransform = pTransform;
	
	//TODO -- barzegar
	//Testing

	this->m_PreTransform = pTransform;
	this->m_PostTransform = pTransform;
	this->m_Optimizer->SetInitialPosition(this->m_InitialParameters);
	this->m_Optimizer->SetCurrentPosition(this->m_InitialParameters);
	this->m_Registration->SetTransformExternally();
	//End Test
}



template <typename TFixedImage, typename TMovingImage>
void
MIMRegistrator<TFixedImage,TMovingImage>::
SetInitialTransformMatrix(InitialMatrixType mMatrix)
{
	typedef RegistrationType::ParametersType ParametersType;
	ParametersType Parameters( m_Transform->GetNumberOfParameters() );

	itk::Matrix<double,3,3> RotMatrix;
	for (int rowIndex=0;rowIndex<3;rowIndex++)
	{
		for (int columnIndex=0;columnIndex<3;columnIndex++)
		{
			RotMatrix(rowIndex,columnIndex) = mMatrix(rowIndex,columnIndex);
		}
	}
	vnl_quaternion<double> quat(RotMatrix.GetVnlMatrix());
	vnl_quaternion<double>   RotationPart = quat.conjugate();	

	// Transfer the quaternion part
	unsigned int par = 0;

	for(unsigned int j=0; j < 4; j++) 
	{
		Parameters[par] = RotationPart[j];
		++par;
	}

	// Transfer the constant part
	for(unsigned int i=0; i < 3; i++) 
	{
		Parameters[par] = mMatrix(i,3);
		++par;
	}

	//std::cout<<"Initial Parameters set = "<<Parameters<<std::endl;
	m_InitialParameters = Parameters;
	//std::cout<<"Initial Parameters get = "<<m_Registration->GetInitialTransformParameters()<<std::endl;
	
}
template <typename TFixedImage, typename TMovingImage>
std::queue<CostValueInformation>
MIMRegistrator<TFixedImage,TMovingImage>::
GetCostValueQueue()
{
	return CostValueQueue;

}

template <typename TFixedImage, typename TMovingImage>
void MIMRegistrator<TFixedImage,TMovingImage>::
SetPreProcessorPostTransform(Rigid3DTransformPointer PostTransform)
{
	m_PostTransform = PostTransform;
}

template <typename TFixedImage, typename TMovingImage>
void MIMRegistrator<TFixedImage,TMovingImage>::
SetPreProcessorPreTransform(Rigid3DTransformPointer PreTransform)
{
	m_PreTransform = PreTransform;
}
 
template <typename TFixedImage, typename TMovingImage>
unsigned int itk::MIMRegistrator<TFixedImage, TMovingImage>::GetCurrentIteration()	
{
	unsigned int CurrentLevel = m_Registration->GetCurrentLevel();
	unsigned int ite = m_Optimizer->GetCurrentIteration();
	unsigned int numberOfIter = m_Optimizer->GetNumberOfIterations();
	if(ite >= numberOfIter)
	{
		ite = 0;
	}
	int pastIter = ite;

	int sumIter = 0;

	if(CurrentLevel>0)
	{
		for(int i = 0; i < CurrentLevel ; i++)
		{
			sumIter = sumIter + m_NumberOfIterations[i];
		}
		pastIter = pastIter+sumIter;
	}

	return pastIter;
}
//End RAMA

} // namespace itk

#pragma warning (pop)

#endif
