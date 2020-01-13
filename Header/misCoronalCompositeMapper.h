#pragma once
#include "misCompositeImageMapper.h"
#include "vtkmapper.h"

class misCoronalCompositeMapper : public misCompositeImageMapper
{
private:
	void			CreateGLSLObjects(vtkRenderer *ren);
	void			makeTexture();
	void			vertex(float x, float y, float z);
	void			drawQuads(float x, float y, float z);
	GLuint			m_program , m_FragmentShader, m_VertexShader;
	bool			LoadExtensionsSucceeded;


public:
	misCoronalCompositeMapper(void);
	~misCoronalCompositeMapper(void);

	static	misCoronalCompositeMapper*  New()
	{
		return  new misCoronalCompositeMapper;
	}
	virtual double*	GetBounds();
	virtual void	Render(vtkRenderer *ren, vtkActor *a);
	void			SetShaderVariables();
	void			LoadExtensions(vtkRenderWindow *window);
	GLuint			m_IND,m_textureId[2];

};

