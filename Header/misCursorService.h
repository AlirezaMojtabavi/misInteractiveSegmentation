#pragma once

#include "AxesColors.h"
#include "ICursorService.h"

class ICornerProperties;
class misColorPointWidget;

class misCursorService  : public ICursorService
{
public:
	misCursorService();
	~misCursorService();


	void SetWidgetInteractor(vtkRenderWindowInteractor* pInteractor);
	void SetRenderer(vtkRenderer* renderer);
	void SetImageOrientation(IMAGEORIENTATION imgOrintation);

	// Sets the relative weight of the line used in drawing the cursor widget.
	void SetWidgetLineWeight(double weight);

	void SetWidgetType(misCursorType widgetType);
	void SetWidgetBounds(double* pBounds);

	void ApplyWidget(vtkProp3D* actor);
	void CreateWidget(double pickingTolerance) override;

	void EnableWidget();
	void DisableWidget();

	void ReleaseWidget();

	void ChangeWidgetType(misCursorType cursorType);
	void AddObserver(vtkCommand* pWdgObserver);

	void Set3DInteractionCapturedFlag(bool val);

	void UpdateWidgetPosition();

	void SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProperties);
	void SetAxesColors(const parcast::AxesColors& colors);

	/*	void SetProcessEventFlag(bool val);*/
private:
	vtkSmartPointer<misColorPointWidget> m_ColorPointWidget;
	vtkSmartPointer<vtkRenderWindowInteractor>	m_WidgetInteractor;
	vtkSmartPointer<vtkRenderer> m_CurrentRenderer; 
	IMAGEORIENTATION m_ImageOrientation;
	misCursorType m_WidgetType;
	double m_Bounds[6];
	double m_WidgetLineWidth;	// See SetWidgetLineWeight()
	parcast::AxesColors m_AxesColors;
};
