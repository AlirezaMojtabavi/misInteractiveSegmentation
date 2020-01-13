#include "StdAfx.h"
#include "misSideAnnotation.h"

using namespace parcast;

misSideAnnotation::misSideAnnotation():misRepresentation("Side Annotation")
{
	m_DefaultColor[0]=1.0;
	m_DefaultColor[1]=1.0;
	m_DefaultColor[2]=0.0;
	m_DefaultFont=16;
	m_TetxureProp = vtkSmartPointer<vtkTextProperty>::New();
	m_TetxureProp->SetColor(m_DefaultColor[0],m_DefaultColor[1],m_DefaultColor[2]);
	m_TetxureProp->SetFontSize(m_DefaultFont);
	m_TetxureProp->SetFontFamily(VTK_TIMES);
}


void misSideAnnotation::SetSideAnnotation(std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo>  annotationData)
{

	const char *str = "W";		//sample string to calculate bounding box information

	if(!AreAnnotationsChanged(m_AnnotationData, annotationData))
		return;

	m_AnnotationData = annotationData;

	int DefaultFont=18;
	double DefaultColor[3];
	DefaultColor[0]=1.0;
	DefaultColor[1]=1.0;
	DefaultColor[2]=0.0;
	int count=0;
	const auto NumberOfTextMD=m_AnnotationData.at(MiddleDown).Text.size();
	const auto NumberOfTextMU=m_AnnotationData.at(MiddleUp).Text.size();
	const auto NumberOfTextMR=m_AnnotationData.at(MiddleRight).Text.size();
	const auto NumberOfTextML=m_AnnotationData.at(MiddleLeft).Text.size();

	m_MiddleDownActors.clear();
	m_MiddleUpActors.clear();
	m_MiddleLeftActors.clear();
	m_MiddleRighActors.clear();
	m_Actors.clear();

	for (size_t index=0;index<NumberOfTextMD;index++)
	{
		vtkSmartPointer<vtkTextActor> actor= AdAnnotationMem(m_AnnotationData[MiddleDown].Text[count], 
			VTK_TEXT_CENTERED,VTK_TEXT_TOP,	m_MiddleDownPosition);
		m_MiddleDownActors.push_back(actor);

	}
	for (size_t index=0;index<NumberOfTextMU;index++)
	{
		vtkSmartPointer<vtkTextActor> actor=AdAnnotationMem(m_AnnotationData[MiddleUp].Text[count], 
			VTK_TEXT_CENTERED,VTK_TEXT_TOP, m_MiddleUpPosition);
		m_MiddleUpActors.push_back(actor);

	}

	for (size_t index=0;index<NumberOfTextML;index++)
	{
		vtkSmartPointer<vtkTextActor> actor= AdAnnotationMem(m_AnnotationData[MiddleLeft].Text[index], 
			VTK_TEXT_LEFT,VTK_TEXT_CENTERED, m_MiddleLeftPosition);
		m_MiddleLeftActors.push_back(actor);
	}
	count=0;
	for (size_t index=0;index<NumberOfTextMR;index++)
	{
		vtkSmartPointer<vtkTextActor> actor = AdAnnotationMem(m_AnnotationData[MiddleRight].Text[count],
			VTK_TEXT_RIGHT,VTK_TEXT_CENTERED, m_MiddleRightPosition);
		m_MiddleRighActors.push_back(actor);
	}

}

vtkSmartPointer<vtkTextActor> misSideAnnotation::AdAnnotationMem( std::string text, int justification ,int verticalJustification,double* position )
{
	vtkSmartPointer<vtkTextActor> actor = vtkSmartPointer<vtkTextActor>::New();
	actor->SetInput(text.c_str());
	vtkSmartPointer<vtkTextProperty> prop = vtkSmartPointer<vtkTextProperty>::New();
	prop->SetColor(m_DefaultColor[0],m_DefaultColor[1],m_DefaultColor[2]);
	prop->SetFontSize(m_DefaultFont);
	actor->SetPosition(position[0],position[1]);
	actor->SetTextProperty(prop);
	prop->SetJustification(justification);
	prop->SetVerticalJustification(verticalJustification);
	m_Actors.push_back(actor);
	return actor;
}


void misSideAnnotation::LayoutPositions()
{
	auto applytoctorPosition=[](std::vector<vtkSmartPointer<vtkTextActor>> actors ,double* pos)
	{
		std::for_each(actors.begin(),actors.end(),[&](vtkSmartPointer<vtkTextActor> prop)
		{

			prop->SetPosition(pos);
		});

	};
	const char *str;		//sample string to calculate bounding box information
	str="W";
	int BoxWidth;				//Bounding Box Width
	int BoxHeight;				//Bonding Box Height
	int BoundBox[4];			//Bounding Box Information
	vtkFreeTypeTools::GetInstance()->GetBoundingBox(m_TetxureProp, str,100 ,BoundBox);
	BoxHeight=BoundBox[3];
	BoxWidth=BoundBox[1];
	double LineOffset=m_TetxureProp->GetLineOffset();
	double LineSpacing=m_TetxureProp->GetLineSpacing();
 
	m_MiddleDownPosition[0]=m_windowHorizantalSize/2;
	m_MiddleDownPosition[1]=3*BoxHeight*LineSpacing+4;
	applytoctorPosition(m_MiddleDownActors,m_MiddleDownPosition);

	m_MiddleUpPosition[0]=m_windowHorizantalSize/2;
	m_MiddleUpPosition[1]=m_windowVerticalSize-(1*BoxHeight*LineSpacing)-4;
	applytoctorPosition(m_MiddleUpActors,m_MiddleUpPosition);

	m_MiddleLeftPosition[0]=0+4;
	m_MiddleLeftPosition[1]=(m_windowVerticalSize/2)+(1*BoxHeight*LineSpacing);
	applytoctorPosition(m_MiddleLeftActors,m_MiddleLeftPosition);

	m_MiddleRightPosition[0]=m_windowHorizantalSize-4;
	m_MiddleRightPosition[1]=(m_windowVerticalSize/2)+(BoxHeight*1*LineSpacing);
	applytoctorPosition(m_MiddleRighActors,m_MiddleRightPosition);

}

bool misSideAnnotation::AreAnnotationsChanged(
	const std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo>& annot1,
	const std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo>& annot2) const
{
	return annot1.size() != annot2.size() ||
		annot1.at(MiddleUp).Text[0] != annot2.at(MiddleUp).Text[0] ||
		annot1.at(MiddleDown).Text[0] != annot2.at(MiddleDown).Text[0] ||
		annot1.at(MiddleLeft).Text[0] != annot2.at(MiddleLeft).Text[0] ||
		annot1.at(MiddleRight).Text[0] != annot2.at(MiddleRight).Text[0];
}


void misSideAnnotation::SetRenWinSize(int HorizantalSize,int VerticalSize)
{
	if (HorizantalSize == 0 || VerticalSize == 0)
		return;
	m_windowHorizantalSize = HorizantalSize;
	m_windowVerticalSize = VerticalSize;
	LayoutPositions();
}
