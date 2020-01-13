#pragma once

using namespace System;
namespace WrapperGUIBase {
	// Base class for showing any splash screen
public ref class misSplashScreenGUIBase abstract
{
public:
	virtual void ShowSplashScreen(String^ logoFileName) = 0;
	virtual void CloseSplashScreen() = 0;

};
}

