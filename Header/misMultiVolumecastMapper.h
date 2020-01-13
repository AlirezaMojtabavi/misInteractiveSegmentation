#pragma once

#include "misEntryExitMapper.h"
#include "voreen/multivolumeraycaster.h"
#include "TransferFuncs3D.h"
#include "TransFuncIntensity.h"

struct LightStruct{
	double		x;
	double		y;
	double		z;
};	
class misMultiVolumecastMapper:public misEntryExitMapper
{
	friend class misRayCasterTest;
protected:

	std::string			lightSourcePropID[5];
	LightStruct			lightSourcePropValue[5];
	
	void SetLightSourceProperties(vtkRenderer *rend);
	void FillLightPropertyList();
	void FillLightPropertyValueList(vtkRenderer *rend);	
	void SetTransferFunctionan(int index, ImageContainedTransferFuncs3D transferFunction);
	void SetRayCastPart(std::map<misOpenglTexture* , voreen::VolumeHandle*> volumeHandleMap, 
		std::map<misOpenglTexture* , ImageContainedTransferFuncs3D> textureMap,tgt::ivec3 size);
	
public:
	voreen::MultiVolumeRaycaster*            m_RayCasterProcess;
	misMultiVolumecastMapper(void);
	~misMultiVolumecastMapper(void);
	virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	void SetToolPosition(double x,double y ,double z);
	void SetCropping( misCroppingDirectionInVR cropping );
	misCroppingDirectionInVR   GetCropping( );
	void CompileVolumeShader(int numberOfVol);
	virtual void SetCmaeraProp( vtkRenderer * ren );
	void SetSampleRate(float fps);
	void ResetMapInShader();
	
};

