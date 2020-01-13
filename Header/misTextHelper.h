#pragma once
#ifndef misTextHelper_H
#define misTextHelper_H

using namespace System;

#pragma warning ( disable : 4996 )
#pragma warning ( disable : 4081 )
#pragma make_public(char)
 
  public  ref class  misTextHelper
{
public:
	//inline static  char*   To_string( String^ source);
	 static System::IntPtr ToStringX( String^ source);

	//static void Trim_string(char*  string);
	  static String^ TransparencyToString( char transparency);
	  static  wchar_t transparencytochar( String^ transparency);

	  // Note : significantDigit show the number after point
	  //        minimumAcceptableNumber set to 0.0 if you don't want to use it
	  // Important Note : gcvt must not used in any ware
	  static  String^  ValueToString(double inputValue, int significantDigit ,double minimumAcceptableNumber  /*= 0*/);
};

#endif
