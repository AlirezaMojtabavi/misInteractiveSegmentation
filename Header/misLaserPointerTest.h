#pragma once

#include "misStrctConnectOption.h"

class misLaserPointerTest
{
private:
	igstk::SerialCommunication::Pointer   m_SerialComminicator;

public:
	bool OpenComminucation(misStrctComConnectionOptions connection);
	void SendCommand(std::string coomand);
	misLaserPointerTest(void);
	~misLaserPointerTest(void);
};

