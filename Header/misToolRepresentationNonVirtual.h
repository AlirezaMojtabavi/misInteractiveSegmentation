#pragma once
#include "IToolRepresentation.h"
#include "misSurfaceRepresentation.h"
#include "misToolProperties.h"
#include "mis2DToolActor.h"
#include "IToolRepresentation.h"
#include "IVirtualTipBuilder.h"

class misToolRepresentationNonVirtual :
	public IToolRepresentation
{
public:
	misToolRepresentationNonVirtual(const std::string& name, std::shared_ptr<parcast::IVirtualTipBuilder>);
	misToolRepresentationNonVirtual(const misToolProperties& tool, std::shared_ptr<parcast::IVirtualTipBuilder>);
	virtual ~misToolRepresentationNonVirtual(void) = default;
	void SetToolRepresentationType(misToolRepresentationType  toolRepType) override;
	void SetVirtualTipVisibility(bool value) override;
	void SetVirtualTipLength(double length) override;
	void SetColor(float r, float g, float  b) override;
	void SetVisibilityOn(void) override;
	void SetVisibilityOff(void) override;
	void SetVisibility(bool visibility) override;
	misToolProperties   GetToolProperties(void)override;
	vtkActor* SetPolyData(vtkAlgorithmOutput* polyData, misToolProperties toolProperties,
		misToolRepresentationType currentToolRepTypemisToolProperties)  override;
	std::shared_ptr<IRepresentation> GetSurface() const override;
	//Gets a vtkTransform and calls TransformDoublePoint(0,0,0) and then sets the result transform to all actors
	void SetUserTransform(vtkTransform *transform) override;
	void UpdateVirtualTipParameters(void) const;


private:

	bool operator ==(misToolRepresentationNonVirtual& right);
	static vtkSmartPointer<vtkActor> CreateActor(misToolRepresentationType currentToolRepTypemisToolProperties);
	void SetTorusRadious(double radious);
	void SetTorusVisibility(bool value);

	void UpdateVirtualTipVisibilty(bool m_Visibility) const;
	void UpdateToolProperties();
	void UpdateTorusParameters(void) const;
	void UpdateVirtualTipTorus(void) const;
	void UpdateShowExtraPartStatus(void);
	void  SetToolProperties(misToolProperties  toolProperties, misToolRepresentationType  currentToolRepType);
	void UpdateTrousVisibility(bool visibility) const;
	vtkMatrix4x4* m_TipTransform;
	misToolProperties m_ToolProperties;
	bool m_ShowExtraActors;
	misToolRepresentationType  m_ToolRepType;
	vtkSmartPointer<vtkParametricTorus> m_Torus = vtkSmartPointer<vtkParametricTorus>::New();
	vtkSmartPointer<vtkActor> m_TorusActor;
	vtkSmartPointer<vtkLineSource> m_VirtualTipLineSource = vtkSmartPointer<vtkLineSource>::New();
	vtkSmartPointer<vtkActor> m_VirtualTipActor;
	vtkSmartPointer<vtkParametricTorus> m_VirtualTipTorus = vtkSmartPointer<vtkParametricTorus>::New();
	vtkSmartPointer<vtkPolyDataMapper> m_VirtualPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkActor> m_VirtualTipTorusActor;
	vtkSmartPointer<vtkActor> m_MainActor;
	vtkSmartPointer<vtkTubeFilter> edgesTuber;
	std::shared_ptr<IRepresentation> m_Surface = std::make_shared<misSurfaceRepresentation>("Tool");
	std::shared_ptr<parcast::IVirtualTipBuilder> m_VirtualTipBuilder;

};

