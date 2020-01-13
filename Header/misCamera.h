#pragma once
#include "BusinessEntities\Vertex.h"
#include "BusinessEntities\Vector.h"
 

// The misCamera keep camera position , focal and up view property
class misCamera
{
public:
	misCamera(double* position, double* focal, double* viewUp);
	misCamera();
	~misCamera();
	parcast::Vertex<double, 3> GetPosition()const;
	parcast::Vertex<double, 3> GetFocal()const;
	parcast::Vector<double, 3> GetViewUp()const;
	parcast::Vector<double, 3> GetCameraDirection() const;
private:
	parcast::Vertex<double, 3>m_Position;
	parcast::Vertex<double, 3> m_Focal;
	parcast::Vector<double, 3> m_ViewUP;
};

