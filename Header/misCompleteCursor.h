#ifndef __misCompleteCursor_h
#define __misCompleteCursor_h

#include "misCursor.h"

class misCompleteCursor : public misCursor
{
public:
	static misCompleteCursor *New();

	void SetModelBounds(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);

	vtkActor *GetActor_X();
	vtkActor *GetActor_Y();
	vtkActor *GetActor_Z();
	vtkActor *GetActor_Torus();

	void Initialization();

private:
	misCompleteCursor();
	~misCompleteCursor();

	void ModifyAxis();
	void ModifyXAxis();
	void ModifyYAxis();
	void ModifyZAxis();

	void ModifyBoundingBox();

	vtkPolyData *Get_X();
	vtkPolyData *Get_Y();
	vtkPolyData *Get_Z();
	bool IsVisible( double object[3],double cameraPos[3] );
	void UpdateCursorColor();
	vtkPolyData * x_output;
	vtkPolyData * y_output;
	vtkPolyData * z_output;

	vtkPolyDataMapper *X_Mapper;
	vtkPolyDataMapper *Y_Mapper;
	vtkPolyDataMapper *Z_Mapper;
	vtkPolyDataMapper *Torus_Mapper;

	vtkActor *X_Actor;
	vtkActor *Y_Actor;
	vtkActor *Z_Actor;
	vtkActor *Torus_Actor;
};

#endif


