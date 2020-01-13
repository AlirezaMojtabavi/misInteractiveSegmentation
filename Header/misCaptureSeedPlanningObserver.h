#pragma  once

class misBiopsyPlanningSubSequence;

class  misCaptureSeedPlanningObserver :public itk::Command
{
public:
	typedef misCaptureSeedPlanningObserver Self;
	typedef itk::SmartPointer<Self> Pointer;
	itkNewMacro(Self);

	misBiopsyPlanningSubSequence* m_planS;

	virtual void Execute(const itk::Object *caller, const itk::EventObject & event)
	{
	}
	virtual void Execute(itk::Object *caller, const itk::EventObject & event);

private:
	misCaptureSeedPlanningObserver() {}
	~misCaptureSeedPlanningObserver() {}

};

