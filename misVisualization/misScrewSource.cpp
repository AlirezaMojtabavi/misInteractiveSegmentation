#include "StdAfx.h"
//#include "misScrewSource.h"
//
//
//#include "misScrewReader.h"
//
//
//
//misScrewSource::misScrewSource(void)
//{
//	readPolyDta = false;
//}
//
//
//misScrewSource::misScrewSource( double point1[3], double point2[3] )
//{
//	SetPoint1(point1);
//	SetPoint2(point2);
//}
//
//misScrewSource::~misScrewSource(void)
//{
//}
//
//vtkSmartPointer<vtkPolyData> misScrewSource::GenerateScrew( float height )
//{
//	if (!readPolyDta)
//	{
//		std::stringstream pathBuilder;
//		pathBuilder << FileSystem::currentDirectory();
//		pathBuilder << "\\Resources\\3d Model\\Screw 3D Model";
//		try
//		{
//			reader.ReadPolyadataFromFile(pathBuilder.str());
//			readPolyDta = true;
//		}
//		catch(const FileNotFoundException& exp)
//		{
//			std::cout << "Screw file not found => " << exp.getFileName();
//			readPolyDta = false;
//			return NULL;
//		}
//	}
//
//	vtkSmartPointer<vtkPolyData> cylinder	= reader.GetScrewcylinder();
//	vtkSmartPointer<vtkPolyData> head		= reader.GetScrewHead();
//
//	vtkSmartPointer<vtkTransform> transformHead = vtkSmartPointer<vtkTransform>::New();
//	transformHead->Translate(0, 0, height);
//	vtkSmartPointer<vtkTransformPolyDataFilter> polyFilterHead = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
//	polyFilterHead->SetInputData(head);
//	polyFilterHead->SetTransform(transformHead);
//
//	vtkSmartPointer<vtkClipPolyData> pClipper = vtkSmartPointer<vtkClipPolyData>::New();
//	pClipper->SetInputData(cylinder);
//	vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
//	plane->SetNormal(0,0,-1);
//	plane->SetOrigin(0,0,height);
//	pClipper->SetClipFunction(plane);
//	pClipper->Update();
//	vtkSmartPointer<vtkPolyData>		clippedcylinde	= pClipper->GetOutput();
//	vtkSmartPointer<vtkAppendPolyData>  appender		= vtkSmartPointer<vtkAppendPolyData>::New();
//
//	appender->AddInputData(polyFilterHead->GetOutput());
//	appender->AddInputData(clippedcylinde);
//	appender->Update();
//	vtkSmartPointer<vtkPolyData> result = appender->GetOutput();
//
//	return  result;
//}
//
//vtkSmartPointer<vtkPolyData> misScrewSource::GenerateScrew( )
//{
//	return GenerateBasicScrew()->GetOutput();
//}
//
//vtkSmartPointer<vtkAppendPolyData> misScrewSource::GenerateBasicScrew()
//{
//	double screwLen = misSimplePointType::EuclideanDistance(m_P1, m_P2);
//	//if (screwLen > 70.0)
//	//{
//	//	screwLen = 70.0;
//	//}
//	double tmpCurrent[3];
//	tmpCurrent[0] = 0.0;
//	tmpCurrent[1] = 0.0;
//	tmpCurrent[2] = screwLen;
//
//	misSimplePointType currentVector;
//	currentVector.SetPoint(tmpCurrent);
//
//	//Translate clippedcylinde
//	misSimplePointType newVector = misSimplePointType::Minus(m_P2, m_P1);
//	double angel = misSimplePointType::GetAngle(newVector, currentVector);
//
//	currentVector.Normalize();
//	newVector.Normalize();
//	misSimplePointType cross = misSimplePointType::CrossProduct(currentVector, newVector);
//
//	vtkTransform* trans = vtkTransform::New();
//	trans->PostMultiply();
//	trans->RotateWXYZ(angel, cross[0], cross[1], cross[2]);
//	trans->Translate(m_P1[0], m_P1[1], m_P1[2]);
//
//	vtkSmartPointer<vtkTransformPolyDataFilter> newTransPoly = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
//	newTransPoly->SetInputData(this->GenerateScrew(screwLen));
//	newTransPoly->SetTransform(trans);
//
//	vtkSmartPointer<vtkAppendPolyData>  appender = vtkSmartPointer<vtkAppendPolyData>::New();
//	appender->AddInputData(newTransPoly->GetOutput());
//
//	appender->Update();
//	return appender;
//}
//
//void misScrewSource::SetRadius( double radius )
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//vtkSmartPointer<vtkTransform> misScrewSource::GetTransform()
//{
//	return{};
//}
//
//vtkAlgorithmOutput* misScrewSource::GetOutputPort()
//{
//	return GenerateBasicScrew()->GetOutputPort();
//}
//
//ScrewWidgetSourceType misScrewSource::GetSourceType()
//{
//	return Screw;
//}
//
//vtkSmartPointer<vtkPolyData> misScrewSource::GetOutput()
//{
//	return GenerateScrew();
//}
//
//void misScrewSource::Setheight( double height )
//{
//	GenerateScrew(height);
//}
//
//void misScrewSource::SetPoint1( double p1[3] )
//{
//	m_P1.SetPoint(p1);
//}
//
//void misScrewSource::SetPoint2( double p2[3] )
//{
//	m_P2.SetPoint(p2);
//	GenerateScrew();
//}
//
//parcast::PointD3 misScrewSource::GetPoint1()
//{
//	return parcast::PointD3(m_P1.data);
//}
//
//parcast::PointD3 misScrewSource::GetPoint2()
//{
//	return parcast::PointD3(m_P2.data);
//}
//
////void misScrewSource::SetScrewLength( float screwLen )
////{
////	screwLen = screwLen;
////}
