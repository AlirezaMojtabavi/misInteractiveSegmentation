#pragma once
#include "misPointStruct.h"
#include "misRobotTester.h"
#include "..\misBiopsyRobotControler\misFileUtilitiesForRobot.h"
#include "misToolData.h"

//a class which makes a complete list of commands and sends them to robot and get the robot response
class misBiopsyRobotAccuracyTest : public misObject
{
	//pointer to serial comm
	//igstk::SerialCommunication::Pointer  m_SerialCommuincator;

	//stores list of commands runnable by robot
	misRobotTester* m_tester;

	//3 pointers to tools to get their current position
	misToolData::Pointer   m_TargetTool;
	misToolData::Pointer   m_RobotHeadTool;
	misToolData::Pointer   m_RefrenceTool;


	//a string which is used to be sent to GUI
	std::string m_LastRobotMessageGottenFromRobot;

	//a string which is used to be sent to GUI
	std::string m_LastCommandSentToRobot;

	//a vector of reachable targets which we make test commands based on them
	//we generate a number of random paths for each target and make commands to reach
	//these targets from these random targets
	vector<misPointStruct> m_ReachableTargets;	



private:

	//Deg To rad converter
	double DegreeToRadian(double Deg);//passed
	//a margin checker
	bool isInWorkspace(double panAngle,double rollAngle,double tiltAngle,double Xpos, double extLength);//passed
	//find reachable targets and puts them in m_ReachableTargets
	void FindReachableTargets();
	//must be updated (3 funcs)
	double CalculateXcooeficient(double Theta_p,double Theta_t,double Theta_r);
	double CalculateYcooeficient(double Theta_p,double Theta_t,double Theta_r);
	double CalculateZcooeficient(double Theta_t,double Theta_r);
	//////////////////////////
	//adds one point to list of commands
	void AddOnePointToRobotCommands( double X, double Y, double Z, double m_x, double m_y, double m_z );//passed
	//generats 6 data in predefined margin with uniform distribution. Outputs are arguments
	void GenerateRandomData(double & X, double &  Y, double &  Z, double &  m_x, double &  m_y, double &  m_z);//passed
	//adds tip to end...to list 
	void Fill_TIP_TO_ENDEFFECTOR_TRANSFORM(double X, double Y, double Z, double Quat1, double Quat2, double Quat3, double Quat4);//passed
	//adds tip coordinate system to list...
	void Fill_TIP_COORDINATE_SYSTEM(double X, double Y, double Z, double Quat1, double Quat2, double Quat3, double Quat4);//passed
	//adds commands of handshake and approval to list
	void FillInitialCommandValues();


	//this func gets current location of robot head tool
	igstk::Transform GetCurrentLocationOfRobotHead();
	//this func gets a file which contains desired locations in robot coordinate system and 
	void MakeManualListForTestAccuracyForExtension(std::string FileAddressContainingdesiredPoints);

	//reads points from a text file and puts them in a vector
	vector<std::string> ReadPointsFromTextFile(std::string PathAndName);

public:
	misBiopsyRobotAccuracyTest(void);
	~misBiopsyRobotAccuracyTest(void);

	//generates a list of commands which are runnable by misRobotTester
	void MakeCommandList();
	//returns command list
	misRobotTester * GetCommandList();

	//gets Robot Tester of this class
	misRobotTester* GetRobotTester()  const;

	//calls RunCommands of misRobotTester
	void RunCommands();

	//makes a command list based on Points which Robot team gives us 
	void MakeCommandListBasedOnTestPointsGottenFromFile(std::string PathAndName);

	//gets last command sent to robot
	string GetLastCommandSentToRobot();

	//gets last message gotten from robot
	string GetLastMessageGottenFromRobot();

	//
	void InitialRequiredValues(misBiopsyRobot::Pointer ROBOT, misToolData::Pointer RobotHeadTool, misToolData::Pointer RefTool, misToolData::Pointer GuideMarkerTool);

	//IMPORTANT  NOTE:  	DON`T ERASE THESE FUNCS FROM BOTH .CPP AND .H FILE



	////sets data into misStrctComConnectionOptions m_ConnectionData
	//bool ConfigConnectionData(misStrctComConnectionOptions ConnectionData);
	////configs serial communicator
	//void ConfigSerialCommunicator( misStrctComConnectionOptions &connecting ); 
	////opens a communication w.r.t robot
	//bool ConnectToRobot(misStrctComConnectionOptions connecting);
	////opens robot communication
	//bool OpenRobotCommunication();//passed
	////adds commands of IDENTIFY into list
	//void IdentificationProcess();
	////makes a list of commands which after running by robot, the robot can run Identify
	//void MakeCommandsForRunRobotIdentify();
};

