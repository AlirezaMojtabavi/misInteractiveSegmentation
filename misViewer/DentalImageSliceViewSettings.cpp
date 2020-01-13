#include "stdafx.h"
#include "DentalImageSliceViewSettings.h"
#include "IPanoramicCoordinatesConverter.h"
#include "DentalSurgeryType.h"
#include "mis3dVector.h"

using namespace parcast;

DentalImageSliceViewSettings::DentalImageSliceViewSettings(
	std::shared_ptr<IDentalViewVector> viewVector, std::shared_ptr<ISquareQuadCreator> squareCreator)
	: m_SquareQuadCreator(squareCreator),
	m_DentalViewVector(viewVector),
	m_ZoomFactor(1),
	m_ViewPlaceholder(VIEW_PLACEHOLDER_AXIAL),
	m_IsOblique(false),
	m_ProbeDirection(mis3DVector<double>(0, 0, -1)),
	m_SurgeryType(DentalSurgeryType::MAXILLA)
{
}

void DentalImageSliceViewSettings::SetZoomFactor(double zoomFactor)
{
	m_ZoomFactor = zoomFactor;
}

const misPlaneAndBoxConfiguration & DentalImageSliceViewSettings::GetPlaneAndBoxConfig() const
{
	return m_PlaneAndBoxConfig;
}

void DentalImageSliceViewSettings::SetPlaneAndBoxConfig(const misPlaneAndBoxConfiguration & config)
{
	m_PlaneAndBoxConfig = config;
}

const IImageSliceViewSettings::VectorType & DentalImageSliceViewSettings::GetPlaneNormalVector() const
{
	return m_ProbeDirection;
}

void DentalImageSliceViewSettings::SetProbeDirection(const VectorType & vect)
{
	m_ProbeDirection = vect;
}

IImageSliceViewSettings::ViewPlaceholderType DentalImageSliceViewSettings::GetViewPlaceholder() const
{
	return m_ViewPlaceholder;
}

void DentalImageSliceViewSettings::SetViewPlaceholder(ViewPlaceholderType val)
{
	m_ViewPlaceholder = val;
}

void DentalImageSliceViewSettings::SetIsOblique(bool isOblique)
{
	m_IsOblique = isOblique;
}

bool DentalImageSliceViewSettings::IsOblique() const
{
	return m_IsOblique;
}

misApplicationType DentalImageSliceViewSettings::GetSurgeryType() const
{
	return Dental;
}

IImageSliceViewSettings::VectorType DentalImageSliceViewSettings::GetViewUpVector()
{
	auto viewVecs = GetViewVectors();
	return itk::Vector<double, 3>(viewVecs.UpView.Elements());
}

misQuadGeometry DentalImageSliceViewSettings::GetImageSliceQuad()
{
	auto viewVecs = GetViewVectors();

	mis3DPoint<double> boxPoint1, boxPoint2;
	m_PlaneAndBoxConfig.GetBoxBounds(boxPoint1, boxPoint2);
	auto quadSideHalfLength = (boxPoint2 - boxPoint1).GetNorm() / 2.0 / m_ZoomFactor;

	Point<double, 3> planePoint(m_PlaneAndBoxConfig.GetPlanePoint().GetDataPointer());
	auto planeOffset = m_PlaneAndBoxConfig.GetPlaneOffset();
	auto normalVec = VectorMath::CrossProduct(viewVecs.RightView, viewVecs.UpView);
	auto quadCentre = planePoint - (normalVec * planeOffset);
	auto quadPoints = m_SquareQuadCreator->Create(viewVecs, quadCentre, quadSideHalfLength);

	std::vector<PointType> quadItkPoints(quadPoints.size());
	std::transform(quadPoints.begin(), quadPoints.end(), quadItkPoints.begin(),
		[&quadPoints](const parcast::Point<double, 3>& pt) { return itk::Point<double, 3>(pt.Elements()); });

	misQuadGeometry imageSliceQuad;
	imageSliceQuad.SetPoints(quadItkPoints);

	return imageSliceQuad;
}

void DentalImageSliceViewSettings::SetSurgeryType(misApplicationType appType)
{
}

void DentalImageSliceViewSettings::SetPanoramicCoordinateConverter(
	std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
{
	m_CoordinateConverter = coordinateConverter;
}

void DentalImageSliceViewSettings::SetDentalSurgeryType(DentalSurgeryType surgeryType)
{
	m_SurgeryType = surgeryType;
}

ViewVectors DentalImageSliceViewSettings::GetViewVectors() const
{
	auto curveTangentialVector = m_CoordinateConverter == nullptr ? Vector<double, 3>(1.0, 0.0, 0.0) :
		Vector<double, 3>(m_CoordinateConverter->GetCurrentTangentialVector().GetDataPointer());

	auto probeDir = m_IsOblique ? Vector<double, 3>(m_ProbeDirection.GetDataPointer()) :
		m_SurgeryType == DentalSurgeryType::MANDIBLE ? Vector<double, 3>(0.0, 0.0, 1.0) :
		Vector<double, 3>(0.0, 0.0, -1.0);

	m_DentalViewVector->SetViewDirections(probeDir, curveTangentialVector);

	switch (m_ViewPlaceholder)
	{
	case IImageSliceViewSettings::VIEW_PLACEHOLDER_AXIAL:
		return m_DentalViewVector->CalculateOcclusalView();
	case IImageSliceViewSettings::VIEW_PLACEHOLDER_CORONAL:
		return m_DentalViewVector->CalculateMesiodistalView();
	case IImageSliceViewSettings::VIEW_PLACEHOLDER_SAGITTAL:
		return m_DentalViewVector->CalculateBuccolingualView();
	}
	return ViewVectors();
}

double DentalImageSliceViewSettings::GetZoomFactor()
{
	return m_ZoomFactor;
}
