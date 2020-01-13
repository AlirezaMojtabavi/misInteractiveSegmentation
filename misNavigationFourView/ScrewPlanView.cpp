#include "stdafx.h"
#include "..\Header\ScrewPlanView.h"
#include <IVolume3DRenderer.h>


parcast::ScrewPlanView::ScrewPlanView(std::shared_ptr<INavigationViewersNView> n4View)
	:m_GroupViewer(n4View)
{
}


parcast::ScrewPlanView::~ScrewPlanView()
{
}



void parcast::ScrewPlanView::DeleteScrew(misUID screwUID)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		tmp3DViewers[i]->DeleteScrew(screwUID);
	}
}

void parcast::ScrewPlanView::ShowScrew(misUID screwUID)
{
	for (auto viewer : m_GroupViewer->GetAllPackageViewers())
	{
		viewer->GetViewer()->OnScrew(screwUID);
	}
}

void parcast::ScrewPlanView::HighlightScrew(misUID screwUID, bool highight)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		tmp3DViewers[i]->HighlightScrew(screwUID, highight);
	}
}

void parcast::ScrewPlanView::DeleteAllScrews()
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		tmp3DViewers[i]->DeleteAllScrews();
	}
}

void parcast::ScrewPlanView::Lock3DWiewerScrews()
{
	auto tmp3DViewers = m_GroupViewer->Get3DViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		tmp3DViewers[i]->LockAllScrews();
	}
}

void parcast::ScrewPlanView::Lock2DWiewerScrews()
{
	auto tmp2DViewers = m_GroupViewer->Get2DViewers();
	for (int i = 0; i < tmp2DViewers.size(); i++)
	{
		tmp2DViewers[i]->LockAllScrews();
	}
}

void parcast::ScrewPlanView::ResetScrewTransfom()
{
	auto imageViewers = m_GroupViewer->Get2DViewers();
	if (imageViewers.empty())
		return;

	misSimplePointType currentPos = imageViewers[0]->GetCornerProperties()->GetSightLineIntersectionPoint();
	misUpdatePositionInfoStruct UpdatePosStr;
	UpdatePosStr.CornerTransform->SetElement(0, 3, currentPos.data[0]);
	UpdatePosStr.CornerTransform->SetElement(1, 3, currentPos.data[1]);
	UpdatePosStr.CornerTransform->SetElement(2, 3, currentPos.data[2]);
	imageViewers[0]->GetCornerProperties()->SetMatrix(UpdatePosStr.CornerTransform);
	imageViewers[0]->UpdateImage(true);
	UpdatePosStr.IsCameraUpdate = true;
	misUpdatePositionEvent ev;
	ev.Set(UpdatePosStr);
	imageViewers[0]->InvokeEvent(ev);
}

void parcast::ScrewPlanView::SetScrewColor(misUID screwUID, misColorStruct color)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		auto tmpWidget = tmp3DViewers[i]->GetScrewWidgetService(screwUID);
		if (tmpWidget)
		{
			tmpWidget->SetColor(color);
		}
	}
}

void parcast::ScrewPlanView::SetScrewWidth(misUID screwUID, double width)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		auto tmpWidget = tmp3DViewers[i]->GetScrewWidgetService(screwUID);
		if (tmpWidget)
		{
			tmpWidget->SetWidth(width);
		}
	}

}


void  parcast::ScrewPlanView::FreeImagesScrew(misUID screwUID)
{
	auto imageViewers = m_GroupViewer->Get2DViewers();
	for (int i = 0; i < imageViewers.size(); i++)
		imageViewers[i]->GetScrewWidgetService(screwUID)->SetFreeStateValue();
}



void  parcast::ScrewPlanView::SetScrewInteractionStyleToFreeLength(misUID screwUID)
{
	auto imageViewers = m_GroupViewer->Get2DViewers();
	for (int i = 0; i < imageViewers.size(); i++)
	{
		imageViewers[i]->GetScrewWidgetService(screwUID)->SetExtendStateValues(500);
	}
}
void parcast::ScrewPlanView::LockScrews(misUID screwUID)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{
		if (!tmp3DViewers[i])
			continue;
		if (!tmp3DViewers[i]->GetScrewWidgetService(screwUID))
			continue;

		tmp3DViewers[i]->GetScrewWidgetService(screwUID)->SetLocked(true);
	}
}
void parcast::ScrewPlanView::UnLockScrew(misUID screwUID)
{
	auto tmp3DViewers = m_GroupViewer->GetAllLandMarkViewers();
	for (int i = 0; i < tmp3DViewers.size(); i++)
	{

		if (!tmp3DViewers[i]->GetScrewWidgetService(screwUID))
			continue;
		tmp3DViewers[i]->GetScrewWidgetService(screwUID)->SetLocked(false);
	}
}
void parcast::ScrewPlanView::LockAllScrews()
{
	Lock2DWiewerScrews();
	Lock3DWiewerScrews();
}