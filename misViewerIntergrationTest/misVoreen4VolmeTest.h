#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misImageViewer.h"

#include "vtkImageMapToWindowLevelColors.h"
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

#include "voreenapplication.h"
#include "vtkTransform.h"
#include "misTransFunctionBuilder.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misVoreen4VolmeTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misVoreen4VolmeTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
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
	misVoreen4VolmeTest(int type)
	{

		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misVoreen4VolmeTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd.FPSDisplayOFF();
		this->m_wnd.set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd.GenerateRenderWindow();
		voreen::VoreenApplication* pApp=new voreen::VoreenApplication();

		pApp->init();
		pApp->initGL();
		//     this->m_cbk->m_RenderWindow=this->m_wnd.GetRenderWindow();
		this->m_Viewer=misHybridViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
		LoadExtensions(m_wnd.GetRenderWindow());
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
		//this->m_wnd.GetRenderer()->SetBackground(0.2,1,1);

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
		//	m_Viewer->GetRenderer()->AddActor(pSphereActor);
		pSphereActor->SetPosition(300,300,300);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(300,300,120);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetFocalPoint(0,0,0);
		m_TestTransform=vtkTransform::New();

	}

	misImage *m_pImage1,*m_pImage2,*m_pImage3,*m_pImage4;
	misVoreenRepresentation::Pointer  pVorreen;
	void AddImage()
	{
		AddImage1();
		AddImage2();
		AddImage3();
		AddImage4();


		pVorreen=misVoreenRepresentation::New("");



		misRootVolumeTexture * m_Texture1 = misRootVolumeTexture::New();				
		m_Texture1->SetInputDataData(m_pImage1);
		m_Texture1->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage1);



		misRootVolumeTexture * m_Texture2 = misRootVolumeTexture::New();				
		m_Texture2->SetInputDataData(m_pImage2);
		m_Texture2->InterpolateOn();
		m_Texture2->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage2);
		misRootVolumeTexture * m_Texture3 = misRootVolumeTexture::New();				
		m_Texture3->SetInputDataData(m_pImage2);
		m_Texture3->InterpolateOn();
		m_Texture3->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage2);

		misRootVolumeTexture * m_Texture4 = misRootVolumeTexture::New();				
		m_Texture4->SetInputDataData(m_pImage2);
		m_Texture4->InterpolateOn();
		m_Texture4->UpdateTexture(this->m_Viewer->GetRenderer(),m_pImage2);
		pVorreen->SetRenderer(m_Viewer->GetRenderer());
	
 		//mr:100
		bonethresholdvalue = this->ConvertIntensityToKeyValue(m_Texture1,-450);
		skinthresholdvalue = this->ConvertIntensityToKeyValue(m_Texture1,100);
 
		pVorreen->SetRenderer(m_Viewer->GetRenderer());
		int* sizer=m_Viewer->GetRenderer()->GetSize();
		tgt::ivec3  wSize;
		wSize[0]=sizer[0];
		wSize[1]=sizer[1];

		wSize[2]=1;

		pVorreen->SetWindowSize(wSize);
 



		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);


		this->m_Viewer->AddRepresentation(pVorreen);	

		misTransFunctionBuilder  builder;
		TransFuncIntensity*  func1=builder.GenerateTransferFunction(m_Texture1);
		pVorreen->SetVolume(0,m_Texture1);
		pVorreen->SetColorTransferFunction(0,func1);
		
		TransFuncIntensity*  func2=builder.GenerateTransferFunction(m_Texture2);
		pVorreen->SetVolume(1,m_Texture2);
		pVorreen->SetColorTransferFunction(1,func2);
		
		TransFuncIntensity*  func3=builder.GenerateTransferFunction(m_Texture3);
		pVorreen->SetVolume(2,m_Texture3);
		pVorreen->SetColorTransferFunction(2,func3);
		/*
		TransFuncIntensity*  func4=builder.GenerateTransferFunction(m_Texture4);
		pVorreen->SetVolume(3,m_Texture4);
		pVorreen->SetColorTransferFunction(3,func4);*/
	}

	void AddImage2() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\abbas bahraeii\\CT\\DICOM\\PA1\\ST1\\SE1");


		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage2=  m_pDicomReader->Get3DImageData(adrees); */
		//
	 
	}

	void AddImage1() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\2-28\\DICOM\\PA1\\ST1\\SE2");


		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage1=  m_pDicomReader->Get3DImageData(adrees); */
		//
	}
	void AddImage3() 
	{
	misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\9-28\\DICOM\\PA000000\\ST000000\\SE000002");


		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage3=  m_pDicomReader->Get3DImageData(adrees); */
		//
 	}

	void AddImage4() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:\\Dicom data\\30-5-90\\DICOM\\PA1\\ST1\\SE1");

		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage4=  m_pDicomReader->Get3DImageData(adrees); */
		//
	}

	float bonethresholdvalue;
	float skinthresholdvalue;

	std::vector<TransFuncIntensity*> m_Transfers;
 
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

	~misVoreen4VolmeTest(void)
	{
	}
};


