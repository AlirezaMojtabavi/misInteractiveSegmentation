#pragma once

#include "ICoordinateSystem.h"
#include "ICoordinateSystemRepository.h"
#include "misLibraryMacroes.h"

// The misCoordinateSystemReposity implement ICoordinateSystemReposity and store a list of ICoordinateSystem and inform 
// subscribers when adding a new ICoordinateSystem -
class MISLIBRARYEXPORT misCoordinateSystemRepository : public ICoordinateSystemRepository 
{
public:
	misCoordinateSystemRepository(void);
	~misCoordinateSystemRepository(void);
	virtual void RemoveCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinatesSystem );
	virtual void AddCoordinateSystem(  std::shared_ptr< ICoordinateSystem> coordinatesSystem );
	virtual std::shared_ptr<ICoordinateSystem> GetCoordinateSystem( misUID coordinateSystemUID ) const override;
	virtual std::vector<std::shared_ptr<ICoordinateSystem>> GetAllCoordinatesSystems() const override;
	virtual void Clear();
private:
	std::vector<std::shared_ptr<ICoordinateSystem>> m_CoordinatesSytems;
 
};

