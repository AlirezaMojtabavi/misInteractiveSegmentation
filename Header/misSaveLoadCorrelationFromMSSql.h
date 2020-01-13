#pragma once

#include "ISaveLoadCorrelationToDB.h"

// A implementation of ISaveLoadCorrelationToDB that loads and stores correlation results to navigationDB (a MS SQL server 
// database. It uses store procedures to save and load correlation data.
class misSaveLoadCorrelationFromMSSql : public ISaveLoadCorrelationToDB
{
public:
	misSaveLoadCorrelationFromMSSql(void);
	~misSaveLoadCorrelationFromMSSql(void);

	virtual void SaveCorrelationsToDB( const ISaveLoadCorrelationToDB::CorrelationStorageListType& correlationStructList , const misUID& solutionUID );
	virtual ISaveLoadCorrelationToDB::CorrelationStorageListType GetCorrelationsFromDB( const misUID& solutionUID );
	virtual void DeleteExisitingCorrelation(const misUID& solutionUID);
};

