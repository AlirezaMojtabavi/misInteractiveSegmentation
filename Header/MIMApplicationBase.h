/*=========================================================================

Program:   Insight Segmentation & Registration Toolkit
Module:    $RCSfile: MIMApplicationBase.h,v $
Language:  C++
Date:      $Date: 2002-10-05 15:49:25 $
Version:   $Revision: 1.2 $

Copyright (c) 2002 Insight Consortium. All rights reserved.
See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MIMApplicationBase_h
#define _MIMApplicationBase_h

#include "itkObjectFactory.h"
#include "itkObject.h"
#include "itkFixedArray.h"
#include "itkArray.h"
#include "itkMatrix.h"
#include "itkImage.h"
#include "itkMatrixOffsetTransformBase.h"

#include "LevelInformation.h"
#include "CostValueInformation.h"
#include <queue>
#include "itkRigid3DTransform.h"
#include "RecursivePyramidFilter.h"

namespace itk
{
	/** \class MIMApplicationBase
	*
	* This class ties together an input parser, a preprocessor,
	* a registrator and an output generator component to form a MIM registration
	* application.
	*
	*/

	template < typename TInputImage,
		typename TImage,
		typename TPreprocessor,
		typename TRegistrator,
		typename TGenerator >
	class MIMApplicationBase : public Object
	{
	public:

		/** Standard class typedefs. */
		typedef MIMApplicationBase Self;
		typedef Object Superclass;
		typedef SmartPointer<Self> Pointer;
		typedef SmartPointer<const Self>  ConstPointer;

		/** Run-time type information (and related methods). */
		itkTypeMacro(MIMApplication, Object);

		/** Method for creation through the object factory. */
		itkNewMacro(Self);

		/** Input image type. */
		typedef TInputImage InputImageType;
		typedef typename InputImageType::PixelType InputPixelType;
		itkStaticConstMacro(ImageDimension, unsigned int, TInputImage::ImageDimension );

		/** Internal image type. */
		typedef TImage ImageType;
		typedef typename ImageType::PixelType PixelType;

		///** Input parser type. */
		//typedef TReader ReaderType;
		//typedef typename ReaderType::Pointer ReaderPointer;

		/** Preprocessor type. */
		typedef TPreprocessor PreprocessorType;
		typedef typename PreprocessorType::Pointer PreprocessorPointer;

		/** Registrator type. */
		typedef TRegistrator RegistratorType;
		typedef typename RegistratorType::Pointer RegistratorPointer;

		/** Output generator type. */
		typedef TGenerator GeneratorType;
		typedef typename GeneratorType::Pointer GeneratorPointer;

		/** Affine transform type */
		typedef typename PreprocessorType::Rigid3DTransformType Rigid3DTransformType;
		typedef typename Rigid3DTransformType::Pointer          Rigid3DTransformPointer;

		/** Execute the application. */
		virtual void Execute();

		itk::FixedArray<unsigned int, TInputImage::ImageDimension>  GetPermuteOrderArray();
		void SetPermuteOrderArray(itk::FixedArray<unsigned int, TInputImage::ImageDimension>  PermuteOrder);

		itk::FixedArray<bool, TInputImage::ImageDimension> GetFlipAxesArray();
		void SetFlipAxesArray(itk::FixedArray<bool, TInputImage::ImageDimension> FlipAxes);

		unsigned short GetNumber_of_Levels();
		void SetNumber_of_Levels(unsigned short Number_Levels);

		itk::FixedArray<unsigned int, TInputImage::ImageDimension> GetFixedImageShrinkFactors();
		void SetFixedImageShrinkFactors(itk::FixedArray<unsigned int, TInputImage::ImageDimension> FixedImageShrinkFactors);

		itk::FixedArray<unsigned int, TInputImage::ImageDimension> GetMovingImageShrinkFactors();
		void SetMovingImageShrinkFactors(itk::FixedArray<unsigned int, TInputImage::ImageDimension> MovingImageShrinkFactors);

		double GetTranslationScale();
		void SetTranslationScale(double scale);

		std::string GetOutputFileName();
		void SetOutputFileName(std::string OutputFileName);

		std::string GetFixedImageFileName();
		void SetFixedImageFileName(std::string FixedFileName);

		std::string GetMovingImageFileName();
		void SetMovingImageFileName(std::string MovingFileName);

		void SetStopOptimization(bool);

		itk::Matrix<double,TInputImage::ImageDimension,TInputImage::ImageDimension> GetTransformMatrix();

		itk::FixedArray<double,TInputImage::ImageDimension> GetOffset();

		void InsertLevelsQueue(levelInformation lInfo);

		void UpdateLevelInformation();

		typedef itk::Matrix<double,TInputImage::ImageDimension+1,
			TInputImage::ImageDimension+1> InitailMatrixType;

		void SetInitialTransformMatrix(InitailMatrixType InitialMatrix);
		void SetInitialTransform(Rigid3DTransformPointer pTransform );

		std::queue<CostValueInformation> GetCostValueQueue();

		void SetFixedImage(itk::Image<float,3>::Pointer pFixedImage);
		void SetMovingImage(itk::Image<float,3>::Pointer pMovingImage);

		void SetIsRegistrationFinished(bool isRegistrationFinished);
		bool GetIsRegistrationFinished();

		//itk::Image< float,3>::Pointer GetOutImage();
		itk::Rigid3DTransform<double>::Pointer GetTransformParameters();

		itk::Rigid3DTransform<double>::Pointer GetCurrentTransformMatrix();

		unsigned int GetCurrentIteration();

	//	bool IsModified();

	protected:

		MIMApplicationBase();
		virtual ~MIMApplicationBase(){};

		/*** Initialize the preprocessor */
		virtual void InitializePreprocessor();

		/*** Initialize the registrator  */
		virtual void InitializeRegistrator();

		/*** Initialize the output generator. */
		virtual void InitializeGenerator(){};

		itk::FixedArray<unsigned int,TInputImage::ImageDimension>
			SetShrinkFactorsAutomatically(string type);

		PreprocessorPointer							 m_Preprocessor;
		RegistratorPointer							 m_Registrator;
		GeneratorPointer								 m_Generator;

		Rigid3DTransformPointer						 m_Transform;

		double										 m_TranslationScale;
		Array<double>									 m_LearningRates;
		itk::FixedArray<unsigned int, ImageDimension>		 m_PermuteOrder;
		itk::FixedArray<bool, ImageDimension>				 m_FlipAxes;
		unsigned short								 m_NumberOfLevels;
		itk::FixedArray<unsigned int,ImageDimension>		 m_FixedImageShrinkFactors;
		itk::FixedArray<unsigned int, ImageDimension>		 m_MovingImageShrinkFactors;
		Array<unsigned int>							 m_NumberOfIterations;
		std::string									 m_OutputFileName;
		std::string									 m_FixedImageFileName;
		std::string									 m_MovingImageFileName;

		typename TInputImage::Pointer					 m_FixedImage;
		typename TInputImage::Pointer					 m_MovingImage;

		/*itk::Image<float,3>::Pointer					 m_FixedImage;
		itk::Image<float,3>::Pointer					 m_MovingImage;*/

		std::queue<levelInformation>                        m_LevelQueue;

		bool											 m_IsFixedShrinkFactorsSet;
		bool                                           m_IsMovingShrinkFactorsSet;

		bool										     m_isMovingImageSet;
		bool										     m_isFixedImageSet;

		bool											m_IsRegistrationFinished;
		CRITICAL_SECTION							  section;
	};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "MIMApplicationBase.txx"
#endif

#endif
