#pragma once

class misMeanFilter
{
 public:
	misMeanFilter()
	{
	}

  typedef itk::Image< unsigned short, 3 > ImageType;
  typedef   unsigned short           InternalPixelType;

  typedef itk::Image< InternalPixelType, 3 >  InternalImageType;
  typedef itk::ImageFileReader< InternalImageType > ReaderType;
  typedef itk::Image< unsigned short, 3 > ImageType;

  InternalPixelType CalculateMeanValue(int Radius, misMeanFilter::InternalImageType::IndexType index,
  std::string ImageFileName);
};
