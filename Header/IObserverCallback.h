#pragma once
class IObserverCallback
{
public:
	virtual ~IObserverCallback() = default;
 	virtual void CallBack(vtkObject* caller, unsigned long eventId, void* callData) = 0;

};