#pragma  once

#include "misStringTools.h"

// The ISaveLoadCorrelationToDB provide an interface for load and save correlation results to any database system or other any 
// storage format such as XML
class ISaveLoadCorrelationToDB
{
public:
	//	Each coordinate identified with an unique UID - each correlation result save in DB with source , destination and transform 
	//between them
	struct CorrelationElement
	{
		misUID source;// source coordinate system UID
		misUID destination; //destination coordinate system UID
		vtkSmartPointer<vtkMatrix4x4> transform;// transform between source and destination
	};
	typedef std::vector<CorrelationElement> CorrelationStorageListType;

	// Save all correlations (specified by the list containing source, destination and transform) to the underlying storage.
	// Insert correlation result to DB - does not delete existing data
	virtual void SaveCorrelationsToDB(const CorrelationStorageListType& correlationStructList, const misUID& solutionUID) = 0;
	
	// Loads all correlations (specified by a list containing source, destination and transform) from the underlying storage.
	virtual CorrelationStorageListType GetCorrelationsFromDB(const misUID& solutionUID) = 0;
	
	// Delete all correlation results
	virtual void DeleteExisitingCorrelation(const misUID& solutionUID) = 0;
	
	virtual ~ISaveLoadCorrelationToDB() { }
};
