#pragma once
#include "vtkTimeStamp.h"
#include "vtkImageData.h"
#include "vtkType.h"
#include <vtkgl.h>

class DICOM2Texture
{
public:
	
	DICOM2Texture();	
	~DICOM2Texture();
	
	//static DICOM2Texture *New();
	
	vtkTimeStamp GetBuildTime();
	
	void Bind();
	
	void *Update(vtkImageData *input,
		int cellFlag,
		int textureExtent[6],
		bool linearInterpolation,
		double tableRange[2],
		int maxMemoryInBytes);
	

	double *GetLoadedBounds();
	
	vtkIdType *GetLoadedExtent();
	

	int GetLoadedCellFlag();
	
	bool IsLoaded();
	

	bool GetSupports_GL_ARB_texture_float();
	

	void SetSupports_GL_ARB_texture_float(bool value);
	const char *OpenGLErrorMessage( unsigned int errorCode);

	GLuint TextureId;

protected:
	
	vtkTimeStamp BuildTime;
	double LoadedBounds[6];
	vtkIdType LoadedExtent[6];
	int LoadedCellFlag;
	bool Loaded;
	bool LinearInterpolation;
	bool Supports_GL_ARB_texture_float;
	double LoadedTableRange[2];
	void *dataPtr;
};
