#include "stdafx.h"
#include "misVolumeCropping.h"
#include <misApplicationSetting.h>
#include <IVolume3DRenderer.h>

misVolumeCropping::misVolumeCropping(std::weak_ptr<INavigationViewersNView> groupViewer, misCroppingDirectionInVR croppingDirection)
	:m_GroupViewer(groupViewer), m_CroppingDirection(croppingDirection)
{

}

void misVolumeCropping::CropVolume(bool oblique,  const double* planeNormal,
	const double* center)
{
	auto groupViewer = m_GroupViewer.lock();

	if (oblique)
		groupViewer->ClipVolumeWithObliquePlane(planeNormal, center);
	else
		groupViewer->SetCroppingDirection(m_CroppingDirection,
			groupViewer->GetCurrentPosition().Elements(), oblique);
}

void misVolumeCropping::UpdateCroppingDirection()
{
	auto groupViewer = m_GroupViewer.lock();

	for (auto volume3D : groupViewer->Get3DViewers())
	{
		auto currentPosition = groupViewer->GetCurrentPosition();
		volume3D->SetToolPosition(currentPosition[0], currentPosition[1], currentPosition[2]);
		volume3D->Get3DViewer()->SetCroppingDirection(m_CroppingDirection);
		volume3D->ModifyVolume();
		volume3D->CompileVolumeShader();
	}
}

misCroppingDirectionInVR misVolumeCropping::GetCroppingDirection() const
{
	return m_CroppingDirection;
}

void misVolumeCropping::SetCroppingDirection(misCroppingDirectionInVR val)
{
	m_CroppingDirection = val;
}

void misVolumeCropping::SetGroupViewer(std::weak_ptr<INavigationViewersNView> groupViewer)
{
	m_GroupViewer = groupViewer;
}

void misVolumeCropping::UpdateViewBasedOnCroppingDirection()
{
	auto groupViewer = m_GroupViewer.lock();

	auto p3DViewers = groupViewer->Get3DViewers();
	for (auto viewer : p3DViewers)
	{
		auto medicalDirection = viewer->GetMedicalCameraDirection();
		switch (m_CroppingDirection)
		{
		case NoCut:
			{
			
				medicalDirection->SetDefaultVeiw();
				break;
			}
		case AnteriorCut:
			{
				medicalDirection->SetAnteriorView();
				break;
			}
		case AnteriorDown:
			{
				medicalDirection->SetAnteriorView();
				break;
			}
		case AnteriorUp:
			{
				medicalDirection->SetAnteriorView();
				break;
			}
		case CoronalUp:
			{
				medicalDirection->SetSupriorView();
				break;
			}
		case CoronalDown:
			{
				medicalDirection->SetInferiorView();
				break;
			}
		case SagittalRight:
			{
				medicalDirection->SetRightView();
				break;
			}
		case SagittalLeft:
			{
				medicalDirection->SetLeftView();
				break;
			}
		}
	}
}
