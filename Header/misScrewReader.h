#pragma once

#include "misException.h"

class misScrewReader
{
private:
	vtkSmartPointer<vtkPolyData> m_HeadPoly;
	vtkSmartPointer<vtkPolyData> m_cylinderrPoly;
public:

	vtkSmartPointer<vtkPolyData>   GetScrewHead();
	vtkSmartPointer<vtkPolyData>   GetScrewcylinder();
#pragma warning (suppress : 4290)
	void ReadPolyadataFromFile(std::string  foldername) throw (FileNotFoundException) ;

	misScrewReader(void);
	~misScrewReader(void);
};
