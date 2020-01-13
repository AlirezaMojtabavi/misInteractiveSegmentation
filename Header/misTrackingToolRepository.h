#pragma once

#include "ITrackingToolRepository.h"

class misTrackingToolRepository : public ITrackingToolRepository
{
public:
	~misTrackingToolRepository(void);

	// Singleton function
	static std::shared_ptr<misTrackingToolRepository> GetInstance();

	virtual void AddTool( std::shared_ptr<ITrackingTool> newTool );
	virtual void RemoveTool( std::shared_ptr<ITrackingTool> tool );
	virtual void RemoveAllTools();
	virtual ITrackingToolRepository::TrackerToolListType GetAllTools() const;

private:
	misTrackingToolRepository();

	TrackerToolListType m_Tools;
	igstk::Tracker* m_Tracker;
};

