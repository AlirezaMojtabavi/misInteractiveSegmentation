#pragma once

#include "misExtraToolInformation.h"
#include "misToolTypeEnum.h"

// The misTrackingToolStateReport class contains a snapshot of the state, statistics, etc. of a single tracking tool. The report
// data are filled during construction and used by report viewers.
class misTrackingToolStateReport
{
public:
	misTrackingToolStateReport(const std::string& toolName, const std::string& partNumber, const double toolPosition[3], 
		double rotationQuaternion[4], misToolStatus status, double lastMovement, double lastRotation)
		: m_ToolName(toolName), m_PartNumber(partNumber), m_LastMovement(lastMovement), m_LastRotation(lastRotation), 
		m_Status(status)
	{
		std::copy(toolPosition, toolPosition + 3, m_ToolPosition);
		std::copy(rotationQuaternion, rotationQuaternion + 3, m_RotationQuaternion);
	}

	misTrackingToolStateReport& operator= (const misTrackingToolStateReport& other)
	{
		m_ToolName = other.m_ToolName;
		m_PartNumber = other.m_PartNumber;
		m_LastMovement = other.m_LastMovement;
		m_LastRotation = other.m_LastRotation;
		m_Status = other.m_Status;
		std::copy(other.m_ToolPosition, other.m_ToolPosition + 3, m_ToolPosition);
		std::copy(other.m_RotationQuaternion, other.m_RotationQuaternion + 3, m_RotationQuaternion);
		return *this;
	}

	// Gets the friendly name of the tracking tool.
	std::string GetToolName() const { return m_ToolName; }

	// Gets the technical unique part number of the tracking tool.
	std::string GetPartNumber() const { return m_PartNumber; }

	// Gets the position (translation) of the tracking tool with respect to a report-specified (probably tracker) coordinate system.
	const double* GetToolPosition() const { return m_ToolPosition; }
	void GetToolPosition(double position[3]) const 
	{ 
		position[0] = m_ToolPosition[0];
		position[1] = m_ToolPosition[1];
		position[2] = m_ToolPosition[2];
	}
	
	// Gets the orientation (rotation) of the tracking tool with respect to a report-specified (probably tracker) coordinate system.
	const double* GetRotationQuaternion() const { return m_RotationQuaternion; }
	void GetRotationQuaternion(double quaternion[4]) const 
	{ 
		quaternion[0] = m_RotationQuaternion[0];
		quaternion[1] = m_RotationQuaternion[1];
		quaternion[2] = m_RotationQuaternion[2];
		quaternion[3] = m_RotationQuaternion[3];
	}

	// Gets the last movement of the tracking tool (the distance, in millimetres, traveled since the last reported tool position).
	double GetLastMovement() const { return m_LastMovement; }

	// Gets the last rotation of the tracking tool (the angular distance, in degrees, traversed since the last reported 
	// tool orientation).
	double GetLastRotation() const { return m_LastRotation; }

	// Gets the current usability status of the tool.
	misToolStatus GetStatus() const { return m_Status; }

private:
	std::string m_ToolName;
	misToolStatus m_Status;
	double m_LastMovement;
	double m_LastRotation;
	std::string m_PartNumber;
	double m_ToolPosition[3];
	double m_RotationQuaternion[4];
};