#include "vtkCommand.h"
#include "misImageViewer.h"
//#include "misMultiplaneImageViewer.h"
#include "misColorPointWidget.h"
#include "misImageViewer.h"
//#include "misTransformedSeedViewer.h"
class MISDLLEXPORT misImageCorrelationWidgetObserver:public vtkCommand
{
private:
	misImageViewer::Pointer  m_FixedViewer;
	misImageViewer::Pointer  m_MovingViewer;
	//misMultiplaneImageViewer::Pointer m_CorrelatedViewer;

	misColorPointWidget*		  m_FixedWidget;
	misColorPointWidget*		  m_MovingWidget;
	//misColorPointWidget*		  m_CorrelatedWidget;

public:

	static misImageCorrelationWidgetObserver* New()
	{

		return  new misImageCorrelationWidgetObserver;
	}
	misImageCorrelationWidgetObserver();
	~misImageCorrelationWidgetObserver();

	virtual void Execute(vtkObject *caller, unsigned long eventId, void*);

	void SetFixedViewer(misImageViewer::Pointer val);
	void SetMovingViewer(misImageViewer::Pointer val);
	//void SetCorrelatedViewer(misMultiplaneImageViewer::Pointer val);

	void SetFixedWidget(misColorPointWidget* val);
	void SetMovingWidget(misColorPointWidget* val);
	//void SetCorrelatedWidget(misColorPointWidget* val);


private:


};

