#pragma once
#include "misRobotSerialCommunication.h"
#include "misRobotTester.h"
#include "misRobotCoordinate.h"
#include "misToolData.h"

enum RobotIdentifyProcessState
{
	NotStarted = 0,
	InProgress,
	DoneCompletely
};

////an enumeration which shows if the message sent by robot in Identify process is
////gotten throughly or not
//enum RobotMessageGettingStatus
//{
//	Good=0,
//	FailedSomewhere
//};

//A class which is solely written to accomplish Identify process of Robot In two ways:
//1- Inside robot (Calculations are done inside robot, which is by default a robot task)
//2- Outside robot (Calculations are done inside this class, which is faster than the above task)
class misRobotIdentificationProcess
{
	RobotIdentifyProcessState m_IdentifyProcessState;
	//
	std::string m_LastRobotMessage;
	std::string m_LastCommand;

	misBiopsyRobot * m_Robot;

	misToolData::Pointer   m_TargetTool;
	misToolData::Pointer   m_RobotHeadTool;
	misToolData::Pointer   m_RefrenceTool;

	typedef   std::set < misToolData * > ToolListType;
	ToolListType   *     m_ToolListPointer;//keep tool representation pointer

	igstk::SerialCommunication::Pointer  m_SerialCommuincator;

	//private keyword, just for separating functions and variables
private:
	//Sets serial communication. The SerialComm must be NEW and initialized before using in this function
	bool SetSerialCommunication(igstk::SerialCommunication * SerialComm);

	//Sets tool which is installed on target cylinder
	bool SetTargetTool(misToolData * CurrentTargetTool);

	//Sets tool which is installed on head of robot
	bool SetRobotHeadTool(misToolData * CurrentRobotHeadTool);

	//Sets tool which is installed as reference
	bool SetReferenceTool(misToolData * CurrentReferenceTool);

	//Sets a pointer pointing to list of tools
	bool SetpointerOfToolsList(ToolListType * ToolList);

	bool SetRobot(misBiopsyRobot * Robot);

	//Gets Position of tool which is installed on the target
	vtkTransform * GetTargetCurrentPosition();

	//Gets Position of tool which is installed on the moving head of Robot
	vtkTransform * GetRobotHeadCurrentPosition();

	//Gets Last command Sent to robot
	std::string GetLastCommandSentToRobot();

	//Gets last message sent by robot to be monitor
	std::string GetLastMessageSentByRobot();

	RobotIdentifyProcessState GetIdentifyProcessState();

	//Waits in a loop until robot sends a text message
	std::string ReadMessageFromRobot();

	//Wraps a coordinate which is taken from camera in a message which robot can understand and Sends
	//it to robot
	bool SendTipCoordinateSystemToRobot(misRobotCoordinate Coord);

	//Gets Position of reference which is installed on a fixed point near robot
	//void GetReferenceCurrentPosition();

public:
	misRobotIdentificationProcess(void);
	~misRobotIdentificationProcess(void);

	//Initialization
	bool InitialrequairedValues(igstk::SerialCommunication * SerialComm , misToolData * CurrentTargetTool , misToolData * CurrentRobotHeadTool , misToolData * CurrentReferenceTool , ToolListType * ToolList , misBiopsyRobot * Robot);

	//Runs identify process of robot which all calculations are done inside robot. This
	//function assumes the robot is in the state which we can send IDENTIFY command to it. This
	//means user must ran some commands before (like USER_HANDSHAKE, TIP_TO_ENDEFFECTOR_TRANSFORMATION, TIP_COORDINATE_SYSTEM)
	void InternalIdentify();

	//Runs identify process of robot. Calculations are done outside robot
	void ExternalIdentify();

	//for test purpose
	//void MoveToLocation(double x, double y, double z, double xr, double yr, double zr);

	//
	//void Test();
};
