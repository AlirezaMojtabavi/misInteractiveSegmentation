#pragma once
#include "IMedicalImage.h"
#include <misImageModalityEnum.h>

namespace parcast
{ 
	template< class ScalarType>
	class MedicalImage : public IMedicalImage
	{
	public:
		MedicalImage();
		~MedicalImage();
		void SetDepth(const int width);
		void SetHeight(const int width);
		void SetWidth(const int width);
		void SetModality(misImageDataModality modality);
		void Allocate();
	private:
		int m_Depth;
		int m_Height;
		int m_Width;
		misImageDataModality m_ImageModality;
	};

	template <class ScalarType>
	MedicalImage<ScalarType>::MedicalImage()
		:m_Depth(0), m_Height(0), m_Width(0), m_ImageModality(CT)
	{
	}

	template <class ScalarType>
	MedicalImage<ScalarType>::~MedicalImage()
	{
	}

	template <class ScalarType>
	void MedicalImage<ScalarType>::SetDepth(const int depth)
	{
		m_Depth = depth;
	}

	template <class ScalarType>
	void MedicalImage<ScalarType>::SetHeight(const int heigth)
	{
		m_Height = heigth;
	}

	template <class ScalarType>
	void MedicalImage<ScalarType>::SetWidth(const int width)
	{
		m_Width = width;
	}

	template <class ScalarType>
	void MedicalImage<ScalarType>::SetModality(misImageDataModality modality)
	{
		m_ImageModality = modality;
	}

	template <class ScalarType>
	void MedicalImage<ScalarType>::Allocate()
	{
		
	}
}

