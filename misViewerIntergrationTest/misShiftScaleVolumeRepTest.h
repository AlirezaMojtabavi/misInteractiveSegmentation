#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"

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
#include "misApplicationSetting.h"
#include "misVoreenViewer.h"
#include "vtkImageShiftScale.h"
#include "vtkimageCast.h"
#include "misImageToTextureConvertor.h"
#include "misOpenglTexture.h"
#include "misTransFunctionBuilder.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misShiftScaleVolumeRepTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misShiftScaleVolumeRepTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   
	float bonethresholdvalue;
	float skinthresholdvalue;
	misVoreenViewer::Pointer   m_Viewer;
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
	misShiftScaleVolumeRepTest(int type)
	{
	
		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misShiftScaleVolumeRepTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd->FPSDisplayOn();
 
	//	m_wnd->FPSDisplayOFF();
		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		m_wnd->AddFPSRenderer();
		this->m_Viewer=misVoreenViewer::New();
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

		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();
		this->AddImage();
		m_AppSetting = misApplicationSetting::GetInstance();	
		
		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
		vtkSphereSource* psh=vtkSphereSource::New();
		psh->SetRadius(5.0);
		this->OnTreeViewClicked();
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
	
	misImage* m_pImage;
	misImage* m_ShiftScaled_Image;
	misVoreenRepresentation::Pointer  pVorreen;
	float CameraRadius;
	float alpha;
	void AddImage()
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("D:\\Dicom Data\\brain Surgery1\\New folder 2\\DICOM\\PA1\\ST1\\SE1");
		
		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage=  m_pDicomReader->Get3DImageData(adrees); */
		m_pImage->Update();
		double range[2];
		m_pImage->GetScalarRange(range);
	

		vtkImageShiftScale	*sc = vtkImageShiftScale::New();
		sc->SetInputDataData(m_pImage);
		sc->SetShift(1024);
		//sc->SetShift(-range[0]);

		sc->SetScale(VTK_UNSIGNED_SHORT_MAX/(4096));
		sc->ClampOverflowOn();
		sc->SetOutputScalarTypeToUnsignedShort();
		sc->Update();

		vtkImageData* pImage = sc->GetOutput();
		int dim[3];
		pImage->GetDimensions(dim);
		m_ShiftScaled_Image = misImage::New();
		m_ShiftScaled_Image->DeepCopy(pImage);
		
		//vtkImageCast* tempCastImage=0;
		//tempCastImage = vtkImageCast::New();
		//tempCastImage->SetOutputScalarTypeToUnsignedShort();
		//tempCastImage->SetInputDataData(pImage);
		//tempCastImage->Update();
		//m_ShiftScaled_Image = misImage::New();
		//m_ShiftScaled_Image->DeepCopy(tempCastImage->GetOutput());
		//m_ShiftScaled_Image->SetDimensions(512,512,270);
		//m_ShiftScaled_Image->SetSpacing(0.4882810,0.4882810,0.599998);
		//m_ShiftScaled_Image->SetExtent(0,511,0,511,0,269);
		
		misImage*  pMisImage = dynamic_cast<misImage*>(m_pImage);
		this->m_volumeStructData.parrentImagePointer = pMisImage;

		pVorreen=misVoreenRepresentation::New("");
	
	}

	void Render()
	{
		alpha=alpha+1;
		if(alpha>360)
			alpha=0;
		float rdd=vtkMath::RadiansFromDegrees(alpha);
		float  x=CameraRadius*sin(rdd);
		float  z=CameraRadius*cos(rdd);
	
		m_Viewer->GetRenderer()->GetActiveCamera()->SetClippingRange(0.1,10000);
		double i = 0.0;
	///*	for (int j = 0 ; j < 50 ; j++)
	//	{
	//		i = j*0.01;
	//		this->ChangeOpacity(i);
	//		this->m_Viewer->Render();
	//	}
	//	*/
		this->m_Viewer->Render();
	}

	~misShiftScaleVolumeRepTest(void)
	{
	}
	misObjectProperties m_ObjectProperties;
	double defaultThreshold ;
	misApplicationSetting* m_AppSetting;
	misVolumeDataDependensies m_volumeStructData;

	void OnTreeViewClicked()
	{
//		showSkinAtFirst();
		showshiftscaledvolume();

	}
	void showshiftscaledvolume()
	{
		misImageToTextureConvertor   convert;
		misOpenglTexture*  texturect= convert(m_ShiftScaled_Image);
		misTransFunctionBuilder  builder;
		TransFuncIntensity* pIntensity;

		pIntensity=builder.GenerateTransferFunction(texturect->GetTableRange(),CT);

		m_Viewer->ShowVolume(texturect,pIntensity);

	}
	void showSkinAtFirst() 
	{
		double volumeThreshold;
		this->m_ObjectProperties.ObjectRenderingType = misVolumeRendering;
		this->m_ObjectProperties.ObjectVolumeViewing = misSkinviewing;
// 		this->m_ObjectProperties.ObjectColor.red = 0;
// 		this->m_ObjectProperties.ObjectColor.blue = 90;
// 		this->m_ObjectProperties.ObjectColor.green = 90;
// 		this->m_ObjectProperties.ObjectColor.alpha = 0;
		
		if (CT == m_volumeStructData.parrentImagePointer->GetImageModality() )
		{
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForCT;
		}
		else if (MRI == m_volumeStructData.parrentImagePointer->GetImageModality())
		{
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForMRI;
		}
		else
			_ASSERT(true == false);
		
		this->m_volumeStructData.useable = true;
		if (0 == this->m_volumeStructData.objectPointer )
		{
			this->m_volumeStructData.objectPointer = std::make_shared<misVolumeData>();
		}

		this->m_volumeStructData.objectPointer->SetImageModality(this->m_volumeStructData.parrentImagePointer->GetImageModality());
		this->m_volumeStructData.objectPointer->SetMinThreshold(this->m_ObjectProperties.ObjectVolumeViewing,volumeThreshold);
//		this->m_volumeStructData.objectPointer->SetObjectColor(this->m_ObjectProperties.ObjectVolumeViewing,this->m_ObjectProperties.ObjectColor);
		this->UpdateVolume();
	}
	void UpdateVolume()
	{			
		int i = m_Viewer->ShowPackageVolumeDatas(m_volumeStructData);
		m_Viewer->Render();
	}
	void OnDeny()
	{
		RemoveAll();
	}
	void RemoveAll()
	{
		m_Viewer->ClearVolumeWindow();
	}
	void ChangeOpacity(double i) 
	{
		double volumeThreshold;
		this->m_ObjectProperties.ObjectRenderingType = misVolumeRendering;
		this->m_ObjectProperties.ObjectVolumeViewing = misSkinviewing;
		this->m_ObjectProperties.ObjectColor.red = 0;
		this->m_ObjectProperties.ObjectColor.blue = 200;
		this->m_ObjectProperties.ObjectColor.green = 20;
		this->m_ObjectProperties.ObjectColor.alpha = 20;

		this->m_volumeStructData.useable = true;
		if (0 == this->m_volumeStructData.objectPointer )
		{
			this->m_volumeStructData.objectPointer = std::make_shared<misVolumeData>();
		}

		if (CT == m_volumeStructData.parrentImagePointer->GetImageModality() )
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForCT;
		else if (MRI == m_volumeStructData.parrentImagePointer->GetImageModality())
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForMRI;
		else
			_ASSERT(true == false);


		this->m_volumeStructData.objectPointer->SetMinThreshold(this->m_ObjectProperties.ObjectVolumeViewing,volumeThreshold);
		if (this->m_volumeStructData.objectPointer)
		{
		
			this->UpdateVolume();
		}

	}

};


