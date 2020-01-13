#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"


#include "misAxialRepresentation.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "misCoronalRepresentation.h"
#include "vtkPNGReader.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTexturedActor2D.h"
#include "vtkProperty2D.h"
#include "misGpuAxialMultiplaneRepresentation.h"
#include "misGpuCoronalMultiplaneRepresentation.h"
#include "vtkLight.h"
#include "misGpuSagittalMultiplaneRepresentation.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h" 
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "misImageGeoProperties.h"
//#include "misVoreenMapper.h"
#include "transfuncmappingkey.h"
#include "misVoreenRepresentation.h"
#include "misDIRReader.h"
#include "vtkImageData.h"
#include "prsDebugVariable.h"
#include "matrixproperty.h"
#include "voreenapplication.h"
#include "vtkTransform.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misVoreenTest2withddelay
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misVoreenTest2withddelay Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   

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

	void LoadExtensions(
		vtkRenderWindow *window)
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
	misVoreenTest2withddelay(int type)
	{

		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misVoreenTest2withddelay::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd->FPSDisplayOFF();
		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		voreen::VoreenApplication* pApp=new voreen::VoreenApplication();

		pApp->init();
		pApp->initGL();
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
		CameraRadius=500;
		alpha=0;
		imageClalback->SetSize(sized);
		//-------------------------
		//this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);

		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();
		this->AddImage();
		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
		vtkSphereSource* psh=vtkSphereSource::New();
		psh->SetRadius(5.0);

		vtkPolyDataMapper*  pSpMapper=vtkPolyDataMapper::New();
		pSpMapper->SetInputDataData(psh->GetOutput());
		vtkActor* pSphereActor=vtkActor::New();
		pSphereActor->GetProperty()->SetColor(1.0,0.0,0.0);
		pSphereActor->SetMapper(pSpMapper);
		m_Viewer->GetRenderer()->AddActor(pSphereActor);
		pSphereActor->SetPosition(300,300,300);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(300,300,120);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetFocalPoint(0,0,0);


	}

	misImage *m_pImage1,*m_pImage2;
	misVoreenRepresentation::Pointer  pVorreen;
	void AddImage()
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\for corrolation\\Mr\\DICOM\\PA000000\\ST000000\\SE000003");

		m_TestTransform=vtkTransform::New();

		//SeriAddress adrees;
		//adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		//m_pImage1=  m_pDicomReader->Get3DImageData(adrees); 
		//
		misImage*  pMisImage1=dynamic_cast<misImage*>(m_pImage1);



		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\for corrolation\\Ct\\DICOM\\PA1\\ST1\\SE1");



		/*adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage2=  m_pDicomReader->Get3DImageData(adrees); */
		//
		misImage*  pMisImage2=dynamic_cast<misImage*>(m_pImage2);

		pVorreen=misVoreenRepresentation::New("");



		misRootVolumeTexture * m_Texture1 = misRootVolumeTexture::New();				
		m_Texture1->SetInputDataData(pMisImage1);
		m_Texture1->InterpolateOn();
		m_Texture1->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage1);



		misRootVolumeTexture * m_Texture2 = misRootVolumeTexture::New();				
		m_Texture2->SetInputDataData(pMisImage2);
		m_Texture2->InterpolateOn();
		m_Texture2->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage2);


		pVorreen->SetRenderer(m_Viewer->GetRenderer());
		pVorreen->SetVolume(0,m_Texture1);
		pVorreen->SetVolume(1,m_Texture2);
		//mr:100
		bonethresholdvalue = this->ConvertIntensityToKeyValue(m_Texture1,-450);
		skinthresholdvalue = this->ConvertIntensityToKeyValue(m_Texture1,100);

		TransFuncIntensity*  mrTrans=SetTransferFunctionanTranslationForMr();
		TransFuncIntensity*  ctTrans=SetTransferFunctionanTranslationForCt();
		pVorreen->SetColorTransferFunction(0,mrTrans);
		pVorreen->SetColorTransferFunction(1,ctTrans);



		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
		pVorreen->SetRenderer(m_Viewer->GetRenderer());
		int* sizer=m_Viewer->GetRenderer()->GetSize();
		tgt::ivec3  wSize;
		wSize[0]=sizer[0];
		wSize[1]=sizer[1];

		wSize[2]=1;
		pVorreen->Update(wSize); 

		this->m_Viewer->AddRepresentation(pVorreen);	
	}
	float bonethresholdvalue;
	float skinthresholdvalue;

	std::vector<TransFuncIntensity*> m_Transfers;
	TransFuncIntensity* SetTransferFunctionanTranslationForCt( )
	{ 
		TransFuncIntensity *IntensityFunc = new TransFuncIntensity();

		auto *key0 = new TransFuncMappingKey( 0.0 , tgt::vec4(0,0,0,0));
		IntensityFunc->addKey(key0);

		auto *skin0 = new TransFuncMappingKey( 0.3 , tgt::vec4(247,222,166,0));
		IntensityFunc->addKey(skin0);

		auto *skin1 = new TransFuncMappingKey( 0.3 + 0.03 , tgt::vec4(247,222,166,200));
		IntensityFunc->addKey(skin1);

		auto *skin2 = new TransFuncMappingKey( float( 0.3+(0.4-0.3)/3), tgt::vec4(247,222,166,255));
		IntensityFunc->addKey(skin2);

		auto *bone0 = new TransFuncMappingKey( 0.4 , tgt::vec4(255,255,255,255));
		IntensityFunc->addKey(bone0);

		auto *bone1 = new TransFuncMappingKey( 0.3 + 0.03 , tgt::vec4(255,255,255,255));
		IntensityFunc->addKey(bone1);

		auto *key1 = new TransFuncMappingKey( 1.0 , tgt::vec4(255,255,255,255));
		IntensityFunc->addKey(key1);

		return IntensityFunc;



	}
	TransFuncIntensity* SetTransferFunctionanTranslationForMr( )
	{ 
		TransFuncIntensity *IntensityFunc = new TransFuncIntensity();

		auto *key0 = new TransFuncMappingKey( 0.0 , tgt::vec4(0,0,0,0));
		IntensityFunc->addKey(key0);

		auto *skin0 = new TransFuncMappingKey( 0.06 , tgt::vec4(247,222,166,0));
		IntensityFunc->addKey(skin0);

		auto *skin1 = new TransFuncMappingKey( 0.06 + 0.03 , tgt::vec4(247,0,0,200));
		IntensityFunc->addKey(skin1);



		auto *key1 = new TransFuncMappingKey( 1.0 , tgt::vec4(255,255,255,255));
		IntensityFunc->addKey(key1);

		return IntensityFunc;


	}

	float CameraRadius;
	float alpha;
	vtkTransform*  m_TestTransform;
	//==========================================================================
	void Render()
	{
		alpha=alpha+1;
		if(alpha>360)
			alpha=0;
		float rdd=vtkMath::RadiansFromDegrees(alpha);
		float  x=CameraRadius*sin(rdd);
		float  z=CameraRadius*cos(rdd);
		m_TestTransform->RotateY(1);


		vtkMatrix4x4*  mat=m_TestTransform->GetMatrix();
		//Creating Volume Transform
		tgt::mat4 transformMatrix = tgt::mat4::Matrix4(mat->GetElement(0,0),mat->GetElement(0,1),mat->GetElement(0,2),mat->GetElement(0,3),
			mat->GetElement(1,0),mat->GetElement(1,1),mat->GetElement(1,2),mat->GetElement(1,3),
			mat->GetElement(2,0),mat->GetElement(2,1),mat->GetElement(2,2),mat->GetElement(2,3)
			,0,0,0,1);

		pVorreen->SetTranformMatrixToVolumes(0,transformMatrix);

		//m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(x,z,120);

		//	m_Viewer->GetRenderer()->GetActiveCamera()->SetFocalPoint(0,120,0);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
		this->m_Viewer->Render();


	}

	float ConvertIntensityToKeyValue( misRootVolumeTexture* texture , int val )
	{
		double* tableRange = NULL;
		tableRange = texture->getRange();
		float key = (val - tableRange[0] )/(tableRange[1] - tableRange[0]);
		return key;
	}

	~misVoreenTest2withddelay(void)
	{
	}
};


