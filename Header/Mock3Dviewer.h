#pragma once

#include "I3DViewer.h"

MOCK_BASE_CLASS(Mock3DViewer, I3DViewer)
{
	MOCK_CONST_METHOD(GetViewerActivity, 0, bool());
	MOCK_NON_CONST_METHOD(SetViewerActivity, 1, void(bool val));
	MOCK_NON_CONST_METHOD(AddAxis, 1, void(misAxisProperty  axis), AddAxis_1);
	MOCK_NON_CONST_METHOD(AddAxis, 3, void(double x, double y, double z), AddAxis_2);
	MOCK_NON_CONST_METHOD(AddRepresentation, 1, void(std::shared_ptr<IRepresentation> pRepresentation));
	MOCK_NON_CONST_METHOD(AddCoordinateSytemRenderer, 1, void(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer));
	MOCK_NON_CONST_METHOD(RemoveRepresentation, 1, void(std::shared_ptr<IRepresentation> pRepresent));
	MOCK_NON_CONST_METHOD(RemoveRepresentationByName, 1, void(std::string name));
	MOCK_NON_CONST_METHOD(FindRepresentationByName, 1, std::vector<std::shared_ptr<IRepresentation>>(const std::string& name));
	MOCK_NON_CONST_METHOD(AddSpatialObject, 1, void(misSpatialObject::Pointer spatialObject));
	MOCK_NON_CONST_METHOD(RemoveSpatialObject, 1, void(misSpatialObject::Pointer spatialObject));
	MOCK_NON_CONST_METHOD(AddAnnotation, 2, void(char* Text, tgt::vec2 position));
	MOCK_NON_CONST_METHOD(Get3dStyleCamera, 0, MIS3DInteractionStyle *());
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(ReleaseRenderingResource, 0, void());
	MOCK_NON_CONST_METHOD(ResetCamera, 0, void());
	MOCK_NON_CONST_METHOD(Render, 0, void());
	MOCK_NON_CONST_METHOD(GetRenderer, 0, vtkRenderer*());
	MOCK_NON_CONST_METHOD(GetRepresentation, 0, RepresentionsListType());
	MOCK_NON_CONST_METHOD(GetNumberOfRepresentations, 0, int());
	MOCK_NON_CONST_METHOD(UpdateRepresentationActors, 0, void());
	MOCK_NON_CONST_METHOD(SetWindow, 2, void(std::shared_ptr<Iwindows> pWindow, int index));
	MOCK_CONST_METHOD(GetWindow, 0, std::shared_ptr<Iwindows>());
	MOCK_CONST_METHOD(GetViewPort, 0, misViewPort());
	MOCK_NON_CONST_METHOD(SetViewPort, 1, void(const misViewPort& val));
	MOCK_NON_CONST_METHOD(SetCroppingDirection, 1, void(misCroppingDirectionInVR croppingDirection));
	MOCK_NON_CONST_METHOD(SetDefaultFocalPoint, 0, void(void));
	MOCK_NON_CONST_METHOD(GetDefaultFocalPoint, 1, void(double focalPoint[3]));
	MOCK_NON_CONST_METHOD(GetMainRepresentation, 0, std::shared_ptr<IRepresentation>());
	MOCK_NON_CONST_METHOD(SetMainRepresentation, 1, void(std::shared_ptr<IRepresentation> pMainRep));
	MOCK_NON_CONST_METHOD(ProcessRequest, 1, bool(const itk::EventObject* event));
	MOCK_NON_CONST_METHOD(SetFPS, 1, void(double fps));
	MOCK_NON_CONST_METHOD(AddFPSRenderer, 0, void());
	MOCK_NON_CONST_METHOD(ShowFPSOn, 0, void());
	MOCK_NON_CONST_METHOD(ShowFPSOff, 0, void());
	MOCK_NON_CONST_METHOD(GetAverageRenderTime, 0, double(void));
	MOCK_CONST_METHOD(GetCoordianteSystemCorrelationManager, 0, std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >());
	MOCK_NON_CONST_METHOD(SetCoordianteSystemCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(UpdateWindowSize, 1, void(misStrctWindowSize &size));
	MOCK_NON_CONST_METHOD(SetTypeDirection, 1, void(misViewerTypeDirection type));
	MOCK_CONST_METHOD(GetTypeDirection, 0, misViewerTypeDirection());
	MOCK_NON_CONST_METHOD(CheckNewRepresentationValidity, 1, bool(std::shared_ptr<IRepresentation> pRepresentation));
	MOCK_CONST_METHOD(GetM_3dStyle, 0, MIS3DInteractionStyle*());
	MOCK_NON_CONST_METHOD(SetM_3dStyle, 1, void(MIS3DInteractionStyle* val));
	MOCK_CONST_METHOD(GetBoundingBox, 0, const double*());
	MOCK_NON_CONST_METHOD(SetBoundingBox, 1, void(double* val));
	MOCK_NON_CONST_METHOD(SetWindowSizeUpdated, 2, void(int val0, int val1));
	MOCK_CONST_METHOD(GetScaleCameraPosition, 0, double());
	MOCK_CONST_METHOD(GetRepresentations, 0, RepresentionsListType());
	MOCK_CONST_METHOD(GetFocalPoint, 0, const double*());
	MOCK_CONST_METHOD(GetIndexInGroup, 0, int());
	MOCK_CONST_METHOD(Get3DStyle, 0, MIS3DInteractionStyle*());
	MOCK_CONST_METHOD(GetCoordinateRenderers, 0, std::vector<std::shared_ptr<ICoordinateSystemRenderer>>());
	MOCK_CONST_METHOD(IsWindowsSizeChanged, 0, bool());
	MOCK_CONST_METHOD(GetWindowSize, 1, void(int* size));
};

