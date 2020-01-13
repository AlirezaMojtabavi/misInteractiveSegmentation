#pragma once
#include "misCompositeImageMapper.h"
#include "vtkmapper.h"
#include "texfile.h"

class misAxialCompositeMapper :	public misCompositeImageMapper
{

private:
	void			CreateGLSLObjects(vtkRenderer *ren);
	void			makeTexture();
	void			makeVolumeTexture();
	void			vertex(float x, float y, float z);
	void			drawQuads(float x, float y, float z);
	GLuint			m_program , m_FragmentShader, m_VertexShader;
	bool			LoadExtensionsSucceeded;


public:
	misAxialCompositeMapper(void);
	~misAxialCompositeMapper(void);

	static	misAxialCompositeMapper*  New()
	{
		return  new misAxialCompositeMapper;
	}
	virtual double*	GetBounds();
	virtual void	Render(vtkRenderer *ren, vtkActor *a);
	void			SetShaderVariables();
	void			LoadExtensions(vtkRenderWindow *window);
	GLuint			m_IND,m_textureId[2];

	
	
};

