#include "StdAfx.h"
#include "misIntegrationNView.h"
#include "misSubsequenceLayout.h"

misIntegrationNView::misIntegrationNView(int &argc, char ** argv, int numberOfView)
	:misIntegrationTestApplication(argc, argv), m_NumberOfViews(numberOfView)//, m_PulseDistbuter(nullptr)
{
	m_ChildWindows.resize(m_NumberOfViews);
	InitilizeWindows();
}

misIntegrationNView::~misIntegrationNView(void)
{
}

void misIntegrationNView::CreateWindows( misNativeWindow parentWindow )
{
	// diveide a 1000 * 1000 window to 2 row
	const int numberofColumn = 2;
	int numofWindow = m_NumberOfViews;
	if (m_NumberOfViews % 2 != 0)
		numofWindow++;

	int numberofRow = numofWindow / numberofColumn;
	int width = 1000 / numberofRow;
	int height = 1000 / numberofColumn;

	for (int i = 0; i < numberofRow; i++)
	{
		for (int j = 0 ; j < numberofColumn ; j++)
		{
			int windowIndex = i * numberofColumn + j;
			if(windowIndex < m_NumberOfViews)
			{
				m_ChildWindows[i * numberofColumn + j].SetParentWindow(parentWindow.Handle());
				m_ChildWindows[i * numberofColumn + j].Create(i * width, j * height, width, height);
			}
		}
	}

}

void misIntegrationNView::GenerateUIModel()
{
	auto integrationUiTestModel = std::make_shared<misSubsequenceLayout>();
	integrationUiTestModel->SetName("TestTab");
	for(unsigned int i = 0 ;i < m_NumberOfViews; i++)
	{
		misWindowModel winMod;
		const auto windowTitle = "window " + std::to_string(i);
		winMod.SetName(windowTitle);
		HWND handle = (HWND)m_ChildWindows[i].Handle();
		winMod.SetHandle(handle);
		winMod.SetWindowIndex(i);
		integrationUiTestModel->AddWindow(winMod);
	}
	m_SubTabModel = integrationUiTestModel;
}


std::shared_ptr<ISubsequenceLayout> misIntegrationNView::GetSubTabModel()
{
	return m_SubTabModel;
}

void misIntegrationNView::IgstkPulseHandler()
{
	misIntegrationTestApplication::IgstkPulseHandler();
	//m_PulseDistbuter.PulsPublish();
}

void misIntegrationNView::SetPulseDistributorSequenceList( sequenceListTypdef sequences )
{
	//m_PulseDistbuter.SetSeqList(sequences);
}

void misIntegrationNView::InitilizeWindows()
{
	CreateWindows(GetMainWindow());
	GenerateUIModel();
}
