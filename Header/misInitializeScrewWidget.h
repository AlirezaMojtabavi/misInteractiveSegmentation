#pragma once
#include "IInitializeScrewWidget.h"
#include "IScrewCompound.h"
#include "misApplication.h"
#include "ICornerProperties.h"
#include "IPlanSourceFactory.h"

class misInitializeScrewWidget : public IInitializeScrewWidget
{
public:
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	explicit misInitializeScrewWidget(std::shared_ptr<ScrewListType> screwServiceList,
	                                  vtkSmartPointer<vtkRenderWindowInteractor>,
	                                  std::shared_ptr<ICornerProperties>,
	                                  std::shared_ptr<IPlanSourceFactory> planSourceFactory,
	                                  misApplicationType appType, bool displayCross);
	std::shared_ptr<IScrewCompound> Initialize(const misScrewWidgetData&, IMAGEORIENTATION) override;
private:

	std::shared_ptr<ScrewListType> m_ScrewServiceList;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	vtkSmartPointer<vtkRenderWindowInteractor> m_vtkRenderWindowInteractor;
	std::shared_ptr<IPlanSourceFactory> m_PlanSourceFactory;
	misApplicationType m_AppType = ENT;
	bool m_DisplayCross;
};
