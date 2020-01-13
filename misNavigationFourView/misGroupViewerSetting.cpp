#include "stdafx.h"
#include "misGroupViewerSetting.h"

#include "misEnumUtilities.h"
#include "misScrewWidgetData.h"
#include "misWindowsLayout.h"
#include "misWindowLayout.h"
#include "misDirectionStringConevrtor.h"

void misGroupViewerSetting::SetElementTo( const itk::EventObject* pEvent,int i , int j , bool val )
{
	misDistributionMap* TargetMap = FindDistributionMap(pEvent);
	if (TargetMap)
		TargetMap->SetElementTo(i , j , val);
	else
		_ASSERT( 0 == 1 );
}

void misGroupViewerSetting::SetAllElemetsToDefault( const itk::EventObject* pEvent )
{
	misDistributionMap* TargetMap = FindDistributionMap(pEvent);
	if (TargetMap)
		TargetMap->SetAllElemetsToDefault();
	else
		_ASSERT( 0 == 1 );
}

misWindowsLayout misGroupViewerSetting::GetWindowsLayout()
{
	misWindowsLayout layOut;
	for (int i =0 ; i< m_WindowElementGroups.size(); i++)
	{
		misWindowLayout window;
		window.SetPosition(m_WindowElementGroups[i].GetPosition());
		window.SetSize(m_WindowElementGroups[i].GetSize());
		misDirectionStringConevrtor convertor;
		window.SetViewerTypeDirection(convertor.ConvertDirectionToString(m_WindowElementGroups[i].GetTypeOfViewer()));

		bool is2D = (m_WindowElementGroups[i].GetTypeOfViewer() == Viewer3DLandmark || m_WindowElementGroups[i].GetTypeOfViewer() == Viewer3DLandmarkPlanning )? false : true;
		window.SetIs2D(is2D);
		window.SetIsOblique(m_WindowElementGroups[i].GetIsObliq());
		layOut.AddWindow(window);
	}
	return layOut;
}

void misGroupViewerSetting::SetWidgetLineWidth(double const width)
{
	m_WidgetWidth = width;
}

void misGroupViewerSetting::SetWidgetColorComposition(const parcast::AxesColors& colors)
{
	m_WidgetColors = colors;
}

parcast::AxesColors misGroupViewerSetting::GetWidgetColorComposition() const
{
	return m_WidgetColors;
}

double misGroupViewerSetting::GetWidgetLineWidth() const
{
	return m_WidgetWidth;
}

void misGroupViewerSetting::serialize(XmlSerializer& s) const
{
 
	auto cursor = misEnumUtilities::ConvertCursorTypeEnumToString(m_CursorType);
	s.serialize("CursorType", cursor);
	s.serialize("Windows", m_WindowElementGroups);
	auto volumeView = misEnumUtilities::ConvertVolumeViewingEnumToString(m_VolumeViewingType);
	s.serialize("VolumeViewingType", volumeView);

}

void misGroupViewerSetting::deserialize(XmlDeserializer& s)
{
	std::string cursorType;
	s.deserialize("CursorType", cursorType);
	m_CursorType = misEnumUtilities::ConvertCursorTypeStringToEnum(cursorType);
	s.deserialize("Windows", m_WindowElementGroups);
	std::string volumeViewing;
	s.deserialize("VolumeViewingType", volumeViewing);
	m_VolumeViewingType = misEnumUtilities::ConvertVolumeViewingStringToEnum(volumeViewing);
	UpdateDistribuationMap();

}

void misGroupViewerSetting::SetAllMapTo( const itk::EventObject* pEvent, bool val )
{
	misDistributionMap* TargetMap = FindDistributionMap(pEvent);
	if (TargetMap)
		TargetMap->SetAllMapTo(val);
	else
		_ASSERT( 0 == 1 );
}

misDistributionMap* misGroupViewerSetting::FindDistributionMap( const itk::EventObject* pEvent )
{
	for (int i = 0 ; i < m_DistributionMaps.size(); i++)
	{
		if (typeid(*pEvent)==typeid(*m_DistributionMaps[i]->GetEventTypeid()))
		{
			return m_DistributionMaps[i];
		}
	}
	return  NULL;
}

misGroupViewerSetting::misGroupViewerSetting()
{
	misUpdatePositionEvent* pointSelectEvent = new misUpdatePositionEvent();
	misDistributionMap* pointSelect = new misDistributionMap(pointSelectEvent);
	m_DistributionMaps.push_back(pointSelect);

	misBackToPanModeEvent* backToPanModeEvent = new misBackToPanModeEvent();
	misDistributionMap* backToPanMap = new misDistributionMap(backToPanModeEvent);
	m_DistributionMaps.push_back(backToPanMap);

	misPlaneContrastEvent* contrastEvent = new misPlaneContrastEvent();
	misDistributionMap* contrast = new misDistributionMap(contrastEvent);
	m_DistributionMaps.push_back(contrast);

	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = new misDistributionMap(addNextLandmarkEvent);
	m_DistributionMaps.push_back(landMarkMap);

	misUpdateLandmarkStatusEvent* updateLandmarkStatusEvent = new misUpdateLandmarkStatusEvent();
	misDistributionMap* landMarStatuskMap = new misDistributionMap(updateLandmarkStatusEvent);
	m_DistributionMaps.push_back(landMarStatuskMap);

	misROIWidgetUpdateEvent* ROIChangeEvent = new misROIWidgetUpdateEvent();
	misDistributionMap* ROIWidgetMap = new misDistributionMap(ROIChangeEvent);
	m_DistributionMaps.push_back(ROIWidgetMap);

	misScrewWidgetUpdateEvent* screwWidgetChangeEvent = new misScrewWidgetUpdateEvent();
	misDistributionMap* screwWidgetMap = new misDistributionMap(screwWidgetChangeEvent);
	m_DistributionMaps.push_back(screwWidgetMap);

	Reset();
}

misCursorType misGroupViewerSetting::GetMainWidgetType()
{
	return m_CursorType;
}

std::map<misPlaneEnum, bool> misGroupViewerSetting::GetPlaneVisibilityStatus( int viewerIndex )
{
	std::map<misPlaneEnum, bool> resultMap;
	int groupIOndex = 0;
	int rangeCheck = 0;
	while(viewerIndex >= rangeCheck)
	{
		rangeCheck = rangeCheck + m_WindowElementGroups[groupIOndex].GetNumberOfViewer();
		groupIOndex++;
	}
	groupIOndex--;
	if (groupIOndex < m_WindowElementGroups.size())
	{
		resultMap = m_WindowElementGroups[groupIOndex].GetPlaneVisibilityStatus();
	}
	return resultMap;
}

misViewerTypeDirection misGroupViewerSetting::GetTypeOfViewer( int pElement )
{
	if (pElement < m_WindowElementGroups.size())
	{		
		return m_WindowElementGroups[pElement].GetTypeOfViewer();
	}
	return UnSetDirection;
}


void misGroupViewerSetting::Reset()
{
	m_LandmarkExisted = false;
	m_CursorType = NoCursor;
	m_VolumeViewingType = misVolumeViewingTypes::UnsetViewingType;
	m_SurgeryType = ENTBrainSurgery;
	m_KeepColorInGroupViewer = true;
}

void misGroupViewerSetting::SetLandmarkExisted( bool pVal )
{
	m_LandmarkExisted = pVal;
}

void misGroupViewerSetting::SetMainWidgetType( misCursorType pCursorType )
{
	m_CursorType = pCursorType;
}



misSurgeryType misGroupViewerSetting::GetSurgeryType()
{
	return m_SurgeryType;
}

IMAGEORIENTATION misGroupViewerSetting::GetOrientation(int pElement)
{
	misViewerTypeDirection currentTypeDir = GetTypeOfViewer(pElement);
	IMAGEORIENTATION ornt = misEnumUtilities::ConvertViewTypeDirectionToEnum(currentTypeDir);
	return ornt;
}

misVolumeViewingTypes misGroupViewerSetting::GetVolumeViewingType()
{
	return m_VolumeViewingType;
}

int misGroupViewerSetting::GetNumberOfViewers()
{
	int num = 0;
	for (int i =0; i<m_WindowElementGroups.size(); i++)
	{
		num = num + m_WindowElementGroups[i].GetNumberOfViewer();
	}
	
	return num;
}

void misGroupViewerSetting::SetVolumeViewingType( misVolumeViewingTypes pVolumeViewingType )
{
	m_VolumeViewingType = pVolumeViewingType;
}

bool misGroupViewerSetting::GetKeepColor()
{
	return m_KeepColorInGroupViewer;
}

void misGroupViewerSetting::SetKeepColor( bool val )
{
	m_KeepColorInGroupViewer = val;
}


misViewPort misGroupViewerSetting::GetViewPort( int groupIndex , int subIndex )
{
	return m_WindowElementGroups[groupIndex].GetViewPort(subIndex);
}

void misGroupViewerSetting::AddWindowGroup( const misViewElementGroup& windowElement )
{
	m_WindowElementGroups.push_back(windowElement);
	UpdateDistribuationMap();

}

void misGroupViewerSetting::UpdateDistribuationMap()
{
	int num = GetNumberOfViewers();
	for (int i = 0; i < m_DistributionMaps.size(); i++)
	{
		m_DistributionMaps[i]->InitializeInerMap(num);
	}
}

int misGroupViewerSetting::GetNumberOfGroupElement()const
{
	return  m_WindowElementGroups.size();
}

const misViewElementGroup& misGroupViewerSetting::GetElement(int index) const
{
	return m_WindowElementGroups[index];
}

 