#pragma once

class misSurfacePointPicker : public vtkPicker
{
public:
	misSurfacePointPicker(void);

	~misSurfacePointPicker(void);

public:
  static misSurfacePointPicker *New();
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the id of the picked point. If PointId = -1, nothing was picked.
  vtkGetMacro(PointId, vtkIdType);
  int Pick(double selectionX, double selectionY, double selectionZ,
                    vtkRenderer *renderer);

protected:

  vtkIdType PointId; //picked point

  double IntersectWithLine(double p1[3], double p2[3], double tol,
                          vtkAssemblyPath *path, vtkProp3D *p,
                          vtkAbstractMapper3D *m);

  void Initialize();

private:
  misSurfacePointPicker(const misSurfacePointPicker&);  // Not implemented.
  void operator=(const misSurfacePointPicker&);  // Not implemented.
  int rayIntersectsTriangle(double *p1, double *p2, double *v0, double *v1, double *v2,double* RetPoint);
};
