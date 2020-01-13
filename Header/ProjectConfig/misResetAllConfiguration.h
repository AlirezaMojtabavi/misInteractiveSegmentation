#pragma once

// The misResetAllConfiguration class is used to reset all application configuration resources (XML files ...) to their initial
// release values. A few of the options can be altered to determine which initial release configuration is desired. These include
// surgery type, tracker type ...
class misResetAllConfiguration
{
public:
	// See SetSurgeryType()
	enum SurgeryType
	{
		ST_EAR_NOSE_THROAT,
		ST_NEUROSURGERY,
		ST_SPINE,
		ST_DENTAL,
		ST_BIOPSY,
		ST_CMF
	};

	// See SetTrackerType()
	enum TrackerType
	{
		TT_POLARIS,
		TT_MICRON,
		TT_ASCENSION,
		TT_AURORA
	};

	misResetAllConfiguration();

	// Sets the directory from which default (initial release) configuration resources are loaded. Default value 
	// is "./DefaultConfig"
	void SetDefaultConfigurationDirectory(const std::string& dir);

	// Sets the directory containing application executable. The configuration files and resources within this directory will be
	// replaced with initial release config resources. Default value is "."
	void SetCurrentExecutableDirectory(const std::string& dir);
	void SetPreferenceFileByAppType() const;

	// Resets all the application configuration resources by copying and replacing all the resources within 
	// DefaultConfigurationDirectory into CurrentExecutableDirectory and then applying extra settings (surgery type ...)
	// to current executable settings.
	void ResetConfiguration();

	// The following methods cause changes to ApplicationSettings.xml in the executable directory to achieve desired 
	// configuration. The changes will be applied after calling ResetConfiguration().
	void SetSurgeryType(SurgeryType surgeryType);
	void SetTrackerType(TrackerType trackerType);
	void SetEndoscopeCaptureDevice(const std::string& captureDevice);
	void ApplySurgeryType();

private:
	const std::string ApplicationSettingsFileName; // = "ApplicationSetting.xml"

	// See IsConfigItemModified()
	enum ModifiableConfigItem
	{
		MCI_SURGERY_TYPE,
		MCI_TRACKER_TYPE,
		MCI_ENDOSCOPE_CAPTURE_DEVICE
	};

	// Determines whether changing of the specified configuration item has been requested (corresponding setter methods called).
	// Unaltered items will have the default values provided by the resources in DefaultConfigurationDirectory.
	bool IsConfigItemModified(ModifiableConfigItem configItem);

	// Copies all the contents of the src directory (and directory itself if not already existing) recursively to the destination.
	// It does not remove files from destination but replaces files that already exist with the same name.
	void CopyDirectory(const std::string& src, const std::string& dest);
	
	std::string GetSurgeryTypeString() const;

	std::string m_DefaultConfigDir;	// See SetDefaultConfigurationDirectory
	std::string m_ExecutableDir;	// See SetCurrentExecutableDirectory
	std::map<ModifiableConfigItem, bool> m_ConfigItemModifiedFlags;	// See IsConfigItemModified
	SurgeryType m_SurgeryType;	// See SetSurgeryType
	TrackerType m_TrackerType;	// See SetTrackerType
	std::string m_EndoscopeCaptureDevice; // See SetEndoscopeCaptureDevice
	std::string m_MyDocumentDirectory;
};

