#pragma once

#include "misStringTools.h"
class misLogger;

class mis3dTexture :	public vtkOpenGLTexture
{
public:
double LoadedBounds[6];
bool Supports_GL_ARB_texture_float;

	vtkTypeRevisionMacro(mis3dTexture,vtkOpenGLTexture);

	static mis3dTexture *New()
	{
		return  new mis3dTexture;
	}

	void Load(vtkRenderer *ren);

	void CheckExtension( vtkRenderer * ren );
	void ApplyBlendingType();
	void CheckDepthPeeling( vtkOpenGLRenderer * oRenderer, GLint &uUseTexture, GLint &uTexture );
	void BuildTransformation();
	mis3dTexture(void);
	virtual ~mis3dTexture(void);
	void ReleaseGraphicsResources(vtkWindow *  window);

	void DeleteTexture( vtkWindow * renWin );
	void LoadImageData(vtkImageData *input, int cellFlag, int textureExtent[6], bool linearInterpolation, double tableRange[2], int maxMemoryInBytes);
	//virtual void PostRender(vtkRenderer *ren);
	void SetImageUID(misUID imageUID);
	misUID GetImageUID(){return this->m_ImageUID;};


protected:
		//virtual void Initialize(vtkRenderer * ren);
	 // 
		//vtkTimeStamp   LoadTime;
		//unsigned int Index; // actually GLuint
		//vtkWeakPointer<vtkRenderWindow> RenderWindow;   // RenderWindow used for previous render
		//bool CheckedHardwareSupport;
		//bool SupportsNonPowerOfTwoTextures;
		//bool SupportsPBO;
		//vtkPixelBufferObject *PBO;

private:
	vtkOpenGLExtensionManager* m_pManger;
	misUID m_ImageUID;
	misLogger*   m_pLogger;



};
