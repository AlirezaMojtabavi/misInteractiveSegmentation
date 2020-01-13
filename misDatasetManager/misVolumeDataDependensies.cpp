#include "stdafx.h"

#include "misVolumeDataDependensies.h"
#include "IImage.h"
#include "misTransFunctionBuilder.h"
#include "misImageToTextureMap.h"
#include "mis3DModelViewingProperties.h"
#include "misStringTools.h"
#include "IVolumeData.h"

misVolumeDataDependensies::misVolumeDataDependensies()
	: m_VisibilityIn2D(true),
	  parrentImagePointer(0),
	  volume(nullptr),
	  m_AutomaticallyCreated(false)
{
}

std::shared_ptr<IImage> misVolumeDataDependensies::GetImage() const
{
	return parrentImagePointer;
}

void misVolumeDataDependensies::operator=(misVolumeDataDependensies right)
{
	volume = right.volume;
	parrentImagePointer = right.parrentImagePointer;
	m_ParentImageUID = right.GetParentImageUID();
	m_ObjectUID = right.GetObjectUID();
	allObjectVisibility = right.allObjectVisibility;
	m_VisibilityIn2D = right.GetVisibilityIn2D();
	m_AutomaticallyCreated = right.GetAutomaticallyCreated();
}

std::shared_ptr<IVolumeData> misVolumeDataDependensies::GetVolume() const
{
	return volume;
}

void misVolumeDataDependensies::SetVolume(std::shared_ptr<IVolumeData> val)
{
	volume = val;
	if (m_ObjectUID.empty())
	{
		m_ObjectUID = misStringTools::GenerateNewUID();
	}
}

void misVolumeDataDependensies::SetImage(std::shared_ptr<IImage> image)
{
	parrentImagePointer = image;
	if (volume)
	{
		volume->SetImage(image);
	}
}

misObjectVisibilityMap misVolumeDataDependensies::GetAllObjectVisibility() const
{
	return allObjectVisibility;
}

int misVolumeDataDependensies::SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap)
{
	if (m_TransferFunction && m_TransferFunction->getNumKeys() > 0)
	{
		return 1;
	}
	volume->SetComponentVisiblityByMap(visibilityMap);
	return visibilityMap.size();
}

void misVolumeDataDependensies::SetAllObjectVisibility(const misObjectVisibilityMap &val)
{
	allObjectVisibility = val;
}

void misVolumeDataDependensies::ClearObjectVisibilities()
{
	allObjectVisibility.clear();
}

void misVolumeDataDependensies::SetObjectVisibilityProperties(
	const misUID &uid, const mis3DModelObjectOpacityPropertiesStrct &properties)
{
	allObjectVisibility[uid] = properties;
}

bool misVolumeDataDependensies::
GetObjectVisibilityProperties(const misUID &uid, mis3DModelObjectOpacityPropertiesStrct& model) const
{
	auto found = allObjectVisibility.find(uid);
	if (found != allObjectVisibility.end())
	{
		model = found->second;
		return true;
	}
	return false;
}

void misVolumeDataDependensies::DeleteObjectVisibility(misUID uid)
{
	allObjectVisibility.erase(uid);
}

bool misVolumeDataDependensies::SetObjectVisibility(
	const misUID &uid, misPresentationDimension whichScene, bool visibility)
{
	auto found = allObjectVisibility.find(uid);
	if (found == allObjectVisibility.end())
	{
		return false;
	}
	if (whichScene == twoDimension)
	{
		found->second.visibilityIn2DScene = visibility;
	}
	else if (whichScene == threeDimension)
	{
		found->second.SetVisibilityIn3DScene(visibility);
	}
	return true;
}

bool misVolumeDataDependensies::SetObjectVisibility(const misUID &uid, bool visibility)
{
	auto found = allObjectVisibility.find(uid);
	if (found == allObjectVisibility.end())
	{
		return false;
	}
	found->second.visibilityIn2DScene = visibility;
	found->second.SetVisibilityIn3DScene(visibility);
	return true;
}

bool misVolumeDataDependensies::SetObjectOpacity(const misUID &uid, misPresentationDimension whichScene, double opacity)
{
	auto found = allObjectVisibility.find(uid);
	if (found == allObjectVisibility.end())
	{
		return false;
	}
	if (whichScene == twoDimension)
	{
		found->second.SetOpacityIn2DScene(opacity);
	}
	else if (whichScene == threeDimension)
	{
		found->second.OpacityIn3DScene = opacity;
	}
	return true;
}
bool misVolumeDataDependensies::SetObjectOpacity(const misUID &uid, double opacity)
{
	auto found = allObjectVisibility.find(uid);
	if (found == allObjectVisibility.end())
	{
		return false;
	}
	found->second.SetOpacityIn2DScene(opacity);
	found->second.OpacityIn3DScene = opacity;
	return true;
}
bool misVolumeDataDependensies::GetVisibilityIn2D() const
{
	return m_VisibilityIn2D;
}

void misVolumeDataDependensies::SetVisibilityIn2D(bool val)
{
	m_VisibilityIn2D = val;
}

misUID misVolumeDataDependensies::GetObjectUID() const
{
	return m_ObjectUID;
}

void misVolumeDataDependensies::SetAllObjectVisibility(bool visibility)
{
	for (auto itr = allObjectVisibility.begin(); itr != allObjectVisibility.end(); itr++)
	{
		if (visibility)
		{
			itr->second.SetAllVisible();
		}
		else
		{
			itr->second.SetAllInvisible();
		}
	}
}

void misVolumeDataDependensies::SetObjectUID(misUID val)
{
	m_ObjectUID = val;
}

bool misVolumeDataDependensies::GetAutomaticallyCreated() const
{
	return m_AutomaticallyCreated;
}

void misVolumeDataDependensies::SetAutomaticallyCreated(bool val)
{
	m_AutomaticallyCreated = val;
}

std::shared_ptr<TransFuncIntensity> misVolumeDataDependensies::
GetTransferFunction(misPresentationDimension presentationDim)
{
	if (m_TransferFunction && m_TransferFunction->getNumKeys() > 0)
	{
		return m_TransferFunction;
	}
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(GetImage());
	misTransFunctionBuilder	trasferfunction;
	auto opacityColorMappingLst = volume->GetOpacityColorMap(presentationDim);
	auto TableRange = imageTexure->GetTableRange();
	auto transfunc = trasferfunction.GenerateTransferFunction(opacityColorMappingLst, TableRange);
	return transfunc;
}

void misVolumeDataDependensies::SetTransferFunction(std::shared_ptr<TransFuncIntensity> transfunction)
{
	m_TransferFunction = transfunction;
}

std::shared_ptr<TransFuncIntensity> misVolumeDataDependensies::GetTransferFunction() const
{
	return m_TransferFunction;
}

void misVolumeDataDependensies::SetParentImageUID(const misUID& uid)
{
	m_ParentImageUID = uid;
}

misUID misVolumeDataDependensies::GetParentImageUID() const
{
	return  m_ParentImageUID;
}
