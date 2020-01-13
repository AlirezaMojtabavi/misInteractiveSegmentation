/*=========================================================================

Program:   Insight Segmentation & Registration Toolkit
Module:    $RCSfile: itkVTKImageToImageFilter.h,v $
Language:  C++
Date:      $Date: 2004-04-25 21:35:10 $
Version:   $Revision: 1.5 $

Copyright (c) 2002 Insight Consortium. All rights reserved.
See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even 
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#pragma once

#include "itkVTKImageImport.h"
#include "vtkImageExport.h"
#include "vtkImageData.h"

#ifndef vtkFloatingPointType
#define vtkFloatingPointType float
#endif

namespace itk {

	/** \class VTKImageToImageFilter
	* \brief Converts a VTK image into an ITK image and plugs a
	*  vtk data pipeline to an ITK datapipeline.
	*
	*  This class puts together an itkVTKImageImporter and a vtkImageExporter.
	*  It takes care of the details related to the connection of ITK and VTK
	*  pipelines. The User will perceive this filter as an adaptor to which
	*  a vtkImage can be plugged as input and an itk::Image is produced as
	*  output.
	*
	* \ingroup   ImageFilters
	*/
	template <class TOutputImage >
	class VTKImageToImageFilter : public ProcessObject {
	public:
		/** Standard class typedefs. */
		typedef VTKImageToImageFilter Self;
		typedef ProcessObject Superclass;
		typedef SmartPointer<Self> Pointer;
		typedef SmartPointer<const Self> ConstPointer;

		/** Method for creation through the object factory. */
		itkNewMacro(Self);

		/** Run-time type information (and related methods). */
		itkTypeMacro(VTKImageToImageFilter, ProcessObject);

		/** Some typedefs. */
		typedef TOutputImage OutputImageType;
		typedef typename OutputImageType::ConstPointer OutputImagePointer;
		typedef VTKImageImport< OutputImageType > ImporterFilterType;
		typedef typename ImporterFilterType::Pointer ImporterFilterPointer;

		/** Get the output in the form of a vtkImage.
		This call is delegated to the internal vtkImageImporter filter  */
		const OutputImageType * GetOutput() const;

		/** Set the input in the form of a vtkImageData */
		void SetInput(vtkImageData *);

		/** Return the internal VTK image exporter filter.
		This is intended to facilitate users the access
		to methods in the exporter */
		vtkImageExport * GetExporter() const;

		/** Return the internal ITK image importer filter.
		This is intended to facilitate users the access
		to methods in the importer */
		ImporterFilterType * GetImporter() const;

		/** This call delegate the update to the importer */
		void Update();

	protected:
		VTKImageToImageFilter();
		virtual ~VTKImageToImageFilter();

	private:
		VTKImageToImageFilter(const Self&); //purposely not implemented
		void operator=(const Self&); //purposely not implemented

		ImporterFilterPointer m_Importer;
		vtkImageExport * m_Exporter;

	};

	/**
	* Constructor
	*/
	template <class TOutputImage> VTKImageToImageFilter<TOutputImage>::VTKImageToImageFilter() {

		m_Exporter = vtkImageExport::New();

		m_Importer = ImporterFilterType::New();

		m_Importer->SetUpdateInformationCallback(m_Exporter->GetUpdateInformationCallback());
		m_Importer->SetPipelineModifiedCallback(m_Exporter->GetPipelineModifiedCallback());
		m_Importer->SetWholeExtentCallback(m_Exporter->GetWholeExtentCallback());
		m_Importer->SetSpacingCallback(m_Exporter->GetSpacingCallback());
		m_Importer->SetOriginCallback(m_Exporter->GetOriginCallback());
		m_Importer->SetScalarTypeCallback(m_Exporter->GetScalarTypeCallback());
		m_Importer->SetNumberOfComponentsCallback(m_Exporter->GetNumberOfComponentsCallback());
		m_Importer->SetPropagateUpdateExtentCallback(m_Exporter->GetPropagateUpdateExtentCallback());
		m_Importer->SetUpdateDataCallback(m_Exporter->GetUpdateDataCallback());
		m_Importer->SetDataExtentCallback(m_Exporter->GetDataExtentCallback());
		m_Importer->SetBufferPointerCallback(m_Exporter->GetBufferPointerCallback());
		m_Importer->SetCallbackUserData(m_Exporter->GetCallbackUserData());

	}

	/**
	* Destructor
	*/
	template <class TOutputImage>
	VTKImageToImageFilter<TOutputImage>
		::~VTKImageToImageFilter() {
			if (m_Exporter) {
				m_Exporter->Delete();
				m_Exporter = 0;
			}
	}

	/**
	* Set a vtkImageData as input
	*/
	template <class TOutputImage>
	void
		VTKImageToImageFilter<TOutputImage>
		::SetInput(vtkImageData * inputImage) {
			m_Exporter->SetInput(inputImage);
	}

	/**
	* Get an itk::Image as output
	*/
	template <class TOutputImage>
	const typename VTKImageToImageFilter<TOutputImage>::OutputImageType *
		VTKImageToImageFilter<TOutputImage>
		::GetOutput() const {
			return m_Importer->GetOutput();
	}

	/**
	* Get the exporter filter
	*/
	template <class TOutputImage>
	vtkImageExport *
		VTKImageToImageFilter<TOutputImage>
		::GetExporter() const {
			return m_Exporter;
	}

	/**
	* Get the importer filter
	*/
	template <class TOutputImage>
	typename VTKImageToImageFilter<TOutputImage>::ImporterFilterType *
		VTKImageToImageFilter<TOutputImage>
		::GetImporter() const {
			return m_Importer;
	}

	/**
	* Delegate the Update to the importer
	*/
	template <class TOutputImage>
	void
		VTKImageToImageFilter<TOutputImage>
		::Update() {
			m_Importer->Update();
	}


} // end namespace itk




