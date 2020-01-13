#pragma once

#include "Adapters/IDentalViewVector.h"
#include "IDentalImageSliceViewSettings.h"
#include "IImageSliceViewSettings.h"
#include "IPanoramicCoordinatesConverter.h"
#include "VisualizationGeneralTypes.h"
#include "misEnums.h"
#include "misEnums.h"
#include "misObject.h"
#include "misSimplePointType.h"
#include "misTexturePropertyStruct.h"
#include "misVideoStruct.h"
#include "BusinessEntities\Point.h"
#include "ICornerProperties.h"

class misCornerProperties :public ICornerProperties
{
public:

	// Creates a misCornerProperties object using the specified injector or the default injector.
	misCornerProperties(misApplicationType appType);
	~misCornerProperties();

	void operator = (misCornerProperties* right);

	bool GetValidity() override;
	vtkMatrix4x4* GetTransform() const override;
	vtkMatrix4x4* GetWidgetTransform() override;
	parcast::PointD3 GetWidgetPositionWithDistance(double distance) const  override;
	parcast::PointD3 GetCameraPosition() const override;
	parcast::PointD3 GetCameraFocalPoint() const override;
	double GetCameraDistanceToPlane() const  override;
 	double* GetBounds() const override;
	std::vector<misSimplePointType> GetTexturePoints(IMAGEORIENTATION pOrientation) override;
 	std::vector<misSimplePointType> GetPlanePoints(IMAGEORIENTATION pOrientation)  override;
 	misSimplePointType GetPlaneViewUp() override;
 	misSimplePointType GetPlaneNormal() override;
 	misSimplePointType GetPlaneCenter() override;
	int GetCurrentSliceNumber() override;
	int GetMaxSliceNumber() override;
	double GetCurrentSlicePosition() override;
	double GetSliceSpacing() override;
	void SetPositionBySliceNumber(int newSliceNumber) override;
	parcast::Point<double, 3> GetCurrentPosition() override;
	ICornerProperties::PointType GetCurrentPositionPoint() const override;
	void SetCurrentPosition(const double* position) override;
	void SetMatrix(vtkMatrix4x4* pTrans) override;
	void SetOrientation(IMAGEORIENTATION pOrn) override;
	void SetObliqueMode(bool val) override;
	void SetSightLineIntersectionPointTo(double position[3]) override;
	void SetSightLineIntersectionPointToPlaneCenter() override;
	void ResetSightLineIntersectionPoint() override;
	misSimplePointType GetSightLineIntersectionPoint() override;
	void SetImageBounding(const ImageBoundingProperty& prop) override;
	void Reset(void) override;
	misQuadGeometry GetImageSliceQuad() override;
 	void ApplyOfsset(double offset) override;
	double GetImagePlaneOffset() const override;
	void SetImageSliceViewerZoomFactor(double zoomFactor) override;
	void SetDentalSurgeryType(DentalSurgeryType surgeryType) override;
	void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter) override;
	std::shared_ptr<const IPanoramicCoordinatesConverter> GetPanoramicCoordinateConverter() const override;

	void SetPlanCentricViewAngle(double angle) override;

private:
	const double CameraPositionDistanceFromPlane;
	const double CameraFocalPointDistanceFromPlane;

	void CreateImageSliceViewSettings();

	// Gets a point at the given distance from the centre of the plane along the plane normal direction. Used to calculate
	// camera position and focal point as well as widget position.
	parcast::PointD3 CalculateTranslatePoint(parcast::PointD3  currentPos, double distance ) const;

	// Calculates and updates m_ViewUp, m_PlaneNormal, m_SliceQuadPoints members before they're used. It uses m_ViewSetting and
	// the input given to corner properties.
	void CalculateViewSettings();

	// CalculateSlicingNumbers() calculates and updates m_MaxSliceNumber, m_CurrentSliceNumber, m_DirectionalSpacing members. It
	// uses m_CurrentPosition and also m_calculated which must be updated previously by a call to CalculateViewSettings.
	void CalculateSlicingNumbers();

	void CalculateBuccolingualSlicingNumbers();
	void CalculateMesiodistalSlicingNumbers();

	// CalculateWidgetTransform() calculates and updates m_WidgeTransform. It uses values previously calculated by 
	// CalculateViewSettings() and must be called after that.
	void CalculateWidgetTransform();

	void CalculateSliceSpacing();
	// Performs ViewSettings, WidgetTransform and SlicingNumbers calculations if a recalculation is necessary (due to a change 
	// to class inputs)
	void PerformCalculations();

	std::shared_ptr<IImageSliceViewSettings> m_ViewSetting;	// Used by CalculateViewSettings
	std::shared_ptr<IDentalImageSliceViewSettings> m_DentalViewSetting;	// Used by CalculateViewSettings

	int m_MaxSliceNumber;	// See CalculateSlicingNumbers(), GetMaxSliceNumber()
	int m_CurrentSliceNumber;	// See CalculateSlicingNumbers(), GetCurrentSliceNumber()
	double m_DistanceFromFirstSlice;	// See GetCurrentSlicePosition()
	double m_SliceSpacing;	// See CalculateSlicingNumbers(), GetSliceSpacing()

	misSimplePointType m_ViewUp;	// See CalculateViewSettings(), GetPlaneViewUp()
	misSimplePointType m_PlaneNormal;	// See CalculateViewSettings(), GetPlaneNormal()
	std::vector<misSimplePointType> m_SliceQuadPoints;	// See CalculateViewSettings(), GetPlanePoints()
	std::vector<misSimplePointType> m_SliceTextureQuadPoints;
	vtkMatrix4x4* m_WidgeTransform;	// See GetWidgetTransform()


	bool                m_CornerValidity;
	IMAGEORIENTATION	m_SetUpOrientation;	// See SetOrientation()
	misSimplePointType	m_SightLineIntersectionPoint;	// See GetSightLineIntersectionPoint()

	misSimplePointType m_ExtentMin;	//
	misSimplePointType m_ExtentMax;
	misSimplePointType m_Spacing;
	misSimplePointType m_RealMaxPosition;
	misSimplePointType m_PlaneCenter;	
	
	double m_PlanCentricViewAngle = 0;
	vtkMatrix4x4* m_Transform;	// See SetMatrix()
	bool m_IsInObliqueMode;	// See SetObliqueMode(), See GetObliqueMode()
	bool m_IsCalculationNecessary;	// Used to track whether output values require recalculation (if input values are altered)
	double m_PlaneOffset;//used to apply distance between plane in one direction
	std::shared_ptr<const IPanoramicCoordinatesConverter> m_CoordinateConverter;
	std::shared_ptr<parcast::IDentalViewVector> m_DentalViewVector;
	misApplicationType m_AppType;
};