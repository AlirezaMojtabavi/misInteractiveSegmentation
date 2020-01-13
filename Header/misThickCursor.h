#pragma once

#include "misCursor.h"

class misThickCursor : public misCursor
{

public:
	
	misThickCursor(void);
	~misThickCursor(void);
 	static misThickCursor *New();

protected:

	void SetModelBounds(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
	void Initialization();
	void UpdateCursorColor();

	vtkPolyDataMapper *RX_Mapper;
	vtkPolyDataMapper *RY_Mapper;
	vtkPolyDataMapper *RZ_Mapper;

	vtkPolyDataMapper *LX_Mapper;
	vtkPolyDataMapper *LY_Mapper;
	vtkPolyDataMapper *LZ_Mapper;

	vtkPolyDataMapper *SphereMapper;
	vtkSphereSource *SphereSource;

	vtkActor *RX_Actor;
	vtkActor *RY_Actor;
	vtkActor *RZ_Actor;

	vtkActor *LX_Actor;
	vtkActor *LY_Actor;
	vtkActor *LZ_Actor;

	vtkActor *SphereActor;

	//vtkParametricFunctionSource *ptorus;
	//vtkParametricTorus *m_torus;

	void ModifyAxis();
	void ModifyXAxis();
	void ModifyYAxis();
	void ModifyZAxis();

	void ModifySphere();

	vtkAlgorithmOutput *Get_RX();
	vtkAlgorithmOutput *Get_RY();
	vtkAlgorithmOutput *Get_RZ();
	
	vtkAlgorithmOutput *Get_LX();
	vtkAlgorithmOutput *Get_LY();
	vtkAlgorithmOutput *Get_LZ();
	
	vtkAlgorithmOutput * Rx_output;
	vtkAlgorithmOutput * Ry_output;
	vtkAlgorithmOutput * Rz_output;
	
	vtkAlgorithmOutput * Lx_output;
	vtkAlgorithmOutput * Ly_output;
	vtkAlgorithmOutput * Lz_output;
};

