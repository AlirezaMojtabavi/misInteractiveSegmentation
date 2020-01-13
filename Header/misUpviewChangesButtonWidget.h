#pragma once
#include "vtkBorderWidget.h"
#include "misUpviewChangesButtonRepresentation.h"

class misUpviewChangesButtonWidget: public vtkBorderWidget
{

public:
	// Description:
	// Instantiate this class.
	static misUpviewChangesButtonWidget *New();

	// Description:
	// Standard VTK class methods.
	vtkTypeRevisionMacro(misUpviewChangesButtonWidget,vtkBorderWidget);
	void PrintSelf(ostream& os, vtkIndent indent);

	// Description:
	// Specify an instance of vtkWidgetRepresentation used to represent this
	// widget in the scene. Note that the representation is a subclass of vtkProp
	// so it can be added to the renderer independent of the widget.
	void SetRepresentation(misUpviewChangesButtonRepresentation *r)
	{this->Superclass::SetWidgetRepresentation(reinterpret_cast<vtkWidgetRepresentation*>(r));}

	// Description:
	// Create the default widget representation if one is not set. 
	void CreateDefaultRepresentation();

protected:
	misUpviewChangesButtonWidget();
	~misUpviewChangesButtonWidget();

	// Description:
	// When selecting the interior of this widget, special operations occur 
	// (i.e., adding a camera view, deleting a path, animating a path). Thus
	// this methods overrides the super classes' method.
	virtual void SelectRegion(double eventPos[2]);

private:
	misUpviewChangesButtonWidget(const misUpviewChangesButtonWidget&);  //Not implemented
	void operator=(const misUpviewChangesButtonWidget&);  //Not implemented
};

