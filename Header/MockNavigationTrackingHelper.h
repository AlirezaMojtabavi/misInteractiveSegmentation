#pragma once

#include "INavigationTrackingHelper.h"

#include "ITrackingStateReporter.h"
#include "misTrackingToolMarkerReporter.h"

MOCK_BASE_CLASS(MockNavigationTrackingHelper, INavigationTrackingHelper)
{
	MOCK_NON_CONST_METHOD(AddTrackerTool, 2,void(std::shared_ptr<misToolRepresentation>, std::shared_ptr<ICoordinateSystemRenderer> ) );
	MOCK_NON_CONST_METHOD(IsNavigationToolVisible, 0, bool());
	MOCK_NON_CONST_METHOD(IsTrackerReportsAvailable, 0, bool());
	MOCK_NON_CONST_METHOD(GenerateToolVisibiltyReport, 0, misTrackingToolMarkerReport( )) ;
	MOCK_NON_CONST_METHOD(UpdateSceneBasedOnToolStatus, 2, void( bool, misUID ));
	MOCK_NON_CONST_METHOD(GetReportAvailabilty, 1, bool( misToolProperties::ApplicationFlag ));
	MOCK_NON_CONST_METHOD(GenerateTrackingReport, 0, misTrackingStateReport());
	MOCK_NON_CONST_METHOD(GetToolStateReporter, 0, std::shared_ptr<ITrackingStateReporter>());
	MOCK_NON_CONST_METHOD(UpdateNavigationToolTransform, 1, void(misUID referenceUID));
	MOCK_CONST_METHOD(GetToolMarkerReporter, 1, std::shared_ptr<misTrackingToolMarkerReporter>(std::shared_ptr<const ITrackingTool>));
	MOCK_NON_CONST_METHOD(UpdateToolData, 1, void(std::shared_ptr<const ITransform> ));
	MOCK_NON_CONST_METHOD(SetCSCorrelationManager,1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >));
	MOCK_CONST_METHOD(GetToolRepresentators , 0, std::vector<std::shared_ptr<misToolRepresentation>>());
	MOCK_CONST_METHOD(GetToolRenderers, 0, std::vector<std::shared_ptr<ICoordinateSystemRenderer>> ()) ;
	MOCK_NON_CONST_METHOD(UpdateVirtualTipLength, 1, void(bool) );
	MOCK_NON_CONST_METHOD(RequestNavigationToolCalibration,0, void());
	MOCK_CONST_METHOD(GetVirtualTipLength, 0, double() );
	MOCK_NON_CONST_METHOD(SetVirtualTipLength, 1, void(double)); 
	MOCK_CONST_METHOD(GetVirtualTipPosition, 0,INavigationTrackingHelper::PointType(void));
	MOCK_CONST_METHOD(GetRealTipPosition,0, INavigationTrackingHelper::PointType(void) );
	MOCK_NON_CONST_METHOD(GetNavigationToolDirection, 1, INavigationTrackingHelper::VectorType(misUID) );
	MOCK_NON_CONST_METHOD(UpdateCalibrationByExtension, 1, void(double) );
	MOCK_NON_CONST_METHOD(GetNavToolTransformToRefImage, 1,std::shared_ptr<const ITransform>(misUID refrenceUid));
	MOCK_NON_CONST_METHOD(GetNavigationToolFaceNormalInImageCoordinate, 1 , parcast::VectorD3(misUID ) );
	MOCK_CONST_METHOD(IsNavigationToolTipVisibleInrefrenceSpace, 0, bool());
	MOCK_CONST_METHOD(GetNavigationToolDynamicFeatureCoordinateSystem, 0, std::string(void));
	MOCK_CONST_METHOD(GetTipPosition, 0, PointType(void));
	MOCK_CONST_METHOD(GetNumberOfLoadedTools, 0, size_t(void));

};