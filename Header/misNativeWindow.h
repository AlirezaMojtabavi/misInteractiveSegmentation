#pragma once

#include "misLibraryMacroes.h"

class MISLIBRARYEXPORT misNativeWindow
{
private:
	WNDCLASSEXW wndClass;
	HWND hWnd;

	HWND  m_parentWindow;
	void CreateWndClass(wchar_t *className, HINSTANCE hInstance, WNDPROC WndProc);

	static  bool Registered;

public:
	HWND GetParentWindow() const { return m_parentWindow; }
	void SetParentWindow(HWND val) { m_parentWindow = val; }

	misNativeWindow();
	~misNativeWindow(void);
	bool Create(int x,int y ,int width,int height,int show_param=SW_SHOW);
	bool RegisterWndClass();
	void Show(int nCmdShow);
	HWND Handle();
	static LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
};
