#pragma once
#pragma  once
#include "misEnums.h"
#include "misobjectProperitiesEnums.h"
#include "misSurgeryType.h"
#include "misViewPort.h"
#include "misViewElementGroup.h"
#include "misDistributionMap.h"
#include "misWindowsLayout.h"
#include "VisualizationGeneralTypes.h"
#include "AxesColors.h"
#include "misVolumeViewingTypes.h"

class IGroupViewerSetting
{
public:
	typedef std::map<misPlaneEnum, bool> MapType;
	virtual void Reset() = 0;
	virtual void SetLandmarkExisted(bool pVal) = 0;
	virtual void SetVolumeViewingType(misVolumeViewingTypes pVolumeViewingType) = 0;
	//--------Widget Props Get/Set
	virtual void SetMainWidgetType(misCursorType pCursorType) = 0;
	virtual void SetWidgetLineWidth(const double  width) = 0;
	virtual void SetWidgetColorComposition(const parcast::AxesColors& colors) = 0;

	virtual parcast::AxesColors GetWidgetColorComposition() const = 0;
	virtual double GetWidgetLineWidth() const = 0;
	virtual misCursorType GetMainWidgetType() = 0;
	//---------------------------------------------

	virtual int GetNumberOfViewers() = 0;
	virtual misViewerTypeDirection GetTypeOfViewer(int pElement) = 0;
	virtual misVolumeViewingTypes GetVolumeViewingType() = 0;
	// Return visibility state of a group of elements - each group have an identical plane visibility stat = 0e
	virtual MapType GetPlaneVisibilityStatus(int viewerIndex) = 0;
	virtual misSurgeryType GetSurgeryType() = 0;
	virtual IMAGEORIENTATION GetOrientation(int pElement) = 0;
	virtual bool GetKeepColor() = 0;
	virtual void SetKeepColor(bool val) = 0;
	virtual misViewPort GetViewPort(int groupIndex, int subIndex) = 0;
	virtual void AddWindowGroup(const misViewElementGroup& windowElement) = 0;
	virtual const misViewElementGroup& GetElement(int index) const = 0;
	virtual int GetNumberOfGroupElement() const = 0;
	virtual misDistributionMap* FindDistributionMap(const itk::EventObject*  pEvent) = 0;
	virtual void SetAllMapTo(const itk::EventObject*  pEvent, bool val) = 0;
	virtual void SetElementTo(const itk::EventObject*  pEvent, int i, int j, bool val) = 0;
	virtual void SetAllElemetsToDefault(const itk::EventObject*  pEvent) = 0;
	virtual misWindowsLayout GetWindowsLayout() = 0;
	virtual  void serialize(XmlSerializer& s) const = 0;
	virtual  void deserialize(XmlDeserializer& s) = 0;
	~IGroupViewerSetting() {}


};

