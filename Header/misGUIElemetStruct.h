#pragma once

#ifndef misGUIElemetStruct_h
#define misGUIElemetStruct_h

enum misGUIElementType
{ 
  PushButton = 0,
  RadioButton,
  ToggleButton,
  EditableText,
  StaticText,
  CheckBox,
  ListBox,
  PopUpMenu,
  Slider,
};


enum misGUIElementEnable
{
	MouseClick = 0,
	MouseOver,
	Active,
	Inactive,
};

#endif