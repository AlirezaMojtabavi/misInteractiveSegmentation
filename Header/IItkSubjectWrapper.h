#pragma once
class IItkSubjectWrapper
{
public:
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual ~IItkSubjectWrapper()
	{}
};
