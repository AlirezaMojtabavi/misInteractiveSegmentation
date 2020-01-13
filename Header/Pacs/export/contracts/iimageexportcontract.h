#pragma once
/*
*
*  $Id: iimageexportcontract.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#ifndef IIMAGEEXPORTCONTRACT_H
#define IIMAGEEXPORTCONTRACT_H

#include <string>
#include <list>
#include <map>

#include <api/api.h>
#include <api/autoptr.h>
#include <api/icontract.h>
#include <api/math/geometry.h>

#include <export/contracts/iviewcontract.h>

#ifdef __DEPRECATED
#undef __DEPRECATED
#endif

#include <itkImage.h>
#include <itkRGBPixel.h>
#include <vtkSmartPointer.h>

class vtkImageData;
namespace GNC {
	namespace GCS {
		class IWidgetsManager;
		class IImageExportContract;

		class EXTAPI IImageExportDelegate {	
		public:
			IImageExportDelegate(IImageExportContract* exportContract);
			virtual ~IImageExportDelegate();

			typedef itk::RGBPixel<unsigned char> PixelType;
			typedef itk::Image< PixelType,  2 > ImageType;
			typedef std::map<std::string, bool> TValorationMaps;

			virtual void GetCurrentImage(ImageType::Pointer& img, TValorationMaps& mapasValoracion, bool conWidgets, const GNC::GCS::Vector& size) = 0;
			virtual void GetImage(ImageType::Pointer& img, int index, TValorationMaps& mapasValoracion, bool conWidgets, const GNC::GCS::Vector& size) = 0;
			virtual int GetNumberOfSlices() = 0;
			virtual IImageExportDelegate::TValorationMaps GetValorationMaps() = 0;
			virtual std::string GetPathActiveDICOM();
			virtual std::string GetPathDICOM(int index);
			virtual std::list<std::string> GetPathAllDICOMs();
			IImageExportContract* GetExportContract();
		protected:
			virtual void CopyRGBToRGBA32(unsigned char* src, unsigned char* dst, unsigned int size);
			virtual void CopyRGBA32ToRGB(unsigned char* src, unsigned char* dst, unsigned int size);
			virtual vtkSmartPointer<vtkImageData> GetVtkImage(int index);

			virtual void Print(vtkSmartPointer<vtkImageData> imageData, bool conWidgets, int index, const GNC::GCS::Vector& size, ImageType::Pointer& out, GNC::GCS::IWidgetsManager* pWidgetsManager);

			virtual void PrintWithWidgets(ImageType::Pointer& img, int index, const GNC::GCS::Vector& aspectRatio, GNC::GCS::IWidgetsManager* pWidgetsManager);

			IImageExportContract* ExportContract;
		};
		class EXTAPI IImageExportContract: public IViewContract {
		public:
			IImageExportContract();
			~IImageExportContract();
			
			virtual GNC::GCS::Ptr<GNC::GCS::IImageExportDelegate> GetNewExportDelegate() = 0;
			virtual bool CanBeExported() = 0;
		};
	}
}

#endif
