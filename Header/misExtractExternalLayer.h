#pragma once

#include "misNativeWindow.h"
#include "misOffScreenRederer.h"

class misExtractExternalLayer  
 
{
private:

	vtkPolyData*  m_GeneratedPolyData;
	vtkPolyData*  m_InputPolyData;
	
	vtkPolyData*  GenerateExternalLayer(bool ShowIsoSurface);

	float* GetAngles();

	vtkActor* PrepareScene( misWindow m_Window, misNativeWindow &windowMain, std::shared_ptr<I3DViewer> m_Viewer );
	TextLog			m_Logger;
	std::string		loggerCat_;

public:

	
	


	vtkPolyData* getExtractedPolyData();
	misExtractExternalLayer(vtkPolyData*  pInputPolyData,bool ShowIsoSurface );
	~misExtractExternalLayer(void);

 
};

