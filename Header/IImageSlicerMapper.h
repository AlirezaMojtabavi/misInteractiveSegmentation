#pragma once
#include "misShaderHeaderGeneratorforImageViewer.h"

class IImageSlicerMapper
{
public:
	virtual ~IImageSlicerMapper() = default;

	virtual void SetUsingTransferFunctionForMainImage(bool usingColored, int groupIndex) = 0;
	virtual void SetVisiblityOfColorMap(int groupIndex, bool val) = 0;
	virtual void SetColorMapTransFuncID(int groupIndex, std::shared_ptr<TransFuncIntensity> val) = 0;
	virtual bool GetVisibilityOfMainTexture(int groupIndex) const = 0;
	virtual void SetVisibilityOfMainTexture(int groupIndex, bool val) = 0;
	virtual void SetVisibilityOfFmriImage(int groupIndex, bool val) = 0;
	virtual void SetVisibilityOfSegmentedImage(int groupIndex, bool val) = 0;
	virtual void SetWindowLevelTransferFunctionTextureID(int layerIndex, int textureId) = 0;
	virtual void SetSegmentedImageTransFunc(std::shared_ptr<TransFuncIntensity> tf, int groupIndex) = 0;
	virtual void SetFmriImageTransFuncID(int val, int groupIndex) = 0;
	virtual void SetMainImageTextureID(int val, int groupIndex) = 0;
	virtual void SetSegmentedImageTextureID(int val, int groupIndex) = 0;
	virtual void SetFmriImageTextureID(int val, int groupIndex)= 0;
	virtual void SetOrientation(IMAGEORIENTATION newOrientatio) = 0;
	virtual void SetImageContainedTF(ImageContainedTransferFuncs , int groupIndex) = 0;
	virtual void ClearFmriTransferFunctionIDs(int groupIndex) = 0;
	virtual void SetUseColorForTexture(bool val, int groupIndex) = 0;
	virtual bool GetUseColorForTexture(int groupIndex) = 0;
	virtual void SetColorValueToTexture(misDoubleColorStruct colorVal, int groupIndex)  = 0;
	virtual void SetOpacityValueToTexture(float opacityValue, int groupIndex)  = 0;
	virtual float GetOpacityValueOfTexture(int groupIndex)  = 0;;
	virtual void ChangeOpacities(int groupIndex)  = 0;
	virtual void SetMaskTextureID(GLuint MaskTexID)  = 0;
	virtual void SetUseMaskFlag(int UseMaskFlag)  = 0;
	virtual void AddTextureGroup(int index)= 0;
	virtual void RemoveTextureGroup(int index)= 0;
	virtual void	SetMatrixTransform(tgt::mat4 transformMatrix, int groupIndex) = 0;
	virtual void	InitializeGrid() = 0;
	virtual void	SetIsContrastShaderUsed(bool val) = 0;
	virtual bool GetIsContrastShaderUsed() = 0;
	virtual void UseAlphaForBlending(bool val, int groupIndex) = 0;
	virtual bool GetUseAlphaForBlending(int groupIndex) = 0;
	virtual vtkMapper* GetMapper() = 0;
	virtual void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp) = 0;
	virtual void GeneratePlaneMesh(misTexturePropertyStruct prop) = 0;

};
