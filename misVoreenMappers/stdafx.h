// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#include "targetver.h"

#include <algorithm>
#include <cstdio>
#include <deque>
#include <stack>
#include <tchar.h>
#include <vector>
#include <memory>

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <objidl.h>


 
#include <GdiPlus.h>

#include "GL/glew.h"

#include "itkEventObject.h"
#include "itkPoint.h"

#include "vtkAbstractMapper3D.h"
#include "vtkAbstractVolumeMapper.h"
#include "vtkActor.h"
#include "vtkAssemblyPaths.h"
#include "vtkBox.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkDataArray.h"
#include "vtkGraphicsFactory.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageReader.h"
#include "vtkImageReader2.h"
#include "vtkLODProp3D.h"
#include "vtkLinearTransform.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLActor.h"
#include "vtkParametricSpline.h"
#include "vtkPicker.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkProp3DCollection.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkTexture.h"
#include "vtkTransform.h"
#include "vtkViewport.h"

#include "igstkTransform.h"
#include "igstkEvents.h"
#include "itkMutexLock.h"

#include "tgt/camera.h"
#include "tgt/matrix.h"
#include "tgt/plane.h"
#include "tgt/texture.h"
#include "tgt/texturereaderdevil.h"
#include "tgt/transfuncintensity.h"
#include "tgt/transfuncmappingkey.h"
#include "tgt/vector.h"
#include "tgt/init.h"

#include "gdcmBinEntry.h"
#include "gdcmDicomDir.h"
#include "gdcmDicomDirImage.h"
#include "gdcmDicomDirMeta.h"
#include "gdcmDicomDirPatient.h"
#include "gdcmDicomDirSerie.h"
#include "gdcmDicomDirStudy.h"

#pragma warning ( push , 0 )

#include "voreen/cameraproperty.h"
#include "voreen/canvasrenderer.h"
#include "voreen/meshentryexitpoints.h"
#include "voreen/multivolumeproxygeometry.h"
#include "voreen/processor.h"
#include "voreen/property.h"
#include "voreen/transfuncproperty.h"
#include "voreen/volume.h"
#include "voreen/volumeatomic.h"
#include "voreen/volumehandle.h"
#include "voreen/volumemetadata.h"
#include "voreen/voreenapplication.h"
#include "voreen/multivolumeraycaster.h"

#pragma warning ( pop )

#include "TinyXml/tinyxml.h"
#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
// TODO: reference additional headers your program requires here
