#pragma once

#include "vtkTexture.h"
//BTX
#include "vtkWeakPointer.h" // needed for vtkWeakPointer.
#include "vtkOpenGLTexture.h"
#include "vtkPixelBufferObject.h"
//ETX

class vtkWindow;
class vtkOpenGLRenderer;
class vtkRenderWindow;
class vtkPixelBufferObject;

class misOpenGLColorTexture : public vtkOpenGLTexture
{
public:
	vtkTypeRevisionMacro(misOpenGLColorTexture,vtkOpenGLTexture);

	static misOpenGLColorTexture *New()
	{
		return  new misOpenGLColorTexture;
	}

	
	virtual void PrintSelf(ostream& os, vtkIndent indent);

	// Description:
	// Implement base class method.
	void Load(vtkRenderer *ren);

	// Descsription:
	// Clean up after the rendering is complete.
	virtual void PostRender(vtkRenderer *ren);

	// Description:
	// Release any graphics resources that are being consumed by this texture.
	// The parameter window could be used to determine which graphic
	// resources to release. Using the same texture object in multiple
	// render windows is NOT currently supported. 
	void ReleaseGraphicsResources(vtkWindow *);


	// Description:
	// Get the openGL texture name to which this texture is bound.
	// This is available only if GL version >= 1.1
	vtkGetMacro(Index, long);
	//BTX
protected:
	misOpenGLColorTexture();
	~misOpenGLColorTexture();

	vtkTimeStamp   LoadTime;
	unsigned int Index; // actually GLuint
	vtkWeakPointer<vtkRenderWindow> RenderWindow;   // RenderWindow used for previous render
	bool CheckedHardwareSupport;
	bool SupportsNonPowerOfTwoTextures;
	bool SupportsPBO;
	vtkPixelBufferObject *PBO;

private:
	misOpenGLColorTexture(const misOpenGLColorTexture&);  // Not implemented.
	void operator=(const misOpenGLColorTexture&);  // Not implemented.

	// Description:
	// Handle loading in extension support
	virtual void Initialize(vtkRenderer * ren);

	//ETX
};


