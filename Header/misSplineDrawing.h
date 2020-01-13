#pragma once

// This class will draw a spline on the current axial slice based on the handle points are given by user. (left click)
class misSplineDrawing : public vtkInteractorStyleTrackballCamera
{
public:
	const double SphereRadius;
	const int SplineResolution;

	static misSplineDrawing* New();
	void Lock();

	void UndoLastPoint();

	void ResetSpline();

	// Set current slice number
	void SetSliceNumber(double);

	// Set a render
	void SetRenderer(vtkSmartPointer<vtkRenderer> renderer);

	// Get parametric spline of the drawn spline
	vtkSmartPointer<vtkParametricSpline> GetParametricSpline() const;

	// Approximate length of the drawn spline
	double GetSplineLength() const;

	// Set loaded points for reconstruction
	void SetLoadedPoints(vtkSmartPointer<vtkPoints> points);

	// Set Image viewer boundary
	void SetViewerBound(double bound[6] );

	// Add spline handle
	void AddHandle(double point[3]);

	void SetVisibility(bool visible);

private:

	misSplineDrawing();
	~misSplineDrawing();

	// Add user selected point to the handle points set and draw new spline accordingly.
	virtual void OnLeftButtonDown() override;

	// Delete last inserted point from the spline on "backspace" key press and clear the spline on "delete" key press.
	virtual void OnKeyPress() override;
	
	//Do nothing when the mouse wheels
	virtual void OnMouseWheelForward() override;
	virtual void OnMouseWheelBackward() override;

	// Draw a sphere at the given point
	vtkSmartPointer<vtkActor> DrawSphere(double *point) const;

	// Align drawn spline respect to X direction.
	void AlignSpline() const;

	// Update spline according to the handle points
	void UpdateSpline();
	
	// Initilize vtk spline widget
	void InitializeSplineWidget();


	double m_Slice;	//
	double m_Bound[6];
	vtkSmartPointer<vtkPoints> m_Points;	// vector of 3D points See vtkPoints for details
	vtkSmartPointer<vtkActor> m_SphereActor;	// 
	vtkSmartPointer<vtkSplineWidget> m_SplineWidget;	// See SetSpline
	vtkSmartPointer<vtkRenderer> m_Renderer;	// See SetRenderer
	bool m_IsLocked;
};