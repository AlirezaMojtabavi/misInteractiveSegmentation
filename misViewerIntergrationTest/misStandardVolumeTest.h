#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"

#include "vtkImageMapToWindowLevelColors.h"
#include "vtkPNGReader.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTexturedActor2D.h"
#include "vtkProperty2D.h"
// #include "misGpuAxialMultiplaneRepresentation.h"
// #include "misGpuCoronalMultiplaneRepresentation.h"
#include "vtkLight.h"
/*#include "misGpuSagittalMultiplaneRepresentation.h"*/
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h" 
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "misImageGeoProperties.h"
#include "transfuncmappingkey.h"
#include "misVoreenRepresentation.h"
#include "misDIRReader.h"
#include "vtkImageData.h"
#include "prsDebugVariable.h"
#include "voreenapplication.h"
#include "misApplicationSetting.h"
#include "misVoreenViewer.h"
#include "vtkImageShiftScale.h"
#include "vtkimageCast.h"
#include "misImageToTextureConvertor.h"
#include "misOpenglTexture.h"
#include "misTransFunctionBuilder.h"
#include "init.h"
#include "misImageToTexturePropertyConvertor.h"

typedef itk::Point<float ,3>  PointType;

class misStandardVolumeTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	typedef misStandardVolumeTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   
	float bonethresholdvalue;
	float skinthresholdvalue;
	misVoreenViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;

	int * m_Size;

	std::shared_ptr<misImage> m_pImage;
	misImage* m_ShiftScaled_Image;
	misVoreenRepresentation::Pointer  pVorreen;
	float CameraRadius;
	float alpha;

	//misObjectProperties m_ObjectProperties;
	double defaultThreshold ;
	misApplicationSetting* m_AppSetting;
	misVolumeDataDependensies m_volumeStructData;

	misStandardVolumeTest(int type)
	{
		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misStandardVolumeTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd->FPSDisplayOn();

		//	m_wnd->FPSDisplayOFF();
		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow(VolumeViewer,);
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		m_wnd->AddFPSRenderer();
		this->m_Viewer=misVoreenViewer::New();
		m_Viewer->SetGenerateGradientImage(true);
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

		int * sized = new int[2];
		sized[0]=size[0];
		sized[1]=size[1];
		CameraRadius=500;
		alpha=0;
		imageClalback->SetSize(sized);
		//-------------------------
		//this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);
		glewInit();
		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();


		voreen::VoreenApplication* m_Voreen=new voreen::VoreenApplication();
		m_Voreen->init();
		m_Voreen->initGL();


		this->AddImage();
		m_Viewer->SetImageForRayIntersection(m_pImage);
		m_AppSetting = misApplicationSetting::GetInstance();	

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
		m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(1000,1000,1000);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetFocalPoint(0,0,0);
		m_PulseGenerator->RequestStart();
		m_PulseGenerator->RequestSetFrequency(200);
	}

	void LoadGui()
	{
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

	void AddImage()
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;

		m_PatientTree = m_pDicomReader->BrowseDir("D:\\DICOM\\Safarkhani Ghorban\\CT\\DICOM\\PA2\\ST1\\SE2");

		PassedAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage=  m_pDicomReader->Get3DImageData(adrees); 
		m_pImage->Update();
		double range[2];
		m_pImage->GetScalarRange(range);


		misImageToTexturePropertyConvertor convertor1;
		misTexturePropertyStruct texProp1 = convertor1(m_pImage);
		misImageGeoProperties m_MainImageProp = misImageGeoProperties(m_pImage);
		misOpenglTexture* pTexture= new misOpenglTexture(texProp1,tgt::Texture::Filter::LINEAR);

		misTransFunctionBuilder  tfbuilder;
		auto tr= tfbuilder.GenerateTransferFunction(texProp1.TableRange,-450);
		m_Viewer->ShowVolume(pTexture,tr);

	//	m_Viewer->GetCursorService()->SetImageOrientation(AXIAL);
		m_Viewer->GetCursorService()->SetWidgetType(misCursorType::CompleteCursor);
		double* bound=m_MainImageProp.GetBound();
		m_Viewer->GetCursorService()->SetWidgetBounds(bound);
		delete  bound;
		m_Viewer->InitializeWidget();
		m_Viewer->GetCursorService()->SetWidgetInteractor((vtkRenderWindowInteractor*)m_wnd->GetInterActor());
		m_Viewer->GetCursorService()->ApplyWidget(m_Viewer->GetMainRepresentation());
		m_Viewer->GetCursorService()->EnableWidget();
		m_Viewer->GetCursorService()->SetWidgetPosition(50 , 50 , 90+5);
// 
// 		misAxisProperty  axis;
// 		axis.m_GeoType=misAxisProperty::line;
// 		axis.y_Lenght=100;
// 		axis.x_Lenght=100;
// 		axis.z_Lenght=100;
// 		m_Viewer->AddAxis(axis);
	}

	void Render()
	{
// 		alpha=alpha+1;
// 	if(alpha>360)
// 		alpha=0;
// 	float rdd=vtkMath::RadiansFromDegrees(alpha);
// 	float  x=CameraRadius*sin(rdd);
// 	float  z=CameraRadius*cos(rdd);

// 	m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
// 	double i = 0.0;
	///*	for (int j = 0 ; j < 50 ; j++)
	//	{
	//		i = j*0.01;
	//		this->ChangeOpacity(i);
	//		this->m_Viewer->Render();
	//	}
	//	*/
	//this->m_Viewer->Render();
	}

	~misStandardVolumeTest(void)
	{
	}
	void PrepareAddLandmark()
	{
		
		this->m_Viewer->SetCaptureLandmarkFlag(true);
	}

};


