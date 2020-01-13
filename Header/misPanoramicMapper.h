#pragma once
#include "misWindowLevelStr.h"
 

// The misPanoramicMapper mapper extends vtkMapper capabilities to render a panoramic view of a slice within a 3D images that is
// defined by a curve.
// 1- A 1-D texture as an array of points that map the spline independent parameter to (x, y) on the curve point.
// 2- A 3-D texture representing the 3D image out of which the panoramic view should be extracted and rendered.
// misPanoramicMapper renders a plane and uses a GLSL shader for extraction of panoramic images. Both width and length of the 
// plane must be provided for view extraction. The rendering process (within the shader) typically involves generating a 2D 
// surface by extending the spline curve (defined in the x-y plane) along the z direction, moving the surface along the y axis 
// with a specified offset (slice offset), and then mapping the generated surface to a rectangular plane that is 
// subsequently displayed as a 2D panoramic image.
class misPanoramicMapper : public vtkMapper
{
public:
	static misPanoramicMapper* New();

	// OpenGL ID of a previously created 1D texture to serve as the curve function. The texture should provide x, y of points on
	// the curve. Internally, the mapper will spline the points, and use the spline curve to create the panoramic view.
	void SetPanoramicTextureData(float *pixelData, int width, int height);
	
	// OpenGL ID of a previously created 3D texture to serve as the 3D image. 
	void SetImage(GLuint imageTexture);
	
	// Set/Get window/level for changing the contrast and brightness.
	void SetWindowLevel( const misWindowLevelStr& windowLevel);
	misWindowLevelStr GetWindowLevel() const;

	// Set range of the pixel values
	void SetRange(double *range);

	// Set transferfunction id
	void SetTransferFunctionID( std::shared_ptr<TransFuncIntensity> colorTransferFunc);

	// Sets the world scale dimensions of the panoramic display volume mapped to the image texture. The rendered panoramic view 
	// will be a plane normal to the Z axis of this rectangular volume. The slice offset determines the plane to be extracted 
	// and displayed. Width corresponds to panoramic spline length, and Height and Depth respectively correspond to Z and Y 
	// extents of the image texture in world scales.
	double GetWidth() const;
	void SetWidth(double val);
	double GetHeight() const;
	void SetHeight(double val);
	void SetDepth(double depth);
	
	// Set the current slice offset (in image scales) for extracting a panoramic view. A slice offset of zero will result in
	// extracting a panoramic view that matches the original spline. Positive slice offset move the spline towards the negative
	// Y direction of the image. The slice offset will be automatically normalized to the Y extent of the image before being
	// transmitted to shader.
	void SetSlice(double slice);

	// vtkMapper interface:
	virtual void GetBounds( double bounds[6] ) override;
	virtual void Render( vtkRenderer *ren, vtkActor *a ) override;



private:
	misPanoramicMapper();
	~misPanoramicMapper();

	void SetUniformVariables();
	void DrawQuad();

	GLuint m_PanoramicTextureID;	// See SetParanomicCurve
	GLuint m_ImageTexture;	// See SetImage
	double m_Width; // See set/get Width/height 
	double m_Height;	 // See set/get Width/height 
	double m_Depth;	 // See set/get Width/height 
	double m_Slice;	// See SetSlice
	double m_Range[2]; //See SetRange
	misWindowLevelStr m_WindowLevel;	// See SetWindowLevel
	std::unique_ptr<tgt::Shader> m_Program;	// Shader program in charge of doing the actual render.
	std::shared_ptr<TransFuncIntensity> m_Transferfunction;
};