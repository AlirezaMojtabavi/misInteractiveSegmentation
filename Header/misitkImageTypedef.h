#pragma once

#include "misitkTypdef.h"
#include "itkNeighborhoodConnectedImageFilter.h"

typedef float						      misitkPixelType;
typedef itk::Image< misitkPixelType, 3 >  misitkImageType;

typedef   float           PixelType;
typedef itk::Image< PixelType, 3 >  misitkImageType;

typedef itk::NeighborhoodConnectedImageFilter<misitkImageType,
	misitkImageType > ConnectedFilterType;

typedef misitkImageType::IndexType     misitkSeedType;
typedef std::vector<misitkSeedType>    misitkSeedListType;