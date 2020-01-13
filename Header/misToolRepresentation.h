#pragma once

#include "misSurfaceRepresentation.h"
#include "misToolProperties.h"
#include "mis2DToolActor.h"
#include "IToolRepresentation.h"
#include "IVirtualTipBuilder.h"

class vtkParametricFunctionSource;
class vtkParametricTorus;
class vtkTubeFilter;
class vtkLineSource;

//////////////////////////////////////////////////////////////////////////
// Representation type
//   if shpere    : disable tool tip and torus
//   if model     : disable tool tip and torus
//   if complete  : upadte  all

//                        **************************************************************
//   important Note:
// every actor has needed own transform for correct rendering 
// i.e. if you set a transform to a actor and the change it and apply to another actor before rendering,
// the two actor draw with same transform !!!!
//                        **************************************************************


class  misToolRepresentation : 	 public IToolRepresentation
{

public:
	misToolRepresentation(const std::string& name, std::shared_ptr<parcast::IVirtualTipBuilder>);
	misToolRepresentation(const misToolProperties& tool, std::shared_ptr<parcast::IVirtualTipBuilder>);
	void SetToolRepresentationType(misToolRepresentationType  toolRepType) override;
	void SetVirtualTipVisibility(bool value) override;
	void SetVirtualTipLength(double length) override;
	void SetColor(float r,float g,float  b) override;
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

	bool operator ==(misToolRepresentation& right);
	static vtkSmartPointer<vtkActor> CreateActor(misToolRepresentationType currentToolRepTypemisToolProperties);
	void SetTorusRadious(double radious) ;
	void SetTorusVisibility(bool value) ;
	void UpdateVirtualTipParameters(void) const;
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
	vtkSmartPointer<vtkTubeFilter> edgesTuber;
	std::shared_ptr<IRepresentation> m_Surface = std::make_shared<misSurfaceRepresentation>("Tool");
	std::shared_ptr<parcast::IVirtualTipBuilder> m_VirtualTipBuilder;

};
