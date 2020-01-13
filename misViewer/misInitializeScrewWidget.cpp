#include "stdafx.h"
#include "misInitializeScrewWidget.h"
#include "misScrewWidgetData.h"
#include "misScrewCompound.h"
#include "misScrewRepresentation.h"
#include "misBiopsyPlanRepresentation.h"


misInitializeScrewWidget::misInitializeScrewWidget(std::shared_ptr<ScrewListType> screwServiceList,
                                                   vtkSmartPointer<vtkRenderWindowInteractor> interactor,
                                                   std::shared_ptr<ICornerProperties> cornerproperties,
                                                   std::shared_ptr<IPlanSourceFactory> planSourceFactory,
                                                   misApplicationType appType, bool displayCross)
	: m_PlanSourceFactory(planSourceFactory),
	  m_Cornerproperties(cornerproperties),
	  m_vtkRenderWindowInteractor(interactor),
	  m_ScrewServiceList(screwServiceList),
	  m_AppType(appType),
	  m_DisplayCross(displayCross)
{
}

std::shared_ptr<IScrewCompound> misInitializeScrewWidget::Initialize(const misScrewWidgetData& screwData,
                                                                     IMAGEORIENTATION orientation)
{
	for (const auto& screw : *m_ScrewServiceList)
	{
		if (screw->GetScrewUID() == screwData.GetScrewUID())
		{
			return nullptr;
		}
	}

	//	m_ScrewRepresentation = std::make_shared<misScrewRepresentation>(cornerProperties, m_ImplantSource);
	auto implantSource = m_PlanSourceFactory->CreatePlanSource(m_Cornerproperties, orientation, m_AppType, m_DisplayCross);
	std::shared_ptr<IPlanWidgetRepresentation> screwRepresention;
	if (m_AppType == Biopsy)
		screwRepresention = std::make_shared<misBiopsyPlanRepresentation>(
			m_Cornerproperties, implantSource);
	else
		screwRepresention = std::make_shared<misScrewRepresentation>(m_Cornerproperties, implantSource);
	auto screwCompound = std::make_shared<misScrewCompound>(implantSource, screwData.GetScrewUID(), screwRepresention);
	screwCompound->SetInteractor(m_vtkRenderWindowInteractor);
	screwCompound->SetWidth(screwData.GetScrewDiameter());
	screwCompound->SetEntry(parcast::PointD3(screwData.GetStartPoint().data));
	screwCompound->SetTarget(parcast::PointD3(screwData.GetEndPoint().data));
	screwCompound->SetTargetRadius(screwData.GetTargetRadius());
	m_ScrewServiceList->push_back(screwCompound);
	return screwCompound;
}
