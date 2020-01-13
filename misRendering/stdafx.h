// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma warning ( push, 0 )

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <algorithm>
#include <cmath>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#include "gl/glew.h"

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "itkBoundingBox.h"
#include "itkCovariantVector.h"
#include "itkImage.h"
#include "itkMutexLock.h"
#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkVector.h"

#define vtkRenderingCore_AUTOINIT 3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL2) 

#include "vtk3DS.h"  // Needed for all the 3DS structures
#include "vtk3DWidget.h"  // Needed for all the 3DS structures
#include "vtkAbstractVolumeMapper.h"
#include "vtkActor.h"
#include "vtkActorCollection.h"
#include "vtkAppendPolyData.h"
#include "vtkAreaPicker.h"
#include "vtkAssemblyNode.h"
#include "vtkAssemblyPath.h"
#include "vtkAssemblyPaths.h"
#include "vtkAxes.h"
#include "vtkBox.h"
#include "vtkBoxWidget.h"
#include "vtkByteSwap.h"
#include "vtkCallbackCommand.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkCellLocator.h"
#include "vtkCellPicker.h"
#include "vtkColorTransferFunction.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkCuller.h"
#include "vtkCullerCollection.h"
#include "vtkCylinderSource.h"
#include "vtkDataArray.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkFrustumCoverageCuller.h"
#include "vtkGraphicsFactory.h"
#include "vtkHardwareSelector.h"
#include "vtkIdList.h"
#include "vtkImageActor.h"
#include "vtkImageCast.h"
#include "vtkImageData.h"
#include "vtkImageGradientMagnitude.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkImageReslice.h"
#include "vtkImageShiftScale.h"
#include "vtkImporter.h"
#include "vtkInteractorStyle.h"
#include "vtkInteractorStyleFlight.h"
#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLODProp3D.h"
#include "vtkLight.h"
#include "vtkLightCollection.h"
#include "vtkLineSource.h"
#include "vtkLookupTable.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkOBJExporter.h"
#include "vtkObject.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLActor.h"
#include "vtkOpenGLCamera.h"
#include "vtkOpenGLLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkOpenGLProperty.h"
#include "vtkOpenGLRenderer.h"
#include "vtkOpenGLTexture.h"
#include "vtkOutlineFilter.h"
#include "vtkOutputWindow.h"
#include "vtkPNGReader.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPerspectiveTransform.h"
#include "vtkPicker.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPlane.h"
#include "vtkPlaneSource.h"
#include "vtkPlaneWidget.h"
#include "vtkPlanes.h"
#include "vtkPointData.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataWriter.h"
#include "vtkProp3DCollection.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderPass.h"
#include "vtkRenderState.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkRendererDelegate.h"
#include "vtkSeedWidget.h"
#include "vtkSelectVisiblePoints.h"
#include "vtkSetGet.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkStripper.h"
#include "vtkSystemIncludes.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkTextSource.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"
#include "vtkTubeFilter.h"
#include "vtkViewport.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkWorldPointPicker.h"
#include "vtkFreeTypeTools.h"

#include "igstkEvents.h"
#include "igstkMacros.h"

#include "tgt/camera.h"
#include "tgt/init.h"
#include "tgt/matrix.h"
#include "tgt/texture.h"
#include "tgt/transfuncintensity.h"
#include "tgt/transfuncmappingkey.h"

#include "TinyXml/tinyxml.h"
#include "tinyxml2.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"

#include "voreen/TransferFuncs3D.h"

#pragma warning ( pop )
