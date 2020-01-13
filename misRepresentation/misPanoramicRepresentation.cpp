#include "StdAfx.h"
#include "misPanoramicRepresentation.h"

#include "misImageSlicerAbstract.h"
#include "misImageSlicerMapper.h"
#include "misImageToTextureMap.h"
#include "misPanoramicTextureGenerator.h"
#include "misPlaneContrast.h"
#include "misTransFunctionBuilder.h"
#include "misDistributionEvent.h"

misPanoramicRepresentation::misPanoramicRepresentation(std::shared_ptr<IRepresentation> mainRep)
	: m_MainRepresentation(mainRep), 
	m_PanoramicMapper(vtkSmartPointer<misPanoramicMapper>::New()), 
	m_Actor(vtkSmartPointer<vtkActor>::New()), 
	m_PanoramicSliceResolution(1), 
	m_PanoramicSliceRange(40),
	m_PanoramicCurveResolution(1), 
	m_Precision(0.1), 
	m_Image(nullptr),
	m_ImageTexture(nullptr)
{
	m_Actor->SetMapper(m_PanoramicMapper);
	m_MainRepresentation->AddProp(m_Actor);
	
}

void misPanoramicRepresentation::SetPanoramicCurve(const std::vector<PointType>& points)
{
	if(!m_Image)
		return;

	auto textureGenerator = std::make_shared<misPanoramicTextureGenerator>(points, m_PanoramicCurveResolution,
		m_PanoramicSliceResolution, m_PanoramicSliceRange, m_Image->GetROI().GetWidth(), m_Image->GetROI().GetHeight(), m_Precision);
	auto panoramicToImageTexture = textureGenerator->GetPanoramicTexture();
	float* pixelData = new float[panoramicToImageTexture->Data.size()];
	std::copy(panoramicToImageTexture->Data.cbegin(), panoramicToImageTexture->Data.cend(), pixelData);
	m_PanoramicMapper->SetPanoramicTextureData(pixelData, panoramicToImageTexture->Width, panoramicToImageTexture->Height);
}

void misPanoramicRepresentation::SetImage(std::shared_ptr<IImage> image)
{
	m_Image = image;
	misImageToTextureMap* textureHandler = misImageToTextureMap::GetInstance();	 
	m_ImageTexture = textureHandler->LookUpTexture(image); 
	m_PanoramicMapper->SetImage(m_ImageTexture->getId());
	InitializeInformation();
	misTransFunctionBuilder builder;
	auto colorMapTexture = builder.GenerateTransferFunction(m_WinLevel, m_Information.m_showErased, 
		m_ImageTexture->GetTexturePropertyStrct().GetTableRange(), m_Information.m_ErasedObjectColor);
	m_PanoramicMapper->SetTransferFunctionID(colorMapTexture);
	auto imageRoi = image->GetROI();
	const int ExpansionDirections = 2;
	m_PanoramicMapper->SetDepth(ExpansionDirections * m_PanoramicSliceRange);
	m_PanoramicMapper->SetHeight(imageRoi.GetDepth());
}

std::shared_ptr<IImage> misPanoramicRepresentation::GetImage()
{
	return m_Image;
}

void misPanoramicRepresentation::SetWindowLevel(misWindowLevelStr windowLevel )
{
	if (!m_ImageTexture)
		return;

	m_PanoramicMapper->SetRange(m_ImageTexture->GetTexturePropertyStrct().GetTableRange());
	m_PanoramicMapper->SetWindowLevel(windowLevel);

	misPlaneContrastEvent  ev;
	misPlaneIndexWinLevStr PlaneWinLevStr;
	PlaneWinLevStr.WinLev = windowLevel;
	PlaneWinLevStr.PlaneIndex = FirstImage;
	ev.Set(PlaneWinLevStr);
	m_MainRepresentation->InvokeEvent(ev);
}

misWindowLevelStr misPanoramicRepresentation::GetWindowLevel()
{
	return m_PanoramicMapper->GetWindowLevel();
}

void misPanoramicRepresentation::SetCurveLength( double val )
{
	m_PanoramicMapper->SetWidth(val);
}

void misPanoramicRepresentation::SetSlice(double slice)
{
	m_PanoramicMapper->SetSlice(slice);
}

void misPanoramicRepresentation::InitializeInformation()
{
	m_Information.m_showErased = false;
	m_Information.m_ErasedObjectColor = misColorStruct(255, 0, 0, 255);
	m_WinLevel.SetWindowParams(605, 1750);
}

void misPanoramicRepresentation::ApplyDefaultVisibilityMap(const std::map<misPlaneEnum, bool>& imageVisibiltes)
{
}

misUID misPanoramicRepresentation::GetImageUID(misPlaneEnum planeIndex)
{
	return {};
}

void misPanoramicRepresentation::ApplyTransformToScene(misPlaneEnum sourcePlane, misPlaneEnum targetPlane,
	vtkSmartPointer<vtkTransform> transform)
{
}

std::shared_ptr<IImage> misPanoramicRepresentation::GetImage(misPlaneEnum planeIndex)
{
	return {};
}

void misPanoramicRepresentation::RemovePlane(int planeindex)
{
}

void misPanoramicRepresentation::SetImageSource(std::shared_ptr<IImage> pImage, misPlaneEnum planeIndex,
	misLayerEnum layerIndex)
{
}

void misPanoramicRepresentation::SetTextureID(misPlaneEnum planeIndex, misLayerEnum layerIndex, int val)
{
}

void misPanoramicRepresentation::SetMinOpacityForSettingWinLev(double threshold)
{
}

void misPanoramicRepresentation::SetTexture(misOpenglTexture* pTexture)
{
}

void misPanoramicRepresentation::SetTexture(misOpenglTexture* pTexture, misPlaneEnum planeIndex)
{
}

void misPanoramicRepresentation::SetTexture(misLayerEnum layerIndex, misOpenglTexture* pTexture)
{
}

float misPanoramicRepresentation::GetOpacityValueOfTexture(misPlaneEnum planeIndex)
{
	return {};
}

void misPanoramicRepresentation::SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex,
	misOpenglTexture* pTexture)
{
}

void misPanoramicRepresentation::SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex,
	misOpenglTexture* pTexture, misTexturePropertyStruct externalSetPlane)
{
}

misWindowLevelStr misPanoramicRepresentation::GetViewingProprties()
{
	return {};
}

misWindowLevelStr misPanoramicRepresentation::GetViewingProprties(misPlaneEnum planeIndex)
{
	return {};
}

IMAGEORIENTATION misPanoramicRepresentation::GetOrientation()
{
	return {};
}



void misPanoramicRepresentation::SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val)
{
 }

void misPanoramicRepresentation::SetColorMapTransFuncID(misPlaneEnum planeIndex,
	std::shared_ptr<TransFuncIntensity> val)
{
	 
}

void misPanoramicRepresentation::SetColorValueToTexture(misDoubleColorStruct colorVal)
{
	 
}

void misPanoramicRepresentation::SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal)
{
}

void misPanoramicRepresentation::SetOpacityValueToTexture(float opacityValue)
{
	 
}

void misPanoramicRepresentation::SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)
{
}

void misPanoramicRepresentation::SetPolyDataTransferFunction(int planeIndex, ImageContainedTransferFuncs ImgCntTF)
{
}

void misPanoramicRepresentation::SetVisibilityOfSegmentedImage(misPlaneEnum planeIndex, bool val)
{
}

void misPanoramicRepresentation::SetVisibilityOfFmriImage(misPlaneEnum planeIndex, bool val)
{
}

void misPanoramicRepresentation::SetApplyColor(int val)
{
}

void misPanoramicRepresentation::SetApplyColor(misPlaneEnum planeIndex, int val)
{
}

void misPanoramicRepresentation::RemoveColorMap(misPlaneEnum planeIndex)
{
}

bool misPanoramicRepresentation::UpdateRepTransformMatrix(misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix)
{
	return {};
}

void misPanoramicRepresentation::SetTransferFunction(std::shared_ptr<TransFuncIntensity> tf)
{
}

void misPanoramicRepresentation::SetTransferFunction(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf)
{
}

void misPanoramicRepresentation::SetFmriTransferFunctionID(int val)
{
}

void misPanoramicRepresentation::SetFmriTransferFunctionID(misPlaneEnum planeIndex, int val)
{
}

void misPanoramicRepresentation::Reset()
{
}

void misPanoramicRepresentation::RemoveLayer(misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
}

void misPanoramicRepresentation::InitilizeLayers()
{
}

void misPanoramicRepresentation::SetIsAlphaSetForBlending(int val)
{
}

void misPanoramicRepresentation::SetIsAlphaSetForBlending(misPlaneEnum planeIndex, int val)
{
}

void misPanoramicRepresentation::SetErasedObjDisplayStatus(bool showErased)
{
}

misPlaneEnum misPanoramicRepresentation::GetPlaneWithMaximumVisibility()
{
	return {};
}

void misPanoramicRepresentation::SetErasedObjectColor(misColorStruct ColorStr)
{
}

void misPanoramicRepresentation::SetWindowLevelTransferFunction(misPlaneEnum planeIndex)
{
}

void misPanoramicRepresentation::SetWindowLevelTransferFunction()
{
}

void misPanoramicRepresentation::SetVisibilityOfMainTexture(misPlaneEnum planeIndex, bool val)
{
}

bool misPanoramicRepresentation::GetVisibilityOfMainTexture(misPlaneEnum planeIndex) const
{
	return true;
}

void misPanoramicRepresentation::SetDefautltVisibiltyPlanesMap(std::shared_ptr<IVisibiltyHolder>)
{
}
