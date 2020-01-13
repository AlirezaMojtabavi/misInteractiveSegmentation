#include "StdAfx.h"
#include "misPlanarRepresentation.h"

#include "IImage.h"
#include "IImageSlicerMapper.h"
#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misDistributionEvent.h"
#include "misEnumUtilities.h"
#include "misImageDataProperties.h"
#include "misImagePlaneInformationStrct.h"
#include "misMathUtils.h"
#include "misTransform.h"
#include "misTransformEquality.h"
#include "misTransFunctionBuilder.h"
#include "misVTKMattoTgtMatConvertor.h"
#include "misReversibleValue.h"

using std::find_if;
using std::string;

misPlanarRepresentation::misPlanarRepresentation(string name, IImageSlicerMapper* mapper) :
	misRepresentation(name),
	m_SliceMapper(mapper), m_ContrastChanged(false)
{
	InitilizeLayers();
	m_RefrencePlaneTexture = 0;
	SetMinOpacityForSettingWinLev(0.1);
	m_ImageGeoProp = 0;
	m_Orientation = misEnumUtilities::ConvertImageOrientationTypeStringToEnum(name);
	m_CornerProperties = 0;
}

misPlanarRepresentation::~misPlanarRepresentation()
{
}

void misPlanarRepresentation::SetWindowLevel(misLayerEnum layerIndex, misWindowLevelStr winlevStr)
{
	SetWindowLevel(GetPlaneWithMaximumVisibility(), layerIndex, winlevStr);
}

void misPlanarRepresentation::SetWindowLevelForSelectedPlane(misWindowLevelStr winlevStr)
{
	auto planeIndex = GetPlaneWithMaximumVisibility();
	SetWindowLevel(planeIndex, MainImage, winlevStr);
}

void misPlanarRepresentation::SetWindowLevel(misPlaneEnum planeIndex, misLayerEnum layerIndex, misWindowLevelStr winlevStr)
{
	if (planeIndex >= m_planeInformation.size())  return;
	double currentWindowCenter = m_planeInformation[planeIndex].m_Layers[layerIndex].GetWinlevel().GetWindowCenter();
	double currentWindowWith = m_planeInformation[planeIndex].m_Layers[layerIndex].GetWinlevel().GetWindowWidth();
	m_planeInformation[planeIndex].m_Layers[layerIndex].SetWinlevel(winlevStr);
	m_planeInformation[planeIndex].m_Layers[layerIndex].GetTexure()->SetWindowLevel(winlevStr);
	if (!m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure()->GetTableRange())
	{
		cout << endl << "table range is not available, windowlevel cant be set!!" << endl;
		return;
	}
	double minImage, MaxImage;
	minImage = m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure()->GetTableRange()[0];
	MaxImage = m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure()->GetTableRange()[1];
	double shift, scale;
	shift = -minImage;
	scale = 1 / (MaxImage - minImage);
	SetWindowLevelTransferFunction(planeIndex);

#pragma endregion for when window and level are being used in order to make WindowLevelTransferFunction
	////---------------------set this setting to image to always see with this setting
	auto mainImage = m_planeInformation[planeIndex].m_Layers[layerIndex].GetSource();
	auto levWin = mainImage->GetImageDataProperties()->GetViewingProperties().GetLevelWindow();
	if (mainImage)
	{
		if ((levWin.GetWindowCenter() != winlevStr.GetWindowCenter()) ||
			(levWin.GetWindowWidth() != winlevStr.GetWindowWidth()))
		{
			mainImage->SetViewingProperties(m_planeInformation[planeIndex].m_ImageViewingType, winlevStr);
		}
	}
	if ((currentWindowCenter == winlevStr.GetWindowCenter()) && (currentWindowWith == winlevStr.GetWindowWidth()))
		return;
	misReversibleValue<bool> guard(m_ContrastChanged);
	if (m_ContrastChanged)
		return;
	m_ContrastChanged = true;

	misPlaneContrastEvent  ev;
	misPlaneIndexWinLevStr PlaneWinLevStr;
	PlaneWinLevStr.PlaneIndex = planeIndex;
	PlaneWinLevStr.WinLev = winlevStr;
	ev.Set(PlaneWinLevStr);
	InvokeEvent(ev);
}

void misPlanarRepresentation::SetWindowLevel(misWindowLevelStr winlevStr)
{
	SetWindowLevel(MainImage, winlevStr);
}

void misPlanarRepresentation::SetWindowLevel(misWindowLevelStr winlevStr, misPlaneEnum planeIndex)
{
	SetWindowLevel(planeIndex, MainImage, winlevStr);
}

parcast::PointD3 misPlanarRepresentation::GetCenter()
{
	return GetCenter(FirstImage);
}

parcast::PointD3 misPlanarRepresentation::GetCenter(int planeIndex)
{
	if (planeIndex >= m_planeInformation.size())
		return{};
	return  m_planeInformation[0].GetPlaneCenter();
}

std::shared_ptr<IImage> misPlanarRepresentation::GetImage()
{
	std::shared_ptr<IImage> tempImage = GetImage(FirstImage);
	return tempImage;
}

std::shared_ptr<IImage> misPlanarRepresentation::GetImage(misPlaneEnum planeIndex)
{
	if (m_planeInformation[planeIndex].m_Layers.empty())
		return nullptr;

	return  m_planeInformation[planeIndex].m_Layers[MainImage].GetSource();
}

misUID misPlanarRepresentation::GetImageUID(misPlaneEnum planeIndex)
{
	if (m_planeInformation[planeIndex].m_Layers.empty())
		return{};
	std::shared_ptr<IImage> image = GetImage(planeIndex);
	if (image)
	{
		return  image->GetUID();
	}
	return{};
}

vtkActor* misPlanarRepresentation::GetQuadPlane()
{
	if (m_Actors.size() > 0)
	{
		vtkActor*  prop = dynamic_cast<vtkActor*>(m_Actors[0].GetPointer());
		if (prop)
		{
			return prop;
		}
		return  0;
	}
	return  0;
}

void misPlanarRepresentation::SetTexture(misOpenglTexture* pTexture)
{
	SetTexture(MainImage, pTexture);
}

void misPlanarRepresentation::SetTexture(misOpenglTexture* pTexture, misPlaneEnum planeIndex)
{
	SetTexture(planeIndex, MainImage, pTexture);
}

void misPlanarRepresentation::SetTexture(misLayerEnum layerIndex, misOpenglTexture* pTexture)
{
	SetTexture(FirstImage, layerIndex, pTexture);
}

void misPlanarRepresentation::SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture)
{
	if (planeIndex == FirstImage)
		m_RefrencePlaneTexture = pTexture;

	if (planeIndex >= m_planeInformation.size())
		return;

	if (layerIndex < m_planeInformation[planeIndex].m_Layers.size())
		m_planeInformation[planeIndex].m_Layers[layerIndex].SetTexure(pTexture);

	if (layerIndex == MainImage && planeIndex == FirstImage)
		GeneratePlaneMesh(planeIndex, pTexture->GetTexturePropertyStrct());
	auto WinLev = pTexture->GetWindowLevel();

	if (0 != m_planeInformation.size())
	{
		if (!(m_planeInformation[planeIndex].m_Layers[layerIndex].GetGrayScaleMapping()))
		{
			m_SliceMapper->SetIsContrastShaderUsed(false);
		}
		else
		{
			m_SliceMapper->SetIsContrastShaderUsed(true);
		}
	}
	if (layerIndex == MainImage)
	{
		SetViewingProperties(planeIndex, WinLev);
	}
	SetTextureID(planeIndex, layerIndex, pTexture->getId());
	m_planeInformation[planeIndex].SetExtends(pTexture->GetTexturePropertyStrct().GetExtent());
	m_planeInformation[planeIndex].m_PlaneSpacing[0] = pTexture->GetTexturePropertyStrct().Spacing.x;
	m_planeInformation[planeIndex].m_PlaneSpacing[1] = pTexture->GetTexturePropertyStrct().Spacing.y;
	m_planeInformation[planeIndex].m_PlaneSpacing[2] = pTexture->GetTexturePropertyStrct().Spacing.z;
}

void misPlanarRepresentation::SetTexture(misPlaneEnum planeIndex, misLayerEnum layerIndex, misOpenglTexture* pTexture, misTexturePropertyStruct externalSetPlane)
{
	auto WinLev = pTexture->GetWindowLevel();
	if (layerIndex < m_planeInformation[planeIndex].m_Layers.size())
	{
		m_planeInformation[planeIndex].m_Layers[layerIndex].SetTexure(pTexture);
		m_planeInformation[planeIndex].SetExtends(pTexture->GetTexturePropertyStrct().GetExtent());
		m_planeInformation[planeIndex].m_PlaneSpacing[0] = pTexture->GetTexturePropertyStrct().Spacing.x;
		m_planeInformation[planeIndex].m_PlaneSpacing[1] = pTexture->GetTexturePropertyStrct().Spacing.y;
		m_planeInformation[planeIndex].m_PlaneSpacing[2] = pTexture->GetTexturePropertyStrct().Spacing.z;
	}
	if (layerIndex == MainImage)
	{
		GeneratePlaneMesh(planeIndex, externalSetPlane);
	}
	if (0 != m_planeInformation.size())
	{
		if (!(m_planeInformation[planeIndex].m_Layers[layerIndex].GetGrayScaleMapping()))
		{
			m_SliceMapper->SetIsContrastShaderUsed(false);
		}
		else
		{
			m_SliceMapper->SetIsContrastShaderUsed(true);
		}
	}
	if (planeIndex == FirstImage)
	{
		if (layerIndex == MainImage)
		{
			SetWindowLevel(WinLev);
		}
	}
	if (planeIndex == SecondImage)
	{
		if (layerIndex == MainImage)
		{
			SetViewingProperties(SecondImage, WinLev);
		}
	}
	SetTextureID(planeIndex, layerIndex, pTexture->getId());
	SetVisibilityOfMainTexture(planeIndex, true);
}

void misPlanarRepresentation::RemoveLayer(misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
	if (0 == m_planeInformation.size())
		return;
	if (layerIndex == SegmentedImage)
		m_SliceMapper->SetVisibilityOfSegmentedImage(planeIndex, false);
	if (m_planeInformation[0].m_Layers[layerIndex].GetTexure()/*m_pQuadActor->GetProperty()->GetTexture(layerIndex)*/)
	{
		m_planeInformation[0].m_Layers[layerIndex].SetTexure(NULL);
		m_planeInformation[0].GetActor()->GetProperty()->RemoveTexture(layerIndex);
	}
}

void misPlanarRepresentation::RemovePlane(int planeindex)
{
	if (0 == m_planeInformation.size())
		return;
	if (planeindex >= m_planeInformation.size())  return;
	if (m_planeInformation[0].GetActor())
	{
		if (m_planeInformation[planeindex].m_Layers[0].GetTexure()/*m_pQuadActor->GetProperty()->GetTexture(layerIndex)*/)
		{
			SetTextureID((misPlaneEnum)planeindex, MainImage, -1);
			SetVisibilityOfMainTexture((misPlaneEnum)planeindex, false);
			m_planeInformation[planeindex].m_Layers[0].SetTexure(NULL);
		}
	}
}

void misPlanarRepresentation::GrayscaleOff()
{
	GrayscaleOff(MainImage);
}

void misPlanarRepresentation::GrayscaleOff(int LayerIndex)
{
	GrayscaleOff(FirstImage, (misLayerEnum)(LayerIndex));
}

void misPlanarRepresentation::GrayscaleOn()
{
	GrayscaleOn(MainImage);
}

void misPlanarRepresentation::GrayscaleOn(int index)
{
	GrayscaleOn(FirstImage, (misLayerEnum)(index));
}

void misPlanarRepresentation::GrayscaleOff(misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
	if (planeIndex >= m_planeInformation.size())  return;
	if (m_planeInformation[planeIndex].m_Layers.size() > layerIndex)
		m_planeInformation[planeIndex].m_Layers[layerIndex].GrayScaleMappingOff();
}

void misPlanarRepresentation::GrayscaleOn(misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
	if (planeIndex >= m_planeInformation.size())  return;
	if (m_planeInformation[planeIndex].m_Layers.size() > 0)
		m_planeInformation[planeIndex].m_Layers[layerIndex].GrayScaleMappingOn();
}

void misPlanarRepresentation::SetTextureTransform(tgt::mat4 pTrans)
{
	SetTextureTransform(FirstImage, pTrans);
}

void misPlanarRepresentation::SetTextureTransform(misPlaneEnum planeIndex, tgt::mat4 pTrans)
{
	if (planeIndex >= m_planeInformation.size())
		return;
	m_SliceMapper->SetMatrixTransform(pTrans, planeIndex);
}



void misPlanarRepresentation::Reset()
{
	m_planeInformation.clear();
	misRepresentation::Reset();
	InitilizeLayers();
}

void misPlanarRepresentation::InitilizeLayers()
{
	for (int i = 0; i < LayerCount; i++)
	{
		layerRep tempLAyerRep;
		misImagePlaneInformationStrct tempstruct;
		tempstruct.Reset();
		m_planeInformation.push_back(tempstruct);

		for (int j = 0; j < LayerCount; j++)
		{
			misStrct3DLayer tempLayer;
			tempLayer.SetLoadStatus(false);
			tempLAyerRep.push_back(tempLayer);
		}
		m_planeInformation[i].m_Layers = tempLAyerRep;
		m_planeInformation[i].m_TransformMatrix = vtkMatrix4x4::New();
	}
}

void misPlanarRepresentation::SetIsAlphaSetForBlending(int val)
{
	SetIsAlphaSetForBlending(FirstImage, val);
}

void misPlanarRepresentation::SetIsAlphaSetForBlending(misPlaneEnum planeIndex, int val)
{
	m_SliceMapper->UseAlphaForBlending(val, planeIndex);
}

void misPlanarRepresentation::SetApplyColor(int val)
{
	SetApplyColor(FirstImage, val);
}

void misPlanarRepresentation::SetApplyColor(misPlaneEnum planeIndex, int val)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetUseColorForTexture(val, planeIndex);
}

void misPlanarRepresentation::SetColorValueToTexture(misDoubleColorStruct colorVal)
{
	SetColorValueToTexture(FirstImage, colorVal);
}

void misPlanarRepresentation::SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetColorValueToTexture(colorVal, planeIndex);
}

void misPlanarRepresentation::SetOpacityValueToTexture(float opacityValue)
{
	SetOpacityValueToTexture(FirstImage, opacityValue);
}

void misPlanarRepresentation::SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetOpacityValueToTexture(opacityValue, planeIndex);
	SetIsAlphaSetForBlending(planeIndex, 1.0);
}

void misPlanarRepresentation::UpdateCorrelated()
{
	auto planeIndex = SecondImage;
	SetIsAlphaSetForBlending(1.0);
	SetIsAlphaSetForBlending(planeIndex, 1.0);
	SetApplyColor(1.0);
	SetApplyColor(planeIndex, 1.0);
}

bool misPlanarRepresentation::UpdateRepTransformMatrix(misPlaneEnum planeIndex, vtkMatrix4x4* TransformMatrix)
{
	if (planeIndex >= m_planeInformation.size())
		return false;
	if (misTransformEquality::EqualMatrix(TransformMatrix, m_planeInformation[planeIndex].m_TransformMatrix))
	{
		return false;
	}
	m_planeInformation[planeIndex].m_TransformMatrix->DeepCopy(TransformMatrix);
	return true;
}

void misPlanarRepresentation::ApplyTransformToScene(misPlaneEnum sourcePlane, misPlaneEnum targetPlane,
	vtkSmartPointer<vtkTransform> transform)
{
	m_planeInformation[targetPlane].m_TransformMatrix->DeepCopy(transform->GetMatrix());
	auto finalTextureTransform = CalculateTransformBetWeenImagePlane(sourcePlane, targetPlane);
	if (!finalTextureTransform)
		return;

	auto tran = vtkSmartPointer<vtkMatrix4x4>::New();
	tran->DeepCopy(finalTextureTransform->GetMatrix());
	misVTKMattoTgtMatConvertor convertor;
	auto transformMat = convertor(tran);
	SetTextureTransform(targetPlane, transformMat);
}

vtkSmartPointer<vtkTransform> misPlanarRepresentation::CalculateTransformBetWeenImagePlane(
	misPlaneEnum sourcePlane, misPlaneEnum targetPlane)
{
	if (!m_planeInformation[targetPlane].m_Layers[MainImage].GetTexure() ||
		!m_planeInformation[FirstImage].GetActor())
		return 0;

	misCoordinateSystemCorrelationTreeManager correlationManager;
	correlationManager.SetTransform("Target", "NormalizedTarget", GetImageNormalizationTransform(targetPlane));
	correlationManager.SetTransform("Source", "NormalizedSource", GetImageNormalizationTransform(sourcePlane));
	auto sourceToTargetTrans = misMathUtils::CreateTransform(m_planeInformation[targetPlane].m_TransformMatrix);
	correlationManager.SetTransform("Source", "Target", sourceToTargetTrans);
	auto normalizedCorrelation = correlationManager.GetTransform("NormalizedSource", "NormalizedTarget")->GetTransform();
	return misMathUtils::CreateVtkTransform(normalizedCorrelation);
}

float misPlanarRepresentation::GetOpacityValueOfTexture(misPlaneEnum planeIndex)
{
	float opacity = 0;
	if (planeIndex >= m_planeInformation.size())
		return opacity;
	if (m_SliceMapper && m_SliceMapper->GetVisibilityOfMainTexture(planeIndex))
		opacity = m_SliceMapper->GetOpacityValueOfTexture(planeIndex);
	return opacity;
}

void misPlanarRepresentation::SetVisibilityOfSegmentedImage(misPlaneEnum planeIndex, bool val)
{
	m_SliceMapper->SetVisibilityOfSegmentedImage(planeIndex, val);
}

void misPlanarRepresentation::SetVisibilityOfFmriImage(misPlaneEnum planeIndex, bool val)
{
	m_SliceMapper->SetVisibilityOfFmriImage(planeIndex, val);
}

void misPlanarRepresentation::SetVisibilityOfMainTexture(misPlaneEnum planeIndex, bool val)
{
	if (m_VisibiltyHolder)
	{
		m_VisibiltyHolder->SetVisibilty(planeIndex, val);
		auto visibilty = m_VisibiltyHolder->GetVisibilty(planeIndex);
		m_SliceMapper->SetVisibilityOfMainTexture(planeIndex, visibilty);
	}
	else
		m_SliceMapper->SetVisibilityOfMainTexture(planeIndex, val);
}

void misPlanarRepresentation::SetTransferFunction(std::shared_ptr<TransFuncIntensity> tf)
{
	SetTransferFunction(FirstImage, tf);
}

void misPlanarRepresentation::SetTransferFunction(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> tf)
{
	m_SliceMapper->SetSegmentedImageTransFunc(tf, planeIndex);
}

void misPlanarRepresentation::SetFmriTransferFunctionID(int val)
{
	SetFmriTransferFunctionID(FirstImage, val);
}

void misPlanarRepresentation::SetFmriTransferFunctionID(misPlaneEnum planeIndex, int val)
{
	m_SliceMapper->SetFmriImageTransFuncID(val, planeIndex);
}

void misPlanarRepresentation::SetTextureID(misPlaneEnum planeIndex, misLayerEnum layerIndex, int val)
{
	if (MainImage == layerIndex)
		m_SliceMapper->SetMainImageTextureID(val, planeIndex);
	if (SegmentedImage == layerIndex)
		m_SliceMapper->SetSegmentedImageTextureID(val, planeIndex);
	if (FmriImage == layerIndex)
		m_SliceMapper->SetFmriImageTextureID(val, planeIndex);
	m_SliceMapper->AddTextureGroup(planeIndex);
}

misWindowLevelStr misPlanarRepresentation::GetViewingProprties()
{
	return GetViewingProprties(FirstImage);
}

misWindowLevelStr misPlanarRepresentation::GetViewingProprties(misPlaneEnum planeIndex)
{
	misWindowLevelStr winLevDefault;
	if (planeIndex >= m_planeInformation.size())
		return winLevDefault;
	auto winLev = m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure()->GetWindowLevel();
	return winLev;
}

void misPlanarRepresentation::SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winlevStr)
{
	if (planeIndex >= m_planeInformation.size())  return;
	if (m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure())
	{
		SetWindowLevel(planeIndex, MainImage, winlevStr);
	}
}

misTexturePropertyStruct misPlanarRepresentation::GetImageProperties(misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
	misTexturePropertyStruct emptyStr;
	if (planeIndex >= m_planeInformation.size())  return emptyStr;
	if (m_planeInformation[planeIndex].m_Layers[layerIndex].GetTexure())
		return m_planeInformation[planeIndex].m_Layers[layerIndex].GetTexure()->GetTexturePropertyStrct();
	return emptyStr;
}

void misPlanarRepresentation::SetImageSource(std::shared_ptr<IImage> pImage, misPlaneEnum planeIndex, misLayerEnum layerIndex)
{
	if (planeIndex >= m_planeInformation.size())
		return;
	m_planeInformation[planeIndex].m_Layers[layerIndex].SetSource(pImage);
}

void misPlanarRepresentation::SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetVisiblityOfColorMap(planeIndex, val);
}

void misPlanarRepresentation::SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetColorMapTransFuncID(planeIndex, val);
}

void misPlanarRepresentation::RemoveColorMap(misPlaneEnum planeIndex)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetVisiblityOfColorMap(planeIndex, false);
}

void misPlanarRepresentation::SetMinOpacityForSettingWinLev(double threshold)
{
	if (threshold < 0)
	{
		threshold = 0;
	}
	else if (threshold > 1.0)
	{
		threshold = 1.0;
	}

	m_MinOpacityForSettingWinLev = threshold;
}

void misPlanarRepresentation::SetWindowLevelTransferFunction(misPlaneEnum planeIndex)
{
	if (m_planeInformation.empty())
		return;
	auto & textureProperty = m_planeInformation[planeIndex].m_Layers[MainImage].GetTexure()->GetTexturePropertyStrct();
	if (!textureProperty.GetTableRange())
		return;
	if (textureProperty.BitStored <= 16) // Image is intensity
	{
		auto colorstr = m_planeInformation[planeIndex].m_ErasedObjectColor;// the color of erased object
		bool showerased = m_planeInformation[planeIndex].m_showErased;  // show/don't show the erased object
		auto wlStr = m_planeInformation[planeIndex].m_Layers[MainImage].GetWinlevel(); // current window level
		misTransFunctionBuilder builder;
		m_TransferFunction[planeIndex] = builder.GenerateTransferFunction(wlStr, showerased, textureProperty.GetTableRange(), colorstr);
		m_TransferFunction[planeIndex]->updateTexture();
		auto wlTexture = m_TransferFunction[planeIndex]->getTexture();
		auto wlTexId = wlTexture->getId();
		m_SliceMapper->SetWindowLevelTransferFunctionTextureID(planeIndex, wlTexId);
	}
	else
		m_SliceMapper->SetUsingTransferFunctionForMainImage(true, planeIndex);// image is RGB or RGBA 
}

void misPlanarRepresentation::SetWindowLevelTransferFunction()
{
	auto planeIndex = GetPlaneWithMaximumVisibility();
	SetWindowLevelTransferFunction(planeIndex);
}

void misPlanarRepresentation::SetErasedObjDisplayStatus(bool showErased)
{
	auto planeIndex = GetPlaneWithMaximumVisibility();
	m_planeInformation[planeIndex].m_showErased = showErased;
}

void misPlanarRepresentation::SetErasedObjectColor(misColorStruct ColorStr)
{
	auto planeIndex = GetPlaneWithMaximumVisibility();
	m_planeInformation[planeIndex].m_ErasedObjectColor = ColorStr;
}

misPlaneEnum misPlanarRepresentation::GetPlaneWithMaximumVisibility()
{
	auto planeIndex = FirstImage;
	// find current plane with opacity more then 0.1
	double firstOpacity = GetOpacityValueOfTexture(FirstImage);
	double SecondOpacity = GetOpacityValueOfTexture(SecondImage);
	if (firstOpacity > m_MinOpacityForSettingWinLev)
		planeIndex = FirstImage;
	else if (SecondOpacity > m_MinOpacityForSettingWinLev)
		planeIndex = SecondImage;
	return planeIndex;
}

IMAGEORIENTATION misPlanarRepresentation::GetOrientation()
{
	return m_Orientation;
}

void misPlanarRepresentation::SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp)
{
	if (pCornerProp)
	{
		if (!m_CornerProperties)
			m_CornerProperties = pCornerProp;
	}
}

void misPlanarRepresentation::SetCornerProperties()
{
	if (m_planeInformation.size() == 0)  return;
	m_SliceMapper->SetCornerProperties(m_CornerProperties);

}

void misPlanarRepresentation::SetRepresentationType()
{
	if (m_SliceMapper)
	{
		m_planeInformation[0].SetMapper(m_SliceMapper->GetMapper());
		SetCornerProperties();
	}
}

void misPlanarRepresentation::GeneratePlaneMesh(misTexturePropertyStruct prop)
{
	GeneratePlaneMesh(FirstImage, prop);
}

void misPlanarRepresentation::GeneratePlaneMesh(misPlaneEnum planeIndex, misTexturePropertyStruct prop)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_planeInformation[0].GeneratePlaneMesh();
	m_planeInformation[FirstImage].SetExtends(prop.GetExtent());
	m_planeInformation[FirstImage].m_PlaneSpacing[0] = prop.Spacing[0];
	m_planeInformation[FirstImage].m_PlaneSpacing[1] = prop.Spacing[1];
	m_planeInformation[FirstImage].m_PlaneSpacing[2] = prop.Spacing[2];
	SetRepresentationType();
	m_SliceMapper->GeneratePlaneMesh(prop);
	auto res = find_if(m_Actors.begin(), m_Actors.end(), [&](vtkSmartPointer<vtkProp>  prp)
	{
		return(prp == m_planeInformation[0].GetActor());

	});
	if (res == m_Actors.end())
	{
		m_Actors.push_back(m_planeInformation[0].GetActor());
	}
}

void misPlanarRepresentation::SetPolyDataTransferFunction(int planeIndex, ImageContainedTransferFuncs ImgCntTF)
{
	if (planeIndex >= m_planeInformation.size())  return;
	m_SliceMapper->SetImageContainedTF(ImgCntTF, planeIndex);
}

void misPlanarRepresentation::ClearFmriTransferFunctionIDs(int groupIndex)
{
	if (m_planeInformation.size() == 0)  return;
	m_SliceMapper->ClearFmriTransferFunctionIDs(groupIndex);
}

void misPlanarRepresentation::SetRefrenecCoordinateSystemUID(const misUID& uid)
{
	m_ReferenceUID = uid;
}

std::vector<misImagePlaneInformationStrct> misPlanarRepresentation::GetPlaneInformation()
{
	return m_planeInformation;
}

void misPlanarRepresentation::ApplyDefaultVisibilityMap(const std::map<misPlaneEnum, bool>& imageVisibiltes)
{
	for (int index = 0; index < imageVisibiltes.size(); index++)
	{
		const auto visibilty = m_VisibiltyHolder->GetVisibilty(static_cast<misPlaneEnum>(index));
		auto plane = static_cast<misPlaneEnum>(index);
		m_SliceMapper->SetVisibilityOfMainTexture(static_cast<misPlaneEnum>(index), visibilty && imageVisibiltes.at(plane));
	}
}

void misPlanarRepresentation::SetDefautltVisibiltyPlanesMap(std::shared_ptr<IVisibiltyHolder> visibilty)
{
	m_VisibiltyHolder = visibilty;
}

std::shared_ptr<IVisibiltyHolder> misPlanarRepresentation::GetVisibiltyHolder()
{
	return  m_VisibiltyHolder;
}

void misPlanarRepresentation::SetOrientation(IMAGEORIENTATION newOrientation)
{
	if (m_planeInformation.size() == 0)
		return;
	m_Orientation = newOrientation;
	m_SliceMapper->SetOrientation(newOrientation);
}

bool misPlanarRepresentation::GetVisibilityOfMainTexture(misPlaneEnum planeIndex) const
{
	if (planeIndex >= m_planeInformation.size())  return false;
	return m_SliceMapper->GetVisibilityOfMainTexture(planeIndex);
}

std::shared_ptr<ITransform> misPlanarRepresentation::GetImageNormalizationTransform(misPlaneEnum plane)
{
	auto spacing = m_planeInformation[plane].m_PlaneSpacing;
	auto extents = m_planeInformation[plane].GetExtends();
	double scaleFactor[] =
	{
		1.0 / ((extents[1] - extents[0]) * spacing[0]),
		1.0 / ((extents[3] - extents[2]) * spacing[1]),
		1.0 / ((extents[5] - extents[4]) * spacing[2])
	};

	auto scaleTransform = vtkSmartPointer<vtkTransform>::New();
	scaleTransform->Identity();
	scaleTransform->Scale(scaleFactor);
	scaleTransform->Update();
	return misMathUtils::CreateTransform(scaleTransform->GetMatrix());
}