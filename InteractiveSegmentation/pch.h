// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include"pch.h"

#include "framework.h"

#include <stdio.h>
#include <tchar.h>

//#define vtkRenderingCore_AUTOINIT 2(vtkInteractionStyle, vtkRenderingOpenGL2)
#include <algorithm>
#include <iostream>
#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include <vtkDICOMImageReader.h>
#include "vtkImageMapper3D.h"
#include "vtkCamera.h"
#include "vtkRendererCollection.h"
#include "vtkContextActor.h"
#include <itkVTKImageToImageFilter.h>
#include "itkBinaryFillholeImageFilter.h"
#include <itkImageToVTKImageFilter.h>
#include <vtkImageSliceMapper.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageReslice.h>

#include "vtkMatrix4x4.h"
#include "itkSmartPointer.h"
#include <itkImageToVTKImageFilter.h>
#include <itkImage.h>
#include <vtkImageSliceMapper.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageSeriesWriter.h"
#include <itkCastImageFilter.h>

#endif //PCH_H
