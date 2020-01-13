#pragma once

struct WaitingBarStringsStr
{
	// appears as a short title on top of progress window : example : "Reading DICOM Files"
	std::string  title;
	 // appears as message which explain work in progress with more details : example : "Please wait, looking for DICOM files ..."
	std::string  status;
	std::string  CancelFunctionName;
	bool		AutomaticProgressBar;

	void Reset()
	{
		title = "";
		status = "";
		CancelFunctionName = "";
		AutomaticProgressBar = true;
	}
	WaitingBarStringsStr()
	{
		Reset();
	}
};