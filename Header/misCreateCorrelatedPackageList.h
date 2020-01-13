#pragma once
#include "ICreateCorrelatedPackageList.h"
#include "ICoordinateSystemCorrelationManager.h"

class misCreateCorrelatedPackageList :
	public ICreateCorrelatedPackageList
{
public:
	misCreateCorrelatedPackageList(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > );
	~misCreateCorrelatedPackageList() = default;

	// Inherited via ICreateCorrelatedPackageList
	virtual void CreateCorrelatedPackageList() override;
private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	 void ClearUnCorrelatedPackage() ;

};

