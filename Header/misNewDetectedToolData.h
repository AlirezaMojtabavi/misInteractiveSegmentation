#pragma once

class misPolarisTracker;
class misMicronTracker;
class misAscensionTracker;
class misToolData;
namespace igstk
{
	class Tracker;
}
class misToolData;
struct misNewDetectedToolData
{
	igstk::Tracker* TrackerUnit;
	misToolData* SubjectTool;
	std::string	CalibratorName;
	misNewDetectedToolData()
	{
      SubjectTool = 0;
	  TrackerUnit = 0;
	}
};
