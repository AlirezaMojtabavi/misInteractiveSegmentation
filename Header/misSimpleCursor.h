#pragma once
#ifndef __misSimpleCursor_h
#define __misSimpleCursor_h

#include "misCursor.h"

class  misSimpleCursor : public misCursor
{
public:

	static misSimpleCursor *New();

protected:

	void SetModelBounds(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
	void Initialization();
	void UpdateCursorColor();

	misSimpleCursor();
	~misSimpleCursor();

	vtkPolyDataMapper *X_Mapper;
	vtkPolyDataMapper *Y_Mapper;
	vtkPolyDataMapper *Z_Mapper;
	vtkPolyDataMapper *torusMapper;

	vtkActor *X_Actor;
	vtkActor *Y_Actor;
	vtkActor *Z_Actor;
	vtkActor *torusActor;

	vtkParametricFunctionSource *ptorus;
	vtkParametricTorus *m_torus;

	void ModifyAxis();
	void ModifyXAxis();
	void ModifyYAxis();
	void ModifyZAxis();

	void ModifyTorus(int radius);

	vtkPolyData *Get_X();
	vtkPolyData *Get_Y();
	vtkPolyData *Get_Z();

	vtkPolyData * x_output;
	vtkPolyData * y_output;
	vtkPolyData * z_output;
};

#endif


