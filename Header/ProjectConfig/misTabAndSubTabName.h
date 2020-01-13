#pragma  once 

#include "misSimpleTabeNameStr.h"
#include "misEnums.h"

class misTabAndSubTabName
{
private:

	misSimpleTabAndSubTabList  m_GUITabsNamel;


	misTabAndSubTabName() { }
	~misTabAndSubTabName() { }

public:


	static misTabAndSubTabName* GetInstanse(bool destroySingletonInstance = false);

	std::string  GetTabNameHomeProcedure(void);
	std::string  GetSubTabNameHomeMain(void);
	std::string  GetTabNameDataProcedure(void);
	std::string  GetSubTabNameDataUploading(void);
	std::string  GetSubTabNameDataChecking(void);
	std::string  GetSubTabNameDataCorrelation(void);
	std::string  GetTabNameAnalysisProcedure(void);
	std::string  GetSubTabNameSegmentation(void);
	std::string  GetSubTabNameComositeMaking(void);
	std::string  GetTabNamePlanningProcedure(void);
	std::string  GetSubTabNameBiposyPlanning(void);
	std::string	GetSubTabNameScrewPlanning(void);
	std::string  GetTabNameTrackingProcedure(void);
	std::string  GetSubTabNameTrackingManger(void);
	std::string  GetSubTabNameToolAccuracy(void);
	std::string GetSubTabNameRoboticNavigation();
	std::string  GetTabNameBiopsyRobotProcedure(void);
	std::string  GetSubTabNameBiopsyRobotManager(void);
	std::string  GetTabNameRegistrationProcedure(void);
	std::string  GetSubTabNameRegistrationLandMarkSelection(void);
	std::string  GetSubTabNameRegistrationLandMarkRegistration(void);
	std::string  GetSubTabNameRegistrationSurfaceRegistration(void);
	std::string  GetTabNameNavigationProcedure(void);
	std::string GetSubTabNameNavigatoinMain(misApplicationType) const;
	std::string  GetTabNameSnapShotProcedure(void);
	std::string  GetSubTabNameSnapShotMain(void);
	std::string GetSubTabNamePacsExplorer(void);

};




