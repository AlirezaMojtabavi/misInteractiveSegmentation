#pragma once

#include "misPlaneContrast.h"
#include "misViewPort.h"
#include "misViewerTypeDirection.h"

typedef std::map<misPlaneEnum, bool> PlaneVisibiltyMapType;

//The misViewingWindowElement describes a rectangular region with a normalized view port, direction and Image plane visibility.
class misViewingWindowElement
{
public:
	
	misViewingWindowElement( misViewerTypeDirection direction, std::map<misPlaneEnum, bool> imagePlaneVisibility , 
		int index = 0, double offset = 0);
	 ~misViewingWindowElement(void);
	
	misViewPort GetViewPort() const;
	void SetViewPort(const misViewPort& viewPort);
	std::map<misPlaneEnum, bool> GetPlaneVisibilityStatus() const;
	misViewerTypeDirection GetTypeOfViewer() const;
	double GetOffset()const;

private:
	misViewerTypeDirection m_ViewerTypeDirection;
	std::map<misPlaneEnum, bool>           m_PlaneVisibility;
	misViewPort            m_ViewPort;
	int                    m_WindowIndex;
	double				   m_Offset;
};

