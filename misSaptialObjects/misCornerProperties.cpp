#include "Stdafx.h"
#include "misCornerProperties.h"

#include "DentalImageSliceViewSettings.h"
#include "DentalViewVector.h"
#include "SquareQuadCreator.h"
#include "mis3dVector.h"
#include "misImageSliceViewSettings.h"
#include "VectorRotator.h"

using namespace std;

misCornerProperties::misCornerProperties(misApplicationType appType)
	: m_IsCalculationNecessary(true), 
	m_PlaneOffset(0.0), 
	CameraFocalPointDistanceFromPlane(-1000), 
	CameraPositionDistanceFromPlane(1000),
	m_Transform(vtkMatrix4x4::New()), 
	m_WidgeTransform(vtkMatrix4x4::New()),
	m_AppType(appType)
{
	CreateImageSliceViewSettings();
	Reset();
}

void misCornerProperties::CreateImageSliceViewSettings()
{
	if (m_AppType == misApplicationType::Dental)
	{
		auto vectorRotator = std::make_shared<parcast::VectorRotator>();
		m_DentalViewVector = std::make_shared<parcast::DentalViewVector>(vectorRotator);
		auto squareQuadCreator = std::make_shared<parcast::SquareQuadCreator>();
		auto dentalImageSliceViewSettings = 
			std::make_shared<parcast::DentalImageSliceViewSettings>(m_DentalViewVector, squareQuadCreator);
		m_DentalViewSetting = dentalImageSliceViewSettings;
		m_ViewSetting = dentalImageSliceViewSettings;
	}
	else
	{
		m_ViewSetting = std::make_shared<misImageSliceViewSettings>();
		m_ViewSetting->SetSurgeryType(m_AppType);
	}
}

misCornerProperties::~misCornerProperties()
{
	if(m_Transform)
		m_Transform->Delete();

	if(m_WidgeTransform)
		m_WidgeTransform->Delete();
}

void misCornerProperties::SetMatrix(vtkMatrix4x4* pTrans)
{
	_ASSERT(pTrans);
	if (!pTrans)
		return;
	m_Transform->DeepCopy(pTrans);
	m_Transform->Modified();
	m_IsCalculationNecessary = true;
	m_CornerValidity = true;
}

void misCornerProperties::SetOrientation( IMAGEORIENTATION pOrn )
{
	m_SetUpOrientation = pOrn;
	m_IsCalculationNecessary = true;
}

misSimplePointType misCornerProperties::GetPlaneViewUp()
{
	if (!m_CornerValidity)
		return misSimplePointType();

	PerformCalculations();
	return m_ViewUp;
}

misSimplePointType misCornerProperties::GetPlaneNormal()
{
	if (!m_CornerValidity)
		return misSimplePointType();

	PerformCalculations();
	return m_PlaneNormal;
}

void misCornerProperties::operator=( misCornerProperties* right )
{
	m_Transform->DeepCopy(right->m_Transform);
	m_SetUpOrientation = right->m_SetUpOrientation;	
	m_SightLineIntersectionPoint = right->m_SightLineIntersectionPoint;
	m_ExtentMax = right->m_ExtentMax;
	m_ExtentMin = right->m_ExtentMin;
	m_RealMaxPosition =	right->m_RealMaxPosition;
	m_Spacing = right->m_Spacing;
	m_SliceTextureQuadPoints = right->m_SliceTextureQuadPoints;
	m_PlaneCenter = right->m_PlaneCenter;
	m_IsInObliqueMode = right->m_IsInObliqueMode;
	m_IsCalculationNecessary = right->m_IsCalculationNecessary;
}

void misCornerProperties::SetCurrentPosition( const double* position )
{
	_ASSERT(position != NULL);
	if (!position)
		return;
	m_Transform->Identity();
 	m_Transform->SetElement(0, 3, position[0]);
	m_Transform->SetElement(1, 3, position[1]);
	m_Transform->SetElement(2, 3, position[2]);
	m_Transform->Modified();
	m_CornerValidity = true;
	m_IsCalculationNecessary = true;
}

void misCornerProperties::ResetSightLineIntersectionPoint()
{
	m_SightLineIntersectionPoint.SetPoint(GetCurrentPositionPoint().GetDataPointer());
}

parcast::PointD3  misCornerProperties::GetWidgetPositionWithDistance(double distance) const
{
	_ASSERT(m_CornerValidity);
	if (!m_CornerValidity)
		return {};

	const auto currentPosition = parcast::PointD3(GetCurrentPositionPoint().GetDataPointer());
 
	if (m_SetUpOrientation == UNKnownDirection)
		return currentPosition;

	const auto widgetPoint = CalculateTranslatePoint(currentPosition, distance);
	const auto normal = parcast::VectorD3(m_PlaneNormal.GetItkVector().GetDataPointer());
 	return widgetPoint + normal * m_PlaneOffset;
}

void misCornerProperties::SetImageBounding(const ImageBoundingProperty& prop)
{
	m_CornerValidity = false;

	if ( (prop.Extent[1] == 0)|| (prop.Extent[3] == 0) || (prop.Extent[5] == 0))
	{
		Reset();
		return;
	}

	m_ExtentMin.SetPoint(prop.Extent[0], prop.Extent[2], prop.Extent[4]);
	m_ExtentMax.SetPoint(prop.Extent[1], prop.Extent[3], prop.Extent[5]);
	m_Spacing.SetPoint(prop.Spacing[0], prop.Spacing[1], prop.Spacing[2]);
	
	m_RealMaxPosition = m_ExtentMax;
	m_RealMaxPosition.Minus(m_ExtentMin);
	m_RealMaxPosition.Multiply(m_Spacing);
	m_PlaneCenter = m_RealMaxPosition;
	m_PlaneCenter.Divide(2.0);
	m_CornerValidity = true;
	m_IsCalculationNecessary = true;
}

double * misCornerProperties::GetBounds() const
{
	double* PlaneBounds = nullptr;
	if (m_CornerValidity)
	{
		misSimplePointType minBound = m_ExtentMin;
		minBound.Multiply(m_Spacing);
		misSimplePointType maxBound = m_ExtentMax;
		maxBound.Multiply(m_Spacing);

		PlaneBounds = new double[6];
		PlaneBounds[0] = minBound[0];
		PlaneBounds[1] = maxBound[0];
		PlaneBounds[2] = minBound[1];
		PlaneBounds[3] = maxBound[1];
		PlaneBounds[4] = minBound[2];
		PlaneBounds[5] = maxBound[2];
	}

	return  PlaneBounds;
}

vector<misSimplePointType> misCornerProperties::GetPlanePoints( IMAGEORIENTATION pOrientation )
{
	if (!m_CornerValidity)
		return vector<misSimplePointType>();

	if (pOrientation == UNKnownDirection) 
	{
		vector<misSimplePointType> volumeSize;
		volumeSize.push_back(m_PlaneCenter);
		return volumeSize;
	}

	PerformCalculations();
	return  m_SliceQuadPoints;
}

vector<misSimplePointType> misCornerProperties::GetTexturePoints( IMAGEORIENTATION pOrientation )
{
	m_SliceTextureQuadPoints = GetPlanePoints(pOrientation);

	for (int i = 0; i < m_SliceTextureQuadPoints.size(); i++)
	{
		if (m_SliceTextureQuadPoints[i].validity)
		{
			m_SliceTextureQuadPoints[i].Divide(m_RealMaxPosition);
		}

	}
	return m_SliceTextureQuadPoints;
}

parcast::PointD3  misCornerProperties::CalculateTranslatePoint(parcast::PointD3  currentPos, double distance ) const
{
	misSimplePointType planeNorm =  m_PlaneNormal;
	auto normal = parcast::VectorD3(planeNorm[0], planeNorm[1], planeNorm[2]);
	return currentPos + normal * distance;
 
}

vtkMatrix4x4* misCornerProperties::GetTransform() const
{
	return  m_Transform;	
}

int misCornerProperties::GetCurrentSliceNumber()
{
	if (!m_CornerValidity)
		return -1;

	PerformCalculations();
	return m_CurrentSliceNumber;
}

double misCornerProperties::GetCurrentSlicePosition()
{
	if (!m_CornerValidity)
		return -1;

	PerformCalculations();
	return m_DistanceFromFirstSlice;
}

void misCornerProperties::SetPositionBySliceNumber( int newSliceNumber )
{
	if (!m_CornerValidity)
		return;

	PerformCalculations();

	int currentSliceNumber = GetCurrentSliceNumber();
	int sliceDisplacement = newSliceNumber - currentSliceNumber;
	itk::Vector<double, 3> displacementVector;
	auto currentPosition = GetCurrentPositionPoint();
	itk::Point<double, 3> newPosition;
	if (m_CoordinateConverter && m_SetUpOrientation == SAGITTAL /* Buccolingual*/ && m_AppType == Dental)
	{
		double currentS, currentZp, currentN;
		m_CoordinateConverter->GetPanoramicCoordinates(currentS, currentZp, currentN);
		newPosition = m_CoordinateConverter->EvaluateCurrentSpline(currentS + sliceDisplacement * m_SliceSpacing);
		displacementVector = newPosition - currentPosition;
	}
	else
	{
		displacementVector = m_PlaneNormal.GetItkVector() * (-1.0 * sliceDisplacement * m_SliceSpacing);
		newPosition = currentPosition + displacementVector;
		
	}
	
	SetCurrentPosition(newPosition.GetDataPointer());
	auto newCameraPosition = m_SightLineIntersectionPoint.GetItkPoint() + displacementVector;
	m_SightLineIntersectionPoint.SetPoint(newCameraPosition.GetDataPointer());
}

void misCornerProperties::SetSightLineIntersectionPointToPlaneCenter()
{
	PerformCalculations();
	auto currentPosition = GetCurrentPositionPoint();
	double APlaneEq =  m_PlaneNormal.data[0];
	double BPlaneEq =  m_PlaneNormal.data[1];
	double CPlaneEq =  m_PlaneNormal.data[2];
	double DplaneEq = -(APlaneEq * currentPosition[0]) - (BPlaneEq * currentPosition[1]) - (CPlaneEq * currentPosition[2]);

	double PlaneDistance = /*abs(*/(APlaneEq*m_PlaneCenter.data[0])+(BPlaneEq*m_PlaneCenter.data[1])+(CPlaneEq*m_PlaneCenter.data[2])+DplaneEq/*)*/;

	misSimplePointType planeNormalDistance =  m_PlaneNormal;
	planeNormalDistance.Multiply(PlaneDistance);

	misSimplePointType finalResult = m_PlaneCenter;
	finalResult.Minus(planeNormalDistance);
	m_SightLineIntersectionPoint = finalResult;
	// finalResult.GetPoint(m_CameraPosition);
}

int misCornerProperties::GetMaxSliceNumber()
{
	if (!m_CornerValidity)
		return -1;

	PerformCalculations();
	return m_MaxSliceNumber;
}

parcast::Point<double, 3> misCornerProperties::GetCurrentPosition()
{
	if (!m_CornerValidity)
		return{};

	return parcast::Point<double, 3>(m_Transform->GetElement(0, 3), m_Transform->GetElement(1, 3), m_Transform->GetElement(2, 3));
}

misCornerProperties::PointType misCornerProperties::GetCurrentPositionPoint() const
{
	double currentPosition[] = 
	{
		m_Transform->GetElement(0, 3),
		m_Transform->GetElement(1, 3),
		m_Transform->GetElement(2, 3)
	};
	return PointType(currentPosition);
}

void misCornerProperties::Reset( void )
{
	m_CornerValidity = false;
	m_Transform->Identity();
	m_SetUpOrientation = UNKnownDirection;
	m_PlaneCenter.Reset();
	m_ExtentMin.Reset();
	m_ExtentMax.Reset();
	m_RealMaxPosition.Reset();
	m_Spacing.Reset();
	m_SightLineIntersectionPoint.Reset();
	m_SliceTextureQuadPoints.clear();
	m_SliceTextureQuadPoints.resize(4);
	m_IsInObliqueMode = false;
	m_IsCalculationNecessary = true;
}

void misCornerProperties::SetObliqueMode( bool val )
{
	m_IsInObliqueMode = val;
	m_ViewSetting->SetIsOblique(val);
	m_IsCalculationNecessary = true;
}

void misCornerProperties::SetSightLineIntersectionPointTo( double position[3] )
{
	m_SightLineIntersectionPoint.SetPoint(position);
}

bool misCornerProperties::GetValidity()
{
	return m_CornerValidity;
}

misSimplePointType misCornerProperties::GetPlaneCenter()
{
	return m_PlaneCenter;
}

misSimplePointType misCornerProperties::GetSightLineIntersectionPoint()
{
	if (!m_SightLineIntersectionPoint.validity)
		return misSimplePointType();

	return m_SightLineIntersectionPoint;
}

void misCornerProperties::CalculateViewSettings()
{
	switch(m_SetUpOrientation)
	{
	case AXIAL:
		m_ViewSetting->SetViewPlaceholder(IImageSliceViewSettings::VIEW_PLACEHOLDER_AXIAL);
		break;
	case CORONAL:
		m_ViewSetting->SetViewPlaceholder(IImageSliceViewSettings::VIEW_PLACEHOLDER_CORONAL);
		break;
	case SAGITTAL:
		m_ViewSetting->SetViewPlaceholder(IImageSliceViewSettings::VIEW_PLACEHOLDER_SAGITTAL);
		break;
	}

	m_ViewSetting->SetIsOblique(m_IsInObliqueMode);
	if (m_DentalViewVector)
		m_DentalViewVector->SetRightViewAngularOffset(m_PlanCentricViewAngle);

	if (m_IsInObliqueMode)
	{
		double originAxis[] = { 0, 0, 1 };
		vtkSmartPointer<vtkTransform> pTransform = vtkSmartPointer<vtkTransform>::New();
		pTransform->SetMatrix(m_Transform);
		double* probeDirection = pTransform->TransformDoubleVector(originAxis);
		m_ViewSetting->SetProbeDirection(probeDirection);
	} 

	std::vector<PointType> points;
	double* bounds = GetBounds();
	if (bounds != nullptr)
	{
		mis3DPoint<double> boxBoundMinPoint(bounds[0], bounds[2], bounds[4]);
		mis3DPoint<double> boxBoundMaxPoint(bounds[1], bounds[3], bounds[5]);
		delete bounds;
		misPlaneAndBoxConfiguration planeBoxConfig;
		planeBoxConfig.SetBoxBounds(boxBoundMinPoint, boxBoundMaxPoint);
		planeBoxConfig.SetPlanePoint(GetCurrentPositionPoint());
		planeBoxConfig.SetPlaneOffset(m_PlaneOffset);
		m_ViewSetting->SetPlaneAndBoxConfig(planeBoxConfig);
		auto viewQuad = m_ViewSetting->GetImageSliceQuad();
		auto planeNormal = viewQuad.GetNormal();
		points = viewQuad.GetPoints();
		auto viewUp = m_ViewSetting->GetViewUpVector();
		m_PlaneNormal.SetPoint(planeNormal[0], planeNormal[1], planeNormal[2]);
		m_ViewUp.SetPoint(viewUp[0], viewUp[1], viewUp[2]);
	}

	m_SliceQuadPoints.clear();
	for_each(points.cbegin(), points.cend(), [this](itk::Point<double, 3> point)
	{
		misSimplePointType pt;
		pt.SetPoint(point[0], point[1], point[2]);
		m_SliceQuadPoints.push_back(pt);
	});
}

misQuadGeometry misCornerProperties::GetImageSliceQuad() 
{
	PerformCalculations();
	return m_ViewSetting->GetImageSliceQuad();
}

vtkMatrix4x4* misCornerProperties::GetWidgetTransform()
{
	PerformCalculations();
	return m_WidgeTransform;
}

void misCornerProperties::CalculateSlicingNumbers()
{
	// We're going to calculate maximum slice number, current slice number, and a by-product value of directional spacing.
	// Consider the following line equation in space: x = a.t + x0  ;  y = b.t + y0  ;  z = c.t + z0
	// where (x0, y0, z0) is the coordinates of the current position, and (a, b, c) is the negative of the plane normal.
	// Since the slice numbers advance in the direction opposite to the plane normal we'll use the negative of the normal.
	// The variable t in the above line equation denotes the displacement from the current position along the described line.
	// What we need to find is the biggest and smallest displacements (t_max, t_min) where a plane perpendicular to the line 
	// intersects with image (defined by X_1 and X_2 ... bounds).
	// The plane equation at t is:
	// a ( x - (a.t + x0) )  +  b ( y - (b.t + y0) )  +  c ( z - (c.t + z0) )  =  0
	// Writing in terms of t, and noting that a^2 + b^2 + c^2 = 1 as the vector is normalized, we obtain:
	// t = a ( x - x0 )  +  b ( y - y0 )  +  c ( z - z0 )
	// To find t_min and t_max we simply evaluate t for all eight vertices of the image cuboid rather than every point in the image
	// and it's mathematically verifiable that no other point on the image will yield a t outside the calculated range.
	double* bounds = GetBounds();
	if (!bounds)
		return;
	double Xs[] = { bounds[0], bounds[1] } ;
	double Ys[] = { bounds[2], bounds[3] } ;
	double Zs[] = { bounds[4], bounds[5] } ;
	delete bounds;

	auto currentPosition = GetCurrentPositionPoint();
	double a = -m_PlaneNormal[0], b = -m_PlaneNormal[1], c = -m_PlaneNormal[2];
	double x0 = currentPosition[0], y0 = currentPosition[1], z0 = currentPosition[2];
	double minT = 0, maxT = 0;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				double t = a * (Xs[i] - x0) + b * (Ys[j] - y0) + c * (Zs[k] - z0);
				maxT = t > maxT ? t : maxT;
				minT = t < minT ? t : minT;
			}

	// Current slice has a displacement of t = 0. Therefore, -t_min is displacement from first slice to the current:
	m_DistanceFromFirstSlice = -minT;
	m_CurrentSliceNumber = m_DistanceFromFirstSlice / m_SliceSpacing;

	// t_max - t_min is the whole length of the line
	m_MaxSliceNumber = (maxT - minT) / m_SliceSpacing;
}

void misCornerProperties::CalculateBuccolingualSlicingNumbers()
{	
	double panoramicZpCoord, panoramicNCoord;
	m_CoordinateConverter->GetPanoramicCoordinates(m_DistanceFromFirstSlice, panoramicZpCoord, panoramicNCoord);
	auto curveLength = m_CoordinateConverter->GetCurrentSplineLength();
	m_MaxSliceNumber = curveLength / m_SliceSpacing;
	m_CurrentSliceNumber = m_DistanceFromFirstSlice / m_SliceSpacing;
}

void misCornerProperties::CalculateMesiodistalSlicingNumbers()
{
	const double MaxMesiodistalRangeLength = 20;
	double panoramicSCoord, panoramicZpCoord, panoramicNCoord;
	m_CoordinateConverter->GetPanoramicCoordinates(panoramicSCoord, panoramicZpCoord, panoramicNCoord);
	m_MaxSliceNumber = MaxMesiodistalRangeLength / m_SliceSpacing;
	m_DistanceFromFirstSlice = 
		std::min(std::max(MaxMesiodistalRangeLength / 2 - panoramicNCoord, 0.0), MaxMesiodistalRangeLength);
	m_CurrentSliceNumber = m_DistanceFromFirstSlice / m_SliceSpacing;
}

void misCornerProperties::PerformCalculations()
{
	if (!m_IsCalculationNecessary)
		return;

	CalculateViewSettings();
	CalculateSliceSpacing();
	if (m_CoordinateConverter && m_AppType == Dental)
		switch(m_SetUpOrientation)
		{
		case SAGITTAL:
			CalculateBuccolingualSlicingNumbers();
			break;
		case CORONAL:
			CalculateMesiodistalSlicingNumbers();
			break;
		default:
			CalculateSlicingNumbers();
		}
	else
		CalculateSlicingNumbers();
	CalculateWidgetTransform();

	m_IsCalculationNecessary = false;
}

void misCornerProperties::CalculateWidgetTransform()
{
	if (!m_WidgeTransform)
		return;

	// Transform needs to align x, y, z axes with the three display vectors (view-up, view-side, and normal) and translate 
	// the origin to current position. Therefore, the first three columns of the transform matrix is composed of these three
	// vectors. The last column is filled with the position.
	auto planePoint = GetCurrentPositionPoint();

	mis3DVector<double> col1(1.0, 0.0, 0.0), col2(0.0, 1.0, 0.0), col3(0.0, 0.0, 1.0);
	m_ViewSetting->SetViewPlaceholder(IImageSliceViewSettings::VIEW_PLACEHOLDER_CORONAL);
	auto quad = m_ViewSetting->GetImageSliceQuad();
	auto normal = quad.GetNormal();
	auto viewUp = m_ViewSetting->GetViewUpVector();
	auto viewRight = itk::CrossProduct(viewUp, normal);
	col1 = viewRight;
	col2 = normal;
	col3 = -viewUp;

	m_WidgeTransform->SetElement(0, 0, col1[0]);
	m_WidgeTransform->SetElement(1, 0, col1[1]);
	m_WidgeTransform->SetElement(2, 0, col1[2]);
	m_WidgeTransform->SetElement(3, 0, 0);
	m_WidgeTransform->SetElement(0, 1, col2[0]);
	m_WidgeTransform->SetElement(1, 1, col2[1]);
	m_WidgeTransform->SetElement(2, 1, col2[2]);
	m_WidgeTransform->SetElement(3, 1, 0);
	m_WidgeTransform->SetElement(0, 2, col3[0]);
	m_WidgeTransform->SetElement(1, 2, col3[1]);
	m_WidgeTransform->SetElement(2, 2, col3[2]);
	m_WidgeTransform->SetElement(3, 2, 0);
	m_WidgeTransform->SetElement(0, 3, planePoint[0]);
	m_WidgeTransform->SetElement(1, 3, planePoint[1]);
	m_WidgeTransform->SetElement(2, 3, planePoint[2]);
	m_WidgeTransform->SetElement(3, 3, 1);
}

void misCornerProperties::CalculateSliceSpacing()
{
	double a = -m_PlaneNormal[0], b = -m_PlaneNormal[1], c = -m_PlaneNormal[2];
	// Absolute values are taken since spacing values are unsigned.
	m_SliceSpacing = sqrt(pow((m_Spacing[0] * a), 2) + pow((m_Spacing[1] * b), 2) + pow((m_Spacing[2] * c), 2));
}

parcast::PointD3 misCornerProperties::GetCameraPosition() const
{
	_ASSERT(m_CornerValidity);
	if (!m_CornerValidity)
		return{};
	return CalculateTranslatePoint(parcast::PointD3(m_SightLineIntersectionPoint.data), CameraPositionDistanceFromPlane);
}

parcast::PointD3 misCornerProperties::GetCameraFocalPoint() const
{
	_ASSERT(m_CornerValidity);
	if (!m_CornerValidity)
		return {};
	 return  CalculateTranslatePoint(parcast::PointD3(m_SightLineIntersectionPoint.data), CameraFocalPointDistanceFromPlane);
}

double misCornerProperties::GetCameraDistanceToPlane() const
{
	return CameraPositionDistanceFromPlane;
}

double misCornerProperties::GetSliceSpacing()
{
	if (!m_CornerValidity)
		return -1;

	PerformCalculations();
	return m_SliceSpacing;
}

void misCornerProperties::ApplyOfsset( double offset )
{
	m_PlaneOffset = offset;
	m_IsCalculationNecessary = true;
}

double misCornerProperties::GetImagePlaneOffset() const
{
	return m_PlaneOffset;
}

void misCornerProperties::SetImageSliceViewerZoomFactor( double zoomFactor )
{
	m_ViewSetting->SetZoomFactor(zoomFactor);
}

void misCornerProperties::SetDentalSurgeryType( DentalSurgeryType surgeryType )
{
	m_DentalViewSetting->SetDentalSurgeryType(surgeryType);
	m_IsCalculationNecessary = true;
}

void misCornerProperties::SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
{
	m_CoordinateConverter = coordinateConverter;
	m_DentalViewSetting->SetPanoramicCoordinateConverter(coordinateConverter);
	m_IsCalculationNecessary = true;
}

std::shared_ptr<const IPanoramicCoordinatesConverter> misCornerProperties::GetPanoramicCoordinateConverter() const
{
	return m_CoordinateConverter;
}

void misCornerProperties::SetPlanCentricViewAngle(double angle)
{
	m_PlanCentricViewAngle = angle;
	m_IsCalculationNecessary = true;
}
