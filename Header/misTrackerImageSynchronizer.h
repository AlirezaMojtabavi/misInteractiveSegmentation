#pragma once

#include "IVolume3DRenderer.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRenderer.h"
#include "IPanoramicCoordinatesConverter.h"
#include "IPanoramicTransformConverter.h"
#include "ITrackerImageSynchronizer.h"
#include "IToolRepresentation.h"
#include "IToolShapeBuilder.h"
#include "IToolRepresentationDecider.h"


// The misTrackerImageSynchronizer class add  tools to scene and update their properties in scene
class misTrackerImageSynchronizer :	public ITrackerImageSynchronizer
{
public:

	misTrackerImageSynchronizer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlation, 
			std::shared_ptr<IToolShapeBuilder> toolBuidler, std::shared_ptr<parcast::IToolRepresentationDecider> toolRepDecider);

	virtual void SetToolPosition(double* center) override;
	void AddTool(std::shared_ptr<ITrackingTool> toolData) override;
	virtual void SetRenderingToolSceneReference(std::string refernce) override;
	virtual void SetToolTransform(vtkMatrix4x4* toolTransform) override;
	void UpdateVirtualTipLength(double lenght) override;
	virtual void ShowTorus(bool visibility) override ;
	void SetViewers(std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp> val) override;

	void ClearViewers() override;

	void SetPanoramicTransformConvertor(std::shared_ptr<IPanoramicTransformConverter> val) override;
	virtual void Freeze() override;
	virtual void Unfreeze() override;
 	void SetPanoramicCoordinateConverter(std::shared_ptr<IPanoramicCoordinatesConverter> val) override;
	virtual void AddExistingRepresentation() override;

private:
	
	virtual void AddToolRepresentation(misToolProperties toolData, std::string toolCoordinate) ;
	void AddToolRepresentation(std::shared_ptr<ITrackingTool> toolData);
	std::shared_ptr<IToolShapeBuilder> m_ToolShapeBuilder;
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> m_ToolRenderers;
	std::vector<std::shared_ptr<IToolRepresentation>> m_ToolRepresentators;
	std::shared_ptr<IPanoramicCoordinatesConverter> m_PanoramicCoordinateConverter;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicTransformConvertor;
	std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp>  m_Viewers;
	double m_VirtualLenght;
	std::vector<std::shared_ptr<ITrackingTool>> m_AddedTool;
	typedef  std::unordered_map < std::shared_ptr<IVolumeRenderer>, std::vector<std::shared_ptr<IToolRepresentation>>>
		ViewerToolsRelationType;
	ViewerToolsRelationType m_ViewrToolsMap;
	std::shared_ptr<parcast::IToolRepresentationDecider> m_ToolRepDecider;
};

