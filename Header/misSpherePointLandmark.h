#pragma once
#include "misPointLandMark.h"

class misSpherePointLandmark :	public misPointLandMark
{
public:
	misSpherePointLandmark(bool disableDepth);
	void GenerateGeometry() override;
private:
	bool m_DisableDepth = true;
};

