#pragma once

#include "misCornerProperties.h"
#include "misImageGeoProperties.h"
#include "misObject.h"
#include "misZoomFinder.h"
#include "misGuiStructures.h"
 

 
class misCameraInteraction 
{
public:

	misCameraInteraction();
	void UpdateView();
	void UpdateView(int );
	void UpdateCamera();
	void SetCameraFocalPoint(PointType);
	void SetCameraFocalPoint(double*);
	void SetAutoCameraScale(double );
	void SetImageOrientation(IMAGEORIENTATION );
	void SetCamera(vtkCamera *);
	void SetPlaneCenter(PointType);
	vtkCamera* GetCamera();
	void SetCurrentZoomProportion(double);
	double GetCurrentZoomProportion() const;
	void SetCurrentZoomPercentage(unsigned int);
	unsigned int GetCurrentZoomPercentage() const;
	zoomStrct UpdateZoomPercentageInGUI( );
	void UpdateZoom(misZoomState , double[3]);
	void SetCornerProperties( std::shared_ptr<ICornerProperties> pCornerProp );
	void Reset();
	void SetDefaultZoom();

	// Return zoom to initial state
	zoomStrct Reset2DZoom();
 
private:
	const double ParallelPlaneScaleFactor; //Initialize zoom (width of plane showing image )

	unsigned int  m_CurrentZoomPercentage;
	double   m_currentZoomProportion;
	void			UpdatePlaneDimension();
	void			SetPlaneDimendion(double *);
	// Compute zoom scale by image plane width, height

	vtkCamera*	m_Camera;
	double m_CameraScale;
	misZoomFinder m_ZoomService;
	double m_PlaneDimension[3]; //Representation Dimension
	double	m_PlaneCenter[3]; //Representation center
	double	m_FocalPointCenter[3];
	IMAGEORIENTATION m_ImageOrientation;
	std::shared_ptr<ICornerProperties> m_CornerProperties;
	bool ResetZoomNeeded(int zoomPercentage);
};