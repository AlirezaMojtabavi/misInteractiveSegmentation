#pragma once

#include "IGroupViewerSetting.h"

#include "..\misNavigationFourView\misViewingWindowElement.h"
#include "misDistributionEvent.h"
#include "misDistributionMap.h"
#include "misEnums.h"
#include "misSurgeryType.h"
#include "misViewElementGroup.h"
#include "misViewerTypeDirection.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"
#include "misWindowLayout.h"
#include "misWindowsLayout.h"


// The class describe a multi windows synchronize showing images in 2d and 3d 
struct misGroupViewerSetting : public Serializable, public IGroupViewerSetting
{
public:
	misGroupViewerSetting();

	void Reset();
	void SetLandmarkExisted(bool pVal);
	void SetMainWidgetType(misCursorType pCursorType);
	void SetVolumeViewingType(misVolumeViewingTypes pVolumeViewingType);
	int GetNumberOfViewers();
	misViewerTypeDirection GetTypeOfViewer(int pElement);
	misVolumeViewingTypes GetVolumeViewingType();
	// Return visibility state of a group of elements - each group have an identical plane visibility state
	std::map<misPlaneEnum, bool> GetPlaneVisibilityStatus(int viewerIndex);
	misCursorType GetMainWidgetType();
	misSurgeryType GetSurgeryType();
	IMAGEORIENTATION GetOrientation(int pElement);
	bool GetKeepColor();
	void SetKeepColor(bool val);
	misViewPort GetViewPort( int groupIndex , int subIndex );
	void AddWindowGroup(const misViewElementGroup& windowElement );


	const misViewElementGroup& GetElement(int index) const;
	int GetNumberOfGroupElement() const;
	misDistributionMap* FindDistributionMap(const itk::EventObject*  pEvent);
	void SetAllMapTo(const itk::EventObject*  pEvent, bool val);
	void SetElementTo(const itk::EventObject*  pEvent,int i , int j , bool val);
	void SetAllElemetsToDefault(const itk::EventObject*  pEvent);
	misWindowsLayout GetWindowsLayout();
	void SetWidgetLineWidth(double const width) override;
	double GetWidgetLineWidth() const override;
	void SetWidgetColorComposition(const parcast::AxesColors& colors) override;
	parcast::AxesColors GetWidgetColorComposition() const override;



	virtual void serialize(XmlSerializer& s) const override;
	virtual void deserialize(XmlDeserializer& s) override;

private:
	void UpdateDistribuationMap();

	bool m_LandmarkExisted;
	misCursorType m_CursorType;
	misVolumeViewingTypes m_VolumeViewingType;
	misSurgeryType	m_SurgeryType;
	std::vector<misViewElementGroup> m_WindowElementGroups;
	
	// size of vector is equal to number of events that are managed.
	std::vector<misDistributionMap*> m_DistributionMaps;
	bool m_KeepColorInGroupViewer;
	double m_WidgetWidth = 1.0 ;
	double m_LineWidth = 1.0;
	parcast::AxesColors m_WidgetColors;
};
