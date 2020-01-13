#pragma once

class MisMicronUtilities
{
public:
	//returns true if handle in not NULL, else throws a NullHandleException exception
	static bool CheckHandleValidity(mtHandle CurrentHandle);

	//returns true if string is not NULL and also != "" else throws NullStringException
	static bool CheckStringValidity(char * CurrentCharPTR);

	//returns true if CurrentCode == mtOK, else throws MTCtaskFailedException exception
	static bool CheckTaskCompletion(mtCompletionCode CurrentCode);

};

