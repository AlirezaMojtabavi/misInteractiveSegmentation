#pragma once

#include "ISubsequenceLayout.h"

MOCK_BASE_CLASS(MockSubsequenceLayout, ISubsequenceLayout)
{
	MOCK_CONST_METHOD(Active, 0, bool(), identifier_2)
		MOCK_NON_CONST_METHOD(Active, 1, void(bool), identifier_1)
		MOCK_CONST_METHOD(GetActiveWindow, 0, int())
		MOCK_NON_CONST_METHOD(SetActiveWindow, 1, void(int left))
		MOCK_CONST_METHOD(GetFullScreenWindowID, 0, int())
		MOCK_NON_CONST_METHOD(SetullScreenWindowID, 1, void(int left))
		MOCK_CONST_METHOD(GetID, 0, int())
		MOCK_NON_CONST_METHOD(SetID, 1, void(int left))
		MOCK_CONST_METHOD(GetName, 0, std::string())
		MOCK_NON_CONST_METHOD(SetName, 1, void(std::string left))
		MOCK_NON_CONST_METHOD(SetParentTabName, 1, void(std::string parentTabName))
		MOCK_NON_CONST_METHOD(get_m_ParentTabName, 0, std::string())
		MOCK_CONST_METHOD(get_m_MainHandle, 0, void* ())
		MOCK_NON_CONST_METHOD(set_m_MainHandle, 1, void(void* left))
		MOCK_NON_CONST_METHOD(AddWindow, 1, void(misWindowModel window))
		MOCK_NON_CONST_METHOD(GetWindow, 2, bool(std::string name, misWindowModel& window), identifier_3)
		MOCK_NON_CONST_METHOD(GetWindow, 2, bool(int id, misWindowModel& window), identifier_4)
		MOCK_NON_CONST_METHOD(GetNumOfWindows, 0, int())
		MOCK_NON_CONST_METHOD(GetchildWindows, 0, ListType())
};