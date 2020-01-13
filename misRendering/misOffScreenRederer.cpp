#include "StdAfx.h"
#include "misOffScreenRederer.h"

misOffScreenRederer::misOffScreenRederer(void)
{
	texture_buffer=-1;
	renderbuffer=-1;
}


misOffScreenRederer::~misOffScreenRederer(void)
{

	if (texture_buffer>=0)
		glDeleteTextures(1,&texture_buffer);
	if (renderbuffer>=0)
	{
		vtkgl::DeleteRenderbuffersEXT(1,&renderbuffer);
	}

}

void misOffScreenRederer::LoadExtensions(  )
{
	const char *gl_vendor=reinterpret_cast<const char *>(glGetString(GL_VENDOR));
	const char *gl_version=reinterpret_cast<const char *>(glGetString(GL_VERSION));

	// Create an extension manager
	vtkOpenGLExtensionManager *extensions=vtkOpenGLExtensionManager::New();
	extensions->SetRenderWindow(m_Window);

	// GL_ARB_draw_buffers requires OpenGL 1.3, so we must have OpenGL 1.3
	// We don't need to check for some extensions that become part of OpenGL
	// core after 1.3. Among them:
	//   - texture_3d is in core OpenGL since 1.2
	//   - texture_edge_clamp is in core OpenGL since 1.2
	//     (GL_SGIS_texture_edge_clamp or GL_EXT_texture_edge_clamp (nVidia) )
	//   -  multitexture is in core OpenGL since 1.3

	int supports_GL_1_3=extensions->ExtensionSupported("GL_VERSION_1_3");
	int supports_GL_2_0=0;

	// Check for 2.0 support
	supports_GL_2_0=extensions->ExtensionSupported("GL_VERSION_2_0");

	// Some extensions that are supported in 2.0, but if we don't
	// have 2.0 we'll need to check further
	int supports_shading_language_100     = 1;
	int supports_shader_objects           = 1;
	int supports_fragment_shader          = 1;
	int supports_texture_non_power_of_two = 1;
	int supports_draw_buffers             = 1;
	if(!supports_GL_2_0)
	{
		supports_shading_language_100=
			extensions->ExtensionSupported("GL_ARB_shading_language_100");
		supports_shader_objects=
			extensions->ExtensionSupported("GL_ARB_shader_objects");
		supports_fragment_shader=
			extensions->ExtensionSupported("GL_ARB_fragment_shader");
		supports_texture_non_power_of_two=
			extensions->ExtensionSupported("GL_ARB_texture_non_power_of_two");
		supports_draw_buffers=
			extensions->ExtensionSupported("GL_ARB_draw_buffers");
	}

	// We have to check for framebuffer objects
	int supports_GL_EXT_framebuffer_object=
		extensions->ExtensionSupported("GL_EXT_framebuffer_object" );

	// Find out if we have OpenGL 1.4 support
	int supports_GL_1_4=extensions->ExtensionSupported("GL_VERSION_1_4");

	// Find out if we have the depth texture ARB extension
	int supports_GL_ARB_depth_texture=
		extensions->ExtensionSupported("GL_ARB_depth_texture");

	// Depth textures are support if we either have OpenGL 1.4
	// or if the depth texture ARB extension is supported
	int supports_depth_texture =
		supports_GL_1_4 || supports_GL_ARB_depth_texture;

	extensions->LoadExtension("GL_VERSION_1_2");
	extensions->LoadExtension("GL_VERSION_1_3");

	// Load the 2.0 extensions if supported
	if(supports_GL_2_0)
	{
		extensions->LoadExtension("GL_VERSION_2_0");
	}
	// Otherwise, we'll need to specifically load the
	// shader objects, fragment shader, and draw buffers
	// extensions
	else
	{
		extensions->LoadCorePromotedExtension("GL_ARB_shader_objects");
		extensions->LoadCorePromotedExtension("GL_ARB_fragment_shader");
		extensions->LoadCorePromotedExtension("GL_ARB_draw_buffers");
	}

	extensions->LoadExtension("GL_EXT_framebuffer_object");

	// Optional extension (does not fail if not present)
	// Load it if supported which will allow us to store
	// textures as floats

	// Optional extension (does not fail if not present)
	// Used to minimize memory footprint when loading large 3D textures
	// of scalars.
	// VBO or 1.5 is required by PBO or 2.1
	int supports_GL_1_5=extensions->ExtensionSupported("GL_VERSION_1_5");
	int supports_vertex_buffer_object=supports_GL_1_5 ||
		extensions->ExtensionSupported("GL_ARB_vertex_buffer_object");
	int supports_GL_2_1=extensions->ExtensionSupported("GL_VERSION_2_1");


	extensions->Delete();
}

void misOffScreenRederer::generateFrameBuffer()
{
	vtkgl::GenFramebuffersEXT(1, &framebuffer);
	vtkgl::BindFramebufferEXT(vtkgl::FRAMEBUFFER_EXT,framebuffer);

	glGenTextures(1, &texture_buffer);
	glBindTexture(GL_TEXTURE_2D, texture_buffer);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, vtkgl::CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vtkgl::CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0,vtkgl::RGBA16F_ARB, m_WindowSize[0], m_WindowSize[1], 0, GL_RGBA, GL_FLOAT, NULL);
	vtkgl::FramebufferTexture2DEXT(vtkgl::FRAMEBUFFER_EXT, vtkgl::COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture_buffer, 0);

	vtkgl::GenRenderbuffersEXT(1, &renderbuffer);
	vtkgl::BindRenderbufferEXT(vtkgl::RENDERBUFFER_EXT, renderbuffer);
	vtkgl::RenderbufferStorageEXT(vtkgl::RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_WindowSize[0], m_WindowSize[1]);
	vtkgl::FramebufferRenderbufferEXT(vtkgl::FRAMEBUFFER_EXT, vtkgl::DEPTH_ATTACHMENT_EXT, vtkgl::RENDERBUFFER_EXT, renderbuffer);
	vtkgl::BindFramebufferEXT(vtkgl::FRAMEBUFFER_EXT, 0);

	GLenum status = vtkgl::CheckFramebufferStatusEXT( vtkgl::FRAMEBUFFER_EXT );

	switch( status )
	{
	case vtkgl::FRAMEBUFFER_COMPLETE_EXT:
		if (m_Logger)
		m_Logger->Debug("GL_FRAMEBUFFER_COMPLETE_EXT!");
		break;

	case vtkgl::FRAMEBUFFER_UNSUPPORTED_EXT:
				MessageBoxW(NULL,L"GL_FRAMEBUFFER_UNSUPPORTED_EXT!",L"ERROR",MB_OK|MB_ICONEXCLAMATION);

		break;

	default:
		MessageBoxW(NULL,L"GL_FRAMEBUFFER unkown error ",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
}

void misOffScreenRederer::enable_renderbuffers()
{
	vtkgl::BindFramebufferEXT (vtkgl::FRAMEBUFFER_EXT, framebuffer);	
	vtkgl::BindRenderbufferEXT(vtkgl::RENDERBUFFER_EXT, renderbuffer);
	vtkgl::FramebufferTexture2DEXT(vtkgl::FRAMEBUFFER_EXT, vtkgl::COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture_buffer, 0);
}

void misOffScreenRederer::disable_renderbuffers()
{
	vtkgl::BindFramebufferEXT(vtkgl::FRAMEBUFFER_EXT, 0);
	vtkgl::BindRenderbufferEXT(vtkgl::RENDERBUFFER_EXT, 0);
}

misOffScreenRederer::Pointer misOffScreenRederer::New( void )
{
	Pointer smartPtr; 
	Self *rawPtr = new Self; 
	smartPtr = rawPtr; 
	rawPtr->UnRegister(); 
	return smartPtr;
}

void misOffScreenRederer::SetWindow( vtkRenderWindow *window )
{
	m_Window=window;
	int* size=m_Window->GetSize();
	m_WindowSize[0]=size[0];
	m_WindowSize[1]=size[1];

}
