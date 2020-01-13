#pragma once

#include "misDirectionAnnotation.h"
#include "misImageDataProperties.h"
#include "misRepresentation.h"
#include "IImageAnnotation.h"

//The class provide annotation actors to be added to a viewer 
class misImageAnnotation : public misRepresentation, public IImageAnnotation
{
public:
	misImageAnnotation();
	void SetTitle(std::string title)override;
	void SetRenWinSize(int HorizantalSize,int VerticalSize)override;
	void AddDistanceAnnotaion(double distance)override;

private:	
	vtkSmartPointer<vtkTextActor> AdAnnotationMem(std::string text, int justification,int verticalJustification ,double* position );

	void UpdateTitlePosition();
	std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo> m_AnnotationData;
	vtkSmartPointer<vtkTextProperty> m_TetxureProp;
	std::vector<std::string> m_AnnotationText;
	double m_DefaultColor[3];
	int m_DefaultFont;

	double m_LeftUpPosition[2];
	double m_LeftDownPosition[2];
	double m_RightUpPosition[2];
	std::vector<vtkSmartPointer<vtkTextActor>> m_leftUpActors;
	std::vector<vtkSmartPointer<vtkTextActor>> m_leftDownpActors;
	vtkSmartPointer<vtkTextActor> m_TitleActor;
	int* ren_size;
	int m_windowHorizantalSize;
	int m_windowVerticalSize;
	std::string Justification;
};
