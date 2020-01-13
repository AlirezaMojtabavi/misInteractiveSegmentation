#include "misImageViewer.h"
//#include "misMultiplaneImageViewer.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "misColorPointWidget.h"
#include "misImageViewer.h"
#include "misAnalysisStudioTypes.h"
//#include "misTransformedSeedViewer.h"

igstkLoadedEventMacro(misLandmarkSelected,misEvent,misSimplePointType);
igstkLoadedEventMacro(misPointTransformed,misEvent,misSimplePointType);

class    MISDLLEXPORT misImageCorrelationPointSelectObserver :	public vtkCommand
{
private:
	misImageViewer::Pointer  m_FixedViewer;
	misImageViewer::Pointer  m_MovingViewer;
	misImageViewer::Pointer m_CorrelatedViewer;

	misColorPointWidget*		  m_FixedWidget;
	misColorPointWidget*		  m_MovingWidget;
	misColorPointWidget*		  m_CorrelatedWidget;

	double * m_position;

	bool						 m_IsCorrelationDone;
public:

	static misImageCorrelationPointSelectObserver* New()
	{return new misImageCorrelationPointSelectObserver;}


	void SetFixedViewer(misImageViewer::Pointer val);
	void SetMovingViewer(misImageViewer::Pointer val);
	void SetCorrelatedViewer(misImageViewer::Pointer val);


	void SetFixedWidget(misColorPointWidget* val);
	void SetMovingWidget(misColorPointWidget* val);
	void SetCorrelatedWidget(misColorPointWidget* val);

	void SetCorrelationFlag(bool val);

	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	void SetWidgetSyncPosition();

	void ChangeImages( vtkWin32RenderWindowInteractor* pviewer , misImageViewer * imageViewer , misColorPointWidget* widget);

	void SetImagAndWidgetSyncPosition( misImageViewer * imageViewer , misColorPointWidget* widget );

	void ResetImages( misImageViewer * imageViewer );

	double* GetPosition();

	misImageCorrelationPointSelectObserver(void);
	~misImageCorrelationPointSelectObserver(void);
};