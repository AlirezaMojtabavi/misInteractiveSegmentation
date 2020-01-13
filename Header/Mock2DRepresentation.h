#pragma once
 
#include "I2DRepresentation.h"

MOCK_BASE_CLASS(Mock2DRepresentation, I2DRepresetation)
{
	MOCK_NON_CONST_METHOD(SetWindowLevel, 1, void (misWindowLevelStr ) );
	MOCK_NON_CONST_METHOD(SetVisibilityOfMainTexture, 2,  void (misPlaneEnum,bool ) );
	MOCK_CONST_METHOD(GetVisibilityOfMainTexture, 1, bool (misPlaneEnum ) );
	MOCK_NON_CONST_METHOD(SetDefautltVisibiltyPlanesMap, 1, void(std::shared_ptr<IVisibiltyHolder>));
	MOCK_NON_CONST_METHOD(ApplyDefaultVisibilityMap, 1, void(const std::map<misPlaneEnum, bool>&));
	MOCK_NON_CONST_METHOD(GetImageUID, 1, misUID (misPlaneEnum ) );
	MOCK_NON_CONST_METHOD(ApplyTransformToScene, 3,void (misPlaneEnum , misPlaneEnum , vtkSmartPointer<vtkTransform> ) );
	MOCK_NON_CONST_METHOD(GetImage ,0, std::shared_ptr<IImage> (), GetImage_1);
	MOCK_NON_CONST_METHOD(GetImage, 1, std::shared_ptr<IImage> (misPlaneEnum ), GetImage_2);
	MOCK_NON_CONST_METHOD(RemovePlane, 1, void (int ) );
	MOCK_NON_CONST_METHOD(SetImageSource, 3, void (std::shared_ptr<IImage> , misPlaneEnum , misLayerEnum ) );
	MOCK_NON_CONST_METHOD(SetTextureID, 3, void (misPlaneEnum , misLayerEnum , int ) );
	MOCK_NON_CONST_METHOD(SetMinOpacityForSettingWinLev, 1, void (double threshold) );
	MOCK_NON_CONST_METHOD(SetTexture, 1, void (misOpenglTexture* pTexture) , SetTexture_1);
	MOCK_NON_CONST_METHOD(SetTexture, 2,void (misOpenglTexture* , misPlaneEnum ) ,  SetTexture_2);
	MOCK_NON_CONST_METHOD(SetTexture, 2, void (misLayerEnum , misOpenglTexture* ), SetTexture_3);
	MOCK_NON_CONST_METHOD(SetTexture, 3, void (misPlaneEnum , misLayerEnum , misOpenglTexture* ), SetTexture_4);
	MOCK_NON_CONST_METHOD(SetTexture, 4, void SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture, misTexturePropertyStruct externalSetPlane) );
	MOCK_NON_CONST_METHOD(GetViewingProprties, 0, misWindowLevelStr () , GetViewingProprties_1);
	MOCK_NON_CONST_METHOD(GetViewingProprties, 1, misWindowLevelStr (misPlaneEnum ) , GetViewingProprties_2);
	MOCK_NON_CONST_METHOD(GetOrientation, 0, IMAGEORIENTATION  () );
	MOCK_NON_CONST_METHOD(SetVisiblityOfColorMap, 2 ,void (misPlaneEnum , bool val) );
	MOCK_NON_CONST_METHOD(SetColorMapTransFuncID, 2, void (misPlaneEnum , std::shared_ptr<TransFuncIntensity> val) );
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 1, void (misDoubleColorStruct ) , SetColorValueToTexture_1);
	MOCK_NON_CONST_METHOD(SetColorValueToTexture, 2, void (misPlaneEnum , misDoubleColorStruct ) , SetColorValueToTexture_2);
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 1,void (float opacityValue), SetOpacityValueToTexture_1);
	MOCK_NON_CONST_METHOD(SetOpacityValueToTexture, 2, void (misPlaneEnum , float ) , SetOpacityValueToTexture_2);
	MOCK_NON_CONST_METHOD(SetPolyDataTransferFunction, 2, void (int , ImageContainedTransferFuncs ) );
	MOCK_NON_CONST_METHOD(SetVisibilityOfSegmentedImage, 2, void (misPlaneEnum , bool ) );
	MOCK_NON_CONST_METHOD(SetVisibilityOfFmriImage, 2, void (misPlaneEnum , bool ) );
	MOCK_NON_CONST_METHOD(SetApplyColor, 1, void (int val), SetApplyColor_1);
	MOCK_NON_CONST_METHOD(SetApplyColor, 2, void (misPlaneEnum , int ), SetApplyColor_2);
	MOCK_NON_CONST_METHOD(RemoveColorMap, 1, void (misPlaneEnum ) );
	MOCK_NON_CONST_METHOD(UpdateRepTransformMatrix, 2, bool (misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix) );
	MOCK_NON_CONST_METHOD(SetTransferFunction , 1, void(std::shared_ptr<TransFuncIntensity> tf), SetTransferFunction_1);
	MOCK_NON_CONST_METHOD(SetTransferFunction, 2, void (misPlaneEnum , std::shared_ptr<TransFuncIntensity> ) , SetTransferFunction_2);
	MOCK_NON_CONST_METHOD(SetFmriTransferFunctionID, 1, void (int ), SetFmriTransferFunctionID_1);
	MOCK_NON_CONST_METHOD(SetFmriTransferFunctionID, 2, void (misPlaneEnum , int ), SetFmriTransferFunctionID_2);
	MOCK_NON_CONST_METHOD(Reset, 0, void () );
	MOCK_NON_CONST_METHOD(RemoveLayer, 2, void (misPlaneEnum , misLayerEnum ) );
	MOCK_NON_CONST_METHOD(InitilizeLayers, 0, void () );
	MOCK_NON_CONST_METHOD(SetIsAlphaSetForBlending, 1, void (int ), SetIsAlphaSetForBlending_1);
	MOCK_NON_CONST_METHOD(SetIsAlphaSetForBlending, 2, void (misPlaneEnum planeIndex, int val) , SetIsAlphaSetForBlending_2);
	MOCK_NON_CONST_METHOD(SetErasedObjDisplayStatus, 1, void (bool ) );
	MOCK_NON_CONST_METHOD(GetPlaneWithMaximumVisibility, 0, misPlaneEnum () );
	MOCK_NON_CONST_METHOD(SetErasedObjectColor, 1, void (misColorStruct ) );
	MOCK_NON_CONST_METHOD(SetWindowLevelTransferFunction, 1, void (misPlaneEnum	planeIndex) , SetWindowLevelTransferFunction_1);
	MOCK_NON_CONST_METHOD(SetWindowLevelTransferFunction, 0, void () , SetWindowLevelTransferFunction_2);
	MOCK_NON_CONST_METHOD(GetOpacityValueOfTexture, 1, float (misPlaneEnum ) );

};