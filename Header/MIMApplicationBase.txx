
#ifndef _MIMApplicationBase_txx
#define _MIMApplicationBase_txx

#pragma warning (push, 0)

#include "MIMApplicationBase.h"
#include "itkFixedArray.h"
#include "itkArray.h"
#include "itkImageFileReader.h"
#include "LevelInformation.h"
#include "itkMatrixOffsetTransformBase.h"
#include "itkRigid3DTransform.h"

using namespace std;

namespace itk
{

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::MIMApplicationBase()
{
  m_Preprocessor = PreprocessorType::New();
  m_Registrator  = RegistratorType::New();
  m_Generator    = GeneratorType::New();

  m_Transform    = Rigid3DTransformType::New();

  for ( unsigned int j = 0; j < ImageDimension; j++ )
	{
	m_PermuteOrder[j] = j;
	}
  m_FlipAxes.Fill( false );

  m_NumberOfLevels = 0;

  m_FixedImageShrinkFactors[0] = 4;
  m_FixedImageShrinkFactors[1] = 4;
  m_FixedImageShrinkFactors[2] = 1;

  m_MovingImageShrinkFactors[0] = 8;
  m_MovingImageShrinkFactors[1] = 8;
  m_MovingImageShrinkFactors[2] = 1;

  m_TranslationScale = 320.0;

  m_FixedImageFileName = "";
  m_MovingImageFileName = "";

  m_OutputFileName = "D:\\CTMrT1.mhd";
  m_IsFixedShrinkFactorsSet = false;
  m_IsMovingShrinkFactorsSet = false;
  m_isMovingImageSet = false;
  m_isMovingImageSet = false;
  m_IsRegistrationFinished= false;
  
  m_FixedImage = 0;
  m_MovingImage = 0;
  //m_InitialMatrix->SetIdentity();
  InitializeCriticalSection(&section);
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::Execute()
{
  std::cout << "Reading input images and setting parameters... " << std::endl;

  try
  {
		/***********************
		* Read in the images
		***********************/
		//typedef typename ImageType::PixelType PixelType;
		typedef itk::ImageFileReader<TInputImage> ReaderType;
		typename ReaderType::Pointer fixedReader  = ReaderType::New();
		typename ReaderType::Pointer movingReader = ReaderType::New();

		if (!m_isFixedImageSet)
		{
			try 
			{
				fixedReader->SetFileName( m_FixedImageFileName );
				fixedReader->Update();

				m_FixedImage = fixedReader->GetOutput();

				std::cout<<"Origin of Fixed Image at first = "<<
					m_FixedImage->GetOrigin()<<std::endl;
			}
			catch(...)
			{
				std::cout << "Error while reading in fixed image." << std::endl;
				throw;
			}
		}
		if (!m_isMovingImageSet)
		{
			try 
			{
				movingReader->SetFileName( m_MovingImageFileName );
				movingReader->Update();

				m_MovingImage = movingReader->GetOutput();

				std::cout<<"Origin of Moving Image at first = "<<
					m_FixedImage->GetOrigin()<<std::endl;
			}
			catch(...)
			{
				std::cout << "Error while reading in moving image." << std::endl;
				throw;
			}
		}

	}
  catch(itk::ExceptionObject & eo)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "itk::ExceptionObject caught" << std::endl;
	std::cout << eo << std::endl;
	throw;
	}
  catch(std::exception & e)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "std::exception caught" << std::endl;
	std::cout << e.what() << std::endl;
	throw;
	}
  catch(...)
   {
   std::cout << "Error occurred during input parsing." << std::endl;
   throw;
   }
  

  /**************************
   * Preprocess the images before registration
   **************************/
  std::cout << "Preprocess the images ... " << std::endl;

  try
	{
	this->InitializePreprocessor();
	m_Preprocessor->Execute();
	}
  catch(itk::ExceptionObject & eo)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "itk::ExceptionObject caught" << std::endl;
	std::cout << eo << std::endl;
	throw;
	}
  catch(std::exception & e)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "std::exception caught" << std::endl;
	std::cout << e.what() << std::endl;
	throw;
	}
  catch(...)
	{
	std::cout << "Error occured during preprocessing." << std::endl;
	throw;
	}


  /**************************
   * Registered the processed images
   **************************/
  std::cout << "Register the images ... " << std::endl;

  try
	{
	//TODO-- Barzegar
	//Test
// 	TInputImage::IndexType  ind;
// 	ind[0]=20;
// 	ind[1]=20;
// 	ind[2]=5;
// 	TInputImage::PixelType  pt2= m_FixedImage->GetPixel(ind);
	//CorrelationImageType::PixelType	pt3 = ImagePyramid->GetOutput(0)->GetPixel(ind);
// 	TInputImage::PixelType	pt4 = m_MovingImage->GetPixel(ind);
// 	TInputImage::PixelType	pt3 = m_Preprocessor->GetOutputFixedImage()->GetPixel(ind);
	//CorrelationImageType::PixelType	pt5 = MovingImagePyramid->GetOutput(0)->GetPixel(ind);
	//EndTest
	
	this->InitializeRegistrator();
	
	//TODO-- Barzegar
	//Test
// 	ind[0]=20;
// 	ind[1]=20;
// 	ind[2]=5;
// 	pt2= m_FixedImage->GetPixel(ind);
// 	pt4 = m_MovingImage->GetPixel(ind	//EndTest
	if(m_Registrator)
		m_Registrator->Execute();
	}
  catch(itk::ExceptionObject & eo)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "itk::ExceptionObject caught" << std::endl;
	std::cout << eo << std::endl;
	//throw;
	}
  catch(std::exception & e)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "std::exception caught" << std::endl;
	std::cout << e.what() << std::endl;
	//throw;
	}
  catch(...)
	{
	std::cout << "Error occured during registration" << std::endl;
	//throw;
	}

  this->SetIsRegistrationFinished(true);
  EnterCriticalSection(&section);
  // Get the results
  std::cout << "Final parameters: " 
			<< m_Registrator->GetTransformParameters() << std::endl;


  /***************************
   * Compute overall transform
   ***************************/
  // compose the preprocess and registration transforms

  m_Transform->SetIdentity();

 // std::cout<<"Preprocessor Post = "<<m_Preprocessor->GetPostTransform()<<std::endl;
 // m_Transform->Compose( m_Preprocessor->GetPostTransform(), true );
 // std::cout<<"Registrator Affine = "<<m_Registrator->GetRigid3DTransform()<<std::endl;
  m_Transform->Compose( m_Registrator->GetCurrentTransformMatrix(), true );
 // std::cout<<"PreProcessor Pre = "<<m_Preprocessor->GetPreTransform()<<std::endl;
  //m_Transform->Compose( m_Preprocessor->GetPreTransform(), true );

  std::cout << "Overall transform matrix: " << std::endl;
  std::cout << m_Transform->GetMatrix() << std::endl;
  std::cout << "Overall transform offset: " << std::endl;
  std::cout << m_Transform->GetOffset() << std::endl;
	LeaveCriticalSection(&section);

  /**************************
   * Generating output
   **************************/
  /*std::cout << "Generating output ... " << std::endl;
  
  try
	{
	this->InitializeGenerator();
	m_Generator->Execute();
	}
  catch(itk::ExceptionObject & eo)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "itk::ExceptionObject caught" << std::endl;
	std::cout << eo << std::endl;
	throw;
	}
  catch(std::exception & e)
	{
	std::cout << "Error occured during registration" << std::endl;
	std::cout << "std::exception caught" << std::endl;
	std::cout << e.what() << std::endl;
	throw;
	}
  catch(...)
   {
   std::cout << "Error occurred during output generation." << std::endl;
   throw;
   }*/

}

//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//bool
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>
//::IsModified()
//{
//	return m_Registrator->IsModified();
//}



template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::Rigid3DTransform<double>::Pointer
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetCurrentTransformMatrix()
{
	return m_Registrator->GetCurrentTransformMatrix();
}
////////////////////////////

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetTranslationScale(double scale)
{
	m_TranslationScale = scale;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
double
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetTranslationScale()
{
	return m_TranslationScale;
}

//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//Array<double>
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>
//::getRateArray()
//{
//	return m_LearningRates;
//}
//
//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//void
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>
//::setRateArray(Array<double> RateArray)
//{
//	m_LearningRates = RateArray;
//}

//1
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::FixedArray<unsigned int, TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetPermuteOrderArray()
{
	return m_PermuteOrder;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetPermuteOrderArray(itk::FixedArray<unsigned int, TInputImage::ImageDimension> PermuteOrder)
{
	m_PermuteOrder = PermuteOrder;
}

//2
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  itk::FixedArray<bool, TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetFlipAxesArray()
{
	return m_FlipAxes;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetFlipAxesArray(itk::FixedArray<bool, TInputImage::ImageDimension> FlipAxesArray)
{
	m_FlipAxes = FlipAxesArray;
}

//3
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
unsigned short
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetNumber_of_Levels()
{
	return m_NumberOfLevels;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetNumber_of_Levels(unsigned short Number_Levels)
{
	m_NumberOfLevels = Number_Levels;
}
//4
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::FixedArray<unsigned int, TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetFixedImageShrinkFactors()
{
	return m_FixedImageShrinkFactors;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetFixedImageShrinkFactors(itk::FixedArray<unsigned int, TInputImage::ImageDimension> 
							 FixedArrayShrinkFactors)
{
	IsFixedShrinkFactorsSet = true;	
	m_FixedImageShrinkFactors = FixedArrayShrinkFactors;
}

//5
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::FixedArray<unsigned int, TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetMovingImageShrinkFactors()
{
	return m_MovingImageShrinkFactors;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetMovingImageShrinkFactors(itk::FixedArray<unsigned int, TInputImage::ImageDimension> 
							  MovingArrayShrinkFactors)
{
	IsFixedShrinkFactorsSet = true;	
	m_MovingImageShrinkFactors = MovingArrayShrinkFactors;
}

////6
//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//Array<unsigned int>
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>
//::getIterationArray()
//{
//	return m_NumberOfIterations;
//}
//
//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//void
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>
//::setIterationArray(Array<unsigned int> IterationArray)
//{
//	m_NumberOfIterations = IterationArray;
//}

//7
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  std::string
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetOutputFileName()
{
	return m_OutputFileName;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetOutputFileName(std::string OutputFileName)
{
	m_OutputFileName = OutputFileName;
}

//8
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  std::string
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetFixedImageFileName()
{
	return m_FixedImageFileName;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetFixedImageFileName(std::string FixedFileName)
{
	m_FixedImageFileName = FixedFileName;
}

//9
template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  std::string
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::GetMovingImageFileName()
{
	return m_MovingImageFileName;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetMovingImageFileName(std::string MovingFileName)
{
	m_MovingImageFileName = MovingFileName;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetStopOptimization(bool mStop)
{
	m_Registrator->set_m_stopOptimization(mStop);
}
///////////////////////////


template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::InitializePreprocessor()
{

  m_Preprocessor->SetInputFixedImage( m_FixedImage );
  m_Preprocessor->SetInputMovingImage( m_MovingImage );

  m_Preprocessor->SetPermuteOrder( m_PermuteOrder );
  m_Preprocessor->SetFlipAxes( m_FlipAxes );
}


template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::InitializeRegistrator()
{
  //This Function upadet Informations about levels
  this->UpdateLevelInformation(); 

  if (!m_IsFixedShrinkFactorsSet)
  {
	  m_FixedImageShrinkFactors = SetShrinkFactorsAutomatically("Fixed");
  }

  if (!m_IsMovingShrinkFactorsSet)
  {
	  m_MovingImageShrinkFactors = SetShrinkFactorsAutomatically("Moving");
  }

  m_Registrator->SetFixedImage( m_Preprocessor->GetOutputFixedImage() );
  m_Registrator->SetMovingImage( m_Preprocessor->GetOutputMovingImage() );

  // set multiresolution related parameters
  m_Registrator->SetNumberOfLevels( m_NumberOfLevels );

  m_Registrator->SetFixedImageShrinkFactors( m_FixedImageShrinkFactors );

  // permute the shrink factors
  unsigned int permutedFactors[TInputImage::ImageDimension];
  for ( unsigned int j = 0; j < TInputImage::ImageDimension; j++ )
	{
	  permutedFactors[j] = m_MovingImageShrinkFactors[m_PermuteOrder[j]];
	}

  m_Registrator->SetMovingImageShrinkFactors( permutedFactors );

  m_Registrator->SetNumberOfIterations( m_NumberOfIterations );
  m_Registrator->SetLearningRates( m_LearningRates );

  double scale = 1.0 / vnl_math_sqr( m_TranslationScale );
  m_Registrator->SetTranslationScale( scale );

  m_Registrator->SetPreProcessorPostTransform(m_Preprocessor->GetPostTransform());
  m_Registrator->SetPreProcessorPreTransform(m_Preprocessor->GetPreTransform());
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::Matrix<double,TInputImage::ImageDimension,TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::GetTransformMatrix()
{
	return  m_Transform->GetMatrix();
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::FixedArray<double,TInputImage::ImageDimension>
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
::GetOffset()
{
	return  m_Transform->GetOffset();
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
  ::InsertLevelsQueue(levelInformation lInfo)
{
	m_LevelQueue.push(lInfo);
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
  ::UpdateLevelInformation()
{
	if (m_NumberOfLevels == 0)
	{
		int Nolevels = m_LevelQueue.size();
		if (Nolevels != 0)
		{
			this->SetNumber_of_Levels(Nolevels);
		}
		else
		{
			this->SetNumber_of_Levels(2);
		}
	}

	itk::Array<unsigned int> NumberOfIterations(m_NumberOfLevels);
	NumberOfIterations.Fill( 1000 );

	m_NumberOfIterations = NumberOfIterations;

	itk::Array<double> LearningRates( m_NumberOfLevels );
	LearningRates[0] = 1e-4;
	if (m_NumberOfLevels > 1)
	{
		LearningRates[1] = 1e-5;
	}

	for (int i =2;i<m_NumberOfLevels;i++)
	{
		LearningRates[i] = 1e-6;
	}

	m_LearningRates =  LearningRates;

	while (!m_LevelQueue.empty())
	{
	  levelInformation lvInfo = m_LevelQueue.front();
	  int index = lvInfo.LevelIndex;

	  if ((index != -1) && (index < m_NumberOfLevels))
	  {
		  if (lvInfo.Number_of_Iterations != 0)
		  {
			m_NumberOfIterations[index] = lvInfo.Number_of_Iterations;
		  }
		  if (lvInfo.Learning_Rate != -1)
		  {
			m_LearningRates[index] = lvInfo.Learning_Rate;
		  }
	  }
	  m_LevelQueue.pop();
	 }
	
}

	template < typename TInputImage,
		typename TImage,
		typename TPreprocessor,
		typename TRegistrator,
		typename TGenerator >
		void itk::MIMApplicationBase<TInputImage, TImage, TPreprocessor, TRegistrator, TGenerator>::SetInitialTransform( Rigid3DTransformPointer pTransform )
	{
		m_Registrator->SetInitialTransform(pTransform);
	}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
  ::SetInitialTransformMatrix(InitailMatrixType InitialMatrix)
{
	m_Registrator->SetInitialTransformMatrix(InitialMatrix);
	
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
std::queue<CostValueInformation> MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
  ::GetCostValueQueue()
{
	return m_Registrator->GetCostValueQueue();
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
itk::FixedArray<unsigned int,TInputImage::ImageDimension> 
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>
  ::SetShrinkFactorsAutomatically(string type)
{
	//In this Function we determine Shrink Factors Automatically
	int dimension = TInputImage::ImageDimension;
	itk::Vector<double,TInputImage::ImageDimension> SpaceFactors;
	
	itk::Array2D<double> factors;
	itk::Array2D<double> temp( m_NumberOfLevels + 1, ImageDimension );
	temp.Fill(1.0);

	factors = temp;
	
	if (strcmp(type.data(), "Fixed") == 0)
	{
	  SpaceFactors = m_FixedImage->GetSpacing();
	}

	if (strcmp(type.data(), "Moving") == 0)
	{
	  SpaceFactors = m_MovingImage->GetSpacing();
	}
	//	std::cout<<"Space Factors = "<<SpaceFactors<<std::endl;
	
	double MaxSpace = 0;
	int MaxSpaceIdx = 0;
	for (int idx=0;idx<dimension;idx++)
	{
		if (SpaceFactors[idx]>MaxSpace)
		{
			MaxSpace = SpaceFactors[idx];
			MaxSpaceIdx = idx;
		}
	}

	for (int levelIdx = m_NumberOfLevels-2; levelIdx>=0; levelIdx--)
	{
		bool allOnes = true;
		for (int dimIdx = 0;dimIdx<dimension;dimIdx++)
		{
			if ((SpaceFactors[MaxSpaceIdx] * factors[levelIdx+1][MaxSpaceIdx]) / 
				(SpaceFactors[dimIdx] * factors[levelIdx+1][dimIdx])>=2)
			{
				factors[levelIdx][dimIdx] = 2;
				allOnes = false;
			}			
		}
		if (allOnes)
		{
			for (int dimIdx = 0;dimIdx<dimension;dimIdx++)
			{
				factors[levelIdx][dimIdx] = 2;
			}
		}
	}
	
	itk::FixedArray<unsigned int, TInputImage::ImageDimension> ShrinkArray;

	for (int shrIdx = 0; shrIdx<TInputImage::ImageDimension; shrIdx++)
	{
		int shrFactor = 1;
		for (int LevelIndx = 0; LevelIndx<m_NumberOfLevels; LevelIndx++)
		{
			shrFactor = shrFactor * factors[LevelIndx][shrIdx];
		}
		ShrinkArray[shrIdx] = shrFactor;
	}
	
	std::cout<<"Shrink Factors are not set by user and they are set automatically \n ShrinkFactors = "
		<<ShrinkArray<<std::endl;
	return ShrinkArray;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetFixedImage(itk::Image<float,3>::Pointer pFixedImage)
{
	m_FixedImage = pFixedImage;
	m_isFixedImageSet = true;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
void
MIMApplicationBase<TInputImage,TImage,TPreprocessor,
TRegistrator, TGenerator>
::SetMovingImage(itk::Image< float , 3 >::Pointer pMovingImage)
{
	m_MovingImage = pMovingImage;
	m_isMovingImageSet = true;
}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  itk::Rigid3DTransform<double>::Pointer 
  MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>::GetTransformParameters()
{
	itk::Rigid3DTransform<double>::Pointer transfromMatrix = itk::Rigid3DTransform<double>::New();
	transfromMatrix = m_Transform;
	return transfromMatrix;
}

//template < typename TInputImage, typename TImage,
//  typename TPreprocessor,
//  typename TRegistrator, typename TGenerator >
//itk::Image< float,3>::Pointer 
//MIMApplicationBase<TInputImage,TImage,TPreprocessor,
//TRegistrator, TGenerator>::GetOutImage()
//{
//	return m_Generator->GetOutImage();
//}

template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  void MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>::SetIsRegistrationFinished(bool isRegistrationFinished)
{
	EnterCriticalSection(&section);
	m_IsRegistrationFinished = isRegistrationFinished;
	LeaveCriticalSection(&section);	
}


template < typename TInputImage, typename TImage,
  typename TPreprocessor,
  typename TRegistrator, typename TGenerator >
  bool MIMApplicationBase<TInputImage,TImage,TPreprocessor,
  TRegistrator, TGenerator>::GetIsRegistrationFinished()
{

	bool registrationIsFinished = false;
	EnterCriticalSection(&section);
	registrationIsFinished = m_IsRegistrationFinished;
	LeaveCriticalSection(&section);
	return registrationIsFinished;
}

template < typename TInputImage,
	typename TImage,
	typename TPreprocessor,
	typename TRegistrator,
	typename TGenerator >
	unsigned int itk::MIMApplicationBase<TInputImage, TImage, TPreprocessor, TRegistrator, TGenerator>::GetCurrentIteration()
{
		return this->m_Registrator->GetCurrentIteration();
}


} // namespace itk

#pragma warning (pop)

#endif