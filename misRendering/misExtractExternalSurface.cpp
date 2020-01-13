#include "StdAfx.h"
#include "misExtractExternalSurface.h"
#include "vtkContourFilter.h"

using namespace std;

 

vtkSmartPointer<vtkPolyData> misExtractExternalSurface::ExtractOuterSurface(vtkImageData* image, double threshold)
{
	auto poly = ComputeCountourFromImage(image, threshold);
	auto points = poly->GetPoints();
	if (points == nullptr)
	{
		return nullptr;
	}
	if (points->GetNumberOfPoints() == 0)
	{
		return nullptr;
	}
	return ComputeExternalSurfaceOfContour(poly);
}

vtkSmartPointer<vtkPolyData> misExtractExternalSurface::ComputeExternalSurfaceOfContour(vtkPolyData* poly)
{
	double center[3], bounds[6];
	poly->GetCenter(center); 
	poly->GetPoints()->GetBounds(bounds);
	// Build a cell locater.
	vtkSmartPointer<vtkCellLocator> cellLocator =  vtkSmartPointer<vtkCellLocator>::New();
	cellLocator->SetDataSet(poly);
	cellLocator->BuildLocator();

	vtkSmartPointer<vtkSphereSource> pShpere = vtkSmartPointer<vtkSphereSource>::New();
	const int phiResolotion = 1000;
	pShpere->SetPhiResolution(phiResolotion);
	const int thetaResolotion = 1000;
	pShpere->SetThetaResolution(thetaResolotion);
	pShpere->SetRadius(GetEstimatedRadius(bounds));
	pShpere->SetCenter(center);
	pShpere->Update();

	vtkSmartPointer<vtkPolyData> spPoly = pShpere->GetOutput();
	vtkIdType numOfPoly = spPoly->GetNumberOfPoints();
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	vtkPolyData* extractedSurface = vtkPolyData::New();
	extractedSurface->SetVerts(cells);
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	for(int i = 0;i < numOfPoly; i++)
	{
		double* point= spPoly->GetPoint(i);
		double rayStart[3];
		for (unsigned int i = 0; i < 3; i++)
			rayStart[i] = point[i] ;

		vtkIdType cellId = -1;
		double xyz[3], t = 0 ;
		double pcoords[3] ;
		const double unInitilzedPoint = -1000000;
		xyz[0] = xyz[1] = xyz[2]= unInitilzedPoint;
		pcoords[0] = pcoords[1] = pcoords[2] = 0;
		int subId=0;

		int ret=cellLocator->IntersectWithLine(	rayStart, center, 0.0001, t, xyz, pcoords, subId, cellId);
		if (ret!=0)
		{
			if((xyz[0]  != unInitilzedPoint)&&	(xyz[1] != unInitilzedPoint) && (xyz[2] != unInitilzedPoint))
			{
				vtkIdType  cellid= points->InsertNextPoint(xyz);
				extractedSurface->InsertNextCell(VTK_VERTEX, 1, &cellid);
			}

		}
	}
	extractedSurface->SetPoints(points);
	if (extractedSurface->GetNumberOfCells() == 0)
	{
		extractedSurface->Delete();
		return NULL;
	}
	return  extractedSurface;
}

double misExtractExternalSurface::GetEstimatedRadius( double * bounds )
{
	std::vector<double> radiosList;
	radiosList.push_back(bounds[1]-bounds[0]);
	radiosList.push_back(bounds[3]-bounds[2]);
	radiosList.push_back(bounds[5]-bounds[4]);
	auto maxRadios = max_element(radiosList.begin(), radiosList.end());
	return *maxRadios / 1.5;
}

vtkSmartPointer<vtkPolyData> misExtractExternalSurface::ComputeCountourFromImage(vtkImageData* image, double threshold)
{
	auto segmentedSurface = vtkSmartPointer<vtkContourFilter>::New();
	segmentedSurface->ComputeGradientsOff();
	segmentedSurface->ComputeNormalsOff();
	segmentedSurface->SetInputData(image);
	segmentedSurface->SetNumberOfContours(1);
	segmentedSurface->SetValue(0, threshold);
	segmentedSurface->Update();
	vtkSmartPointer<vtkPolyData> poly = segmentedSurface->GetOutput();
	return poly;
}
