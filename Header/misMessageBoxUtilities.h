#pragma once



using namespace WrapperGUIBase;
using namespace System;

public ref class misMessageBoxUtilities
{
public:

	static String^     ConvertMessageBoxButtonEnumToString(CommandEnum messageBoxButton);
	static CommandEnum ConvertMessageBoxButtonStringToEnum(String^ enumInStringFormat);
};
