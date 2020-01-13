#pragma once


class misSyncronViwer;
class misPointWidgetObserver:public vtkCommand
{
public:

	static misPointWidgetObserver* New()
	{

		return  new misPointWidgetObserver;
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void*);
	void SetNavigator(misSyncronViwer* pNav){this->m_pNavigator = pNav;};

private:
	misSyncronViwer* m_pNavigator;

};