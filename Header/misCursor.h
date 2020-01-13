#ifndef __misCursor_h
#define __misCursor_h

#include "AxesColors.h"
#include "Color.h"
#include "VisualizationGeneralTypes.h"

class ICornerProperties;

// 3d representation of axises 
class misCursor : public vtkPolyDataAlgorithm
{
public:

	std::vector < vtkSmartPointer<vtkActor>> GetActors();

	void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProperties);
	void UpdateWidgetPosition();
	virtual bool IsVisible(double object[3], double cameraPos[3]);

	// Sets the relative weight of the line used in drawing the cursor widget.
	void SetLineWidth(double width);
	void SetFocalPoint(double x[3]);
	void SetFocalPoint(double x, double y, double z);
	void SetColorsComposition(const parcast::AxesColors& colors);
	
	vtkGetVectorMacro(ModelBounds, double, 6);
	vtkGetVectorMacro(FocalPoint, double, 3);
	std::shared_ptr<ICornerProperties> m_CornerPropreties;
	virtual void Initialization() = 0;
	IMAGEORIENTATION m_WidgetOrientation;
	virtual void ModifyAxis() = 0;

	// 	virtual void ModifyBoundingBox() = 0;
	// 	virtual void ModifyTorus(int) = 0;

	virtual void SetModelBounds(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
	virtual void SetModelBounds(double bounds[6]);

	virtual vtkSmartPointer<vtkPolyData> GetFocus(void);

protected:
	misCursor();

	static void SetColorToActor(vtkActor* actor, const parcast::Color::NormRgbType& normRgb);
	static void SetColorToActors(vtkActor* actor1, vtkActor* actor2, const parcast::Color::NormRgbType& normRgb);

	void virtual UpdateCursorColor() = 0;

	virtual double GetDParam() { return this->DParam; }
	virtual void SetDParam(double d) { this->DParam = d; }

	// Used by subclasses to access the value set using SetLineWidth.
	double GetLineWidth() const;

	// Used by subclasses to access the value set using SetLineWidth.
	parcast::AxesColors GetColorComposition();

	vtkSmartPointer<vtkPolyData> Focus = vtkSmartPointer<vtkPolyData>::New();
	double ModelBounds[6];
	double FocalPoint[3];
	bool m_TorusVisibility;
	bool m_initial;
	double DParam;
	std::vector< vtkSmartPointer<vtkActor>> m_Actors;

private:
	const parcast::Color DefaultColorWhite = parcast::Color::FromRgb(255, 255, 255);
	double m_LineWidth = 1.0; 
	parcast::AxesColors m_ColorCompo = { DefaultColorWhite, DefaultColorWhite, DefaultColorWhite };
};

#endif


