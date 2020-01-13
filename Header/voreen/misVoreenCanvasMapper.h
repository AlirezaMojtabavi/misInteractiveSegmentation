#pragma once

#include "misMultiVolumecastMapper.h"
#include "misTransferFunctionSelecting.h"

class misApplicationSetting;
class misVoreenCanvasMapper : 	public misMultiVolumecastMapper
{
public:
	static misVoreenCanvasMapper* New();
	misVoreenCanvasMapper(void);
	~misVoreenCanvasMapper(void);
	virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	void SetCanvasPart(std::vector<voreen::VolumeHandle*> handles,std::vector<TransFuncIntensity*> trnsferFunctions,tgt::ivec3 size);
	void SetCanvasPart(std::map<misOpenglTexture* , voreen::VolumeHandle*> volumeHandleMap, std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> textureMap,tgt::ivec3 size );
	void SetWindowSize( tgt::ivec2  size);
	void ClipingOn( );
	void ClipingOF( );
	void SetClipingPlane(tgt::vec4 plane);
	tgt::RenderTarget*  GetVolumeRenderOutputTarget();
	void Modify();
	void RnderProxyGeometry(bool val);//Only for test
	int  FindNearestPoint(double p1[3], double p2[3], double tol,double* intersectedPoint);
	void FindNewPositionOnLine( double * newPosition, double * startPosition, double * lineNormal, float& step );
	int  GetIndexInImagePointer( misOpenglTexture* pImage, double * position, bool &rangeChecX, bool &rangeChecY, bool &rangeChecz );
	float IsInside( double * position, double * p1,  double * p2);
	void SetTransferFunctionSelector(misTransferFunctionSelecting* viewerTFSelector);
	voreen::CanvasRenderer* GetCanvasProcess() const;

private:
	tgt::Camera  m_CuurentCamera;
	//bool   m_NeedUpdtae;
	bool   m_CameraChanged;
	bool   m_Modified;
	misTransferFunctionSelecting* m_TFSelector;
protected:
	voreen::CanvasRenderer*  m_CanvasProcess;
	tgt::ivec2  m_WindowSize;
	void SortProcessors();	
	bool NeedUpdate();
};

