#pragma once
#include "Iwindows.h"

MOCK_BASE_CLASS(Mockwindows, Iwindows)
{
	MOCK_NON_CONST_METHOD(AddRenderer, 1, void(misRenderer::Pointer renderer));
	MOCK_CONST_METHOD(CheckActivation, 1, void(RECT &rc));
	MOCK_NON_CONST_METHOD(GenerateFormWindowModel, 1, void(misWindowModel  model));
	MOCK_CONST_METHOD(get_m_Handle, 0, HWND());
	MOCK_NON_CONST_METHOD(set_m_Handle, 1, void(HWND left));
	MOCK_CONST_METHOD(get_m_Name, 0, std::string());
	MOCK_NON_CONST_METHOD(set_m_Name, 1, void(std::string left));
	MOCK_NON_CONST_METHOD(GetRenderWindow, 0, vtkRenderWindow*());
	MOCK_NON_CONST_METHOD(GetInterActor, 0, vtkSmartPointer<vtkRenderWindowInteractor>());
	MOCK_NON_CONST_METHOD(GetRenderer, 1, vtkSmartPointer<vtkRenderer>(int index));
	MOCK_NON_CONST_METHOD(GetContextId, 0, HGLRC());
	MOCK_CONST_METHOD(GetWindowIndex, 0, int());
	MOCK_NON_CONST_METHOD(SetWindowIndex, 1, void(int val));
	MOCK_NON_CONST_METHOD(GetRenderWindowSize, 0, int*());
	MOCK_NON_CONST_METHOD(Show, 0, void());
	MOCK_NON_CONST_METHOD(Hide, 0, void());
	MOCK_NON_CONST_METHOD(Destroy, 0, void());
	MOCK_NON_CONST_METHOD(GenerateRenderWindow, 2, int(ViewerType type, misViewPort viewport = misViewPort()));
	MOCK_CONST_METHOD(GetWindowSize, 0, misStrctWindowSize());
	MOCK_NON_CONST_METHOD(Start, 0, void());
	MOCK_CONST_METHOD(GetParentTabName, 0, std::string());
	MOCK_NON_CONST_METHOD(SetParentTabName, 1, void(std::string val));
	MOCK_CONST_METHOD(GetParentSubTabName, 0, std::string());
	MOCK_NON_CONST_METHOD(SetParentSubTabName, 1, void(std::string val));
	MOCK_CONST_METHOD(GetActive, 0, bool());
	MOCK_NON_CONST_METHOD(SetActive, 1, void(bool val));
	MOCK_NON_CONST_METHOD(SetProvidedWindowAsParent, 1, void(bool value));
	MOCK_NON_CONST_METHOD(MakeCurrent, 0, void());
};