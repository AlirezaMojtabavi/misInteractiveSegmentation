#pragma once

#include "IImageSlicerMapper.h"

MOCK_BASE_CLASS(MockImageSlicerMapper, IImageSlicerMapper)
{
	MOCK_NON_CONST_METHOD(SetWindowLevelTransferFunctionTextureID, 2, void(misPlaneEnum planeIndex, GLuint wlTexId), Idenyifier_1);
	MOCK_NON_CONST_METHOD(SetUsingTransferFunctionForMainImage, 2, void(bool usingColored, int groupIndex));
	MOCK_NON_CONST_METHOD(SetVisiblityOfColorMap, 2, void(int groupIndex, bool val));
	MOCK_NON_CONST_METHOD(SetColorMapTransFuncID, 2, void(int groupIndex, std::shared_ptr<TransFuncIntensity> val));
	MOCK_CONST_METHOD(GetVisibilityOfMainTexture, 1, bool(int groupIndex));
	MOCK_NON_CONST_METHOD(SetVisibilityOfMainTexture, 2, void(int groupIndex, bool val));
	MOCK_NON_CONST_METHOD(SetVisibilityOfFmriImage, 2, void(int groupIndex, bool val));
	MOCK_NON_CONST_METHOD(SetVisibilityOfSegmentedImage, 2, void(int groupIndex, bool val));
	MOCK_NON_CONST_METHOD(SetWindowLevelTransferFunctionTextureID, 2, void(int layerIndex, int textureId), Idenyifier_2);
	MOCK_NON_CONST_METHOD(SetSegmentedImageTransFunc, 2, void(std::shared_ptr<TransFuncIntensity> tf, int groupIndex));
	MOCK_NON_CONST_METHOD(SetFmriImageTransFuncID, 2, void(int val, int groupIndex));
	MOCK_NON_CONST_METHOD(SetMainImageTextureID, 2, void(int val, int groupIndex));
	MOCK_NON_CONST_METHOD(SetSegmentedImageTextureID, 2, void(int val, int groupIndex));
	MOCK_NON_CONST_METHOD(SetFmriImageTextureID, 2, void(int val, int groupIndex));
	MOCK_NON_CONST_METHOD(SetOrientation, 1, void(IMAGEORIENTATION newOrientatio));
	MOCK_NON_CONST_METHOD(SetImageContainedTF, 2, void(ImageContainedTransferFuncs, int groupIndex));
	MOCK_NON_CONST_METHOD(ClearFmriTransferFunctionIDs, 1, void(int groupIndex));
	MOCK_NON_CONST_METHOD(SetUseColorForTexture, 2, void(bool val, int groupIndex));
	MOCK_NON_CONST_METHOD(GetUseColorForTexture, 1, bool(int groupIndex));
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void(misDoubleColorStruct colorVal, int groupIndex));
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void(float opacityValue, int groupIndex));
	MOCK_NON_CONST_METHOD(GetOpacityValueOfTexture, 1, float(int groupIndex));
	MOCK_NON_CONST_METHOD(ChangeOpacities, 1, void(int groupIndex));
	MOCK_NON_CONST_METHOD(SetMaskTextureID, 1, void(GLuint MaskTexID));
	MOCK_NON_CONST_METHOD(SetUseMaskFlag, 1, void(int UseMaskFlag));
	MOCK_NON_CONST_METHOD(AddTextureGroup, 1, void(int index));
	MOCK_NON_CONST_METHOD(RemoveTextureGroup, 1, void(int index));
	MOCK_NON_CONST_METHOD(SetMatrixTransform, 2, void(tgt::mat4 transformMatrix, int groupIndex));
	MOCK_NON_CONST_METHOD(InitializeGrid, 0, void());
	MOCK_NON_CONST_METHOD(SetIsContrastShaderUsed, 1, void(bool val));
	MOCK_NON_CONST_METHOD(GetIsContrastShaderUsed, 0, bool());
	MOCK_NON_CONST_METHOD(UseAlphaForBlending, 2, void(bool val, int groupIndex));
	MOCK_NON_CONST_METHOD(GetUseAlphaForBlending, 1, bool(int groupIndex));
	MOCK_NON_CONST_METHOD(GetMapper, 0, vtkMapper*());
	MOCK_NON_CONST_METHOD(SetCornerProperties, 1, void(std::shared_ptr<ICornerProperties> pCornerProp));
	MOCK_NON_CONST_METHOD(GeneratePlaneMesh, 1, void(misTexturePropertyStruct));
};

