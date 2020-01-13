#pragma once

class JitterParameters:public Serializable
{
public:
	double JitterFilterCoefficient;
	bool JitterFilteron_off;
	int ExtrapolatedFramesNum;
	bool KalmanFilter;
	double AngularDotProductToleranceDeg ;
	double AngularJitter;
	int JitterFilterHistoryLength;
	JitterParameters();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};

class misMicronTrackerSetting:public Serializable
{
public:
	misMicronTrackerSetting();

	const std::vector<std::string>& GetReferencePrefixList() const;
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	int MicronFrequncy;
	int PredictiveFrameInterleave;
	double TemplateMatchToleranceMMValue;
	bool SmallerXpFootprint;
	bool BackGroundProcess ;
	bool UseBackgroundProcessingMutex ;
	bool MiddleSensorEnable;
	bool AutomaticLightCoolness;
	double lightcoolnessValue;
	int    ReportInterval;
	int NumberOfsampleForanAnalyzeJitter;
	JitterParameters jitterParam;

private:
	std::vector<std::string>        m_ReferencePrefixList;
};