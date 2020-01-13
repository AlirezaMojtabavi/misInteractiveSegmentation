#pragma once

#include "IDatasetManager.h"
#include "INavigationViewersNView.h"
#include "IPackageDataVisualizer.h"
#include "misSplineDrawing.h"
#include "ISplineVisualizer.h"

class misSplineVisualizer :public ISplineVisualizer
{
public:
	misSplineVisualizer(std::shared_ptr<misVolumeSlicer> imageViewer, std::shared_ptr<misPanoramicViewer> panoViewer);
	~misSplineVisualizer();

	bool AddSplineWidgetToAxialViewer(const std::vector<itk::Point<double, 3> >& splinePoints) override;
	void NewSpline() override;
	bool UndoSpline() override;
	bool LockSpline() override;
	void ChangeWidgetVisibility(bool visibility) override;
	SplinePoints GetSplinePoints() override;

private:
	void InitializeSplineWidget();
	void AddSplineRepresentation();
	void LoadSpline(const SplinePoints& splinePoints);
	void DeletSplineWidget();
	void RestoreImageInteractions();
	void RestoreSplineInteractor();
	
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<misVolumeSlicer> m_AxialImageViewer;
	std::shared_ptr<misPanoramicViewer> m_PanoramicViewer;
	vtkInteractorObserver* m_AxialInteractorObserver;
	vtkSmartPointer<misSplineDrawing> m_SplineDrawing;

};

