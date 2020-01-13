#pragma once





class   misFollowerFixedArea : public vtkActor
{
 public:
  static misFollowerFixedArea *New();
  virtual void SetCamera(vtkCamera*);
  vtkGetObjectMacro(Camera,vtkCamera);

  virtual void Render(vtkRenderer *ren);
  static vtkSmartPointer<vtkTransform> ComputeShiftTransform(vtkCamera* camera, double distance2Plane);

  virtual void GetMatrix(vtkMatrix4x4 *m);
  virtual void GetMatrix(double m[16]);
  virtual vtkMatrix4x4* GetMatrix()
    {return this->vtkActor::GetMatrix();}
  virtual int RenderOpaqueGeometry(vtkViewport *viewport);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport *viewport);
  virtual int HasTranslucentPolygonalGeometry();
  void DisableDepthOn();
  void DisableDepthOff();
  void SetDisableDepth(bool state);

protected:
  misFollowerFixedArea();
  ~misFollowerFixedArea();

  vtkCamera *Camera;
  vtkActor  *Device;
private:
  // hide the two parameter Render() method from the user and the compiler.
  virtual void Render(vtkRenderer *, vtkMapper *) {};
private:
  misFollowerFixedArea(const misFollowerFixedArea&);  // Not implemented.
  void operator=(const misFollowerFixedArea&);  // Not implemented.
  float DistanceToCamera( );
  float m_ScaleCoef;
  float m_ClampScaleRange[2];
  vtkRenderer *m_Renderer;
  const double m_distance2Plane = 20.0;
  bool m_DisableDepth = true;
};
