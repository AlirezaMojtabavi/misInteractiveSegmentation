#pragma once

#include "misToolProperties.h"
#include "misTrackingToolStateReport.h"

// The misTrackingStateReport class describes a snapshot of the current tracking state, statistics, and all the tracking tools.
// The report is filled during construction and used by report viewers.
class misTrackingStateReport
{
public:
	typedef std::vector<misTrackingToolStateReport> ToolReportsListType;
	typedef std::map<misToolProperties::ApplicationFlag, bool> VisibilityFlagsMapType;

	misTrackingStateReport() 
		: m_NumberOfVisibleTools(0), m_InterferenceExists(false)
	{ }

	misTrackingStateReport(const ToolReportsListType &toolStateReports, const VisibilityFlagsMapType &visibilityFlags, 
		int numberOfVisibleTools, const std::string &navToolName, bool interferenceExists)
		: m_VisibilityFlags(visibilityFlags), m_NumberOfVisibleTools(numberOfVisibleTools), m_ToolReports(toolStateReports),
		m_NavigationToolName(navToolName), m_InterferenceExists(interferenceExists)
	{ }

	misTrackingStateReport& operator= (const misTrackingStateReport& other)
	{
		m_VisibilityFlags = other.m_VisibilityFlags;
		m_NumberOfVisibleTools = other.m_NumberOfVisibleTools;
		m_InterferenceExists = other.m_InterferenceExists;
		m_ToolReports = other.m_ToolReports;
		return *this;
	}

	// Determines whether the tracker is experiencing optical interference - this error state is not supported by all trackers
	// (so far only Polaris reports interference)
	bool InterferenceExists() const { return m_InterferenceExists; }

	// Determines whether any tracking tool of the specified application class is currently visible. It is used by the GUI to
	// inform the user whether or not any of calibration, reference, or navigation tools are currently visible.
	bool IsToolWithApplicationVisible(misToolProperties::ApplicationFlag flag) const 
	{ 
		return m_VisibilityFlags.count(flag) != 0 ? m_VisibilityFlags.at(flag) : false;
	}

	// Gets the number of tracking tools that are currently visible.
	int GetNumberOfVisibleTools() const { return m_NumberOfVisibleTools; }

	// Gets the number of tracking tools that are currently visible.
	std::string GetNavigationToolName() const { return m_NavigationToolName; }

	// Gets a list of individual reports pertaining to all the tools loaded by the tracker.
	std::vector<misTrackingToolStateReport> GetTrackingToolStateReports() const { return m_ToolReports; }

private:
	VisibilityFlagsMapType m_VisibilityFlags;
	std::string m_NavigationToolName;
	int m_NumberOfVisibleTools;
	bool m_InterferenceExists;
	ToolReportsListType m_ToolReports;
};