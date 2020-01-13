#pragma once

#include "misQuadMapperBase.h"

class misVideoStarter;
class misVideoMapper : 	public misQuadMapperBase
{

private:
	misVideoMapper(HWND windowHandle,std::wstring deviceName , IMAGEORIENTATION orientation);
	misVideoStarter* m_pVideoStarter;
	tgt::Texture* m_ErrorText;
public:
	
	static misVideoMapper* New(HWND windowHandle,std::wstring deviceName , IMAGEORIENTATION orientation);

	~misVideoMapper(void);
	void Render( vtkRenderer *ren, vtkActor *a );

	GLuint GenerateVideoTexture();

	virtual void	BuildPlane();
	virtual void	InitializeCoorinatePoints();
	virtual void	SetInitialSetting();
	virtual void	UpdatePlaneAndTexturePoints();
	void dispose();

	std::shared_ptr<ICornerProperties> GetCornerProperties();

};

