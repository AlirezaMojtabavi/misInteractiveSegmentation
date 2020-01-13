#pragma once

#include "misMultiViewSubSequence.h"
#include "misSubSequence.h"
#include "misSubSeqTreeViewEventProcessor.h"
#include "misTrackingStateReport.h"

class misPacsManager : public misSubSequence
{
public:

 

	misPacsManager(std::shared_ptr<misSoftwareInformation> softwareInformation);
	~misPacsManager(void);

	virtual void OnSelected(void);



	//????????????????????????????//
	virtual void LogCallBack(itk::Object *caller, const itk::EventObject &capturedEvent);



	//Specifies the events this class can observe(or send????). Simply add events you want to observe(or send????) to this class in this method
	misEventListTypedef GetEventToGui();

	//TODO: NEEDS REVISION
	//??????????????????????????????????
	//virtual void InitialeGuiProcessing();


	//
	bool ProcessRequest(misGUIEvent* pEvent);

	virtual void RequestTreeViewClicked();

	virtual void SetPackageContent();

	virtual void ShowCurrentPackageContentsInViewer();

	virtual void ShowTreePackageInGUI();

	virtual void ShowPackageListInGUI();

	virtual void InitialeGuiProcessing();

	virtual void RealseAllResources();

	virtual void Render( void );

	//TODO: NEEDS REVISION
	//??????????????????????????????????
	//void UpdateStatus(long long int puls);

	

	
};

