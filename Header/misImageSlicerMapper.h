#pragma once

#include "misImageGeoProperties.h"
#include "misOpenglTexture.h"
#include "misPolyDatasSpecifications.h"
#include "misQuadMapperBase.h"
#include "misSegmentedObjectTransferFunction.h"
#include "misShaderHeaderGeneratorforImageViewer.h"
#include "misSimplePointType.h"
#include "misStrctColorData.h"
#include "misTexturePropertyStruct.h"
#include "misTextureViewingProperties.h"
#include "misPlaneContrast.h"
#include "IImageSlicerMapper.h"
#include "IRepresentation.h"


class vtkTimerLog;

//The most important point: shader just works by units and only knows the units. it doesn't matter what is textureID. In shader, 
// we can assign more than one textureID to a unique Unit.As we found, the priority of Texture_3D is higher than priority of 
// Texture_2D, and priority of Texture_1D is the lowest. So, if  we assign a Texture_3D and a Texture_1D or Texture_2D to one unit 
// at the same time, only Texture_3D is showed, and other textures are ignored.And if we assign several Texture to one unit, the 
// last one is showed and the others are ignored.

typedef std::vector<misSegmentedObjectTransferFunction> ImageContainedTransferFuncs;
class misImageSlicerMapper :	public misQuadMapperBase, public IImageSlicerMapper
{
public:

	void SetShaderVariables(vtkRenderer *ren, vtkActor *a) override;
	virtual void BuildPlane();
	void	SetWindowLevel(misWindowLevelStr normalizedWinLevStr, int groupIndex );

	// If the texture is color there is no need to use transfer function otherwise use transfer function
	void SetUsingTransferFunctionForMainImage(bool usingColored, int groupIndex ) override;

	void	SetMatrixTransform( tgt::mat4 transformMatrix,int groupIndex)override;
	void	InitializeGrid()override;
	void	SetIsContrastShaderUsed(bool val)override;
	bool GetIsContrastShaderUsed()override;
	void UseAlphaForBlending(bool val, int groupIndex)override;
	bool GetUseAlphaForBlending(int groupIndex)override;
	void SetUseColorForTexture(bool val, int groupIndex) override;
	bool GetUseColorForTexture(int groupIndex)override;
	double*	GetDimention();

	bool m_UseContrastShader;

	void SetColorValueToTexture(misDoubleColorStruct colorVal, int groupIndex) override;
	void SetOpacityValueToTexture(float opacityValue,int groupIndex) override;
	float GetOpacityValueOfTexture(int groupIndex) override;;
	void ChangeOpacities(int groupIndex) override;
	void SetMaskTextureID(GLuint MaskTexID) override;
	void SetUseMaskFlag(int UseMaskFlag) override;
	void SetShiftInDirectionValue(float ShiftValue);
	void SetVisibilityOfSegmentedImage(int groupIndex , bool val) override;
	void SetVisibilityOfFmriImage(int groupIndex , bool val) override;
	void SetVisibilityOfMainTexture(int groupIndex , bool val) override;
	bool GetVisibilityOfMainTexture(int groupIndex ) const override;
	void SetVisiblityOfColorMap(int groupIndex , bool val) override;
	void SetColorMapTransFuncID(int groupIndex , std::shared_ptr<TransFuncIntensity> val) override;


	void SetMainImageTextureID( int val,int groupIndex ) override;
	void SetSegmentedImageTextureID( int val , int groupIndex) override;
	void SetFmriImageTextureID( int val , int groupIndex)override;
	void SetWindowLevelTransferFunctionTextureID(int layerIndex, int textureId) override;
	void SetSegmentedImageTransFunc(std::shared_ptr<TransFuncIntensity> tf ,int groupIndex ) override ;
	void SetFmriImageTransFuncID( int val , int groupIndex) override;
	void AddTextureGroup(int index)override;
	void RemoveTextureGroup( int index )override;
	std::string ConvertPlaneIndexToString( int id );
	std::string ConvertSegmentedObjectIndexToString(int groupIndex , int objectIndex);


	misImageSlicerMapper(IMAGEORIENTATION imageorientation);
	~misImageSlicerMapper();
	void Render( vtkRenderer *ren, vtkActor *a );
	void SetImageContainedTF(ImageContainedTransferFuncs ImgCntTF , int groupIndex) override;
	void ClearFmriTransferFunctionIDs( int groupIndex ) override;

	void SetOrientation(IMAGEORIENTATION newOrientatio) override;

	
	vtkMapper* GetMapper() override;
	void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp) override;
	void GeneratePlaneMesh(misTexturePropertyStruct prop) override;

protected:

	void SetSkinBoneRenderingUniforms(const misTextureViewingProperties& texureProp,
		tgt::TextureUnit& colorMapTransFuncTextureUnit,// Use reference to prevent from destruct texture units
		std::string planeName);


	std::vector<std::string> m_planeNames;
	Point m_Grid[3][3][3];
	std::vector<ImageContainedTransferFuncs> m_GroupImageContainedTFs;
	std::vector<misTextureViewingProperties> m_GroupTextureViewingProperties;
	tgt::Shader* m_program;
	GLuint	m_maskTextureID;
	float	m_shiftInDirectionValue;
	int		m_useMaskFlag;
 	void	CreateGLSLObjects();
	virtual void	InitializeCoorinatePoints();
	void	InitialTextureColorValue(int groupIndex);
	void	UpdateCoordinatePoints(int groupIndex);
	virtual void	UpdatePlaneAndTexturePoints();
	void	AddDeformitytoGrid();
	virtual void	SetInitialSetting();
 

private:
	vtkTimerLog*  m_pTimer;
	std::shared_ptr<IShaderHeaderGenerator2D> m_ShaderHeaderGenerator;
};
