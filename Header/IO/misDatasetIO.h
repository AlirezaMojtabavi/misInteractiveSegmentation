#pragma once

#ifndef misDatasetIO_H
#define misDatasetIO_H

#include "misImageIOProperties.h"
#include "misPrimaeryNeededHeader.h" 
#include "misResultCode.h"
#include "misStrctImageData.h"

class vtkImageData;
class vtkImageReader;
class vtkImageWriter;
    	 
class vtkPolyData;
class vtkPLYReader;
class vtkPLYWriter;

class vtkActorCollection;
/*class mis3DSImporter;*/
class vtkRenderWindow;
class vtkRenderer;

namespace dataBaseIOPackage
{
	class  dataBaseIOClass;
}


 
 class    misDatasetIO
{
private:

static bool checkImageValidity( vtkImageData* spVtkImage );
public:
	static vtkSmartPointer<vtkImageData> ReadVtkImage(std::string completeFileNameAddress, int NOC, int extent[6],
	                                                  double spacing[3], int st);
	static vtkSmartPointer<vtkImageData> ReadVtkImage(std::string completeFileNameAddress,
	                                                  misImageIOProperties imageIOProperties);
	static bool ReadRawImage( std::string completeFileNameAddress, misImageIOProperties imageIOProperties ,vtkImageData* image);
	static misResultCode::ResultIds       SaveVtkImage(vtkImageData*   pVtkImage, std::string completeFileNameAddress);
	static misResultCode::ResultIds			SaveRaWImage(vtkImageData* spVtkImage, std::string completeFileNameAddress );

	

	static vtkPolyData*                   LoadFromPolyDataFile(  std::string completeFileNameAddress);
	static misResultCode::ResultIds       WritePolyDataFile( vtkPolyData* pPolyData, std::string completeFileNameAddress);
	static misResultCode::ResultIds       CreateFolderPath(std::string mainFolderPath, std::string demandedFolder);
	static vtkActorCollection*            LoadBody3DModel(std::string modelPath);
	static  vtkPolyData*                   ReadObjFiles(std::string modelPath);




		 
		  /* 
			 static std::string    TransformToString(vtkTransform* transform);
			 static vtkTransform*	StringToTransform(string transformString);
		 */
public:
	friend class misDataBaseIO;
	misDatasetIO(void);


static	bool FileExists( const char* FileName );
 };


#endif
