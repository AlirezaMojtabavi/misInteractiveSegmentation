#pragma once
#include "misHeader.h"
#include "mis3DLandmarkViewer.h"
#include "misViwerObserevr.h"
 
#include "misSyncronViwer.h"
#include "igstkEvents.h"
class misPointSelctObserver;
class misHybridInteractionObserver;
class misColorPointWidget;
 

 struct misIndexedLandmark
 {
 	int index;
 	misItkPointType  point;
 };

igstkLoadedEventMacro(misChangedwidgetPosition,misEvent,misIndexedLandmark);
itkEventMacro(misAddedSeedEvent,misEvent);

#include "misSeedRepresentation.h"
#include "misPointSelctObserverUpdateLandmark.h"
#include "misPointWidgetObserverLandMarkUpdate.h"
#include "misPointSelctObserver.h"
#include "misitkImageTypedef.h"


class MISDLLEXPORT misGroupViewLandMark  :public misSyncronViwer
{
protected:
	misLandmarkType   m_SeedMode;
	//a  class for capturing position chnaged on image  from vtkpointWidget chanfgging position
	int m_CurrentLandmarkIndex;


	misGroupViewLandMark(void);
	//observe  landmark selection events 

	misViwerObserevr::Pointer             m_ViewerObserver;
/*	void UpdateCurrentLandmarkIndex(void);*/
	void AddLandmarkToImageViewers( double * position );
	void AddNextLandmarkToImageViewers( double * position );
	
	bool m_AddLandmarksTo3DScene;
	virtual	void  AddLeftButtomPressObserver();
	virtual void AddChangeWidgetObserver();

public:
	void SetLandmarkType(misLandmarkType typr);
	void AddLandmarkTo3DScene(bool value);
	void SetCurrentLandmarkPosition(double position[3]);
	
 
public:
	igstkStandardClassTraitsMacro( misGroupViewLandMark,misGoupViewerFourViwer) ;
	virtual void AddLandMark(int index,double position[3],double direction[3]); // used in 3d View
	virtual void AddLandMark(int index,double position[3]);
	virtual void SetLandmarkPosition(int index,double position[3]);
	//void         AddLandMark( double position[3] );
	void		 AddNextLandMark( double position[3] );

	void RemoveLankMark(int index);
	virtual void InitilizeViewer();

	void    SetAddLandmarkByLeftMouseUp(bool value);
	bool    GetAddLandmarkByLeftMouseUp(void);
	

	
	virtual ~misGroupViewLandMark(void);	
	int  GetCurrentLandmarkIndex() const { return m_CurrentLandmarkIndex; }
	void SetCurrentLandmarkIndex(int val) ;
	bool GetLandmarkList(mis3DLandmarkViewer::LandmarkListType* plIst);
	void SetLandmarkList(mis3DLandmarkViewer::LandmarkListType  m_lndList);

	misSimplePointListType  GetLandmarkList(misLandmarkType seedType = misLandmarkType::GeneralSeed);


	void ResetLandMarks();
	void ShowLandmarks();
	void HideLandmarks();
	bool GetFixedLandmarks() const;
	void SetFixedLandmarks(bool val);

	bool UpdateViewWithLandMark(int index, misLandmarkPointerRepresentation*   lnd );
	bool UpdateImagesInLandMarkSelection(double pos[3],bool focalcenterplane=true);
	virtual bool ReleaseResource();
	virtual bool CreateWidgets();

	misHybridInteractionObserver* GetWindowObserver();

protected:
	misHybridInteractionObserver*			m_pWindowObserver;
	misPointWidgetObserverLandMarkUpdate*   m_LndMarkUpdateWidgetObserver;

private:
// 	misPointSelctObserverUpdateLandmark*  m_pPtnSelcxtObservertAxialLndUpdate;
// 	misPointSelctObserverUpdateLandmark*  m_pPtnSelcxtObservertCoronalLndUpdate;
// 	misPointSelctObserverUpdateLandmark*  m_pPtnSelcxtObservertSagittalLndUpdate;

	vector<misPointSelctObserverUpdateLandmark*> m_PointSelectObservers;

 
	bool m_FixedLandmarks;
	bool m_AddLMByClick;

};
