#pragma once

class misVideoStarter;

class misVideoWindow
{
public:
	misVideoWindow(HWND ParentWin);//misVideoStarter* video
	~misVideoWindow(void);
	HWND GetVideoWindow();
	void SetVideo(misVideoStarter* video);
private:
	static misVideoStarter*  m_video;
	static HWND	m_MainWindow;
	
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ATOM MyRegisterClass(HINSTANCE hInstance);

};

