#pragma once
#include "IDefaultVolumeRenderer.h"
#include "IVolume3DRenderer.h"
#include "IVolumeViewerInitilizer.h"


class misDefaultVolumeRenderer :
	public IDefaultVolumeRenderer
{
public:
	misDefaultVolumeRenderer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >, 
		std::shared_ptr<IVolume3DRenderer> viewer, std::shared_ptr<IVolumeViewerInitilizer>);
 
	// Inherited via IDefaultVolumeRenderer
	void ShowDefaultVolume(int SegmentedNum, ImageDependencyListTypes currentImageDataDependencies, 
		misVolumeViewingTypes volumeViewing) override;

private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<IVolume3DRenderer> m_viewer;
	misCursorType m_WidgetType;
	misUID m_SceneReferenceUID;
	std::shared_ptr<IVolumeViewerInitilizer> m_VolumeInitilizer;
	
	void SetTranformMatrixToVolumes(const std::string& id, const tgt::mat4& matrix);
	// Inherited via IDefaultVolumeRenderer
	virtual void SetSceneReferenceUID(const std::string & sceneReferenceUID) override;

	// Inherited via IDefaultVolumeRenderer
	virtual void SetWidgetType(misCursorType pWidgetType) override;

	
};

