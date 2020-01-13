#pragma once
//
//#include "misScrewReader.h"
//#include "misSimplePointType.h"
//#include "IImplantSource.h"
//// class for reading screw polydata from stl
//class misScrewSource :public IImplantSource
//{
//
//public:
//	misScrewSource(void);
//	~misScrewSource(void);
//	misScrewSource(double point1[3], double point2[3]);
//	virtual vtkSmartPointer<vtkPolyData> GetOutput();
//	virtual void SetPoint1(double p1[3]) override;
//	virtual void SetPoint2(double p2[3]) override;
//	virtual void Setheight( double height );
//	virtual parcast::PointD3 GetPoint1();
//	virtual parcast::PointD3 GetPoint2();
//	virtual ScrewWidgetSourceType GetSourceType();
//	virtual void SetRadius( double radius );
//
//	vtkSmartPointer<vtkTransform> GetTransform() override;
//
//	virtual vtkAlgorithmOutput* GetOutputPort() override;
//
//private:
//	vtkSmartPointer<vtkPolyData> GenerateScrew( float height );
//	vtkSmartPointer<vtkPolyData> GenerateScrew( );
//
//	vtkSmartPointer<vtkAppendPolyData> GenerateBasicScrew();
//
//
//	vtkSmartPointer<vtkPolyData> m_PolyData;
//
//
//	misScrewReader	reader;
//	bool			readPolyDta;
//	misSimplePointType	m_P1, m_P2;
//	float m_Height;
//};
//
