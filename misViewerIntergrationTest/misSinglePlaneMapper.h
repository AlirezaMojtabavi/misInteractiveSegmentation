#pragma once
#include "vtkmapper.h"
#include "vtkgl.h"
#include "vtkOpenGLExtensionManager.h"
#include "vtkTransform.h"
#include "misStrctColorData.h"
#include "misOpenglTexture.h"
#include "shadermanager.h"
#include "vtkRenderer.h"
#include "vtkActor.h"
#include "misitkTypdef.h"
#include "textureunit.h"

class misSinglePlaneMapper :	public vtkMapper
{
protected:

	vtkTransform*		m_transform;
	misItkPointType     m_InitialPoints[4];
	misItkPointType     m_TransformedPoints[4];
	struct  Point{
		float x;
		float y;
		float z;
	};
	Point m_Grid[3][3][3];
	tgt::TextureUnit  MainImageTextureUnit;

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
	int		m_Extend[6];
	void CreateGLSLObjects();


	tgt::Shader*  m_program;
	float	m_CurrentWindowCenter;
	float	m_CurrentWindowWidth;
	bool	m_VisiblityOfMT;
	bool	m_UseAlphaForBlending;
	bool	m_UseColorForTexture;
	misDoubleColorStruct m_TextureColorValue;
	float		m_OpacityOfTexture;

	GLuint		m_MainImageID;
	float m_shiftInDirectionValue;

public:
	static misSinglePlaneMapper *New()
	{
		return new misSinglePlaneMapper;
	};
	void	TransformInPlace(vtkTransform*  pTrans);
	void	SetExtend(int* val) ;
	void	SetSpacing(double* val);

	virtual void SetShaderVariables(vtkRenderer *ren, vtkActor *a)  ;

	double GetWidthInDirection() const { return m_WidthInDirection; }
	void   SetWidthInDirection(double val) { m_WidthInDirection = val; }

	void SetIsContrastShaderUsed(bool val) {m_UseContrastShader = val;}
	bool GetIsContrastShaderUsed() {return m_UseContrastShader;}

	void UseAlphaForBlending(bool val) {m_UseAlphaForBlending = val;}
	bool GetUseAlphaForBlending() {return m_UseAlphaForBlending;}

	void SetVisiblityOfMT(bool val) {m_VisiblityOfMT = val;}
	bool GetVisiblityOfMT() {return m_VisiblityOfMT;}

	void SetUseColorForTexture(bool val) {m_UseColorForTexture = val;}
	bool GetUseColorForTexture() {return m_UseColorForTexture;}

	void SetWindowLevel(double windowCenter, double windowWidth); 
	misSinglePlaneMapper(void);
	~misSinglePlaneMapper(void);	

	float	GetNormalizedSlice() const {return m_NormalizedSlice;}
	void	SetNormalizedSlice(float val){m_NormalizedSlice= val;}
	bool m_UseContrastShader;

	void SetColorValueToTexture(misDoubleColorStruct colorVal){this->m_TextureColorValue = colorVal;}
	void SetOpacityValueToTexture(float opacityValue){m_OpacityOfTexture = opacityValue;}
	float GetOpacityValueOfTexture(){return this->m_OpacityOfTexture;};
	void Render(vtkRenderer *ren, vtkActor *a)  ;
	void BindTexture(GLenum type , GLint texUnit , GLint id );
	void SetShiftInDirectionValue(float ShiftValue){this->m_shiftInDirectionValue = ShiftValue;}
	void SetMainImageTextureID( int val ){m_MainImageID = val;}
	void vertex(float x, float y, float z);
	void drawQuads(float x, float y, float z);
	void InitializeGrid();
	void SetGridParameters();
	void UpdateGrid(float xtranslation, float ytranslation , float ztranslation);
};
