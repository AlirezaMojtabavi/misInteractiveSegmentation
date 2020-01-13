#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================

#include "vtkSphereSource.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "misCoronalRepresentation.h"
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
//#include "../glmath.h"
#include "misHybridViewer.h"
#include "transfuncintensity.h"

#include "misDIRReader.h"
#include "vtkImageReader.h"
#include "vtkimageCast.h"
 #include "voreenapplication.h"
using namespace tgt;
typedef itk::Point<float ,3>  PointType;


class  textureMapper:public  vtkMapper
{
public:
	static  textureMapper*  New()
	{
		return new textureMapper;
	}
	GLint m_program;
	bool LoadExtensionsSucceeded;
	GLuint	tex_id,TF_ID;
//	float k;

virtual void Render(vtkRenderer *ren, vtkActor *a)  
	{
		if (!this->LoadExtensionsSucceeded)
		{
			this->LoadExtensions(ren->GetRenderWindow());
			CreateGLSLObjects(ren);
		//	k = 0;
		}
		SetShaderVariables();

		// ----------- 3D Display -------------
		drawQuads(1.0,1.0,1.0);
	/*	k = k + 0.001;
		if (k>1)
			k=0;*/

		glDisable(GL_TEXTURE_3D);

		vtkgl::UseProgram(0);

	}
void textureMapper::CreateGLSLObjects( vtkRenderer *ren )
{
	GLuint		m_FragmentShader=0,m_VertexShader=0;
	char		*vs = NULL,*fs = NULL;

	m_FragmentShader = vtkgl::CreateShader(vtkgl::FRAGMENT_SHADER);
	m_VertexShader	  = vtkgl::CreateShader(vtkgl::VERTEX_SHADER);

	char *FragmentShaderStr = "textureandtf.frag";
	char *VertexShaderStr = "textureSimple.vert";


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
void textureMapper::SetShaderVariables()
{
	vtkgl::UseProgram(m_program);

//                         TEXTURE 
//  _____________________________________________________________

	GLint texsampler;

	vtkgl::ActiveTexture(vtkgl::TEXTURE0 + tex_id);
	glEnable(vtkgl::TEXTURE_3D);
	glBindTexture(vtkgl::TEXTURE_3D, tex_id);

	texsampler= vtkgl::GetUniformLocation(this->m_program,"tex");
	vtkgl::Uniform1i(texsampler,tex_id);

	glDisable(vtkgl::TEXTURE_3D);
	vtkgl::ActiveTexture(vtkgl::TEXTURE0);

//                              TF
//  _____________________________________________________________
   
	GLint tf;
	vtkgl::ActiveTexture(vtkgl::TEXTURE0 + TF_ID);
	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, TF_ID);

	tf= vtkgl::GetUniformLocation(this->m_program,"transferFunc_");
	vtkgl::Uniform1i(tf,TF_ID);

	glDisable(GL_TEXTURE_1D);
	vtkgl::ActiveTexture(vtkgl::TEXTURE0);

}
void textureMapper::vertex(float x, float y, float z)
{
	//glColor3f(x,y,z);
	glTexCoord3f( x, y, z);
	glVertex3f(x,y,z); 

}
void textureMapper::drawQuads(float x, float y, float z)
{

	glBegin(GL_QUADS);

	int res=100;
	float step=1.0/res;

	/* Back side */
	glNormal3f(0.0, 0.0, -1.0);
for (int i=0;i<res;i++)
{
	vertex(0.0, 0.0, i*step);
	vertex(0.0, y, i*step);
	vertex(x, y, i*step);
	vertex(x, 0.0, i*step);
}
	

	glEnd();

}
void textureMapper::LoadExtensions( vtkRenderWindow *window )
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

class misPolydataTfTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];
	misRootVolumeTexture * texx;
	GLuint tf_id;
	float CameraRadius;
	float alpha;
	int windowSize[2];
	//		misImageInteractionStyle* pStyle;
	typedef misPolydataTfTest  Self;
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

	void Render()
	{
		alpha=alpha+1;
		if(alpha>360)
			alpha=0;
		float rdd=vtkMath::RadiansFromDegrees(alpha);
		float  x=CameraRadius*sin(rdd);
		float  z=CameraRadius*cos(rdd);
		//	m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(x,z,3);

		this->m_Viewer->Render();

	}

	void AddImage()
	{

		vtkImageReader *reader  = vtkImageReader::New();
		reader->SetFileName("specificImage");
		reader->SetDataScalarTypeToUnsignedChar();
		reader->SetNumberOfScalarComponents(1);
		reader->SetFileDimensionality(3);
		reader->SetDataSpacing(0.484375,0.484375,0.599998);
		reader->SetDataOrigin(0.0,0.0,0.0);
		reader->SetDataExtent(0,511,0,511,0,377);
		reader->SetNumberOfScalarComponents(1);
		reader->Update();

		// ...................vtkImageData..............................

		m_pImage = reader->GetOutput();
		m_pImage->Update();
	//	m_pImage->SetScalarTypeToUnsignedShort();
		m_pImage->SetExtent(0,511,0,511,0,377);
		m_pImage->AllocateScalars();
		m_pImage->SetDimensions(512,512,378);
		m_pImage->Update();

		//.................. vtkImageCast .....................................

		vtkImageCast* tempCastImage=0;
		tempCastImage = vtkImageCast::New();
		tempCastImage->SetOutputScalarTypeToUnsignedChar();
		tempCastImage->SetInputDataData(m_pImage);
		tempCastImage->Update();

		//.......................misImage.......................................

		misImage * pMisImage = misImage::New();
		pMisImage->DeepCopy(tempCastImage->GetOutput());
		pMisImage->SetScalarTypeToShort();

		//........................misRootVolumeTexture..........................
		texx = misRootVolumeTexture::New();				
		texx->InterpolateOn();
		texx->SetInputDataData(pMisImage);
		texx->Update();
		texx->SetIsPolydataFlag(true);
		texx->UpdateTexture(this->m_Viewer->GetRenderer(),pMisImage);

	}

	void SetTransferFunction()
	{ 
		//RAMA
		int argc = 1;
		char* argv[1];
		argv[0] = "rama";



		// TODO : sara ; do sth about the keys
		double keys[5];

		double* tableRange = NULL;
		tableRange = this->texx->getRange();
		double dif = 1/(3*tableRange[1]);
		keys[0]= 160/tableRange[1];
		keys[1]= 250/tableRange[1];
// 		keys[2]= 4/tableRange[1];
// 		keys[3]= 8/tableRange[1];
// 		keys[4]= 12/tableRange[1];
		//.............................................

		voreen::VoreenApplication* app = new voreen::VoreenApplication("simple-GLUT", "simple-GLUT", argc, argv,voreen::VoreenApplication::APP_ALL);
		app->init();
		app->initGL();
		//......................................................................................................
		TransFuncIntensity *IntensityFunc = new TransFuncIntensity();

		TransFuncMappingKey *k0 = new TransFuncMappingKey( 0.0 , tgt::vec4(0,0,0,0));
		IntensityFunc->addKey(k0);

		TransFuncMappingKey *k11 = new TransFuncMappingKey( keys[0]-dif , tgt::vec4(255,0,0,0));
		IntensityFunc->addKey(k11);

		TransFuncMappingKey *k12 = new TransFuncMappingKey( keys[0] , tgt::vec4(255,0,0,255));
		IntensityFunc->addKey(k12);

		TransFuncMappingKey *k13 = new TransFuncMappingKey( keys[0]+dif , tgt::vec4(255,0,0,0));
		IntensityFunc->addKey(k13);

		TransFuncMappingKey *k21 = new TransFuncMappingKey( keys[1]-dif , tgt::vec4(0,255,0,0));
		IntensityFunc->addKey(k21);

		TransFuncMappingKey *k22 = new TransFuncMappingKey( keys[1] , tgt::vec4(0,255,0,255));
		IntensityFunc->addKey(k22);

		TransFuncMappingKey *k23 = new TransFuncMappingKey( keys[1]+dif , tgt::vec4(0,255,0,0));
		IntensityFunc->addKey(k23);

	/*	TransFuncMappingKey *k31 = new TransFuncMappingKey( keys[2]-dif , tgt::vec4(0,0,255,0));
		IntensityFunc->addKey(k31);

		TransFuncMappingKey *k32 = new TransFuncMappingKey( keys[2], tgt::vec4(0,0,255,255));
		IntensityFunc->addKey(k32);

		TransFuncMappingKey *k33 = new TransFuncMappingKey( keys[2]+dif, tgt::vec4(0,0,255,0));
		IntensityFunc->addKey(k33);

		TransFuncMappingKey *k41 = new TransFuncMappingKey( keys[3]-dif , tgt::vec4(255,255,0,0));
		IntensityFunc->addKey(k41);

		TransFuncMappingKey *k42 = new TransFuncMappingKey( keys[3], tgt::vec4(255,255,0,255));
		IntensityFunc->addKey(k42);

		TransFuncMappingKey *k43 = new TransFuncMappingKey( keys[3]+dif, tgt::vec4(255,255,0,0));
		IntensityFunc->addKey(k43);

		TransFuncMappingKey *k51 = new TransFuncMappingKey( keys[4]-dif , tgt::vec4(255,0,255,0));
		IntensityFunc->addKey(k51);

		TransFuncMappingKey *k52 = new TransFuncMappingKey( keys[4], tgt::vec4(255,0,255,255));
		IntensityFunc->addKey(k52);

		TransFuncMappingKey *k53 = new TransFuncMappingKey( keys[4]+dif , tgt::vec4(255,0,255,0));
		IntensityFunc->addKey(k53);*/

		TransFuncMappingKey *k1 = new TransFuncMappingKey( 1.1 , tgt::vec4(255,0,255,0));
		IntensityFunc->addKey(k1);

		IntensityFunc->updateTexture();
		IntensityFunc->bind();
		tgt::Texture * tf_tex = IntensityFunc->getTexture();
		tf_id = tf_tex->getId();
	}

	misPolydataTfTest(int type)
	{
		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misPolydataTfTest::Render);
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

		double  sized[2];
		sized[0]=size[0];
		sized[1]=size[1];
		
		windowSize[0]=size[0];
		windowSize[1]=size[1];

		CameraRadius=10;
		alpha=0;
		imageClalback->SetSize(sized);


		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();


// -----------------------------------------
		textureMapper*  pMapper=textureMapper::New();
		pMapper->LoadExtensionsSucceeded = false;

		AddImage();
		pMapper->tex_id = texx->getId();

		SetTransferFunction();
		pMapper->TF_ID = tf_id;

// -------------------------------------------
		vtkActor* pActor=  vtkActor::New();
		pActor->SetMapper(pMapper);
		
		m_Viewer->GetRenderer()->AddActor(pActor);

	}

	
	

	~misPolydataTfTest (void)
	{
	}
};


