#pragma once

#include "VisualizationGeneralTypes.h"
#include "misColorStruct.h"
#include "misPlanWidget.h"
#include "misScrewWidgetData.h"
#include "misSimplePointType.h"
#include "misVertebraEnum.h"
#include "IScrewCompound.h"
#include "ICornerProperties.h"
#include "mis3DImplant.h"
#include "IPlanWidgetRepresentation.h"
#include <memory>

class misScrewRepresentation;
class  vtkLineWidget2;
namespace parcast
{
	class I3DPlanCrossSectionFunction;
}

class misScrewCompound : public IScrewCompound
{
public:
	typedef itk::Vector<double, 3> VectorType;
	misScrewCompound(std::shared_ptr<IImplantSource> implantSource, std::string, std::shared_ptr<IPlanWidgetRepresentation> screwRepresentation);
	~misScrewCompound(void);

	void	SetRotationStateValues() override;
	void	SetExtendStateValues(double maxLineLen) override;
	void	SetPositionStateValue() override;
	void	SetFreeStateValue() override;
	void	SetScrewWidget(misScrewWidgetData screwWidgetNewVal)  override;
	//IMPORTANT NOTE:This method must call after setting transform matrix to corner properties if we are going to get 
	// plane normal from corner properties and  
	// we know it's transform matrix has already changed override.
	double* GetPoint1WorldPosition() const override;
	double* GetPoint2WorldPosition() const override;
	ScrewWidgetInteractionType GetInteractionType() const override;
	
	vtkMatrix4x4*	GetTransformMatrix() const override;
	misPlanWidget* GetWidget() const override;
	void SetInteractor(vtkRenderWindowInteractor*	pRenderWindowInteractor) override;
	void	Off() override;
	void	On() override;
	void	SetColor(misColorStruct screwColor) override;
	void SetWidth(const double& width) override;
	void	SetLocked(bool finalized) override;
	misUID	GetScrewUID() const override;
	void	HighlightScrew(bool highlight) override;
	void	SetSelected(bool selected) override;
	bool	GetSelected() const override;
	void SetTargetRadius(double val) override;

	void SetEntry(parcast::PointD3 point) override;
	void SetTarget(parcast::PointD3 point) override;

private:

 	std::shared_ptr<IImplantSource> m_ImplantSource;
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix = vtkMatrix4x4::New();
	std::shared_ptr<IPlanWidgetRepresentation>	m_ScrewRepresentation = nullptr;
	misPlanWidget* m_LineWidget;
	misUID m_ScrewUID;
	bool m_Selected;
	double m_TubeRadius = 1.0;
};
