#pragma once
#include "misPolyDataPropInImageContainted.h"

typedef std::vector<int> misAllocatedByteNumbersTypdef;
struct misColorVector2D3D
{
	misColorVector colorVector2D;
	misColorVector colorVector3D;

	void Reset()
	{
		colorVector2D.clear();
		colorVector3D.clear();
	};
	misColorVector2D3D()
	{
		Reset();
	};
};

typedef std::map<misAllocatedByteNumbersTypdef, misColorVector2D3D> misPolyDatesColormapTypedef;

typedef std::vector<misUID> SelectedPolyDatasTypedef;
class misPolyDatasSpecifications
{

public:
	misPolyDatasSpecifications(void);
	~misPolyDatasSpecifications(void);

	misPolyDatesColormapTypedef GetPolyDatasColorTable(void);
	misPolyDataPropInImageContainted GetPolyDataProperties(misUID polydataUID);
	misAllocatedByteNumbersTypdef GetPolyDataAllByteNembers(misUID polydataUID);
	int GetNumberOfObjects();
	void Reset(void);
	bool ReplaceUID(misUID oldUID, misUID newUID);
	bool ShowMargin(misUID polydataUID, bool val);
	bool SetPolyDataColor(misUID polydataUID, misColorStruct color);
	bool SetPolyDataOpacity(misUID polydataUID, mis3DModelObjectOpacityPropertiesStrct opacity);
	bool SetPolyDataVolume(misUID polydataUID, double volume);
	bool SetPolyDataName(misUID polydataUID, std::string polydataName);
	bool SetPolyDataOpacityScale(double opacityScale);
	bool AddNewPolyData(misUID parrentImageUID, misUID polydataUID, int requiredBitNumber);
	bool AddNewPolyData(misUID parentImageUID, misUID polydataUID, misAllocatedByteNumbersTypdef allByteIndex);
	bool DeletePolyData(misUID polydataUID);
	void DeleteAllObjects();
	void SetViewableObjectAll();
	void SetViewableObjectNone();
	void SetViewableObjectUIDsOnly(SelectedPolyDatasTypedef viewableObjects);
	void SetViewableObjectByMap(misObjectVisibilityMap visiblityMap);
	int GetNumberOfViewableObject();
	int  FindPolyDataSpecIndex(misUID polyDataUID);
	void SetAlarmMargin(misUID objectUID, bool val);
	bool GetAlarmMargin(misUID objectUID);
	void ShowMarginRegion(misUID objectUID, bool val);
	bool GetShowMarginRegion(misUID objectUID);
	void SetMarginValue(misUID objectUID, double marginVal);
	double GetMarginValue(misUID objectUID);
	std::map<misUID, bool> GetAllObjectsUIDMarginStat();
	void AddObjectExtent(misUID objectUID, int* objectExtent);

private:

	int  FindFreeIndex(int requiredBitNumber);
	void UpdatePolyDatasColorMaps(void);
	PolyDataSpecificationListTypedef  m_PolyDataSpecifications;
	misPolyDatesColormapTypedef  m_PolyDatasColorMaps;
	bool m_ShowMariginAll;
	bool m_ComplementColorForMargin;
	bool m_ModificationFlag;
	bool m_AlarmMargin;


};

