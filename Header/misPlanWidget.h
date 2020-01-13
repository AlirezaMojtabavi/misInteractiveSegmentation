

#include "vtkInteractionWidgetsModule.h" // For export macro
#include "vtkAbstractWidget.h"
#include "IPlanWidgetRepresentation.h"

class vtkLineRepresentation;
class vtkHandleWidget;
#include "misStringTools.h"

class   misPlanWidget : public vtkAbstractWidget
{
public:
	/**
	 * Instantiate the object.
	 */
	static misPlanWidget *New();

	//@{
	/**
	 * Standard vtkObject methods
	 */
	vtkTypeMacro(misPlanWidget, vtkAbstractWidget);
	void PrintSelf(ostream& os, vtkIndent indent) override;
	void	SetLineWidgetUID(misUID uid);
	misUID	GetLineWidgetUID();

	void SetEnabled(int enabling) override;

	/**
	 * Specify an instance of vtkWidgetRepresentation used to represent this
	 * widget in the scene. Note that the representation is a subclass of vtkProp
	 * so it can be added to the renderer independent of the widget.
	 */
	void SetRepresentation(IPlanWidgetRepresentation *r)
	{
		auto rep = dynamic_cast<vtkWidgetRepresentation*>(r);
		this->Superclass::SetWidgetRepresentation(rep);
	}

	/**
	 * Return the representation as a vtkLineRepresentation.
	 */
	vtkWidgetRepresentation *GetLineRepresentation()
	{
		return reinterpret_cast<vtkWidgetRepresentation*>(this->WidgetRep);
	}

	/**
	 * Create the default widget representation if one is not set.
	 */
	void CreateDefaultRepresentation() override;

	/**
	 * Methods to change the whether the widget responds to interaction.
	 * Overridden to pass the state to component widgets.
	 */
	void SetProcessEvents(int) override;

protected:
	misPlanWidget();
	~misPlanWidget() override;

	// Manage the state of the widget
	int WidgetState;
	enum _WidgetState { Start = 0, Active };
	int CurrentHandle;

	// These methods handle events
	static void SelectAction(vtkAbstractWidget*);
	static void TranslateAction(vtkAbstractWidget*);
	static void ScaleAction(vtkAbstractWidget*);
	static void EndSelectAction(vtkAbstractWidget*);
	static void MoveAction(vtkAbstractWidget*);

	// The positioning handle widgets
	vtkHandleWidget *Point1Widget; //first end point
	vtkHandleWidget *Point2Widget; //second end point
	vtkHandleWidget *LineHandle; //used when selecting the line

	char ActiveKeyCode;
	vtkCallbackCommand *KeyEventCallbackCommand;
	static void ProcessKeyEvents(vtkObject *, unsigned long, void *, void *);

private:
	misPlanWidget(const misPlanWidget&) = delete;
	void operator=(const misPlanWidget&) = delete;
	misUID	m_LineWidgetUID;
};

 
