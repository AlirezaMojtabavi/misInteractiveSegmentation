#pragma once

struct misCapSetting
{
	double main;
	double CapSetting;

	void Reset(void)
	{
		main = 0.5;
		CapSetting = 0.0;
	};

	void UpCap(void)
	{
		this->main = this->main + 0.002;
	};

	void SetCap(double cap)
	{
		main = 0.0;
		CapSetting = cap;
	};

	misCapSetting()
	{
		this->Reset();
	};
};

typedef std::vector<misCapSetting> misCapSettingList;


struct misAllCapSetting
{
	misCapSetting       main;
	misCapSetting       IU;
	misCapSettingList   DetailList;

	void Reset()
	{
		main.Reset();
		IU.Reset();
		DetailList.clear();
	};

	misAllCapSetting()
	{
		this->Reset();
	};
};