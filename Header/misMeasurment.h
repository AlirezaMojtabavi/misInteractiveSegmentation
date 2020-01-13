#pragma  once

#include "misDistanceRepresentation2D.h"
#include "misDistanceWidget.h"
#include "misInteractorSTyleImageExtend.h"
#include "misObject.h"
 
class misMeasurment: public misOldObject
{
public:
	typedef misMeasurment				Self;  
	typedef ::itk::SmartPointer< Self >			Pointer; 
	static Pointer New(void); 

	virtual void SetMeasurmentWidget(); 
	virtual void ResetMeasurmentWidget();
	void SetInteractionStyleExtend(misInteractorSTyleImageExtend*, IMAGEORIENTATION orientation );
	void SetRenderWindowInteractor(vtkRenderWindowInteractor* );
	void SetControlToWidget();

protected:
	misMeasurment();
	~misMeasurment();

	 vtkSmartPointer<vtkPointHandleRepresentation2D> m_Handle;
	 vtkSmartPointer<misDistanceRepresentation2D> m_Representation;
	 vtkSmartPointer<misDistanceWidget> m_widget;
	 vtkSmartPointer<misInteractorSTyleImageExtend>	m_InteractionStyleExtend;
	 vtkSmartPointer <vtkRenderWindowInteractor> m_RenderWindowInteractor;

};


