#pragma once
#include "misRepresentation.h"
#include "misVideoMapper.h"
class misVideoRepresentation : public misRepresentation
{
public:
	igstkStandardClassBasicTraitsMacro(misVideoRepresentation,misRepresentation);
	static Pointer New(string name);

	void InitializeMapper(misTexturePropertyStruct PlaneProp , HWND HandleWindow, std::wstring deviceName );
	void TerminateVideoCapture();
	void SetTransformMatrix(vtkMatrix4x4* transformMat);
	void SetTransformOffset(double pos[3]);
	
private:

	misVideoRepresentation(string name);
	~misVideoRepresentation(void);

	misVideoMapper* m_VideoMapper;
	vtkActor* m_VideoActor;


	
};

