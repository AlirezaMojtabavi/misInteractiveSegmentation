#pragma once
#include "vtkmapper.h"
#include "vtkgl.h"
#include "vtkOpenGLExtensionManager.h"
#include "vtkTransform.h"
//#include "misStrctColorData.h"
#include "misOpenglTexture.h"
#include "shadermanager.h"
#include "vtkRenderer.h"
#include "vtkActor.h"
#include "misitkTypdef.h"
#include "textureunit.h"
#include "misStrctColorData.h"

class misTestMapper :	public vtkMapper
{
protected:

	vtkTransform*		m_transform;
	misItkPointType     m_InitialPoints[4];
	misItkPointType     m_TransformedPoints[4];

	std::vector<tgt::TextureUnit>  MainImageTextureUnit;
	std::vector<tgt::TextureUnit>  SegmentedImageTextureUnit;
	std::vector<tgt::TextureUnit>  SegmentedImageTransFuncTextureUnit;
	std::vector<tgt::TextureUnit>  ColorMapTransFuncTextureUnit;
	std::vector<tgt::TextureUnit>  WindowLevelTransFuncTextureUnit;
	float	m_NormalizedSlice;
	float	m_P1[3];
	float	m_P2[3];
	float	m_P3[3];
	float	m_P4[3];
	float	m_Coordinate1[3];
	float	m_Coordinate2[3];
	float	m_Coordinate3[3];
	float	m_Coordinate4[3];
	double  m_WidthInDirection;
	double  m_Spacing[3];
	double  m_Bounds[6];
	int		m_useMaskFlag[5];
	int		m_Extend[6];
	void CreateGLSLObjects();


	tgt::Shader*  m_program;
	float	m_CurrentWindowCenter[5];
	float	m_CurrentWindowWidth[5];
	bool	m_VisiblityOfMT[5];
	bool	m_VisiblityOfColorMap[4];
	bool	m_UseAlphaForBlending[5];
	bool	m_UseColorForTexture[5];
	bool	m_IsPolydata[5];
	misDoubleColorStruct m_TextureColorValue[5];

	float		m_OpacityOfTexture[5];
	float		m_OpacityOfZeroInTexure[5];
	
	GLuint		m_ColorMapID[4];
	GLuint		m_MainImageID[5];
	GLuint		m_SegmentedImageID[5];
	GLuint		m_TransferFunc_ID[5];
	GLuint		m_maskTextureID[5];
	GLuint		m_WindowLevelTransferFuncID[5];

	float m_shiftInDirectionValue;

//	void			InitialTextureColorValue();
	
public:
	static misTestMapper *New()
	{
		return new misTestMapper;
	};
	void	TransformInPlace(vtkTransform*  pTrans);
	void	SetExtend(int* val) ;
	void	SetSpacing(double* val);

	virtual void SetShaderVariables(vtkRenderer *ren, vtkActor *a)  ;

	double GetWidthInDirection() const { return m_WidthInDirection; }
	void   SetWidthInDirection(double val) { m_WidthInDirection = val; }

	void SetIsContrastShaderUsed(bool val) {m_UseContrastShader = val;}
	std::string ConvertPlaneIndexToString(int id);
	bool GetIsContrastShaderUsed() {return m_UseContrastShader;}

	void UseAlphaForBlending(bool val,int id) {m_UseAlphaForBlending[id] = val;}
	bool GetUseAlphaForBlending(int id) {return m_UseAlphaForBlending[id];}

	void SetVisiblityOfMT(bool val,int id) {m_VisiblityOfMT[id] = val;}
	bool GetVisiblityOfMT(int id) {return m_VisiblityOfMT[id];}

	void SetUseColorForTexture(bool val,int id) {m_UseColorForTexture[id] = val;}
	bool GetUseColorForTexture(int id) {return m_UseColorForTexture[id];}

	void SetWindowLevel(int id , double windowCenter, double windowWidth); 
	misTestMapper(void);
	~misTestMapper(void);	
	
	float	GetNormalizedSlice() const;
	void	SetNormalizedSlice(float val);
	bool m_UseContrastShader;

	void SetColorValueToTexture(misDoubleColorStruct colorVal, int id);
	void SetOpacityValueToTexture(float opacityValue,int id);
	float GetOpacityValueOfTexture(int id){return this->m_OpacityOfTexture[id];};
	void Render(vtkRenderer *ren, vtkActor *a)  ;
	void SetMaskTextureID(GLuint MaskTexID,int id);
	void SetVisiblityOfColorMap(bool val,int id) {m_VisiblityOfColorMap[id] = val;}
	bool GetVisiblityOfColorMap(int id) {return m_VisiblityOfColorMap[id];}
	void BindTexture(GLenum type , GLint texUnit , GLint id)	;
	void SetUseMaskFlag(int UseMaskFlag, int id);
	void SetShiftInDirectionValue(float ShiftValue);
	void SetOpacityValueOfZero(float OpacityOfZeroValues,int id);
	void SetPolydataOn(int id);
	void SetTransferFunctionID( int val , int planeId );
	void SetMainImageTextureID( int val , int planeId );
	void SetSegmentedImageTextureID( int val , int planeId  );
	void SetColorMapTFID( int val, int index);
	void vertex(float x, float y, float z);
	void drawQuads(float x, float y, float z);
	void SetWindowLevelTransferFunctionTextureID( int val, int id);
};
