#pragma once

#include "misSubSequence.h"

class misDatasetManager;
class misApplicationSetting;

class misSnapShotManager : public misSubSequence
{

public:
	misSnapShotManager(std::shared_ptr<misSoftwareInformation> softwareInformation);

	~misSnapShotManager(void);
	void InitialeGuiProcessing();
	void UpdateStatus(long long int puls);
	void TaskOnLeave(void);
	void UpdateSettingFromAppSetting(void);
	void RealseAllResources();
	void Render();
	misEventListTypedef GetEventToGui();
private:
	misDatasetManager*     m_dataSetManager;

};

