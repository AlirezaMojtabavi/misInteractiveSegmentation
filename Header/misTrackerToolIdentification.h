#ifndef MISTRACKERTOOLIDENTIFICATION_H_HEADER_INCLUDED
#define MISTRACKERTOOLIDENTIFICATION_H_HEADER_INCLUDED


#include "mis3DViewer.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingManagerTypes.h"

 
class misToolData;


class   misTrackerToolIdentification :public misOldObject
{
private:
	misTrackerToolIdentification();
	virtual ~misTrackerToolIdentification();
	
	typedef misTrackerToolIdentification Self;
	
	std::shared_ptr<misSurfaceRepresentation> m_toolRep;
	std::shared_ptr<misSurfaceRepresentation> m_refRep;

	std::shared_ptr<I3DViewer>						m_ToolViewr;

public:
	itk::MutexLock::Pointer							m_ShowTrackerToolGUILock;
	misToolData*									m_ToolNeedToBeIdentified;
	
	typedef misTrackerToolIdentification			Self;
	typedef itk::SmartPointer<Self>					Pointer;
	static Pointer New(void); 

	void Initialize(std::shared_ptr<Iwindows>);
	void SetToolNeedToBeIdentified(misToolData* Tool);
	void DoIdentification(misToolData* Tool); 
	void Render();
};

#endif
