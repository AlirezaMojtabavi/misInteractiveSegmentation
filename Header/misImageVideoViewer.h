#pragma once
#include "misimageviewer.h"
#include "misVideoMapper.h"
#include "misVideoRepresentation.h"

class misImageVideoViewer : public misImageViewer
{
public:
	igstkStandardClassBasicTraitsMacro(misImageVideoViewer,misImageViewer);
	igstkNewMacro(misImageVideoViewer);

	misImageVideoViewer(void);
	~misImageVideoViewer(void);

	virtual void AddRepresentation(misRepresentation* pRepresentation);
	void TerminateCapture();
	virtual void     Render();

	void UpdateCurrentPosition( double pos[3] );
	void UpdateTransformMatrix( vtkMatrix4x4* currMatrix );

private:

	misVideoRepresentation::Pointer m_VideoRep;
	std::wstring s2ws(const std::string& s);
	
};

