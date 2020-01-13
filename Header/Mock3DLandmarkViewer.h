
#include "IVolume3DRenderer.h"

MOCK_BASE_CLASS(Mock3DLandmarkViewer, IVolume3DRenderer)
{
	MOCK_NON_CONST_METHOD(SetCurrentLandmarkIndex, 1, void(int val));
	MOCK_NON_CONST_METHOD(SetCurrentLandmarkType, 1, void(misLandmarkType val));
	MOCK_NON_CONST_METHOD(SetCurrentLandmark, 2, void(misLandmarkType ,int ));
	MOCK_NON_CONST_METHOD(SetCurrentLandmarkLableType, 1, void(LANDMARKLABLETYPE val));
	MOCK_NON_CONST_METHOD(SetCaptureLandmarkFlag, 1, void(bool val));
	MOCK_NON_CONST_METHOD(SetUpdateLandmarkFlag, 1, void(bool val));
	MOCK_NON_CONST_METHOD(AddLandmarks, 1, void(std::vector<mislandMarkPosAndStatusStr> landmarkList), identifier_9);
	MOCK_NON_CONST_METHOD(AddLandmarks, 3, void(std::vector<mislandMarkPosAndStatusStr> landmarkList, misLandmarkType landmarkType, 
		LANDMARKLABLETYPE lableType), identifier_10);
	MOCK_NON_CONST_METHOD(RemoveRepresentation, 1, void(std::shared_ptr<IRepresentation> pRepresent));
	MOCK_NON_CONST_METHOD(AddLandmark, 4, void(int index, const double position[3], misLandmarkType category ,
		LANDMARKLABLETYPE lableType ), identifier_11);
	MOCK_NON_CONST_METHOD(AddOrSetNextLandmark, 4, void(int index, const double position[3], misLandmarkType category ,
		LANDMARKLABLETYPE lableType ), identifier_12);
	MOCK_NON_CONST_METHOD(AddNextLandmark, 3, int(const double position[3], misLandmarkType category ,
		LANDMARKLABLETYPE lableType ), identifier_13);
	MOCK_NON_CONST_METHOD(AddOrSetNextLandmark, 3, int(const double position[3], misLandmarkType category ,
		LANDMARKLABLETYPE lableType ), identifier_14);
	MOCK_NON_CONST_METHOD(SetLandmarkPosition, 2, void(int index, const double position[3]));
	MOCK_NON_CONST_METHOD(SetViewCentrePosition, 1, void(const double position[3]));
	MOCK_NON_CONST_METHOD(UpdateLandmarkCameraView, 1, void(int index));
	MOCK_NON_CONST_METHOD(InvalidateLandmark, 1, void(int index));
	MOCK_NON_CONST_METHOD(HideLandmarks, 0, void());
	MOCK_NON_CONST_METHOD(ShowLandmarks, 0, void());
	MOCK_NON_CONST_METHOD(SetToolTransform, 1, void(std::shared_ptr<ITransform> transform));
	MOCK_NON_CONST_METHOD(RemoveLandMarkRepresentations, 0, void());
	MOCK_NON_CONST_METHOD(FindRepresentationByName, 1, std::vector<std::shared_ptr<IRepresentation>>(const std::string& name));
	MOCK_NON_CONST_METHOD(HasRepresentationByName,1,  bool(const std::string& name)) ;

	MOCK_NON_CONST_METHOD(AddCoordinateSytemRenderer, 1, void(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer));
	MOCK_NON_CONST_METHOD(GetLandmarkPosition, 1, double*(int index), identifier_1);
	MOCK_NON_CONST_METHOD(GetLandmarkPosition, 2, double*(int index, misLandmarkType category), identifier_2);
	MOCK_NON_CONST_METHOD(GetLandmarkList, 0, LandmarkListType(void), identifier_15);
	MOCK_NON_CONST_METHOD(GetLandmarkList, 1, misSimplePointListType(misLandmarkType seedType), identifier_3);
	MOCK_NON_CONST_METHOD(ResetLandMarks, 0, void(void), identifier_16);
	MOCK_NON_CONST_METHOD(ResetLandMarks, 1, void(misLandmarkType lndType), identifier_4);
	MOCK_NON_CONST_METHOD(GetCursorService, 0, std::shared_ptr<ICursorService>());
	MOCK_NON_CONST_METHOD(GetScrewWidgetService, 1, std::shared_ptr<IScrewCompound>(misUID uid));
	MOCK_NON_CONST_METHOD(SetROI, 1, void(const double* data), identifier_5);
	MOCK_NON_CONST_METHOD(SetROI, 1, void(misROI data), identifier_6);
	MOCK_NON_CONST_METHOD(InitializeWidget, 2, void(misCursorType ,double));
	MOCK_NON_CONST_METHOD(GetWidgetBoundedActor, 0, vtkProp3D*());
	MOCK_NON_CONST_METHOD(AddRepresentation, 1, void(std::shared_ptr<IRepresentation> pRepresentation));
	MOCK_NON_CONST_METHOD(AddImageOrientation3DModel, 1, void(std::shared_ptr<IRepresentation> pRepresentation));
	MOCK_NON_CONST_METHOD(ProcessRequest, 1, bool(const itk::EventObject* event));
	MOCK_NON_CONST_METHOD(SetCurrentPosition, 1, void(vtkMatrix4x4* info));
	MOCK_NON_CONST_METHOD(SetVolume, 2, void(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction), identifier_7);
	MOCK_NON_CONST_METHOD(SetVolume, 2, void(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs), identifier_8);
	MOCK_NON_CONST_METHOD(PassVolumeMapToRepresentation, 0, void());
	MOCK_NON_CONST_METHOD(ReleaseImageResource, 0, void());
	MOCK_NON_CONST_METHOD(ClippingOn, 0, void());
	MOCK_NON_CONST_METHOD(ClippingOff, 0, void());
	MOCK_NON_CONST_METHOD(ClipingWidgetOn, 0, void());
	MOCK_NON_CONST_METHOD(ClippingWidgetOff, 0, void());
	MOCK_NON_CONST_METHOD(SetClippingPlane, 1, void(tgt::vec4 plane));
	MOCK_NON_CONST_METHOD(SetSupriorView, 0, void());
	MOCK_NON_CONST_METHOD(SetInferiorView, 0, void());
	MOCK_NON_CONST_METHOD(SetAnteriorView, 0, void());
	MOCK_NON_CONST_METHOD(SetPosteriorView, 0, void());
	MOCK_NON_CONST_METHOD(SetLeftView, 0, void());
	MOCK_NON_CONST_METHOD(SetRightView, 0, void());
	MOCK_CONST_METHOD(GetCornerProperties, 0, std::shared_ptr<ICornerProperties>());
	MOCK_NON_CONST_METHOD(InitializeCornerProperties, 0, void());
	MOCK_NON_CONST_METHOD(GetROIBox, 0, misROIWidget*());
	MOCK_NON_CONST_METHOD(GetROICompressData, 0, double *());
	MOCK_NON_CONST_METHOD(ResetROI, 0, void());
	MOCK_NON_CONST_METHOD(ROIWidgetActivation, 1, void(bool activation));
	MOCK_NON_CONST_METHOD(RemoveRenderingVolume, 0, void());
	MOCK_NON_CONST_METHOD(ModifyVolume, 0, void());
	MOCK_NON_CONST_METHOD(CompileVolumeShader, 0, void());
	MOCK_NON_CONST_METHOD(RemoveSegmentedVolume, 0, void());
	MOCK_NON_CONST_METHOD(HighlightScrew, 2, void(misUID screwUID, bool highlight));
	MOCK_NON_CONST_METHOD(OffAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(OnAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(SetAllScrewsLocked, 1, void(bool isLocked));
	MOCK_NON_CONST_METHOD(RemoveAllScrewServices, 0, void());
	MOCK_NON_CONST_METHOD(LockAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(UnlockAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(OnScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(OffScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(DeleteScrew, 1, void(misUID screwUID));
	MOCK_NON_CONST_METHOD(DeleteAllScrews, 0, void());
	MOCK_NON_CONST_METHOD(InitializeScrewWidget, 1, void(misScrewWidgetData initVals), id_1);
	MOCK_NON_CONST_METHOD(SetShowManModel, 1, void(bool val));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 1, void(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter));
	MOCK_NON_CONST_METHOD(SetDentalSpecialViewsEnable, 1, void(bool enabled));
	typedef std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> TextureTransferfunctionMap;
	MOCK_CONST_METHOD(GetVolumeMap, 0, TextureTransferfunctionMap());
	MOCK_NON_CONST_METHOD(SetWindow, 2, void(std::shared_ptr<Iwindows> pWindow, int index));
	MOCK_NON_CONST_METHOD(AddObserver, 2, unsigned long(const itk::EventObject & event, itk::Command *command));
	MOCK_NON_CONST_METHOD(InvokeEvent, 1, void(const itk::EventObject& event));
	MOCK_CONST_METHOD(HasObserver, 1, bool(const itk::EventObject & event));
	MOCK_NON_CONST_METHOD(SetToolPosition, 3, void(double xCoord, double yCoord, double zCoord));
	MOCK_CONST_METHOD(GetTypeDirection, 0, misViewerTypeDirection(void));
	MOCK_CONST_METHOD(GetWindow, 0, std::shared_ptr<Iwindows>());
	MOCK_NON_CONST_METHOD(SetState, 1, void(int val));
	MOCK_NON_CONST_METHOD(UpdateWindowSize, 1, void(misStrctWindowSize &size));
	MOCK_NON_CONST_METHOD(Render, 0, void());
	MOCK_NON_CONST_METHOD(RemoveRepresentationByName, 1, void(std::string name));
	MOCK_NON_CONST_METHOD(InitializeScrewWidget, 2,  void(misScrewWidgetData, IMAGEORIENTATION ), id_2);
	MOCK_NON_CONST_METHOD(GetMainRepresentation, 0,  std::shared_ptr<IRepresentation>  () );
	MOCK_NON_CONST_METHOD(SetMainRepresentation, 2, void(std::shared_ptr<IRepresentation> , IMAGEORIENTATION));
	MOCK_CONST_METHOD(Get3DViewer, 0, std::shared_ptr<I3DViewer> () );
	MOCK_NON_CONST_METHOD(GetRenderer, 0,  vtkRenderer* () );
	MOCK_NON_CONST_METHOD(Reset, 0,  void ());
	MOCK_NON_CONST_METHOD(SetDentalSurgeryType, 1, void(DentalSurgeryType));
	MOCK_NON_CONST_METHOD(MakeCurrentRenderer, 0, void () );
	MOCK_NON_CONST_METHOD(SetViewPort, 1, void(const misViewPort& ));
	MOCK_NON_CONST_METHOD(ZoomIn, 0, void () );
	MOCK_NON_CONST_METHOD(ZoomOut,0, void() );
	MOCK_NON_CONST_METHOD(ResetZoom, 0, void () );
	MOCK_NON_CONST_METHOD(SetObliqueFlag, 1, void(bool ) );
	MOCK_CONST_METHOD(GetMedicalCameraDirection, 0, std::shared_ptr<IMedicalCameraDirection> ());

};