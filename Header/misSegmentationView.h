#pragma once
#include "misGoupViewerFourViwer.h"
#include "misHeader.h"
#include "missyncronviwer.h"
//#include "misGroupViewLandMark.h"
#include "misSeedRepresentation.h"
//#include "misROIWidget.h"
#include "misitkImageTypedef.h"

//igstkEventMacro(misHeadRestSeedSelected,misEvent);

class  misSegmentationView:public misSyncronViwer/*misGroupViewLandMark*/
	{

private:

	bool m_IsPointSelectObserverAdded;

public:
	igstkStandardClassBasicTraitsMacro( misSegmentationView,misSyncronViwer/*misGroupViewLandMark*/) ;
	igstkNewMacro(Self);
//	misROIWidget* m_box;

public:
	misSegmentationView(void);
	~misSegmentationView(void);

//	int          SetImageContaindPolyDatas(misImageContainedPolydata*  pImageContainedPolys);
/*	virtual	void  InitilizeViewer();*/
//	void AddInternalObservers();


	//misitkSeedListType  GetBackgroundLandmarks();
	//misitkSeedListType  GetForegroundLandmarks();

	
	void          ResetSegmentation();
	void		  UpdateAllWidgets(Object *caller, const EventObject & event );
//	void		  UpdateWidgetData(double* );
	void		  SetROI(double*);
	void		  RemoveROI(void);
	void          SetROIDeactive();
	void          SetROIActive();
/*	void		  SetShaderOn();*/
 	//void		  AddHeadRestSeed(Object *caller, const EventObject & event);
//	void		  UpdateSceneAfterRightClickOnROI(IMAGEORIENTATION orientation);
/*	void		  SetImageStatuseByHeadRest(misImageStatus headrestState);*/
//	void		  SetHeadRestState();

/*	bool		  CreateResources();*/
	//bool GetHeadRestState();

	//misImageStatus GetImageStatuseByHeadRest();

	double *      GetWidgetData();
	void          RemoveSegmentedLayer();
protected:
	//misPointWidgetObserverSeeedUpdate*      m_WidgetObserver;
	//misHybridInteractionObserver*			m_pWindowObserver;
	
	//vtkImageData*  m_SegmentedImage;

	/*misImageStatus m_ImageStatus;		//this variable is used for updating GUI during and after Remove Headrest procedure*/
//protected:

//	virtual void InitilizeWidgetandRepresentation();

};
