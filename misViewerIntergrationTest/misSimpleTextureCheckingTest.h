#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================

#include "vtkSphereSource.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkPNGReader.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTexturedActor2D.h"
#include "vtkProperty2D.h"
#include "vtkLight.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h" 
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "transfuncmappingkey.h"
#include "vtkImageData.h"
 #include "tgt/init.h"
#include "tgt/filesystem.h"
#include "tgt/shadermanager.h"
#include "tgt/timer.h"
#include "tgt/gpucapabilities.h"
#include "vtkMapper.h"
#include "vtkgl.h"
#include "../misVisualization/texfile.h"
#include "glmath.h"
#include "misHybridViewer.h"
#include "transfuncintensity.h"
#include "misDIRReader.h"
#include "misImageToTextureMap.h"
#include "misOpenglTexture.h"
#include "misDICOMImageLoader.h"
  
using namespace tgt;
typedef itk::Point<float ,3>  PointType;


class  MyTestMapper:public  vtkMapper
{
public:
	static  MyTestMapper*  New()
	{
		return new MyTestMapper;
	}
	GLint m_program;
	bool LoadExtensionsSucceeded;
	GLuint tex_id;
virtual void Render(vtkRenderer *ren, vtkActor *a)  
	{
		if (!this->LoadExtensionsSucceeded)
		{
			this->LoadExtensions(ren->GetRenderWindow());
			CreateGLSLObjects(ren);

		}
		SetShaderVariables();

		// ----------- 3D Display -------------

		drawQuads(1.0,1.0,1.0);
		glDisable(GL_TEXTURE_3D);

		vtkgl::UseProgram(0);

	}
void MyTestMapper::CreateGLSLObjects( vtkRenderer *ren )
{
	GLuint		m_FragmentShader=0,m_VertexShader=0;
	char		*vs = NULL,*fs = NULL;

	m_FragmentShader = vtkgl::CreateShader(vtkgl::FRAGMENT_SHADER);
	m_VertexShader	  = vtkgl::CreateShader(vtkgl::VERTEX_SHADER);

	char *FragmentShaderStr = "simpleTexture.frag";
	char *VertexShaderStr = "SimpleVertexShader.vert";


	fs = textFileRead(FragmentShaderStr);
	vs = textFileRead(VertexShaderStr);

	const char * ff = fs;
	const char * vv = vs;

	m_program = vtkgl::CreateProgram();


	vtkgl::ShaderSource(m_FragmentShader, 1, &ff,NULL);
	vtkgl::ShaderSource(m_VertexShader, 1, &vv,NULL);

	free(fs);
	free(vs);

	GLint completed;

	vtkgl::CompileShader(m_VertexShader);
	vtkgl::CompileShader(m_FragmentShader);
	vtkgl::GetShaderiv(m_FragmentShader, vtkgl::COMPILE_STATUS, &completed);

	if (!completed) {
	GLint len;
	char* msg;
	vtkgl::GetShaderiv(m_FragmentShader, vtkgl::INFO_LOG_LENGTH, &len);
	msg = (char*) malloc(len);
	vtkgl::GetShaderInfoLog(m_FragmentShader, len, &len, msg);
	fprintf(stderr, "Vertex shader compilation failure:\n%s\n", msg);
	free(msg);
	vtkgl::DeleteProgram(m_program);
	exit(EXIT_FAILURE);
	}


	vtkgl::AttachShader(m_program,m_FragmentShader);
	vtkgl::AttachShader(m_program,m_VertexShader);

	vtkgl::LinkProgram(m_program);

	vtkgl::GetProgramiv(m_program, vtkgl::LINK_STATUS, &completed);
	if (!completed) {
		GLint len;
		char* msg;
		vtkgl::GetProgramiv(m_program, vtkgl::INFO_LOG_LENGTH, &len);
		msg = (char*) malloc(len);
		vtkgl::GetProgramInfoLog(m_program, len, &len, msg);
		fprintf(stderr, "Program link failure:\n%s\n", msg);
		free(msg);
		vtkgl::DeleteProgram(m_program);
		exit(EXIT_FAILURE);
	}
}
void MyTestMapper::SetShaderVariables()
{
	vtkgl::UseProgram(m_program);

// tf,tex
//                        DICOM     TEXTURE 
//  _____________________________________________________________

	GLint texsampler;
	//GLint tf;
	vtkgl::ActiveTexture(vtkgl::TEXTURE0 + tex_id);
	glEnable(vtkgl::TEXTURE_3D);
	glBindTexture(vtkgl::TEXTURE_3D, tex_id);

	texsampler= vtkgl::GetUniformLocation(this->m_program,"tex");
	vtkgl::Uniform1i(texsampler,tex_id);

	glDisable(vtkgl::TEXTURE_3D);
	vtkgl::ActiveTexture(vtkgl::TEXTURE0);

}
void MyTestMapper::vertex(float x, float y, float z)
{
	//glColor3f(x,y,z);
	glTexCoord3f( x, y, z);
	glVertex3f(x,y,z); 

}
void MyTestMapper::drawQuads(float x, float y, float z)
{

	glBegin(GL_QUADS);
	/* Back side */
	glNormal3f(0.0, 0.0, -1.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(x, y, 0.0);
	vertex(x, 0.0, 0.0);

	/* Front side */
	glNormal3f(0.0, 0.0, 1.0);
	vertex(0.0, 0.0, z);
	vertex(x, 0.0, z);
	vertex(x, y, z);
	vertex(0.0, y, z);

	/* Top side */
	glNormal3f(0.0, 1.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(0.0, y, z);
	vertex(x, y, z);
	vertex(x, y, 0.0);

	/* Bottom side */
	glNormal3f(0.0, -1.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, 0.0, z);
	vertex(0.0, 0.0, z);

	/* Left side */
	glNormal3f(-1.0, 0.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, 0.0, z);
	vertex(0.0, y, z);
	vertex(0.0, y, 0.0);

	/* Right side */
	glNormal3f(1.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, y, 0.0);
	vertex(x, y, z);
	vertex(x, 0.0, z);
	glEnd();

}
void MyTestMapper::LoadExtensions( vtkRenderWindow *window )
{

	const char *gl_vendor=reinterpret_cast<const char *>(glGetString(GL_VENDOR));
	const char *gl_version=reinterpret_cast<const char *>(glGetString(GL_VERSION));

	// Create an extension manager
	vtkOpenGLExtensionManager *extensions=vtkOpenGLExtensionManager::New();
	extensions->SetRenderWindow(window);

	// GL_ARB_draw_buffers requires OpenGL 1.3, so we must have OpenGL 1.3
	// We don't need to check for some extensions that become part of OpenGL
	// core after 1.3. Among them:
	//   - texture_3d is in core OpenGL since 1.2
	//   - texture_edge_clamp is in core OpenGL since 1.2
	//     (GL_SGIS_texture_edge_clamp or GL_EXT_texture_edge_clamp (nVidia) )
	//   -  multi texture is in core OpenGL since 1.3

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

	// Now start adding messages to the UnsupportedRequiredExtensions string
	// Log message if shading language 100 is not supported



	// Have we succeeded so far? If not, just return.

	// Now start loading the extensions
	// First load all 1.2 and 1.3 extensions (we know we
	// support at least up to 1.3)
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


	this->LoadExtensionsSucceeded = true;
	extensions->Delete();
}
};

class misSimpleTextureCheckingTest 
{
public:
	int m_Type;
	float  slice;
	double  pos[3];
	misOpenglTexture * texx;
	//		misImageInteractionStyle* pStyle;
	typedef misSimpleTextureCheckingTest  Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   
	vtkImageData* m_pImage;
	misHybridViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	void LoadGui()
	{	
		//a window object
		HINSTANCE  hInstance=GetModuleHandle(0);
		if(!windowMain.Create(0, 0, 1000,1000))
		{
			MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK);
		}
	}

	void AddImage()
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("D:\\Dicom Data\\Davood Kaveh\\Main CT\\DICOM\\PA1\\ST1\\SE1");
		misImage*  pMisImage = dynamic_cast<misImage*>(m_pImage);

		misImageToTextureMap*	TextureHandler = misImageToTextureMap::GetInstance();
		texx = TextureHandler->LookUpTexture(pMisImage);
	}

	void LoadExtensions(vtkRenderWindow *window)
	{

		const char *gl_vendor=reinterpret_cast<const char *>(glGetString(GL_VENDOR));
		const char *gl_version=reinterpret_cast<const char *>(glGetString(GL_VERSION));

		// Create an extension manager
		vtkOpenGLExtensionManager *extensions=vtkOpenGLExtensionManager::New();
		extensions->SetRenderWindow(window);

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

		// Now start adding messages to the UnsupportedRequiredExtensions string
		// Log message if shading language 100 is not supported



		// Have we succeeded so far? If not, just return.

		// Now start loading the extensions
		// First load all 1.2 and 1.3 extensions (we know we
		// support at least up to 1.3)
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


		//		this->LoadExtensionsSucceeded = true;
		extensions->Delete();
	}

	//==========================================================================

	float CameraRadius;
	float alpha;
	int windowSize[2];
	//==========================================================================
	misSimpleTextureCheckingTest(int type)
	{
		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misSimpleTextureCheckingTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd->FPSDisplayOFF();
		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		this->m_Viewer=misHybridViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
		LoadExtensions(m_wnd->GetRenderWindow());
		//-------------------------
		vtkRenderer *rendere=this->m_Viewer->GetRenderer();
		//rendere->LightFollowCameraOn();
		//rendere->RemoveAllLights();
		rendere->TwoSidedLightingOn();
		//		rendere->UpdateLightGeometry();
		vtkLight* pLight=vtkLight::New();
		pLight->SetDiffuseColor(0.8,0.8,0.8);
		pLight->SetAmbientColor(0.8,0.8,0.8);

		pLight->SetLightTypeToHeadlight();
		rendere->AddLight(pLight);
		//pLight->SetPosition()
		size=rendere->GetRenderWindow()->GetSize();

		int*  sized= new int[2];
		sized[0]=size[0];
		sized[1]=size[1];
		
		windowSize[0]=size[0];
		windowSize[1]=size[1];

		CameraRadius=10;
		alpha=0;
		imageClalback->SetSize(sized);
//  -------------------------

		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();


// -----------------------------------------
		MyTestMapper*  pMapper=MyTestMapper::New();
		pMapper->LoadExtensionsSucceeded = false;
		
		AddImage();
		pMapper->tex_id = texx->getId();

// -------------------------------------------
		vtkActor* pActor=  vtkActor::New();
		pActor->SetMapper(pMapper);
		
		m_Viewer->GetRenderer()->AddActor(pActor);

	}

	void Render()
	{
		alpha=alpha+1;
		if(alpha>360)
			alpha=0;
		float rdd=vtkMath::RadiansFromDegrees(alpha);
		float  x=CameraRadius*sin(rdd);
		float  z=CameraRadius*cos(rdd);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(x,z,3);

		this->m_Viewer->Render();

	}


	~misSimpleTextureCheckingTest (void)
	{
	}
};


