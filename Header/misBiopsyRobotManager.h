#pragma once
#include "misSubSeqStyle.h"
#include "igstkMacros.h"
#include <vector>
#include "igstkSerialCommunication.h"
#include "misStrctConnectOption.h"
#include "misBiopsyRobot.h"
#include "misToolData.h"
#include "misRobotSerialCommunication.h"
#include "misRobotStrct.h"
#include "misToolsState.h"
#include "itkMutexLock.h"
//#include "misBiopsyRobotAccuracyTest.h"
#include "misRobotIdentificationProcess.h"
#include "..\misBiopsyRobotControler\misFileUtilitiesForRobot.h"
#include "..\misBiopsyRobotControler\misRobbyRobotTester.h"

#define NumPointsUsedInIdentify 10

class misBiopsyRobotManager:public  misSubSeqStyle
{
	struct PlanStruct
	{
		misSimplePointType TargetPoint;
		misSimplePointType TragetSlope;
	};

	struct RobotDataStruct
	{
		misSimplePointType RobotPosition;
		double             RobotQuaternion[4]; // wxyz
	};
public:
	misRobbyRobotTester m_RobbyRobotTester;

	//misFileUtilitiesForRobot m_RobotFileUtility;

	misRobotIdentificationProcess m_RobotIdentifier;
	//misBiopsyRobotAccuracyTest m_RobotTester;

	misBiopsyRobotManager(void);
	misRobotSerialCommunication::Pointer  m_SerialCommuincator; 
	misBiopsyRobot*     m_Robot;

	misToolData::Pointer   m_TargetTool;
	misToolData::Pointer   m_RobotTrackerTool;
	misToolData::Pointer   m_RefrenceTool;
	virtual void LogCallBack(itk::Object *caller, const itk::EventObject &capturedEvent);
	itk::SimpleMutexLock   m_CommandReadingMutext;
	itk::SimpleMutexLock   m_PortReadWriteAccess;

	
	static void ReadCommandThread(void* pParams);
	std::string m_RobotCommand;
	bool  m_RobotCommandChanged;
	bool  m_ContinueReadingThread;
	mis3DViewer::Pointer			m_Viewer;

	typedef   std::set<misToolData*> ToolListType;
	ToolListType     m_ToolList;//keep tool representation pointer to show or hide them

	PlanStruct                     m_PlanData;
	RobotDataStruct                m_RobotData;
	misToolsState     m_LastRequiredToolInfo;

	// TODO: this two string must be re factored
	std::string                         m_OPERATION_LOCATION;
	std::string                         m_ROBOT_COORDINATE_SYSTEM;
	std::string                         m_TIP_TO_ENDEFFECTOR_TRANSFORMATION;
	std::string                         m_LastRobotCommand;


public:

	igstkStandardClassBasicTraitsMacro( misBiopsyRobotManager , misSubSeqStyle )  
	igstkNewMacro( Self );  
	~misBiopsyRobotManager(void);
	bool Connect(misStrctComConnectionOptions connecting);
	virtual void OnSelected(void);
	virtual void InitialeGuiProcessing();
 	void UpdateStatus(long long int puls);
	bool ProcessRequest(misGUIEvent* pEvent);
	virtual void Render(void);
	virtual void RealseAllResources(void);
	misEventListTypedef GetEventToGui();

	void  AddTrackerTool(misToolData*   trackerToool);
	void  ShowTools(bool value );
	void  ResetTools(void);
	void  UpdateTools(void);	
	void  IdentifyInsideRobot();
	void InitialRobotTrackerTool(misToolData::Pointer toolPtr);

private:
	void  ProcessCommand(misRobotCommandStr command);
	void  AutoFillMessage(misRobotCommandStr* command );
	void  UpdateToolStatus(void);
	void  UpdateToolStatusInGUI(void);
	void  UpdateToolPosition(void);
	void  UpdatePlanData(bool update);
	void  UpdateRobotdata(bool update);

	std::string MakeAutomaticRobotPositionCommand(void);
	std::string MakeAutomaticPlanCommand(void);
	std::string ConvertDoubleToString(double val);

	void   ExtractTipToEndeffectorTransform(std::string robotCommand);
	std::string MakeAutomaticEndeffectorTransform(void);
	void SendCurrnetCoordinate();

	void AddPointToRobotSceen(misSimplePointType CurrentPosition);
	static void ReadCommandThreadROBBYTESTER( void* pParams );

	static void GotoEndOfPanInterval( void* pParams );


	

};
