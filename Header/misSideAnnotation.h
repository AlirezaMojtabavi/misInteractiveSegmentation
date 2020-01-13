#pragma once
#include "misRepresentation.h"
#include "misDirectionAnnotation.h"
#include "ISideAnnotation.h"

class misSideAnnotation	:public misRepresentation, public ISideAnnotation
{
public:
	misSideAnnotation();
	void SetSideAnnotation(std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo >  annotationData) override;
	void SetRenWinSize(int HorizantalSize,int VerticalSize) override;
private:
	vtkSmartPointer<vtkTextActor> AdAnnotationMem( std::string text, int justification ,int verticalJustification, 
		double* position );
	void LayoutPositions();
	bool AreAnnotationsChanged(
		const std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo>& annot1,
		const std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo>& annot2) const;
	std::vector<vtkSmartPointer<vtkTextActor>> m_MiddleUpActors;
	std::vector<vtkSmartPointer<vtkTextActor>> m_MiddleDownActors;
	std::vector<vtkSmartPointer<vtkTextActor>> m_MiddleRighActors;
	std::vector<vtkSmartPointer<vtkTextActor>> m_MiddleLeftActors;
	double m_MiddleUpPosition[2];
	double m_MiddleDownPosition[2];
	double m_MiddleRightPosition[2];
	double m_MiddleLeftPosition[2];
	std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo> m_AnnotationData;
	int* ren_size;
	int m_windowHorizantalSize;
	int m_windowVerticalSize;
	std::string Justification;
	double m_DefaultColor[3];
	vtkSmartPointer<vtkTextProperty> m_TetxureProp;
	int m_DefaultFont;
};

