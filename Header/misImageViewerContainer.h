#pragma once

#include "misObject.h"
#include "IVolumeSlicer.h"

class misImageViewerContainer : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misImageViewerContainer, misOldObject);
	igstkNewMacro(Self);
	std::shared_ptr<IVolumeSlicer> GetImageViewer() const;
	void SetImageViewer(std::shared_ptr<IVolumeSlicer> val);
private:
	std::shared_ptr<IVolumeSlicer> m_ImageViewer;
	
};
