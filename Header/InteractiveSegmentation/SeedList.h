
#pragma once
#include"vtkCommand.h"
#include<vector>
#include "vtkRenderWindowInteractor.h"
#include "vtkObjectFactory.h"
#include "vtkImageActor.h"
#include "math.h"
#include <vtkRegularPolygonSource.h>
#include <vtkPolyDataMapper.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include <vtkProperty.h>
#include "MyInteractionStyle3D.h"
#include "Reslicer.h"


struct coordinate3D
{
	double _x;
	double _y;
	double _z;
};

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
 

class SeedList 
{
public:

	SeedList(std::vector<coordinate3D>, std::vector<double>Intensity);
 
	
	void SetLastposition(double x, double y, int z);
	int paint(int x, int y, int z); // show seeds on window


	double* get_min_max();
	int GetCurrentSlice();

	std::vector<coordinate3D> get_vector();
 

 
private:
 	std::vector<coordinate3D> m_PointList;

	std::vector<double> m_Intensity;
	 
};

