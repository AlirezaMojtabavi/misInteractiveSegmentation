#include "StdAfx.h"
#include "misPanoramicTransformConverter.h"

#include "misDebug.h"
#include "misMathUtils.h"
#include "misTransform.h"

misPanoramicTransformConverter::misPanoramicTransformConverter( 
	std::shared_ptr<IPanoramicCoordinatesConverter> coordConv /*= nullptr*/, std::shared_ptr<Injector> injector /*= nullptr*/ )
	: m_Injector(injector), m_PanoramicCoordinatesConverter(coordConv)
{
	if (!m_Injector)
		m_Injector = std::make_shared<Injector>();
}

void misPanoramicTransformConverter::SetTransformInImageSpace( std::shared_ptr<const ITransform> objectTransform )
{
	m_InputTransform = objectTransform;
	m_SourceCoordinateSystem = CS_IMAGE;
}

void misPanoramicTransformConverter::SetTransformInPanoramicSpace( std::shared_ptr<const ITransform> objectTransform )
{
	m_InputTransform = objectTransform;
	m_SourceCoordinateSystem = CS_PANORAMIC;
}

std::shared_ptr<ITransform> misPanoramicTransformConverter::GetTransformInImageSpace() const
{
	if (m_SourceCoordinateSystem == CS_IMAGE)
		return m_InputTransform->Clone();
	auto originImage = TransformAndConvertPointFromPanoramicToImage(0, 0, 0);
	auto axisXImage = TransformAndConvertPointFromPanoramicToImage(1, 0, 0) - originImage;
	auto axisYImage = TransformAndConvertPointFromPanoramicToImage(0, 1, 0) - originImage;
	axisXImage.Normalize();
	axisYImage.Normalize();
	auto axisZImage = itk::CrossProduct(axisXImage, axisYImage);

	double conversionMat[] = 
	{
		axisXImage[0],	axisYImage[0],	axisZImage[0],	originImage[0],
		axisXImage[1],	axisYImage[1],	axisZImage[1],	originImage[1],
		axisXImage[2],	axisYImage[2],	axisZImage[2],	originImage[2],
		0,				0,				0,				1
	};
	return m_Injector->CreateTransform(conversionMat);
}

std::shared_ptr<ITransform> misPanoramicTransformConverter::GetTransformInPanoramicSpace() const
{
	if (m_SourceCoordinateSystem == CS_PANORAMIC)
		return m_InputTransform->Clone();

	auto originPano = TransformAndConvertPointFromImageToPanoramic(0, 0, 0);
	auto axisXPano = TransformAndConvertPointFromImageToPanoramic(1, 0, 0) - originPano;
	auto axisYPano = TransformAndConvertPointFromImageToPanoramic(0, 1, 0) - originPano;
	axisXPano.Normalize();
	axisYPano.Normalize();
	auto axisZPano = itk::CrossProduct(axisXPano, axisYPano);

	double conversionMat[] = 
	{
		axisXPano[0],	 axisYPano[0],	 axisZPano[0],	 originPano[0],
		axisXPano[1],	 axisYPano[1],	 axisZPano[1],	 originPano[1],
		axisXPano[2],	 axisYPano[2],	 axisZPano[2],	 originPano[2],
		0,				0,				0,				1
	};
	return m_Injector->CreateTransform(conversionMat);
}

itk::Point<double, 3> misPanoramicTransformConverter::TransformAndConvertPointFromPanoramicToImage( double s, double zp, double n ) const
{
	itk::Point<double, 3> pointImage;
	auto transVtk = misMathUtils::CreateVtkTransform(m_InputTransform);
	auto pointPano = itk::Point<double, 3>(transVtk->TransformDoublePoint(s, zp, n));
	m_PanoramicCoordinatesConverter->SetPanoramicCoordinates(pointPano[0], pointPano[1], pointPano[2]);
	m_PanoramicCoordinatesConverter->GetImageCoordinates(pointImage[0], pointImage[1], pointImage[2]);
	return pointImage;
}

itk::Point<double, 3> misPanoramicTransformConverter::TransformAndConvertPointFromImageToPanoramic( double x, double y, double z ) const
{
	itk::Point<double, 3> pointPano;
	auto transVtk = misMathUtils::CreateVtkTransform(m_InputTransform);
	auto pointImage = itk::Point<double, 3>(transVtk->TransformDoublePoint(x, y, z));
	m_PanoramicCoordinatesConverter->SetImageCoordinates(pointImage[0], pointImage[1], pointImage[2]);
	m_PanoramicCoordinatesConverter->GetPanoramicCoordinates(pointPano[0], pointPano[1], pointPano[2]);
	return pointPano;
}

std::shared_ptr<ITransform> misPanoramicTransformConverter::Injector::CreateTransform(const double matrixElements[16]) const
{
	return std::make_shared<misTransform>(matrixElements);
}
