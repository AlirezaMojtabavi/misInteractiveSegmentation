
#pragma once
#include "misHeader.h"
#include "misgoupviewerfourviwer.h"
//#include "misPointSelctObserver.h"
#include "misColorPointWidget.h"
#include "misSyncronViwer.h"
class misHybridInteractionObserver;

class MISDLLEXPORT misNavigationView :public misSyncronViwer
{

protected:
	

	misNavigationView(void);
	/*void ContrastSetting(Object *caller, const EventObject & event );*/
//	vtkTransform* m_pTransform;
	
	double			m_MinOpacityForSettingWinLev;
public:
	igstkStandardClassBasicTraitsMacro( misNavigationView, misGoupViewerFourViwer )  ;
	igstkNewMacro( Self );  

/*	double* GetPosition();;*/

	/*virtual void InitilizeWidgetandRepresentation();*/
	//updtae image position with tracker data that previously attached to navigation viewer

	/*virtual void	UpdateSettingFromAppSetting();*/
/*	void ApplyWidget();*/

//	void  AddLeftButtomPressObserver();
	//void SetTransform(vtkTransform* pTransForm);
	/*void ChangeWidgetType(misCursorType cursorType);*/
	void AddLandmark(int index,double*pos, misLandmarkType landmarkType);
	void RemoveLandmark( int index );
 	
 	void Hidelandmark(int id);
 	void ShowLandmark(int id);

	~misNavigationView(void);
//	void AddAllPackageContent( misSimpleDataPackage* package );
//	void SetMinOpacityForSettingWinLev( double threshold );
	void SetErasingProperties();
};
