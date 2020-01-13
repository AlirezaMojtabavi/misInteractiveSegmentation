#pragma once
//*****************************  keep  it independent fro   itk,vtk,igstk,..********************************
#include "misMacros.h"
#include "misToolImageStrct.h"
#include "misToolTypeEnum.h"
#include "serializable.h"

enum misToolRepresentationType
{
	SpatialObj2D,
	SpatialObj3D,
	BiopsySpatialObj2D,
	BiopsySpatialObj3D,
	RealModel2D,
	RealModel3D,
	SpatialObjComplete2D,
	SpatialObjComplete3D,
	toolRepReplacedByRobotENDEFFECTOR	// added to distinguish between robot representation of tool and normal representation of tool
};

struct misStrctTool
{
	std::string RepresentationName;
	std::string PartNumber;
};

typedef tgt::Vector3<double> misTripleComponentTypdef;
typedef std::vector<misTripleComponentTypdef>  misTripleComponentListTypdef;

class misToolProperties : public Serializable
{
	// Maximum amount of deviation that the position of subject tracking tool tip is allowed demonstrate during tool validation.
	misPrivateVariableWithPublicAccessorsMacro(double, m_TipValidationDistanceThreshold, TipValidationDistanceThreshold);

	// Maximum amount of deviation that the position of subject tracking tool tip is allowed demonstrate during tool calibration
	// from the original position set for the tool. Values as high as 50cm are justified as detached tools demonstrate great 
	// deviations from original tool tip position.
	misPrivateVariableWithPublicAccessorsMacro(double, m_TipCalibrationDistanceThreshold, TipCalibrationDistanceThreshold);

	// Maximum amount of deviation angle (in degrees) that the orientation of the subject tracking tool is allowed to demonstrate 
	// during tool calibration from the original orientation set for the tool. When setting this value, detachable tools must also
	// be considered (with possibly great amounts of deviation).
	misPrivateVariableWithPublicAccessorsMacro(double, m_OrientationCalibrationAngleThreshold, 
		OrientationCalibrationAngleThreshold);

	// Maximum amount of deviation (in millimetres) that the position of subject tracking tool tip is allowed to demonstrate 
	// during fixation analysis in order to be considered "roughly" fixed.
	misPrivateVariableWithPublicAccessorsMacro(double, m_PositionFixationDistanceThreshold, PositionFixationDistanceThreshold);

	// Maximum amount of angular deviation (in degrees) that the orientation of the subject tracking tool is allowed to 
	// demonstrate during fixation analysis in order to be considered "roughly" fixed.
	misPrivateVariableWithPublicAccessorsMacro(double, m_OrientationFixationAngleThreshold, OrientationFixationAngleThreshold);

public:
	// The ApplicationFlag enum contains values serving as tracker tool usage indicators. Each tracker tool can have zero or
	// more of these flags. See HasApplicationFlag
	enum ApplicationFlag
	{
		Calibration,
		Reference,
		Registration,
		CameraConfig,
		Navigation,
		Detachable,
		NoFlag
	};

	misToolProperties();

	//Port for ascension tools of ascension tracker
	unsigned int PortNumberForAttachedTool;

	std::string	toolName;
	std::string	partNumber;
	std::string	toolSerialNumber;


	unsigned nailLength;
	unsigned nailDiameter;
	unsigned numberOfMarkers;
	unsigned minOfMarkers;
	unsigned toolWeight;
	misTooltipStyle tooltipStyle;
	misToolImageStrct toolImages;

	bool accurateToolOrientationCalibration;        // must only serialize for calibrator tools

	misToolStatus  toolStatus;

	bool    showTorus;
	bool    useSameColorOfToolForTorus; // def:1
	float   torusColor[3]; //   between [0 1]
	double  torusDiameter;
	double  torusCrossSectionDiameter;
	double  torusDistanceToToolTip;


	bool    useSameColorOfToolForVirtualTool; // def :1
	misTripleComponentTypdef  virtaulToolColor; //   between [0 1]

	///////////////////     virtual tip Torus Properties
	double  virtualTipTorusDiameter;
	double  virtualTipTorusCrossSectionDiameter;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	void Reset(void);

	// Gets/sets the current time of the system when the tool was last calibrated ( as reported by time() )
	time_t GetLastCalibrationTimeTag() const;
	void SetLastCalibrationTimeTag(time_t timeTag);
	misTripleComponentTypdef GetTipCalibrationViewCameraPosition() const;
	void SetTipCalibrationViewCameraPosition(const misTripleComponentTypdef& val);
	misTripleComponentTypdef GetOrientationCalibrationViewCameraPosition() const;
	void SetOrientationCalibrationViewCameraPosition(const misTripleComponentTypdef &val);
	misTripleComponentTypdef GetTipCalibrationViewCameraFocal() const;
	void SetTipCalibrationViewCameraFocaln(const misTripleComponentTypdef& val);
	misTripleComponentTypdef GetOrientationCalibrationViewCameraFocal() const;
	void SetOrientationCalibrationViewCameraFocal(const misTripleComponentTypdef &val);

	virtual std::string GetToolUID() const;

	virtual std::string GetAxisStaticFeatureUID() const;
	virtual std::string GetAxisDynamicFeatureUID() const;
	virtual std::string GetCalibrationFeatureUID() const;

	const tgt::Matrix4d& GetCalibrationFeatureTransform() const;
	void SetCalibrationFeatureTransform(const tgt::Matrix4d &calibrationFeatureTransform);
	tgt::Matrix4d GetDynamicAxisTransform() const;
	void SetDynamicAxisTransform(const tgt::Matrix4d& val);
	tgt::Matrix4d GetStaticAxisTransform() const;
	void SetStaticAxisTransform(const tgt::Matrix4d& val);

	bool OverrideRecalibration() const;
	void SetOverrideRecalibration(bool val);

	// Gets the UID of the patient for which this tracker tool has been calibrated - dynamic axis transform. Therefore, the
	// dynamic axis transform should not be used if another patient is loaded.
	const std::string& GetPatientUid() const;
	void SetPatientUid(const std::string& patientUid);

	// Determines whether the tool has the specified ToolApplicationFlag set.
	virtual bool HasApplicationFlag(ApplicationFlag flag) const;
	
	// Set port number associate with each sensor (0, 3) - aurora tracker only
	unsigned int GetPortNumber() const;
	void SetPortNumber(unsigned int val);

	// Set sensor type base on degree of freedom (5,6) - aurora tracker only
	unsigned int GetDegreesOfFreedom() const;
	void SetDegreesOfFreedom(unsigned int val);

	// if 2 sensor are used with the same port number each one specified by channel number 
	unsigned int GetChannelNumber() const;
	void SetChannelNumber(unsigned int val);

	bool GetShowVirtualTipTorus() const;
	void SetShowVirtualTipTorus(bool val);
	void AddApplicationFlag(ApplicationFlag flag);
	bool GetShowVirtualTip() const;
	void SetShowVirtualTip(bool val);
	double GetVirtualToolLength() const;
	void SetVirtualToolLength(double val);
private:
	// Parses the specified ToolApplicationFlag string and returns its equivalent ApplicationFlag enum value.
	ApplicationFlag ParseApplicationFlag(const std::string& flag) const;

	// Generates the string equivalent of an ApplicationFlag value.
	std::string GetApplicationFlagString(ApplicationFlag flag) const;
	
	time_t m_LastCalibrationTimeTag;
	tgt::Matrix4d m_StaticAxisTransform;	
	tgt::Matrix4d m_DynamicAxisTransform;
	tgt::Matrix4d m_CalibrationFeatureTransform;

	misTripleComponentTypdef m_TipCalibrationViewCameraPosition;
	misTripleComponentTypdef m_OrientationCalibrationViewCameraPosition;
	misTripleComponentTypdef m_TipCalibrationViewCameraFocal;
	misTripleComponentTypdef m_OrientationCalibrationViewCameraFocal;
	std::string m_ToolUID;
	std::string m_AxisStaticFeatureUID;
	std::string m_CalibrationFeatureUID;
	std::string m_AxisDynamicFeatureUID;
	std::vector<ApplicationFlag> m_ApplicationFlags;
	std::string m_PatientUid;
	unsigned int m_PortNumber;
	unsigned int m_DegreesOfFreedom;
	unsigned int m_ChannelNumber;
	bool m_OverrideRecalibration;
	bool m_ShowVirtualTipTorus;
	bool m_ShowVirtualTip;
	double  m_VirtualToolLength = 0;
};

typedef std::vector<misToolProperties> misToolPropertiesListTypdef;