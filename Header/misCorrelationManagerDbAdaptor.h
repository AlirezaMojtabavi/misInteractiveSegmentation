#pragma once

#include "ICoordinateSystem.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRepository.h"
#include "ICorrelationManagerDbAdaptor.h"
#include "ISaveLoadCorrelationToDB.h"

// Implements ICorrelationManagerDbAdaptor. It uses a coordinate system repository and a coordinate system correlation manager.
// When loading correlations from the persistent storage, the coordinate systems with the loaded UIds 
// might not have already been added to the coordinate system repository (so they cannot be added to the correlation manager 
// immediately after loading). Therefore this class observes the coordinate system repository and whenever a new coordinate
// system is registered with the repository, it updates the correlation manager.
class MISLIBRARYEXPORT misCorrelationManagerDbAdaptor :public ICorrelationManagerDbAdaptor
{
public:
	typedef ICoordinateSystemCorrelationManager<std::string>::DirectCorrelation DirectCorrelationType;

	class MISLIBRARYEXPORT Injector
	{
	public:
		virtual std::shared_ptr<ISaveLoadCorrelationToDB> CreateSaveLoadCorrelationToDB();
	};

	misCorrelationManagerDbAdaptor(std::shared_ptr<Injector> injector = nullptr);
	~misCorrelationManagerDbAdaptor(void);

	void virtual SaveCorrelationResults(const std::string& solutionUID) override;
	void virtual LoadCorrelationResult(const std::string& solutionUID) override;
	void virtual SetCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val) override;

private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<ISaveLoadCorrelationToDB>  m_LoadSaveCorrelations;
	ISaveLoadCorrelationToDB::CorrelationStorageListType m_LoadedCorrelationResults;
};

