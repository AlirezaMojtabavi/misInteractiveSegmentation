#pragma once

#include "misObject.h"
#include "IVolume3DRenderer.h"

class misVolumeRendererContainer : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misVolumeRendererContainer, misOldObject);
	igstkNewMacro(Self);
	IVolumeRenderer* GetViewer() const;
	void SetViewer(IVolumeRenderer* val);
private:
	IVolumeRenderer* m_Viewer;

};