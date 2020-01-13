#pragma once
#ifndef ___misRenderWinow__
#define ___misRenderWinow__

class vtkTimerLog;

    class   misRenderWinow : public vtkWin32OpenGLRenderWindow
{
protected:
	vtkTimerLog* m_Timer;
	float m_avgFrameRate;

	int m_index;

public:
	static misRenderWinow *New()
	{
		return new misRenderWinow;
	}

	misRenderWinow(void);
	virtual ~misRenderWinow(void);
	virtual void  Render();
	virtual void DoStereoRender();
	virtual void DoFDRender();
	virtual void DoAARender();
	virtual void CreateAWindow();
		virtual void Frame() ;

		void SetupPixelFormatPaletteAndContext(HDC hDC, DWORD dwFlags, int debug, int bpp, int zbpp);

	// Description:
	// Set the size of the window in pixels.
	virtual void SetSize(int,int);

};

#endif