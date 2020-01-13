#pragma once
#include "misStrctDataSets.h"
#include "misPlaneContrast.h"
#include "I2DRepresentation.h"
#include "I2DImageRenderingAdapter.h"
#include "misSurgeryDirectionViewerType.h"
#include "IWidgetConfigure.h"
#include "IVolume3DRenderer.h"
#include "IRepresentationFactory.h"
#include "misPlanarRepresentation.h"

class IVolumeSlicer;
class misVolumeSlicer;
class IViewerFactory;
class IImageToTextureMap;

class mis2DImageRenderingAdapter :public I2DImageRenderingAdapter
{
public:
	mis2DImageRenderingAdapter(std::shared_ptr<IVolumeSlicer> viewer,
		misSurgeryDirectionViewerType m_CurrentTypeDir, std::shared_ptr<IRepresentationFactory> representationFactory, 
		IImageToTextureMap* textureFactory);
	~mis2DImageRenderingAdapter();
	void ShowImages(std::shared_ptr<IImage> firstImage, bool, std::shared_ptr<IImage> secondImage, bool, double minOpacity) override;
	void Reset()override;
	void SetImage(std::shared_ptr<IImage> pImage, double minOpacity)override;
	void SetImage(misLayerEnum layerIndex, std::shared_ptr<IImage> pImage, double minOpacity)override;
	void SetNextImage(misPlaneEnum planeIndex, misLayerEnum layerIndex, std::shared_ptr<IImage> pImage, 
		double minOpacity)override;
	void SetNextImage(misPlaneEnum planeIndex, std::shared_ptr<IImage> pImage, double minOpacity)override;
	misWindowLevelStr GetCurrentWindowLevel(misUID imageUID) override;
	misPlaneEnum GetCorrespondingPlaneIndex(misUID ParentImageUID) const override;
	void SetWidgetType(misCursorType val) override;

private:
	void ExtractImage(std::shared_ptr<IImage>  ,
		misPlaneEnum planeIndex, double minOpacity , bool resetNeed = true);

		void InitializeImage();
	void SetTextureProperties(misLayerEnum layerIndex, std::shared_ptr<IImage> pImage);
	void SetTextureProperties(misLayerEnum layerIndex, misPlaneEnum planeIndex, std::shared_ptr<IImage> pImage);
	void SetMinimumOpacity(double minOpacity);
	void InitilizeRepresentation(double minOpacity);
	void ShowImageIn2D(int planeIndex, std::shared_ptr<IImage>  , double minOpacity, bool visibility);
	void SetVisibilityOfMainTexture(misPlaneEnum pPlaneIndex, bool visibility);
	void Remove2dImageRepresentation();
	void InitilizeWidgetandRepresentation(double minOpacity);


	misSurgeryDirectionViewerType m_CurrentTypeDir;
	misCursorType m_WidgetType;
	std::map<int, misPlaneEnum>	m_PlaneMap;
	std::shared_ptr<IVolumeSlicer> m_2DViewer;

	struct  layerTextureType
	{
		misOpenglTexture* texture[4];
	};
	std::vector<layerTextureType>	m_3DTexture;
	std::shared_ptr<IWidgetConfigure> m_WidgetConfigure;
	std::shared_ptr<IRepresentationFactory> m_Factory;
	IImageToTextureMap* m_TextureFactory;
};

