#pragma once

#include "misObject.h"
#include "IVolumeSlicer.h"

class misPanoramicViewerContainer : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misPanoramicViewerContainer, misOldObject);
	igstkNewMacro(Self);
	std::shared_ptr<IVolumeSlicer> GetPanoramicViewer() const;
	void SetPanoramicViewer(std::shared_ptr<IVolumeSlicer> val);
private:
	std::shared_ptr<IVolumeSlicer> m_PanoramicViewer;

};
