#pragma once

#include "misGroupViewer.h"
#include "misIntegrationTestApplication.h"
#include "misPulsDistributer.h"

//Base class for test with 4 view: axial, coronal, Sagittal, volume 
class misIntegrationNView : public misIntegrationTestApplication
{
public:
	misIntegrationNView(int &argc, char ** argv, int numberOfView = 4);

	virtual ~misIntegrationNView(void);

protected:
	std::shared_ptr<ISubsequenceLayout> GetSubTabModel();
	// Generate model describing GUI layout - mainly windows handles.update result in m_SubTabModel
	virtual void GenerateUIModel();

	// Handles the issue caused due to license protection.
	void SetPulseDistributorSequenceList(sequenceListTypdef sequences);

	std::shared_ptr<ISubsequenceLayout> m_SubTabModel;
	std::vector<misNativeWindow>  m_ChildWindows;

private:

	// Create 4 window in parentWindow
	virtual void CreateWindows(misNativeWindow parentWindow );
	void InitilizeWindows();
	virtual void IgstkPulseHandler() override;
	//misPulsDistributer m_PulseDistbuter;
	int m_NumberOfViews;
};

