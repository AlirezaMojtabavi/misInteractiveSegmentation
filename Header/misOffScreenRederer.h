#pragma once

#include "misObject.h"
#include "misWindow.h"

class misOffScreenRederer :
	public misOldObject
{
private:
	GLuint framebuffer, texture_buffer, renderbuffer;
	vtkRenderWindow* m_Window;
	int m_WindowSize[2];
public:
	typedef misOffScreenRederer                         Self;
	typedef misOldObject                    Superclass;
	typedef ::itk::SmartPointer< Self >       Pointer;
	typedef ::itk::SmartPointer< const Self > ConstPointer;

	static Pointer New(void);
	misOffScreenRederer(void);
	~misOffScreenRederer(void);
	void SetWindow(vtkRenderWindow* window);
	void generateFrameBuffer();
	void enable_renderbuffers();
	void disable_renderbuffers();
	void LoadExtensions( );
};
