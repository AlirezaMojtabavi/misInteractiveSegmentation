#ifndef __misCorrelationFourViewer__
#define __misCorrelationFourViewer__

#include "misobject.h"
#include "misImageViewer.h"
#include "mis3DViewer.h"
#include "misVoreenRepresentation.h"
#include "misImageCorrelationPointSelectObserver.h"
#include "misImageCorrelationWidgetObserver.h"
#include "misColorPointWidget.h"
#include "misWindow.h"
#include "misStrctSubTabModel.h"
#include "misStrctColorData.h"
#include "misImageViewer.h"
#include "misVoreenViewer.h"
#include "misOpenglTexture.h"
#include "transfuncintensity.h"
#include "matrix.h"
#include "misGPUStandardRepresentation.h"

igstkLoadedEventMacro( misPointSelect, misEvent,   misItkPointType) ;

class MISDLLEXPORT misCorrelationFourViewer :public misObject
{
friend class misImageCorrelationSubSeq;
friend  class misCorrolationViewTest;
private:
 
	misUID  m_FixedImageUID;
	misUID  m_MovingImageUID;

	misImageViewer::Pointer m_Panel_viewer_2D_Fixed;
	misImageViewer::Pointer m_Panel_viewer_2D_Moving;
	misImageViewer::Pointer			  m_Panel_viewer_2D_Correlated;
	misVoreenViewer::Pointer		  m_Panel_viewer_3D_Correlated;

	misGPUStandardRepresentation::Pointer m_ImageFixedRepresentor;
	misGPUStandardRepresentation::Pointer m_ImageMovingRepresentor;
	misGPUStandardRepresentation::Pointer m_CorrelatedRepresentation;

	misImageCorrelationPointSelectObserver* m_PointObserver;
	misImageCorrelationWidgetObserver* m_WidgetObserver;

	misColorPointWidget*		  m_FixedWidget;
	misColorPointWidget*		  m_MovingWidget;
	//misColorPointWidget*		  m_CorrelatedWidget;

	misWindow::Pointer   Panel_Renderer_2D_1;
	misWindow::Pointer   Panel_Renderer_2D_2;
	misWindow::Pointer   Panel_Renderer_2D_Correlated;
	misWindow::Pointer   Panel_Renderer_3D_Correlated;

	misOpenglTexture *m_FixedTexture;
	misOpenglTexture *m_MovingTexture;
	 
	TransFuncIntensity *m_FixedVolumeIntensityFunc;
	TransFuncIntensity *m_MovingVolumeIntensityFunc;

	misColorStruct m_FixedColor;
	misColorStruct m_MovingColor;

	double m_FixedImageOpacity;
	double m_MovingImageOpacity;

	bool m_IScalculateButtonClicked ;
	bool m_IsSliderSync;
	int m_PlaneIndex;
	int m_differenceForVieweingWidgets;
public:
	typedef misCorrelationFourViewer		         Self;  
	typedef misObject							 Superclass; 
	typedef ::itk::SmartPointer< Self >			 Pointer; 
	typedef ::itk::SmartPointer< const Self >	 ConstPointer; 

private:
	double UpdateSliders(Object *caller, const EventObject & event);
	void UpdateSliderAfterCorrelation( Object * caller );
	void UpdateSliderBeforeCorrelation( Object * caller );

	void ContrastSetting(Object *caller, const EventObject & event);
	void OnLandmarkSelected(Object *caller, const EventObject & event);
	void InitializeViewer();
	bool ShareContetxInResource();

	void UpdateFixedWidgetPosition( double * OldPos, double newPos );
	void UpdateMovingWidgetPosition( double * OldPos, double newPos );
	void UpdateCorrelatedWidgetPosition( double * OldPos, double newPos );

	void CreateWidgets();
	void ApplyWidgets();

	void InitialPanelviewer2DFixed();
	void InitialPanelviewer2DMoving();
	void InitialPanelviewer2DCorrelated();

 	void SetMovingTexture2MovingRepresentor();

	void SetColorValueOfMovingTexture(misDoubleColorStruct colorVal);
	void SetColorValueOfFixedTexture(misDoubleColorStruct colorVal);

	void SetOpacityValueOfMovingTexture(float opacityValue);
	void SetOpacityValueOfFixedTexture(float opacityValue);

	void SetFixedVolumeTransferFunction();
	void SetMovingVolumeTransferFunction();

	void AddObservers();
	void RemoveObserver();
	void MoveCameratoRepresentationCenter();
	
public:
	static Pointer New(void);
	misCorrelationFourViewer();

	void InintRepresentors();
	void ShowVolumes();
	~misCorrelationFourViewer();
	void SetCorrelationCalculatedFlag(bool val);
	void SetSliderSyncFlag(bool val);
	void SetPlaneIndex(int val);

	void Initialize(misStrctSubTabModel::Pointer  model);
 
	void SetMovingImage(misOpenglTexture* movingImage);
	void SetFixedImage(misOpenglTexture* fixedImage);
	void ChangeCorrelatedImageOpacity(misOpacityAndUID opacityPack);
	void ChangeCorrelatedImageColor(misColorAndUID colorPack);

	void ApplyTrasformToScene();
	void PrepareImagesForMultiPlaneView();
	void ApplyTransformMatrixToTextures(vtkTransform* TextureTransform);
	void AddTransformMatrixToRepresentation(vtkMatrix4x4* TransformMatrix);
	vtkTransform *CalculateTextureTransformMatrix(vtkMatrix4x4* TransformMatrix);

	void SetFixedColor(misColorStruct color);
	void SetMovingColor(misColorStruct color);

	void SetFixedOpacity(double opacity);
	void SetMovingOpacity(double opacity);

	void ReleaseResource();
	void Render();

	misImageViewer* GetFixedViewer();
	misImageViewer* GetMovingViewer();
	misImageViewer* GetCorrelatedViewer();
	misVoreenViewer::Pointer GetVoreenViewer();

	void UpdateImagesInteractionState();

	misOpenglTexture* GetFixedTexture();
	misOpenglTexture* GetMovingTexture();

	misUID GetFixedImageUID();
	misUID GEtMovingImageUID();
	void SetFixedImageUID(misUID val);
	void SetMovingImageUID(misUID val);

	void SetCorrelatedTextureTransform( misPlaneEnum planeIndex, tgt::mat4 pTrans );
	void SetMovingTextureTransform(tgt::mat4 pTrans );

	void SetIntersectionSelectionStatus(bool status);
	void LoadExtensions( vtkRenderWindow *window );

	void WidgetsOn(int index , misCorrelationImageType imageType);
	void WidgetsOff();
	void WidgetOff(misCorrelationImageType imageType);

	void UpdateViewLandmark(int index , misCorrelationImageType imageType);

	void CheckFixedWidgetPosition( double* FixedPos);
	void CheckMovingWidgetPosition( double* MovingPos);
	void CheckFixedLandmarkPosition(double* FixedPos);
	void CheckMovingLandmarkPosition(double* MovingPos);

	void LinkViewerWithWindowsAndlogger();
	TransFuncIntensity* CreateVolumeTransferFunction(misOpenglTexture* texture, misColorStruct color, double opacity);
	
};

#endif
