#include "stdafx.h"
#include "misFrustumRepresentationForMicronTracker.h"

using namespace std;

misFrustumRepresentationForMicronTracker::misFrustumRepresentationForMicronTracker(string name)
	: misRepresentation(name)
{
	this->Init();
}

misFrustumRepresentationForMicronTracker::~misFrustumRepresentationForMicronTracker()
{
}

void misFrustumRepresentationForMicronTracker::Init()
{
	this->InitPlanesCoordinateds();

	vtkPoints*  pFrustumPlanePoints=vtkPoints::New();
	vtkFloatArray* scalar=vtkFloatArray::New();

	misItkPointType planesCoordinates;

	for (int i=0; i< this->m_PlanesCoordinateds.size(); i++)
	{
		planesCoordinates = this->m_PlanesCoordinateds[i];
		float color = 1.0;

		pFrustumPlanePoints->InsertNextPoint(-(1 * planesCoordinates[0]/2),+(1 * planesCoordinates[1]/2),planesCoordinates[2]);
		scalar->InsertNextValue(color);

		pFrustumPlanePoints->InsertNextPoint(+(1 * planesCoordinates[0]/2),+(1 * planesCoordinates[1]/2),planesCoordinates[2]);
		scalar->InsertNextValue(color);

		pFrustumPlanePoints->InsertNextPoint(+(1 * planesCoordinates[0]/2),-(1 * planesCoordinates[1]/2),planesCoordinates[2]);
		scalar->InsertNextValue(color);

		pFrustumPlanePoints->InsertNextPoint(-(1 * planesCoordinates[0]/2),-(1 * planesCoordinates[1]/2),planesCoordinates[2]);
		scalar->InsertNextValue(color);
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


	////========================================================
	//ids[0]=8;
	//ids[1]=11;
	//ids[2]=15;
	//ids[3]=12;

	//pFrustumCells->InsertNextCell(4,ids);


	//ids[0]=8;
	//ids[1]=9;
	//ids[2]=13;
	//ids[3]=12;

	//pFrustumCells->InsertNextCell(4,ids);
	//ids[0]=9;
	//ids[1]=10;
	//ids[2]=14;
	//ids[3]=13;

	//pFrustumCells->InsertNextCell(4,ids);


	//ids[0]=10;
	//ids[1]=11;
	//ids[2]=15;
	//ids[3]=14;

	//pFrustumCells->InsertNextCell(4,ids);
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

void misFrustumRepresentationForMicronTracker::InitPlanesCoordinateds()
{

	misItkPointType    planesCoordinates;

	planesCoordinates[0]= 100;
	planesCoordinates[1]= 50;
	planesCoordinates[2]= 300;
	m_PlanesCoordinateds.push_back(planesCoordinates);

	planesCoordinates[0]= 2000;
	planesCoordinates[1]= 1600;
	planesCoordinates[2]= 2180;
	m_PlanesCoordinateds.push_back(planesCoordinates);


	planesCoordinates[0]= 2400;
	planesCoordinates[1]= 2000;
	planesCoordinates[2]= 2650;
	m_PlanesCoordinateds.push_back(planesCoordinates);

}

 
