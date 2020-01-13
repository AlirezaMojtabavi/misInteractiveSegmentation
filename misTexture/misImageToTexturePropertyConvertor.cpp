#include "stdafx.h"
#include "misImageToTexturePropertyConvertor.h"

#include "IImage.h"
#include "misImageContained.h"
#include "misTexturePropertyStruct.h"
#include "misImageDataProperties.h"

using namespace std;

using tgt::vec3;
using tgt::ivec3;

misImageToTexturePropertyConvertor::misImageToTexturePropertyConvertor()
{
	m_texProp.Origin = 0;
	m_texProp.Data = 0;
}

misTexturePropertyStruct misImageToTexturePropertyConvertor::operator()(std::shared_ptr<IImage> input)
{
	if (input)
	{
		SetModality(input);
		SetExtent(input);
		auto points = input->GetRawImageData()->GetPointData();
		if (points)
		{
			auto scalar = points->GetScalars();
			if (scalar)
			{
				m_texProp.ScalarType = input->GetScalarType();
			}
		}

		switch (m_texProp.ScalarType)
		{
		case VTK_FLOAT:
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_FLOAT;
			break;
		case VTK_UNSIGNED_CHAR:
		{
			auto numberOfScalarComponents = input->GetRawImageData()->GetNumberOfScalarComponents();
			_ASSERT(numberOfScalarComponents >= 3);
			if (numberOfScalarComponents == 3)
			{
				m_texProp.Data = (signed char*)input->GetScalarPointer();
				m_texProp.InternalFormat = GL_RGB;
				m_texProp.Format = GL_RGB;
				m_texProp.DataType = GL_UNSIGNED_BYTE;
			}
			else if (numberOfScalarComponents == 4)
			{
				m_texProp.Data = (signed char*)input->GetScalarPointer();
				m_texProp.InternalFormat = GL_RGBA;
				m_texProp.Format = GL_RGBA;
				m_texProp.DataType = GL_UNSIGNED_BYTE;
			}
		break;
		}
		case VTK_SIGNED_CHAR:
			// Assumed that image 3 3-component rgb and each component is char 
			m_texProp.Data = (signed char*)input->GetScalarPointer();
			m_texProp.InternalFormat = GL_RGB;
			m_texProp.Format = GL_RGB;
			m_texProp.DataType = GL_UNSIGNED_BYTE;
			break;
		case VTK_CHAR:
			// Assumed that image 3 3-component rgb and each component is char 
			m_texProp.Data = (signed char*)input->GetScalarPointer();
			m_texProp.InternalFormat = GL_RGB;
			m_texProp.Format = GL_RGB;
			m_texProp.DataType = GL_UNSIGNED_BYTE;
			break;
		case VTK_BIT:
			_ASSERT("check: impossible case" && 0);
			break;

		case VTK_ID_TYPE:
			_ASSERT("check: impossible case" && 0);
			break;
		case VTK_INT:
			m_texProp.Data = (int*)input->GetScalarPointer();
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_INT;
			break;
		case VTK_DOUBLE:
		case VTK___INT64:
		case VTK_LONG:
		case VTK_LONG_LONG:
		case VTK_UNSIGNED___INT64:
		case VTK_UNSIGNED_LONG:
		case VTK_UNSIGNED_LONG_LONG:
			/*if(this->Supports_GL_ARB_texture_float)
			InternalFormat=GL_INTENSITY16F_ARB;
			else*/
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_FLOAT;
			break;
		case VTK_SHORT:
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_SHORT;
			m_texProp.Data = (short *)input->GetScalarPointer();
			break;
		case VTK_STRING:
			_ASSERT("check: impossible case" && 0);
			break;
		case VTK_UNSIGNED_SHORT:
			m_texProp.Data = (unsigned short*)input->GetScalarPointer();
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_UNSIGNED_SHORT;
			break;
		case VTK_UNSIGNED_INT:
			m_texProp.Data = (unsigned int*)input->GetScalarPointer();
			m_texProp.InternalFormat = GL_INTENSITY16;
			m_texProp.Format = GL_RED;
			m_texProp.DataType = GL_UNSIGNED_INT;
			break;
		default:
			break;
		}

		SetOrigin(input);
		SetSpacing(input);
		SetBitStored(input);
		SetTableRange(input);
		m_texProp.SetROI(input->GetROI());
	}
	return m_texProp;
}

void misImageToTexturePropertyConvertor::SetTableRange(std::shared_ptr<IImage> input)
{
	auto neededTableRange = input->GetScalerRangeNeeded();
	double tableRange[2];
	tableRange[0] = neededTableRange[0];
	tableRange[1] = neededTableRange[1];
	m_texProp.SetTableRane(tableRange);
}

void misImageToTexturePropertyConvertor::SetModality(std::shared_ptr<IImage> image)
{
	auto levWin = image->GetImageDataProperties()->GetViewingProperties().GetLevelWindow();
	double windowCenter = levWin.GetWindowCenter();
	m_texProp.SetWindowCenter(windowCenter);
	double windowWidth = levWin.GetWindowWidth();
	m_texProp.SetWindowLevel(windowWidth);
	this->m_texProp.Modality = image->GetImageModality();
}

void misImageToTexturePropertyConvertor::SetExtent(std::shared_ptr<IImage> input)
{
	if (input)
	{
		auto extent = input->GetRawImageData()->GetExtent();
		m_texProp.SetExtent(extent);
	}
}

void misImageToTexturePropertyConvertor::SetOrigin(std::shared_ptr<IImage> input)
{
	if (input)
	{
		m_texProp.Origin = input->GetRawImageData()->GetOrigin();
	}
}

void misImageToTexturePropertyConvertor::SetSpacing(std::shared_ptr<IImage> input)
{
	if (input)
	{
		auto spacing = input->GetSpacing();
		m_texProp.Spacing = tgt::vec3(spacing[0], spacing[1], spacing[2]);
	}
}

void misImageToTexturePropertyConvertor::SetBitStored(std::shared_ptr<IImage> input)
{
	if (input)
	{
		m_texProp.BitStored = input->GetRawImageData()->GetScalarSize() * 8/*size of Byte */ *
			input->GetRawImageData()->GetNumberOfScalarComponents();
	}
}