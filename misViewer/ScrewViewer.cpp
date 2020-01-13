#include "stdafx.h"
#include "..\Header\ScrewViewer.h"
#include "IPlanWidgetRepresentation.h"
#include <misMemberCommandCallback.h>
#include "misPlanWidget.h"
#include "PlanTransformCalculator.h"


ScrewViewer::ScrewViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
	std::shared_ptr<ScrewListType> screwServiceList,
	std::shared_ptr<ICornerProperties> cornerproperties,
	misVolumeRendererContainer::Pointer parent) :
	m_InitializeScrewWidget(std::move(initializeScrewWidget)),
	m_ScrewServiceList(screwServiceList),
	m_Cornerproperties(cornerproperties),
	m_Parent(parent)
{
}


ScrewViewer::~ScrewViewer()
{
}

bool ScrewViewer::ProcessUpdateScrewWidget(const misScrewWidgetUpdateEvent& screwWidgetUpdate,
                                                    const std::shared_ptr<ICursorService>& cursorService)
{
	misScrewWidgetData screwWidgetVals = screwWidgetUpdate.Get();
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if (screwWidgetVals.GetScrewUID() == (*m_ScrewServiceList)[i]->GetScrewUID())
		{
			(*m_ScrewServiceList)[i]->SetScrewWidget(screwWidgetVals);
			m_Cornerproperties->SetMatrix(screwWidgetVals.GetTransformMatrix());
			cursorService->UpdateWidgetPosition();

			return true;
		}
	}
	return false;
}

void ScrewViewer::UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData)
{
	misPlanWidget* lineCaller = dynamic_cast<misPlanWidget*>(caller);
	if (!lineCaller)
	{
		return;
	}
	if (m_ScrewServiceList->size() == 0)
	{
		return;
	}

	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		misPlanWidget* tmpLine = (*m_ScrewServiceList)[i]->GetWidget();
		if (lineCaller->GetLineWidgetUID() == tmpLine->GetLineWidgetUID())
		{
			if (eventId == vtkCommand::EndInteractionEvent)
			{
				misScrewWidgetData screwWidgetVal;
				screwWidgetVal.SetStartPoint((*m_ScrewServiceList)[i]->GetPoint1WorldPosition());
				screwWidgetVal.SetEndPoint((*m_ScrewServiceList)[i]->GetPoint2WorldPosition());
				screwWidgetVal.SetInterationType((*m_ScrewServiceList)[i]->GetInteractionType());
				const auto transCalc = parcast::PlanTransformCalculator();
				const auto startPoint = parcast::Point<double, 3>((*m_ScrewServiceList)[i]->GetPoint1WorldPosition());
				const auto endPoint = parcast::Point<double, 3>((*m_ScrewServiceList)[i]->GetPoint2WorldPosition());
				IPlanTransformCalculator::TransformAndLength transform;
				ModifyPlane(tmpLine, screwWidgetVal);
				if (screwWidgetVal.IsEndPointModified())
				{
					transform = transCalc.FromPlanPointsWithEndTranslation(startPoint, endPoint);
				}
				else if (screwWidgetVal.IsStartPointModified())
				{
					transform = transCalc.FromPlanPointsWithStartTranslation(startPoint, endPoint);
				}
				else
				{
					transform = transCalc.FromPlanPointsWithEndTranslation(startPoint, endPoint);
				}

				auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
				for (auto i = 0; i < 4; i++)
				{
					for (auto j = 0; j < 4; j++)
					{
						matrix->SetElement(i, j, transform.CoordSysTransform[j + (4 * i)]);
					}
				}
				screwWidgetVal.DeepCopyTransformMatrix(matrix);
				screwWidgetVal.SetScrewUID((*m_ScrewServiceList)[i]->GetScrewUID());

				misScrewWidgetUpdateEvent wchanged;
				wchanged.Set(screwWidgetVal);
				InvokeEvent(wchanged);
				return;
			}
		}
	}
}


void ScrewViewer::ModifyPlane(misPlanWidget* planWidget, misScrewWidgetData& screwWidgetVal)
{
	auto rep = dynamic_cast<IPlanWidgetRepresentation*>(planWidget->GetRepresentation());
	switch (rep->GetInteractionState())
	{
	case 1:
		screwWidgetVal.SetStartPointModified();
		break;
	case 2:
		screwWidgetVal.SetEndPointModified();
		break;
	default:
		break;
	}
}

void ScrewViewer::InvokeEvent(const itk::EventObject& event)
{
	m_Parent->SetViewer(static_cast<IVolumeRenderer*>(m_Parent->GetViewer()));
	m_Parent->InvokeEvent(event);
}


std::shared_ptr<IScrewCompound> ScrewViewer::GetScrewWidgetService(misUID uid)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if (uid == (*m_ScrewServiceList)[i]->GetScrewUID())
		{
			return (*m_ScrewServiceList)[i];
		}
	}
	return 0;
}

void ScrewViewer::SetAllScrewsLocked(bool isLocked)
{
	if (m_ScrewServiceList->empty())
		return;

	for (auto screwItr = m_ScrewServiceList->begin(); screwItr != m_ScrewServiceList->end(); screwItr++)
	{
		(*screwItr)->SetLocked(isLocked);
	}
}

void ScrewViewer::RemoveAllScrewServices()
{
	m_ScrewServiceList->clear();
}

void ScrewViewer::OnScrew(misUID screwUID)
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
			{
				(*m_ScrewServiceList)[i]->SetSelected(true);
				(*m_ScrewServiceList)[i]->On();
			}
		}
	}
}

void ScrewViewer::DeleteAllScrews()
{
	if (m_ScrewServiceList && !m_ScrewServiceList->empty())
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetInteractor(NULL);
		}
		m_ScrewServiceList->clear();
	}
}

void ScrewViewer::DeleteScrew(misUID screwUID)
{
	if (m_ScrewServiceList->empty())
		return;
	OffScrew(screwUID);
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
		{
			(*m_ScrewServiceList)[i]->SetInteractor(NULL);
			m_ScrewServiceList->erase(m_ScrewServiceList->begin() + i);
		}
	}
}

void ScrewViewer::OffScrew(misUID screwUID)
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
			{
				(*m_ScrewServiceList)[i]->SetSelected(false);
				(*m_ScrewServiceList)[i]->Off();
			}
		}
	}
}

void ScrewViewer::HighlightScrew(misUID screwUID, bool highlight)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		(*m_ScrewServiceList)[i]->HighlightScrew(false);
		if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
		{
			(*m_ScrewServiceList)[i]->HighlightScrew(highlight);
		}
	}
}

void ScrewViewer::Clear()
{
	m_ScrewServiceList->clear();
}

void ScrewViewer::OffAllScrews()
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetSelected(false);
			(*m_ScrewServiceList)[i]->Off();
		}
	}
}

void ScrewViewer::OnAllScrews()
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			(*m_ScrewServiceList)[i]->SetSelected(true);
			(*m_ScrewServiceList)[i]->On();
		}
	}
}