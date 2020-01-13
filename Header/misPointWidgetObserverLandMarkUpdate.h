class misGroupViewLandMark;
class misPointWidgetObserverLandMarkUpdate:public vtkCommand
{
private:
	misLandmarkType   m_SeedMode;

public:

	static misPointWidgetObserverLandMarkUpdate* New()
	{

		return  new misPointWidgetObserverLandMarkUpdate;
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void*);
	void SetNavigator(misGroupViewLandMark* pGroupView);
	void SetLandmarkType(misLandmarkType typr);


private:
	misGroupViewLandMark* m_pGroupView;

};
