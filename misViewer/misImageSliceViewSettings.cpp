#include "StdAfx.h"
#include "misImageSliceViewSettings.h"
#include "misEnums.h"
#include "misMathUtils.h"
#include "misPointArrangementAlgorithm.h"
#include "misApplication.h"

misImageSliceViewSettings::misImageSliceViewSettings()
	: m_IsOblique(false), m_ViewPlaceholder(VIEW_PLACEHOLDER_AXIAL),
	m_IsCalculationNecessary(true),	SuperiorToInferiorUnitVector(0, 0, 1), PosteriorToAnteriorUnitVector(0, 1, 0),
	DexterToSinisterUnitVector(1, 0, 0), m_ZoomFactor(1.2)
{
}

misImageSliceViewSettings::~misImageSliceViewSettings(void)
{
}

const misPlaneAndBoxConfiguration & misImageSliceViewSettings::GetPlaneAndBoxConfig() const
{
	return m_PlaneAndBoxConfig;
}

void misImageSliceViewSettings::SetPlaneAndBoxConfig( const misPlaneAndBoxConfiguration &config )
{
	m_PlaneAndBoxConfig = config;
	// Apparently, the maximum slice side length is the magnitude of the image cuboid diagonal.
	mis3DPoint<double> boxPoint1, boxPoint2;
	m_PlaneAndBoxConfig.GetBoxBounds(boxPoint1, boxPoint2);
	m_QuadSideHalfLength = (boxPoint2 - boxPoint1).GetNorm() / 2.0 / m_ZoomFactor;
	m_IsCalculationNecessary = true;
}

bool misImageSliceViewSettings::IsOblique() const
{
	return m_IsOblique;
}

void misImageSliceViewSettings::SetIsOblique( bool isOblique )
{
	m_IsOblique = isOblique;
	m_IsCalculationNecessary = true;
}

const misImageSliceViewSettings::VectorType & misImageSliceViewSettings::GetPlaneNormalVector() const
{
	return m_ProbeDirection;
}

void misImageSliceViewSettings::SetProbeDirection( const VectorType &vec )
{
	m_ProbeDirection = vec;
	m_IsCalculationNecessary = true;
}

misImageSliceViewSettings::ViewPlaceholderType misImageSliceViewSettings::GetViewPlaceholder() const
{
	return m_ViewPlaceholder;
}

void misImageSliceViewSettings::SetViewPlaceholder( ViewPlaceholderType val )
{
	m_ViewPlaceholder = val;
	m_IsCalculationNecessary = true;
}

misApplicationType misImageSliceViewSettings::GetSurgeryType() const
{
	return m_AppType;
}

misQuadGeometry misImageSliceViewSettings::GetImageSliceQuad()
{
	PerformCalculations();
	return m_ImageSliceQuad;
}

IImageSliceViewSettings::VectorType misImageSliceViewSettings::GetViewUpVector()
{
	PerformCalculations();
	return m_ViewUpVector;
}

void misImageSliceViewSettings::SetSurgeryType(misApplicationType appType)
{
	m_AppType = appType;
}

double misImageSliceViewSettings::GetZoomFactor()
{
	return m_ZoomFactor;
}

void misImageSliceViewSettings::PerformCalculations()
{
	if (!m_IsCalculationNecessary)
		return;

	VectorType axialVec, coronalVec, sagittalVec;
	ComputeOrthogonalVectors(axialVec, coronalVec, sagittalVec);

	VectorType horizontalVec, verticalVec;
	switch (m_ViewPlaceholder)
	{
	case VIEW_PLACEHOLDER_AXIAL:
		verticalVec = m_AppType == misApplicationType::Spine ? -coronalVec : coronalVec;
		horizontalVec = m_AppType == misApplicationType::Spine ? -sagittalVec : sagittalVec;
		break;
	case VIEW_PLACEHOLDER_CORONAL:
		horizontalVec = m_AppType == misApplicationType::Spine ? -sagittalVec : sagittalVec;
		verticalVec = -axialVec;
		break;
	case VIEW_PLACEHOLDER_SAGITTAL:
		horizontalVec = m_AppType == misApplicationType::NeroSurgery ? -coronalVec : coronalVec;
		verticalVec = -axialVec;
		break;
	}

	auto normalVec = itk::CrossProduct(horizontalVec, verticalVec);
	normalVec.Normalize();
	PointType quadCentre = m_PlaneAndBoxConfig.GetPlanePoint() - (normalVec * m_PlaneAndBoxConfig.GetPlaneOffset());
	std::vector<PointType> quadVertices(4);	// horizontal x vertical = normal, right-handed unit vectors
	quadVertices[0] = quadCentre + (horizontalVec * m_QuadSideHalfLength) + (verticalVec * m_QuadSideHalfLength);
	quadVertices[1] = quadCentre - (horizontalVec * m_QuadSideHalfLength) + (verticalVec * m_QuadSideHalfLength);
	quadVertices[2] = quadCentre - (horizontalVec * m_QuadSideHalfLength) - (verticalVec * m_QuadSideHalfLength);
	quadVertices[3] = quadCentre + (horizontalVec * m_QuadSideHalfLength) - (verticalVec * m_QuadSideHalfLength);

	m_ImageSliceQuad.SetPoints(quadVertices);
	m_ViewUpVector = verticalVec;
	m_IsCalculationNecessary = false;
}

void misImageSliceViewSettings::ComputeOrthogonalVectors( VectorType& axial, VectorType& coronal, VectorType& sagittal )
{
	if (m_AppType == misApplicationType::Spine)
		coronal = m_IsOblique ? m_ProbeDirection : PosteriorToAnteriorUnitVector;
	else

		coronal = m_IsOblique ? -m_ProbeDirection : PosteriorToAnteriorUnitVector;
	
	coronal.Normalize();
	axial = itk::CrossProduct(DexterToSinisterUnitVector, coronal);
	axial.Normalize();
	sagittal = itk::CrossProduct(coronal, axial);
}

void misImageSliceViewSettings::SetZoomFactor( double zoomFactor )
{
	m_ZoomFactor = zoomFactor;
}