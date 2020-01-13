#pragma once
#include "IRepresentation.h"

struct SegmentedObjectTransferFunction3D;
typedef std::vector<SegmentedObjectTransferFunction3D> ImageContainedTransferFuncs3D;
template < typename CST >
class ICoordinateSystemCorrelationManager;

enum misCroppingDirectionInVR;

typedef std::string misUID;

class IvolumeRepresentation :public virtual IRepresentation
{
public:
	virtual void SetToolPosition(double xCoord, double yCoord, double zCoord) = 0;
	virtual void SetToolAngle(float toolAngle) {}
	virtual void SetCroppingDirection(misCroppingDirectionInVR direction) = 0;
	virtual void SetWindowSize(tgt::ivec3 size) = 0;
	virtual void SetVolume(int id, misOpenglTexture*  pTexture) = 0;
	virtual void SetVolume(misOpenglTexture* pTexture, ImageContainedTransferFuncs3D pTextureTFs) = 0;
	virtual void SetTranformMatrixToVolumes(int, tgt::mat4) = 0;
	virtual void SetTranformMatrixToVolumes(std::string name, tgt::mat4) = 0;
	virtual void UpdateInternalTransforms(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> transforms,
		misUID referenceImage) = 0;
	virtual void ClipingOn() = 0;
	virtual void ClipingOF() = 0;
	virtual void SetClipingPlane(tgt::vec4 plane) = 0;
	virtual void  SetSampleRate(float fps) = 0;
	virtual void  ClearTextureHnadleMapBeforSetVolume() = 0;
	virtual void  ResetMapInShader() = 0;
	virtual void  SetROI(const double* fov) = 0;
	virtual void  RemoveFOV() = 0;
	virtual void  ModifyVolume() = 0;
	virtual void  CompileVolumeShader() = 0;
	virtual void  RnderProxyGeometry(bool val) = 0;//Only for test
	virtual void SetRenderer(vtkRenderer* val) = 0;
 };
