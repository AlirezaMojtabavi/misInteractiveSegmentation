#pragma once
#include "vtkMapper.h"
#include "vtkOpenGLExtensionManager.h"
#include "vtkTransform.h"
#include "misStrctColorData.h"
#include "misOpenglTexture.h"
#include "shadermanager.h"
#include "misTextureStrcts.h"
#include "misImageGeoProperties.h"
#include "vector.h"
#include "textureunit.h"
#include "misTextureViewingProperties.h"

class misQuadMapper: public vtkMapper
{
private:
	vector<std::string> m_planeNames;
	std::vector<tgt::TextureUnit>  m_MainImageTextureUnit;
	std::vector<tgt::TextureUnit>  m_SegmentedImageTextureUnit;
	std::vector<tgt::TextureUnit>  m_SegmentedImageTransFuncTextureUnit;
	std::vector<tgt::TextureUnit>  m_ColorMapTransFuncTextureUnit;
	std::vector<tgt::TextureUnit>  m_WindowLevelTransFuncTextureUnit;


	struct  Point{
		float x;
		float y;
		float z;
	};
	Point m_Grid[3][3][3];
	struct PlaneCoordionatePropertiesStrct
	{
		tgt::mat4			Transform;
		tgt::vec4     TransformedPoints[4];
	};
	vector<PlaneCoordionatePropertiesStrct>	m_GroupCoordinateProperties;
	vector<misTextureViewingProperties> m_GroupTextureViewingProperties;

	tgt::vec4		m_InitialPoints[4];
	tgt::vec3		m_Spacing;
	tgt::Shader*	m_program;
	GLuint			m_maskTextureID;

	float	m_NormalizedSlice;
	float	m_P1[3];
	float	m_P2[3];
	float	m_P3[3];
	float	m_P4[3];
	float	m_Coordinate1[3];
	float	m_Coordinate2[3];
	float	m_Coordinate3[3];
	float	m_Coordinate4[3];
	float	m_shiftInDirectionValue;
	double  m_WidthInDirection;
	double  m_Bounds[6];
	int		m_useMaskFlag;
	int		m_Extend[6];
	IMAGEORIENTATION m_Orientation;

	void	CreateGLSLObjects();
	void	InitializeCoorinatePoints();
	void	InitialTextureColorValue(int groupIndex);
	void	UpdateCoordinatePoints(int groupIndex);
	void	SetExtend(int* val) ;
	void	SetSpacing(tgt::vec3 val);
	void	SetWidthInDirection(double val) { m_WidthInDirection = val; }
	virtual void UpdateSliderInMapper(float slide , int groupIndex) = 0;
	void	AddDeformitytoGrid();
	void	SetInitialSetting();
public:

	virtual void SetShaderVariables(vtkRenderer *ren, vtkActor *a);
	void		 SetTestShaderParameters();
	virtual void SetWindowLevel(misWindowLevelStr normalizedWinLevStr, int groupIndex );
	virtual void GeneratePlaneMesh(misTexturePropertyStruct prop)=0;
	void SetMatrixTransform( tgt::mat4 transformMatrix,int groupIndex);
	void	TransformInPlace(vtkTransform*  pTrans);
	void		InitializeGrid();
	double	GetWidthInDirection() const { return m_WidthInDirection; }

	void	SetIsContrastShaderUsed(bool val) {m_UseContrastShader = val;}
	bool	GetIsContrastShaderUsed() {return m_UseContrastShader;}

	void	UseAlphaForBlending(bool val, int groupIndex) {this->m_GroupTextureViewingProperties[groupIndex].UseAlphaForMainBlending = val;}
	bool	GetUseAlphaForBlending(int groupIndex) {return this->m_GroupTextureViewingProperties[groupIndex].UseAlphaForMainBlending;}

	void	SetUseColorForTexture(bool val, int groupIndex) {this->m_GroupTextureViewingProperties[groupIndex].UseColorForMT = val;}
	bool	GetUseColorForTexture(int groupIndex) {return this->m_GroupTextureViewingProperties[groupIndex].UseColorForMT;}

	float	GetNormalizedSlice() const;
	void	SetNormalizedSlice(float val ,int groupIndex);

	PointType* GetPlaneCoord();

	double*	GetDimention();
	tgt::vec3     GetCenter()    ;       
	vtkOpenGLExtensionManager* m_pManger;

	bool m_UseContrastShader;

	void		SetColorValueToTexture(misDoubleColorStruct colorVal, int groupIndex);
	void		SetOpacityValueToTexture(float opacityValue,int groupIndex);
	float		GetOpacityValueOfTexture(int groupIndex){return this->m_GroupTextureViewingProperties[groupIndex].OpacityOfMT;};
	void		ChangeOpacities();
	void		SetMaskTextureID(GLuint MaskTexID);
	void		SetTransform(vtkTransform* transformMatrix);
	void		SetUseMaskFlag(int UseMaskFlag);
	void		SetShiftInDirectionValue(float ShiftValue);
	void		SetVisibilityOfSegmentedImage(int groupIndex , bool val);
	void		SetVisibilityOfMainTexture(int groupIndex , bool val);
	void		SetVisiblityOfColorMap(int groupIndex , bool val);
	void		SetColorMapTransFuncID(int groupIndex , int val);
	void		SetSegmentedImageTransFuncID( int val,int groupIndex );
	void		SetMainImageTextureID( int val,int groupIndex );
	void		SetWindowLevelTransferFunctionTextureID( int val,int groupIndex);
	void		SetSegmentedImageTextureID( int val , int groupIndex);
	void		AddTextureGroup(int index);
	void		RemoveTextureGroup( int index );
	std::string ConvertPlaneIndexToString( int id );
	void		BindTexture(GLenum type , GLint texUnit , GLint id);
	void		RemoveColorMapTexture(int groupIndex);
	void		RemoveSegmentedImageTexture( int groupIndex );
	void		RemoveSegmentedImageTransFuncTexture( int groupIndex );

public:
	misQuadMapper(IMAGEORIENTATION );
	~misQuadMapper(void);
};

