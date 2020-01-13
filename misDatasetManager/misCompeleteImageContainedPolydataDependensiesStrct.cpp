#include "stdafx.h"
#include "misCompeleteImageContainedPolydataDependensiesStrct.h"
#include "misTransFunctionBuilder.h"
#include "misStringTools.h"
#include "misImageContained.h"
#include "misGuiStructures.h"
#include "misSegmentedObjectTransferFunction.h"
#include "misShort3DModelViewingStrct.h"


misCompeleteImageContainedPolydataDependensiesStrct::misCompeleteImageContainedPolydataDependensiesStrct()
	: m_ImageContained(std::make_shared<misImageContained>()),
	m_ObjectUID(misStringTools::GenerateNewUID())
{
}



void misCompeleteImageContainedPolydataDependensiesStrct::SetParentUID(const misUID& uid)
{
	m_ParentUID = uid;
}

misUID misCompeleteImageContainedPolydataDependensiesStrct::GetParentUID() const
{
	return  m_ParentUID;
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetImageContained(const std::shared_ptr<IImageContained> imageCOntained)
{
	m_ImageContained = imageCOntained;
}

std::shared_ptr<IImageContained> misCompeleteImageContainedPolydataDependensiesStrct::GetImageContained() const
{
	return m_ImageContained;
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetObjectUID(const misUID& uid)
{
	m_ObjectUID = uid;
}

misUID misCompeleteImageContainedPolydataDependensiesStrct::GetObjectUID() const
{
	return m_ObjectUID;
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetAllObjectVisibility(const misObjectVisibilityMap& visibilityMap)
{
	m_AllObjectVisibility = visibilityMap;
}

misObjectVisibilityMap misCompeleteImageContainedPolydataDependensiesStrct::GetAllObjectVisibility() const
{
	return m_AllObjectVisibility;
}

void misCompeleteImageContainedPolydataDependensiesStrct::AddObjectVisibility(const misObjectVisibilityPair& objectVisibilty)
{
	m_AllObjectVisibility.insert(objectVisibilty);
}

void misCompeleteImageContainedPolydataDependensiesStrct::RemoveObjcteVisibility(const misUID& segmentedObjUID)
{
	auto it = m_AllObjectVisibility.find(segmentedObjUID);
	if (it != m_AllObjectVisibility.end())
	{
		m_AllObjectVisibility.erase(it);
	}
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetAlarmMargin(const misUID& SegmentedObjectUID, bool val)
{
	m_ImageContained->SetAlarmMargin(SegmentedObjectUID, val);
}

void misCompeleteImageContainedPolydataDependensiesStrct::ShowMarginRegion(const misUID& SegmentedObjectUID, bool val)
{
	m_ImageContained->ShowMarginRegion(SegmentedObjectUID, val);
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetObjctVisibility(misUID uid, mis3DModelObjectOpacityPropertiesStrct prop)
{
	m_AllObjectVisibility[uid] = prop;
}

void misCompeleteImageContainedPolydataDependensiesStrct::Set2dVisibility(misUID objectUID, bool visibility)
{
	auto it = m_AllObjectVisibility.find(objectUID);
	if (it != m_AllObjectVisibility.end())
	{
		m_AllObjectVisibility[objectUID].visibilityIn2DScene = visibility;
	}
}

void misCompeleteImageContainedPolydataDependensiesStrct::Set3dVisibility(misUID objectUID, bool visibility)
{
	auto it = m_AllObjectVisibility.find(objectUID);
	if (it != m_AllObjectVisibility.end())
	{
		m_AllObjectVisibility[objectUID].SetVisibilityIn3DScene(visibility);
	}
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetOpacity(misUID objectUID, double opacity)
{
	auto it = m_AllObjectVisibility.find(objectUID);
	if (it != m_AllObjectVisibility.end())
	{
		m_AllObjectVisibility[objectUID].SetOpacityIn2DScene(opacity);
		m_AllObjectVisibility[objectUID].OpacityIn3DScene = opacity;
	}
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetAllInvisible()
{
	for (misObjectVisibilityPair visibility : m_AllObjectVisibility)
	{
		m_AllObjectVisibility[visibility.first].SetAllInvisible();
	}
}

std::vector<misShort3DModelViewingStrct> misCompeleteImageContainedPolydataDependensiesStrct::GetPolydataStrcViewing() const
{
	std::vector<misShort3DModelViewingStrct> PolydataViewingPropList;
	if (!m_ImageContained)
	{
		return PolydataViewingPropList;
	}
	auto polydataStrc = m_ImageContained->GetPolydataPropertyStruct();;
	for (int i = 0; i < polydataStrc.size(); i++)
	{
		misShort3DModelViewingStrct PolydataViewingProp;
		PolydataViewingProp.color = polydataStrc[i].PolyDataColor;
		PolydataViewingProp.name = polydataStrc[i].PolyDataName;
		PolydataViewingProp.objectUID = polydataStrc[i].PolyDataUID;
		auto polydataUID = polydataStrc[i].PolyDataUID;
		PolydataViewingProp.parentImageUID = m_ParentUID;
		auto machedMap = m_AllObjectVisibility.find(polydataUID);
		if (machedMap != m_AllObjectVisibility.end())
		{
			PolydataViewingProp.visibility3D = machedMap->second.GetVisibilityIn3DScene();
			PolydataViewingProp.segmentedObjectVisibility = machedMap->second.visibilityIn2DScene;
			PolydataViewingProp.opacity = machedMap->second.GetOpacityIn2DScene();
			PolydataViewingProp.renderingType = misSurfaceRendering;
			PolydataViewingProp.objectContainerUID = m_ImageContained->GetUID();
			PolydataViewingPropList.push_back(PolydataViewingProp);
		}
	}
	return PolydataViewingPropList;
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetObjectColor(misUID polyDataUID, misColorStruct polyDataColor)
{
	auto foundedObject = m_AllObjectVisibility.find(polyDataUID);
	if (foundedObject == m_AllObjectVisibility.end())
	{
		return;
	}
	m_ImageContained->SetObjectColor(polyDataUID, polyDataColor);
}

void misCompeleteImageContainedPolydataDependensiesStrct::ClearVisibilities()
{
	m_AllObjectVisibility.clear();
}

bool misCompeleteImageContainedPolydataDependensiesStrct::HasVisibilityProperties(misUID polyDataUID)
{
	auto it = m_AllObjectVisibility.find(polyDataUID);
	return (it != m_AllObjectVisibility.end());
}

void misCompeleteImageContainedPolydataDependensiesStrct::SetinitilizeProperties(double segmentedObjectOpacityScale, misUID imageUID)
{
	m_ImageContained->SetOpacityScale(segmentedObjectOpacityScale);
	SetParentUID(imageUID);
	m_ImageContained->ShowMargin(true);
	m_ImageContained->UseDepositColorForBordersOff();
	SetAllInvisible();
}

std::vector<misSegmentedObjectTransferFunction> misCompeleteImageContainedPolydataDependensiesStrct::GetTransferFuncs() const
{
	auto polydataColorMap = m_ImageContained->GetPolyDatasColorMap();
	std::vector<misSegmentedObjectTransferFunction> ImgContTFs;
	for (auto polyColrMap : polydataColorMap)
	{
		misSegmentedObjectTransferFunction segmentedObjTF;
		segmentedObjTF.allocatedByte = polyColrMap.first;
		if (polyColrMap.second.colorVector2D.size())
		{
			segmentedObjTF.SetTf(misTransFunctionBuilder::GenerateTransferFunction(polyColrMap.second.colorVector2D));
			ImgContTFs.push_back(segmentedObjTF);
		}
	}
	return ImgContTFs;
}
