#include "StdAfx.h"
#include "misScrewReader.h"

misScrewReader::misScrewReader(void)
{
}


misScrewReader::~misScrewReader(void)
{
}

vtkSmartPointer<vtkPolyData> misScrewReader::GetScrewHead()
{
	return  m_HeadPoly;
}

vtkSmartPointer<vtkPolyData>  misScrewReader::GetScrewcylinder()
{
	return  m_cylinderrPoly;
}

void misScrewReader::ReadPolyadataFromFile( std::string foldername )
{
	std::string  path1=foldername+"//"+ "head.stl";
	bool res1=FileSystem::fileExists(path1);
	if(!res1)
	{
		throw FileNotFoundException();
	}
	std::string  path2=foldername+"//"+ "cylinder.stl";
	bool res2=FileSystem::fileExists(path1);
	if (!res2)
	{
		FileNotFoundException*  exp=new FileNotFoundException;
		throw  exp;
	}
	vtkSmartPointer<vtkSTLReader> objectReader=vtkSmartPointer<vtkSTLReader>::New();
	objectReader->SetFileName(path1.c_str());
	objectReader->MergingOff();
	objectReader->Update();
	m_HeadPoly=objectReader->GetOutput();
	vtkSmartPointer<vtkSTLReader> objectReader2=vtkSmartPointer<vtkSTLReader>::New();

	objectReader2->SetFileName(path2.c_str());
	objectReader2->MergingOff();
	objectReader2->Update();
	m_cylinderrPoly=objectReader2->GetOutput();
}
