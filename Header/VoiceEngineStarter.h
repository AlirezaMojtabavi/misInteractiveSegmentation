#pragma once

class misOvCore;
class misApplicationSetting;

ref class VoiceEngineStarter
{
public:
	VoiceEngineStarter(System::Windows::Window^ ui, misOvCore* core);
	~VoiceEngineStarter();

	void Start();
	void Stop();

private:

	static void PullMessageFunction(System::Object^ object);
	misOvCore* GetCore();
	System::Windows::Window^ GetWindow();
	bool m_IsStopPullMessageThread = false;
	System::Windows::Window^ m_Ui;
	System::Threading::Thread^ m_PullMessageThread;
	misOvCore* m_Core;
	System::Diagnostics::ProcessStartInfo^ m_ProcessStartInfo;
	System::Diagnostics::Process^ m_VoiceEngineProcess;
};

