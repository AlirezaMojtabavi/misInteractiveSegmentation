#include "stdafx.h"
#include "misFrustumRepresentation.h"

using std::string;

misFrustumRepresentation::misFrustumRepresentation(string name):misRepresentation(name),m_StateMachine(this)
{
	this->Init();
}
misFrustumRepresentation::~misFrustumRepresentation()
{
}

void misFrustumRepresentation::Init()
{
	this->InitPlanesCoordinateds();

	vtkPoints*  pFrustumPlanePoints=vtkPoints::New();
	vtkFloatArray* scalar=vtkFloatArray::New();

misItkPointType    planesCoordinates;
unsigned char color;


//color = 150;
//scalar->InsertNextValue(color);

for (int i=0; i< this->m_PlanesCoordinateds.size(); i++)
{
	planesCoordinates = this->m_PlanesCoordinateds[i];
	color = 1.0;

	pFrustumPlanePoints->InsertNextPoint(-(1 * planesCoordinates[0]/2),+(1 * planesCoordinates[1]/2),planesCoordinates[2]);
	scalar->InsertNextValue(color);

	pFrustumPlanePoints->InsertNextPoint(+(1 * planesCoordinates[0]/2),+(1 * planesCoordinates[1]/2),planesCoordinates[2]);
	scalar->InsertNextValue(color);

	pFrustumPlanePoints->InsertNextPoint(+(1 * planesCoordinates[0]/2),-(1 * planesCoordinates[1]/2),planesCoordinates[2]);
	scalar->InsertNextValue(color);

	pFrustumPlanePoints->InsertNextPoint(-(1 * planesCoordinates[0]/2),-(1 * planesCoordinates[1]/2),planesCoordinates[2]);
	scalar->InsertNextValue(color);
    
	
	
	//if (i<3)
	//{
	//	scalar->InsertNextValue(color);
	//}
	//

}



	vtkPolyData* pFrustumPoly=vtkPolyData::New();
	pFrustumPoly->SetPoints(pFrustumPlanePoints);

	//=============================================================
	vtkCellArray* pFrustumCells= vtkCellArray::New();

	vtkIdType ids[4];

	ids[0]=0;
	ids[1]=1;
	ids[2]=2;
	ids[3]=3;

	pFrustumCells->InsertNextCell(4,ids);

	ids[0]=0;
	ids[1]=3;
	ids[2]=7;
	ids[3]=4;

	pFrustumCells->InsertNextCell(4,ids);

	ids[0]=0;
	ids[1]=1;
	ids[2]=5;
	ids[3]=4;

	pFrustumCells->InsertNextCell(4,ids);

	ids[0]=1;
	ids[1]=2;
	ids[2]=6;
	ids[3]=5;

	pFrustumCells->InsertNextCell(4,ids);


	ids[0]=2;
	ids[1]=3;
	ids[2]=7;
	ids[3]=6;

	pFrustumCells->InsertNextCell(4,ids);
	//========================================================
	ids[0]=4;
	ids[1]=7;
	ids[2]=11;
	ids[3]=8;

	pFrustumCells->InsertNextCell(4,ids);


	ids[0]=4;
	ids[1]=5;
	ids[2]=9;
	ids[3]=8;

	pFrustumCells->InsertNextCell(4,ids);
	ids[0]=5;
	ids[1]=6;
	ids[2]=10;
	ids[3]=9;

	pFrustumCells->InsertNextCell(4,ids);


	ids[0]=6;
	ids[1]=7;
	ids[2]=11;
	ids[3]=10;

	pFrustumCells->InsertNextCell(4,ids);
	//=====================================================================================


	//========================================================
	ids[0]=8;
	ids[1]=11;
	ids[2]=15;
	ids[3]=12;

	pFrustumCells->InsertNextCell(4,ids);


	ids[0]=8;
	ids[1]=9;
	ids[2]=13;
	ids[3]=12;

	pFrustumCells->InsertNextCell(4,ids);
	ids[0]=9;
	ids[1]=10;
	ids[2]=14;
	ids[3]=13;

	pFrustumCells->InsertNextCell(4,ids);


	ids[0]=10;
	ids[1]=11;
	ids[2]=15;
	ids[3]=14;

	pFrustumCells->InsertNextCell(4,ids);
	//=====================================================================================

	pFrustumPoly->SetPolys(pFrustumCells);
	pFrustumPoly->GetPointData()->SetScalars(scalar);


	vtkPolyDataMapper* pMapper=vtkPolyDataMapper::New();
	pMapper->SetInputData(pFrustumPoly);
	pMapper->ScalarVisibilityOff();
	//pMapper->

	vtkActor* pNearActor=vtkActor::New();
	pNearActor->GetProperty()->SetRepresentationToWireframe();
	pNearActor->SetMapper(pMapper);
 	pNearActor->GetProperty()->SetColor(1.0,1.0,1.0);
 	pNearActor->GetProperty()->SetOpacity(0.5);
	this->m_Actors.push_back(pNearActor);


}

void misFrustumRepresentation::InitPlanesCoordinateds()
{

   misItkPointType    planesCoordinates;

   planesCoordinates[0]= -448;
   planesCoordinates[1]= -480;
   planesCoordinates[2]= -950;
   m_PlanesCoordinateds.push_back(planesCoordinates);

   planesCoordinates[0]= -796;
   planesCoordinates[1]= -1144;
   planesCoordinates[2]= -1532;
   m_PlanesCoordinateds.push_back(planesCoordinates);


   planesCoordinates[0]= -1312;
   planesCoordinates[1]= -1566;
   planesCoordinates[2]= -2400;
   m_PlanesCoordinateds.push_back(planesCoordinates);


   planesCoordinates[0]= -1470;
   planesCoordinates[1]= -1856;
   planesCoordinates[2]= -3000;
   m_PlanesCoordinateds.push_back(planesCoordinates);


}

 