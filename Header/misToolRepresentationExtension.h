#pragma once
#include "IToolRepresentation.h"
#include "misSurfaceRepresentation.h"
#include "misToolProperties.h"
#include "mis2DToolActor.h"
#include "IToolRepresentation.h"
#include "IVirtualTipBuilder.h"

 

class misToolRepresentationExtension :	public IToolRepresentation
{
public:
	misToolRepresentationExtension(const std::string& name, std::shared_ptr<parcast::IVirtualTipBuilder>);
	misToolRepresentationExtension(const misToolProperties& tool, std::shared_ptr<parcast::IVirtualTipBuilder>);
	void SetToolRepresentationType(misToolRepresentationType  toolRepType) override;
	void SetVirtualTipVisibility(bool value) override;
	void SetVirtualTipLength(double length) override;
	void SetColor(float r, float g, float  b) override;
	virtual void SetTorusVisibility(bool value) override{};
	void SetVisibilityOn(void) override;
	void SetVisibilityOff(void) override;
	void SetVisibility(bool visibility) override;
	misToolProperties   GetToolProperties(void)override;
	vtkSmartPointer<vtkActor> SetPolyData(vtkSmartPointer<vtkPolyData> polyData, misToolProperties toolProperties,
		misToolRepresentationType currentToolRepTypemisToolProperties)  override;
	std::shared_ptr<IRepresentation> GetSurface() const override;
	//Gets a vtkTransform and calls TransformDoublePoint(0,0,0) and then sets the result transform to all actors
	void SetUserTransform(vtkTransform *transform) override;
private:
	bool operator ==(misToolRepresentationExtension& right);
	static vtkSmartPointer<vtkActor> CreateActor(misToolRepresentationType currentToolRepTypemisToolProperties);

	void  SetToolProperties(misToolProperties  toolProperties, misToolRepresentationType  currentToolRepType);
	void UpdateVirtualTipParameters(double length) const;

	vtkMatrix4x4* m_TipTransform;
	misToolProperties m_ToolProperties;
	misToolRepresentationType  m_ToolRepType;
	vtkSmartPointer<vtkLineSource> m_VirtualTipLineSource = vtkSmartPointer<vtkLineSource>::New();
	vtkSmartPointer<vtkActor> m_VirtualTipActor;
	vtkSmartPointer<vtkPolyDataMapper> m_VirtualPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkActor> m_MainActor;
	vtkSmartPointer<vtkTubeFilter> edgesTuber;
	std::shared_ptr<IRepresentation> m_Surface = std::make_shared<misSurfaceRepresentation>("Tool");
	std::shared_ptr<parcast::IVirtualTipBuilder> m_VirtualTipBuilder;

};

