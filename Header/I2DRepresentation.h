# pragma once

#include "misPlaneContrast.h"
#include "misWindowLevelStr.h"
#include "IVisibiltyHolder.h"
#include "misTypes.h"
#include "IImage.h"
#include "misOpenglTexture.h"
#include "VisualizationGeneralTypes.h"
#include "TransFuncIntensity.h"
#include "misStrctColorData.h"

// This class is an interface for 2D representation such as panoramic representation and standard representations
// Date : May 2014
// Author : Mohsen Rahimimoghaddam

// enumerate different layers can be exist in standard views. If a view has only one layer that would be MainImage 
// (e.g. PanoramicView)
enum misLayerEnum
{
	MainImage = 0,
	SegmentedImage,
	FmriImage,
	UnSetLayer
};

class misSegmentedObjectTransferFunction;
typedef std::vector<misSegmentedObjectTransferFunction> ImageContainedTransferFuncs;


class I2DRepresetation
{
public :
	// Set window level for the view of an Image. Window level affect on contrast of the displayed image on a view
	virtual void SetWindowLevel(misWindowLevelStr winlevStr) = 0;
	virtual void SetVisibilityOfMainTexture(misPlaneEnum planeIndex, bool val) = 0;
	virtual bool GetVisibilityOfMainTexture(misPlaneEnum planeIndex) const = 0;
	virtual void SetDefautltVisibiltyPlanesMap(std::shared_ptr<IVisibiltyHolder>)  = 0;
	virtual void ApplyDefaultVisibilityMap(const std::map<misPlaneEnum, bool>& imageVisibiltes) = 0;
	virtual misUID GetImageUID(misPlaneEnum planeIndex) = 0;
	virtual void ApplyTransformToScene(misPlaneEnum sourcePlane, misPlaneEnum targetPlane, vtkSmartPointer<vtkTransform> transform) = 0;
	virtual std::shared_ptr<IImage> GetImage() = 0;
	virtual std::shared_ptr<IImage> GetImage(misPlaneEnum planeIndex) = 0;
	virtual void RemovePlane(int planeindex) = 0;
	virtual void SetImageSource(std::shared_ptr<IImage> pImage, misPlaneEnum planeIndex, misLayerEnum layerIndex) = 0;
	virtual void SetTextureID(misPlaneEnum planeIndex, misLayerEnum layerIndex, int val) = 0;
	virtual void SetMinOpacityForSettingWinLev(double threshold) = 0;
	virtual void SetTexture(misOpenglTexture* pTexture) = 0;
	virtual void SetTexture(misOpenglTexture* pTexture, misPlaneEnum planeIndex) = 0;
	virtual void SetTexture(misLayerEnum layerIndex, misOpenglTexture* pTexture) = 0;
	virtual void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture) = 0;
	virtual void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture, misTexturePropertyStruct externalSetPlane)= 0;
	virtual misWindowLevelStr GetViewingProprties() = 0;
	virtual misWindowLevelStr GetViewingProprties(misPlaneEnum planeIndex)= 0;
	virtual IMAGEORIENTATION  GetOrientation() = 0;
	virtual void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) = 0;
	virtual void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) = 0;
	virtual void SetColorValueToTexture(misDoubleColorStruct colorVal) = 0;
	virtual void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) = 0;
	virtual void SetOpacityValueToTexture(float opacityValue) = 0;
	virtual void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)= 0;
	virtual void SetPolyDataTransferFunction(int planeIndex, ImageContainedTransferFuncs ImgCntTF) = 0;
	virtual void SetVisibilityOfSegmentedImage(misPlaneEnum planeIndex, bool val) = 0;
	virtual void SetVisibilityOfFmriImage(misPlaneEnum planeIndex, bool val)= 0;
	virtual void SetApplyColor(int val)= 0;
	virtual void SetApplyColor(misPlaneEnum planeIndex, int val)= 0;
	virtual void RemoveColorMap(misPlaneEnum planeIndex) = 0;
	virtual bool UpdateRepTransformMatrix(misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix) = 0;
	virtual void SetTransferFunction(std::shared_ptr<TransFuncIntensity> tf) = 0;
	virtual void SetTransferFunction(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf) = 0;
	virtual void SetFmriTransferFunctionID(int val) = 0;
	virtual void SetFmriTransferFunctionID(misPlaneEnum planeIndex, int val) = 0;
	virtual void Reset() = 0;
	virtual void RemoveLayer(misPlaneEnum planeIndex, misLayerEnum layerIndex) = 0;
	virtual void InitilizeLayers() = 0;
	virtual void SetIsAlphaSetForBlending(int val) = 0;
	virtual void SetIsAlphaSetForBlending(misPlaneEnum planeIndex, int val) = 0;
	virtual void SetErasedObjDisplayStatus(bool showErased)=0;
	virtual misPlaneEnum GetPlaneWithMaximumVisibility()= 0;
	virtual void SetErasedObjectColor(misColorStruct ColorStr)= 0;
	virtual void SetWindowLevelTransferFunction(misPlaneEnum	planeIndex)= 0;
	virtual void SetWindowLevelTransferFunction()= 0;
	virtual float GetOpacityValueOfTexture(misPlaneEnum planeIndex) = 0;

	virtual ~I2DRepresetation() = default;
};