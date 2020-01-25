#pragma once

#include "misObject.h"

class IVolumeRenderer;

class misVolumeRendererContainer : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misVolumeRendererContainer, misOldObject);
	igstkNewMacro(Self);
	IVolumeRenderer* GetViewer() const;
	void SetViewer(IVolumeRenderer* val);
private:
	IVolumeRenderer* m_Viewer = nullptr;

};
