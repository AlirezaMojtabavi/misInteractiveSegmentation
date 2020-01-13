#pragma once

#pragma warning (push)
#pragma warning (disable : 4290)

#include "misTrackingManagerEnums.h"
#include <igstkTracker.h>

//This class provide a utility to handle multiple trackers simultaneously in the project
//misMultipleTrackerHandler is SINGLETON and could be used all over the project
//
//
class misMultipleTrackerHandler
{
private:

	//Private intentionally because of Singleton pattern 
	misMultipleTrackerHandler(void);
	~misMultipleTrackerHandler(void);


	//A list of pointers which points to existing trackers
	std::vector<igstk::Tracker::Pointer> m_TrackerList;
	 
	//A list which contains type of trackers. Its size is always equal to the size of m_TrackerList
	std::vector<TrackerType> m_TrackerType;

	
public:
	
	//Returns a pointer to one singleton object of 'misMultipleTrackerHandler' class
	misMultipleTrackerHandler* GetInstance();

	//Adds a tracker into list of trackers
	//************************************
	// Method:    AddTrackerToListOfTrackers
	// FullName:  misMultipleTrackerHandler::AddTrackerToListOfTrackers
	// Access:    public 
	// Returns:   void
	// Qualifier: throw (exception)
	// Parameter: igstk::Tracker::Pointer CurrentTracker
	// Parameter: TrackerType CurrnetTrackerType
	//************************************
	void AddTrackerToListOfTrackers(igstk::Tracker::Pointer CurrentTracker, TrackerType CurrnetTrackerType) throw (std::exception);

	//Removes the tracker from list of trackers
	//************************************
	// Method:    RemoveTrackerFromListOfTrackers
	// FullName:  misMultipleTrackerHandler::RemoveTrackerFromListOfTrackers
	// Access:    public 
	// Returns:   void
	// Qualifier: throw (exception)
	// Parameter: igstk::Tracker::Pointer CurrentTracker
	//************************************
	void RemoveTrackerFromListOfTrackers(igstk::Tracker::Pointer CurrentTracker) throw (std::exception);

	//returns the specific tracker from list
	//************************************
	// Method:    GetTracker
	// FullName:  misMultipleTrackerHandler::GetTracker
	// Access:    public 
	// Returns:   igstk::Tracker::Pointer
	// Qualifier: throw (exception)
	// Parameter: int index
	//************************************
	igstk::Tracker::Pointer GetTracker(int index) throw (std::exception);


	//returns index of a tracker in list of trackers. -1 means not found
	//************************************
	// Method:    GetIndexOfSpecificTracker
	// FullName:  misMultipleTrackerHandler::GetIndexOfSpecificTracker
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: igstk::Tracker::Pointer CurrentTracker
	//************************************
	int GetIndexOfSpecificTracker(igstk::Tracker::Pointer CurrentTracker);

	//returns index of a tracker in list of trackers. -1 means not found
	//************************************
	// Method:    GetIndexOfSpecificTracker
	// FullName:  misMultipleTrackerHandler::GetIndexOfSpecificTracker
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: igstk::Tracker * CurrentTracker
	//************************************
	int GetIndexOfSpecificTracker(const igstk::Tracker * CurrentTracker);

	std::vector<igstk::Tracker::Pointer> GetTrackersOfSpecificType(TrackerType CurrentType);

private:
	//returns the type of tracker
	//************************************
	// Method:    GetTypeOfTracker
	// FullName:  misMultipleTrackerHandler::GetTypeOfTracker
	// Access:    private 
	// Returns:   TrackerType
	// Qualifier: throw exception
	// Parameter: igstk::Tracker::Pointer CurrentTracker
	//************************************
	TrackerType GetTypeOfTracker(igstk::Tracker::Pointer CurrentTracker) throw (std::exception);

};

#pragma warning (pop)