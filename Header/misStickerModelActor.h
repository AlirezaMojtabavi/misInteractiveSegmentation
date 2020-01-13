#pragma once

class misStickerModelActor : public vtkActor
{
public:
	void SetObjectPosition(double ObjectPos[3]);
	void SetScaleRatio(double val);
	void SetOffset(double* val);
	void PrintSelf(ostream& os, vtkIndent indent);

	// Description:
	// Creates a follower with no camera set
	static misStickerModelActor *New(double scaleRatio,double* offset);

	// Description:
	// Set/Get the camera to follow. If this is not set, then the follower
	// won't know who to follow.
	virtual void Setm_Renderer(vtkRenderer*);
	vtkGetObjectMacro(m_Renderer,vtkRenderer);

	// Description:
	// This causes the actor to be rendered. It in turn will render the actor's
	// property, texture map and then mapper. If a property hasn't been
	// assigned, then the actor will create one automatically.
	virtual int RenderOpaqueGeometry(vtkViewport *viewport);
	virtual int RenderTranslucentPolygonalGeometry(vtkViewport *viewport);
	virtual void Render(vtkRenderer *ren);

	// Description:
	// Does this prop have some translucent polygonal geometry?
	virtual int HasTranslucentPolygonalGeometry();

	// Description:
	// Copy the follower's composite 4x4 matrix into the matrix provided.
	virtual void GetMatrix(vtkMatrix4x4 *m);
	virtual void GetMatrix(double m[16]);
	virtual vtkMatrix4x4* GetMatrix()
	{return this->vtkActor::GetMatrix();}
	void  SetCamera(vtkCamera*  pCamera);

protected:
	virtual void Render(vtkRenderer *, vtkMapper *) {};
	misStickerModelActor();
	virtual ~misStickerModelActor();

	vtkRenderer *m_Renderer;
	vtkActor  *Device;
	vtkCamera *Camera;
	double m_ScaleRatio;
	double m_Offset[2];
	double m_ParallelOffset[2];
	double m_ObjectPosition[3];
	double m_CameraModificationTime;

private:
	// hide the two parameter Render() method from the user and the compiler.
	misStickerModelActor(const misStickerModelActor&);  // Not implemented.
	void operator=(const misStickerModelActor&);  // Not implemented.
};

//#endif
