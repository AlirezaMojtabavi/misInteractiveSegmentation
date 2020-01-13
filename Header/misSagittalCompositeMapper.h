#pragma once
#include "misCompositeImageMapper.h"
#include "vtkmapper.h"
#include "vtkRenderWindow.h"

class misSagittalCompositeMapper : 	public misCompositeImageMapper
{
private:

	void			CreateGLSLObjects(vtkRenderer *ren);
	void			makeTexture();
	void			vertex(float x, float y, float z);
	void			drawQuads(float x, float y, float z);
	GLuint			m_program , m_FragmentShader, m_VertexShader;
	bool			LoadExtensionsSucceeded;

public:
	misSagittalCompositeMapper(void);
	~misSagittalCompositeMapper(void);

	static	misSagittalCompositeMapper*  New()
	{
		return  new misSagittalCompositeMapper;
	}
	virtual double*	GetBounds();
	virtual void	Render(vtkRenderer *ren, vtkActor *a);
	void			SetShaderVariables();
	void			LoadExtensions(vtkRenderWindow *window);
	GLuint			m_IND,m_textureId[2];

};



