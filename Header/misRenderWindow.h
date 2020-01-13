#pragma once
class misRenderWindow :public vtkWin32OpenGLRenderWindow
{
public:
	misRenderWindow();
	~misRenderWindow();
	static misRenderWindow *New()
	{
		return new misRenderWindow;
	}
	virtual void CreateAWindow();
	void Render()  override;


};

