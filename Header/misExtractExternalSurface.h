#pragma once

#include "logmanager.h"
#include "IImage.h"
#include "vtkSmartPointer.h"

// The misExtractExternalSurface is used for extracting outermost surface layer of a polydata. It bounds the surface within 
// a sphere that it builds and connects each point on the sphere to surface [bounding box] center and extracts intersection 
// points (between the lines and the spherical surface) as a new surface.
class misExtractExternalSurface
{
 public:
	static vtkSmartPointer<vtkPolyData> ExtractOuterSurface(vtkImageData* image, double threshold);

private:
	static vtkSmartPointer<vtkPolyData> ExtractOuterSurface(vtkPolyData* poly);
	static  	vtkSmartPointer<vtkPolyData> ComputeExternalSurfaceOfContour(vtkPolyData* poly);

	// Gets a length proportionate to the longest bounding box edge an estimate for the radius of the bounding sphere.
	static  double GetEstimatedRadius( double * bounds );
	static  vtkSmartPointer<vtkPolyData> ComputeCountourFromImage(vtkImageData* image, double threshold);
};

