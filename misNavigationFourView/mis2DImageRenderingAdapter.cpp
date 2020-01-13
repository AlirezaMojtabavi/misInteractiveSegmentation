#include "stdafx.h"

#include "ICursorService.h"
#include "mis2DImageRenderingAdapter.h"
#include "misImageToTextureMap.h"
#include "misVolumeSlicer.h"
#include "misPlanarRepresentation.h"
#include "misPlaneContrast.h"
#include "misWidgetConfigure.h"
#include "IImageToTextureMap.h"
#include "IImageToTextureMap.h"
#include "misApplicationSetting.h"


mis2DImageRenderingAdapter::mis2DImageRenderingAdapter(std::shared_ptr<IVolumeSlicer> viewer2D,
	misSurgeryDirectionViewerType currentTypeDir, std::shared_ptr<IRepresentationFactory> representationFactory,
	IImageToTextureMap* textureFactory)
	:
	m_2DViewer(viewer2D),
	m_CurrentTypeDir(currentTypeDir),
	m_WidgetConfigure(std::make_shared<misWidgetConfigure>(m_2DViewer)),
	m_Factory(representationFactory),
	m_TextureFactory(textureFactory)
{
	m_PlaneMap.insert(std::pair<int, misPlaneEnum>(0, FirstImage));
	m_PlaneMap.insert(std::pair<int, misPlaneEnum>(1, SecondImage));
}

mis2DImageRenderingAdapter::~mis2DImageRenderingAdapter()
{
}


void mis2DImageRenderingAdapter::ShowImages(std::shared_ptr<IImage> firstImage, bool firstImageVisibilty,
                                            std::shared_ptr<IImage> secondImage, bool secondVisibilty,
	double minOpacity )
{
	if (!firstImage && !secondImage)
		return;
	if(firstImage)
		ShowImageIn2D(FirstImage, firstImage, minOpacity, firstImageVisibilty);
 	if(secondImage)
		ShowImageIn2D(SecondImage, secondImage, minOpacity, secondVisibilty);

	for (auto& texture: m_3DTexture)
		texture.texture[1] = nullptr;
}
void mis2DImageRenderingAdapter::InitilizeRepresentation(double minOpacity)
{

	if (m_2DViewer->GetImageRprensentaion())
		return;

	auto Representation = m_Factory->CreateRepresentation(m_CurrentTypeDir.orientation, m_CurrentTypeDir.viewerType);
	m_2DViewer->SetMainRepresentation(Representation, m_CurrentTypeDir.orientation);
	SetMinimumOpacity(minOpacity);
}


void mis2DImageRenderingAdapter::ShowImageIn2D(int planeIndex, std::shared_ptr<IImage> image,
                                               double minOpacity, bool visibility)
{
	misPlaneEnum pPlaneIndex = m_PlaneMap.find(planeIndex)->second;
	ExtractImage(image, pPlaneIndex, minOpacity);
	SetVisibilityOfMainTexture(pPlaneIndex, visibility);
	m_2DViewer->UpdateImage(true);
}

void mis2DImageRenderingAdapter::SetVisibilityOfMainTexture(misPlaneEnum pPlaneIndex, bool visibility)
{
	auto Gpu2DRep = m_2DViewer->GetImageRprensentaion();
	if (Gpu2DRep)
		Gpu2DRep->SetVisibilityOfMainTexture(pPlaneIndex, visibility);
}


void mis2DImageRenderingAdapter::Reset()
{
	m_3DTexture.clear();
	m_2DViewer->Reset();
}

void mis2DImageRenderingAdapter::ExtractImage(std::shared_ptr<IImage> image, misPlaneEnum planeIndex,
	  double minOpacity, bool resetNeed/*= true*/)
{
	if (!m_2DViewer)
		return;
 
	if (!image)
	{
		auto Gpu2DRep = m_2DViewer->GetImageRprensentaion();
		if (Gpu2DRep)
			Gpu2DRep->RemovePlane(planeIndex);
		return;
	}
	if (planeIndex == FirstImage)
	{
		if (resetNeed)
		{
			m_3DTexture.clear();
			m_2DViewer->ReleaseImageResource();
			m_2DViewer->GetCursorService()->ReleaseWidget();

		}
		SetImage(image, minOpacity);
		auto pos = image->GetImageCenter();
		m_2DViewer->GetCornerProperties()->SetCurrentPosition(pos.Elements());
		m_2DViewer->GetCursorService()->UpdateWidgetPosition();
	}
	else
		SetNextImage(planeIndex, MainImage, image, minOpacity);
}
void mis2DImageRenderingAdapter::SetImage(std::shared_ptr<IImage>   pImage, double minOpacity)
{

	SetImage(MainImage, pImage, minOpacity);
}

void mis2DImageRenderingAdapter::SetImage(misLayerEnum layerIndex, std::shared_ptr<IImage>  pImage, double minOpacity)
{
	if (layerIndex == MainImage)
		InitilizeWidgetandRepresentation(minOpacity);

	// Call render to set current context before generating texture
	m_2DViewer->MakeCurrentRenderer();
	auto imageTexure = m_TextureFactory->LookUpTexture(pImage);
	if (m_3DTexture.empty())
		m_3DTexture.resize(2);
	m_3DTexture[0].texture[layerIndex] = imageTexure;
	if (m_3DTexture[0].texture[layerIndex])
		SetTextureProperties(layerIndex, pImage);

	if (layerIndex == MainImage)
	{
		InitializeImage();
		const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
		const auto toleranceFactor = settingContainer->GetDouble("misVisualizationSetting/WidgetProperties/WidgetPickingTolerance");

		m_2DViewer->InitializeWidget(m_WidgetType, toleranceFactor);
		m_WidgetConfigure->PlaceWidgetatCenter(FirstImage, pImage);
	}
}
void mis2DImageRenderingAdapter::InitializeImage()
{
	auto gpu2DRep = m_2DViewer->GetImageRprensentaion();
	m_2DViewer->AddRepresentation(std::dynamic_pointer_cast<IRepresentation>(gpu2DRep));
	m_2DViewer->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
}


void mis2DImageRenderingAdapter::SetNextImage(misPlaneEnum planeIndex, std::shared_ptr<IImage> pImage, double minOpacity)
{
	SetNextImage(planeIndex, MainImage, pImage, minOpacity);
}

void mis2DImageRenderingAdapter::SetNextImage(misPlaneEnum planeIndex, misLayerEnum layerIndex, 
	std::shared_ptr<IImage>  pImage, double minOpacity)
{

	if (m_3DTexture.size() == 0)
	{
		if (layerIndex == MainImage)
			InitilizeWidgetandRepresentation(minOpacity);
	}
	misImageToTextureMap*  TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* pTexture = TextureHandler->LookUpTexture(pImage);
	m_3DTexture[planeIndex].texture[layerIndex] = pTexture;

	if (m_3DTexture[planeIndex].texture[layerIndex])
		SetTextureProperties(layerIndex, planeIndex, pImage);

	if (layerIndex == MainImage)
	{
		m_WidgetConfigure->PlaceWidgetatCenter(SecondImage, pImage);
	}
}


void mis2DImageRenderingAdapter::SetTextureProperties(misLayerEnum layerIndex, std::shared_ptr<IImage> pImage)
{
	SetTextureProperties(layerIndex, FirstImage, pImage);
}

void mis2DImageRenderingAdapter::SetTextureProperties(misLayerEnum layerIndex, misPlaneEnum planeIndex, std::shared_ptr<IImage> pImage)
{
	if (!m_2DViewer)
		return;
	auto gpu2DRep = m_2DViewer->GetImageRprensentaion();

	if (gpu2DRep)
	{
		gpu2DRep->SetImageSource(pImage, planeIndex, layerIndex);
		gpu2DRep->SetTexture(planeIndex, layerIndex, m_3DTexture[planeIndex].texture[layerIndex]);
		if (m_3DTexture[planeIndex].texture[layerIndex]->GetIsPolydataFlag())
			m_3DTexture[planeIndex].texture[layerIndex]->SetParentimageID(pImage->GetParentImageUID());
	}
}


void mis2DImageRenderingAdapter::SetMinimumOpacity(double minOpacity)
{
	if (!m_2DViewer)
		return;
	auto gpu2DRep = m_2DViewer->GetImageRprensentaion();
	if (!gpu2DRep)
		return;
 	if (minOpacity < 0)
		minOpacity = 0;
	else if (minOpacity > 1.0)
		minOpacity = 1.0;
	if (gpu2DRep)
		gpu2DRep->SetMinOpacityForSettingWinLev(minOpacity);
}
misWindowLevelStr mis2DImageRenderingAdapter::GetCurrentWindowLevel(misUID imageUID)
{
	bool imageExisted = false;

	misWindowLevelStr currentWinLevel;

	if (imageExisted == true)
	{
		misPlaneEnum corresponsingPlane = GetCorrespondingPlaneIndex(imageUID);
		if (corresponsingPlane != UnSetPlane)
		{

			auto gpu2DRep = m_2DViewer->GetImageRprensentaion();
			if (gpu2DRep)
				currentWinLevel = gpu2DRep->GetViewingProprties(corresponsingPlane);

		}
	}
	return currentWinLevel;
}
void mis2DImageRenderingAdapter::InitilizeWidgetandRepresentation(double minOpacity)
{
	if (!m_2DViewer->GetImageRprensentaion())
	{
		Remove2dImageRepresentation();
		m_3DTexture.resize(2);
		InitilizeRepresentation(minOpacity);
	}

}
misPlaneEnum mis2DImageRenderingAdapter::GetCorrespondingPlaneIndex(misUID parentImageUid) const
{
	if (!m_2DViewer)
		return UnSetPlane;
	auto gpu2DRep = m_2DViewer->GetImageRprensentaion();
	if (!gpu2DRep)
		return UnSetPlane;

	auto firtImageUid = gpu2DRep->GetImageUID(FirstImage);
	if (!firtImageUid.empty() && (firtImageUid == parentImageUid))
	{
		return  FirstImage;
	}
	auto secondImageUid = gpu2DRep->GetImageUID(SecondImage);
	if (!secondImageUid.empty() && (secondImageUid == parentImageUid))
	{
		return  SecondImage;
	}
	return UnSetPlane;
}


void mis2DImageRenderingAdapter::Remove2dImageRepresentation()
{
	if (m_2DViewer)
	{
		if (m_2DViewer->GetImageRprensentaion())
		{
			m_2DViewer->RemoveRepresentation(std::dynamic_pointer_cast<IRepresentation>(m_2DViewer->GetImageRprensentaion()));
			m_2DViewer->SetMainRepresentation(0, UNKnownDirection);
		}
	}
}

 

void mis2DImageRenderingAdapter::SetWidgetType(misCursorType val)
{
	m_WidgetType = val;
}




	