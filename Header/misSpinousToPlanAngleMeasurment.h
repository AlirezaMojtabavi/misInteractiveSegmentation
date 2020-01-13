#pragma once
#include "ISpinousToPlanAngleMeasurment.h"
class misSpinousToPlanAngleMeasurment : public ISpinousToPlanAngleMeasurment
{
public:

	virtual void SetSpinousStart(const parcast::Point<double, 3>& point) override;
	virtual void SetSpinousEnd(const parcast::Point<double, 3>& point) override;
	virtual void SetPlan(const parcast::Point<double, 3>& start, const parcast::Point<double, 3>& end) override;
	virtual void SetRenderWindowInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;
	virtual void DeleteWidget() override;
	void SetEnable(int) override;

private:
	double GetAngle() const ;
	void UpdateAngleCaption(const double x1[3], const double x2[3]) const;
	class vtkLWCallback : public vtkCommand
	{
	public:
		static vtkLWCallback *New()
		{
			return new vtkLWCallback;
		}
		void Execute(vtkObject *caller, unsigned long, void*) override
		{
			vtkLineWidget2 *lineWidget = reinterpret_cast<vtkLineWidget2*>(caller);
			auto startPoint = lineWidget->GetLineRepresentation()->GetPoint1WorldPosition();
			auto endPoint = lineWidget->GetLineRepresentation()->GetPoint2WorldPosition();
			m_Measurement->SetSpinousStart(parcast::Point<double, 3>(startPoint));
			m_Measurement->SetSpinousEnd(parcast::Point<double, 3>(endPoint));
		}
		void SetMeasurement(misSpinousToPlanAngleMeasurment* val) { m_Measurement = val; }
	private:
		misSpinousToPlanAngleMeasurment* m_Measurement;
	};

	parcast::Point<double, 3> m_PlanStart; 
	parcast::Point<double, 3> m_PlanEnd;
	parcast::Point<double, 3> m_WidgetStart;
	parcast::Point<double, 3> m_WidgetEnd;
	vtkSmartPointer<vtkRenderWindowInteractor> m_Interactor;
	vtkSmartPointer<vtkLineRepresentation> m_Representation;
	vtkSmartPointer<vtkLineWidget2> m_LineWidget;
	vtkSmartPointer<vtkCaptionActor2D> m_LineLenCaption;;
	

};

