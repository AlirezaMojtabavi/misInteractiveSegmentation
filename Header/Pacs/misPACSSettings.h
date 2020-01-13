#pragma once
 

struct misPACSSettings:public Serializable
{
public:
	misPACSSettings(void);
	~misPACSSettings(void);
	void serialize(XmlSerializer& s) const override;
	void deserialize(XmlDeserializer& s) override;
	std::string GetLocalAET() const;
	void SetLocalAET(std::string localAet) ;
	std::string GetLocalPort() const;
	void SetLocalPort(std::string localPort) ;

	std::string GetServerID() const;
	void SetServerID(std::string serverID);

	std::string GetServerAET() const;
	void SetServerAET(std::string serverAet) ;

	std::string GetServerHost() const;
	void SetServerHost(std::string serverHost);

	std::string GetServerPort() const;
	void SetServerPort(std::string serverPort);

	std::string GetRetrieveMethod() const;
	void SetRetrieveMethod(std::string method)  ;

	std::string GetUsername() const;
	void SetUsername(std::string userName) ;

	std::string GetPassword() const;
	void SetPassword(std::string pass)  ;


private:

	std::string m_LocalAET;
	std::string m_LocalPort;
	std::string m_ServerID;
	std::string m_ServerAET;
	std::string m_ServerHost;
	std::string m_ServerPort;
	std::string m_RetrieveMethod;
	std::string m_Username;
	std::string m_Password;

};

