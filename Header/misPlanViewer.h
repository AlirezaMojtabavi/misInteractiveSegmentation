#pragma once
//#include "misGroupViewLandMark.h"
#include "misHeader.h"

//class vtkLineWidget2;
//class vtkLineRepresentation;


class MISDLLEXPORT misPlanViewer : public misGroupViewLandMark
{
 

public:
	igstkStandardClassBasicTraitsMacro( misPlanViewer, misGroupViewLandMark )   ;
	igstkNewMacro( Self );  

	
	//vtkLineWidget2 *  m_lineWidget;
	//void DrawApproach(double  point1[3],double  point2[3]);
	//void HideApproach(void);
	//void DeleteLineWidget(void);
/*	void InitializeVolumeWindow(void);*/

// 	void AddLandMark(int index,double position[3]);
// 	void AddLandMark(double position[3]);
// 
// 	void RemoveLankMark(misLandmarkType  landmarkType);
/*	void Add3dRepresentation( misRepresentation* PSurfaceRep );*/

	
protected:
	//void InitilizeViewer();

private:
//	vtkLineRepresentation *m_LineRepresentation;
	misPlanViewer(void);
	~misPlanViewer(void);
	
};

