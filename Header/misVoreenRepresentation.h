#pragma once

#include "IPartialVolumeBaseRepresentation.h"
#include "IVolumeRepresentation.h"
#include "misImage.h"
#include "misOpenglTexture.h"
#include "misRepresentation.h"
#include "misVoreenActor.h"
#include "misVoreenCanvasMapper.h"
#include "misobject.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"


class  misVoreenRepresentation :public IPartialVolumeBaseRepresentation, public IvolumeRepresentation, 
	public std::enable_shared_from_this<misVoreenRepresentation>

{
public:
	misVoreenRepresentation();


 	virtual void SetToolPosition(double xCoord, double yCoord, double zCoord);	//double *GetBounds();
	virtual void SetToolAngle(float toolAngle){}
	// When direction is 	AnteriorUp,	AnteriorDown shader crop the image directly by computing , in other direction the proxy 
	// geometry clips for better performance
	virtual void SetCroppingDirection( misCroppingDirectionInVR direction);
	void SetWindowSize(tgt::ivec3 size);
	void SetVolume(int id , misOpenglTexture*  pTexture);
	void SetVolume(  misOpenglTexture* pTexture, ImageContainedTransferFuncs3D pTextureTFs);
	void SetTranformMatrixToVolumes(int, tgt::mat4);
	void SetTranformMatrixToVolumes(std::string name, tgt::mat4);
	void ClipingOn( );
	void ClipingOF( );
	void SetClipingPlane(tgt::vec4 plane);
	void  SetSampleRate(float fps);
	void  ClearTextureHnadleMapBeforSetVolume();
	void  ResetMapInShader();
	void  SetROI(const double* fov);
	void  RemoveFOV();
	void  ModifyVolume();
	void  CompileVolumeShader();
	void  RnderProxyGeometry(bool val);//Only for test
	void SetRenderer(vtkRenderer* val);
	std::vector<voreen::VolumeHandle*> GetVolumehandles() const;
	vtkSmartPointer<misVoreenCanvasMapper> GetVoreenMapper() const;


	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command* command) override;


	virtual void InvokeEvent(const itk::EventObject& event) override;


	virtual bool HasObserver(const itk::EventObject & event) const override;


	virtual std::string GetObjectName() const override;


	virtual void SetObjectName(std::string val) override;


	virtual void SetRepresentationName(std::string name) override;


	virtual void AddProp(vtkProp*) override;


	virtual void SetVisibilityOff(void) override;


	virtual void SetVisibility(bool value) override;


	virtual void SetVisibilityOn(void) override;


	virtual int GetNumberOfActors() override;


	virtual void Reset() override;


	virtual void SetPosition(double position[3]) override;


	virtual void SetPosition(double x, double y, double z) override;


	virtual double* GetPosition() const override;


	virtual void GetPosition(double position[3]) override;


	virtual void SetUserTransform(vtkTransform *transform) override;


	virtual vtkProp* GetActor(int index) override;


	virtual bool CalculatedBoundingBox() override;


	virtual itk::BoundingBox<double, 3, double>::Pointer GetBoundingBox() override;


	virtual bool GetBoundingBox(double *boundingBox) override;


	virtual ActorsListType GetActors() const override;


	virtual void UpdateInternalTransforms(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> transforms, 
		misUID referenceImage) override;
private:

	void ClipByPlane( misCroppingDirectionInVR direction );
	std::shared_ptr<IRepresentation> m_Representation;
	vtkSmartPointer<misVoreenCanvasMapper>		m_VoreenMapper;
	vtkSmartPointer<misVoreenActor>	m_VoreenActor;
	vtkRenderer* m_Renderer;
	std::vector<voreen::VolumeHandle*>  m_Volumehandles;
	std::vector<TransFuncIntensity*>  m_TransferFunctions;
 	tgt::ivec3	m_WindowSize;
	std::map<misOpenglTexture* , voreen::VolumeHandle*>			m_VolumeHandleMap;
	std::map<misOpenglTexture* , ImageContainedTransferFuncs3D> m_TextureMap;
 	int m_numOfVolume;
	double m_ToolPosition[3];
	misCroppingDirectionInVR m_CroppingDir;
	misRepresentationContainer::Pointer m_DummyObject = misRepresentationContainer::New();
};

