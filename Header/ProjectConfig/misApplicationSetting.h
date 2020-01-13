#pragma once

#include "ISettingsContainer.h"
#include "misAppFoldersAddress.h"
#include "misAuthenticationSettings.h"
#include "misCaptureDevices.h"
#include "misDataBaseSetting.h"
#include "misDataCkeckingSetting.h"
#include "misDataSettingStruct.h"
#include "misDebugSettings.h"
#include "misDefaultObjectColor.h"
#include "misEnums.h"
#include "misGUISetting.h"
#include "misNavigationSetting.h"
#include "misPathSettingStrct.h"
#include "misRegistrationSetting.h"
#include "misSegmentationSetting.h"
#include "misSnapShotSetting.h"
#include "misVideoSetting.h"
#include "misVisualizationSetting.h"
#include "misWindowLevelStr.h"
#include "ITFIAddressMapper.h"
#include "misTrackingManagerEnums.h"
#include "misStructTrackingSetting.h"

 class misApplicationSetting : public Serializable
{
	// TODO : add for app address, after remove it from application setting  this friend condition must be remove
	friend class misAppManager;
	friend class Singleton<misApplicationSetting>;
	friend class SerializationTest;

public:
	// Raise the destroySingletonInstance flag ONLY in test tear down procedures
	static misApplicationSetting* GetInstance(bool destroySingletonInstance = false);

	static std::shared_ptr<ISettingsContainer> GetSettingsContainer(bool reloadSettings = false) ;

	void InitialzeToolNameIDMap();	
	void InitilizeLogger();

	std::string	 GetToolName(std::string toolID);
	void UpdateCapSetting(void);
	void SetDefalutDataBaseSettings(void);
	void SetDefaultDataUploading(void);
	void SetDefaultDataChecking(void);
	void SetDefaultRegistration(void);
	void SetDefaultNavigation(void);
	void SetDefaultSegmentationSetting(void);
	void SetDefaultVisulizationSetting(void);
	void SetDefaultSnapShotSetting(void);
	void SetDefaultVideoSetting(void);
	void SetDefaults();
	void makePathSetting(void);
	void LoadMisDebugSettingsDefaultValues();
	mis3DModelColorTypdef    GetDefaultDModelColor(void) { return this->m_Default3DModelColor;};
	misStructTrackingSetting GetTrackerSetting(void);;
	misNavigationSetting     GetNavigationSetting(void);;
	misGUISetting            GetGUISetting(void);;
	misDataUploadingSetting GetDataUploadingSetting();
	const misDataCkeckingSetting &GetDataCheckingSetting() const;
	// TODO: must check
	void                       GetImageViewingSettingFromXML();
	std::string GetPatientsDatePath();

	std::string GetMainDatabaseConnectionString();
	static std::string Get3DModelPath();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	bool isDeserilaized() const;
	void SetTrackerSetting( misStructTrackingSetting tSetting );
	void SetDefaultSettingOfTracking( void );
	void SetDefaultTracking( void );
	std::string GetPortableDatabaseConnectionString();
	static std::string GetDatabaseFolderPath();
	std::string GetGUIImagesPath();
	void SetTrackerType(TrackerType CurrentType);//Added by -M.A-
	TrackerType GetTrackerType();//Added by -M.A-
	TipCalibrationApproach GetTipCalibrationApproach();//Added by -M.A-
	std::string GetPathBasedOnTrackerType(TrackerType TypeOfTracker);//Added by -M.A-
	std::string GetRawDICOMImagesPath();
	void SetAppFoldersAddress(misAppFoldersAddress appAddress);
	std::shared_ptr<ITFIAddressMapper> GetTFIAddressMap() const;
	void SetTFIAddressMap(std::shared_ptr<ITFIAddressMapper> tfiMap);

	misApplicationType		 m_WorkflowButtonSet;
	misDataBaseSetting		 m_DataBaseSetting;
	misDataUploadingSetting m_DataUploadingSetting;
	misStructTrackingSetting m_TrackingSetting;
	RegisterationSetting	 m_RegistrationSetting;
	misNavigationSetting	 m_NavigationSetting;
	misVisualizationSetting	 m_VisulaizationSetting;
	misSegmentationSetting	 m_segmentationSetting;
	misSnapShotSetting		 m_SnapshotSetting;
	misGUISetting			 m_GUISetting;
	misStrctSettingPath      m_PathSetting;
	misDebugSettings	     m_misDebugSettings;
	misCaptureDevices		 m_CaptureDevices;
	misAuthenticationSettings m_AuthenticationSettings;
	
	std::shared_ptr<misAppFoldersAddress> GetAppAddress() const;

private:
	misApplicationSetting();
	~misApplicationSetting(void);

	void InitilazeDefault3DModelColor(void);
	void InitializeWarningToolSatus(void);
	std::string                xmlFileName;
	std::shared_ptr<misAppFoldersAddress> m_AppAddress;
	bool                 m_Deserilaized;
	void OpenLogger();
	void AddLoggerOutput();
	
	misDataCkeckingSetting m_DataCheckingSetting;
	misVideoSetting m_VideoSetting;
	mis3DModelColorTypdef m_Default3DModelColor;
	std::vector<std::string> m_ReferencePrefixes;
	std::shared_ptr<ITFIAddressMapper> m_TFIAddressMap;
	//std::string m_PatientName;
	//std::string m_SolutionPath;
};

template class Singleton<misApplicationSetting>;


