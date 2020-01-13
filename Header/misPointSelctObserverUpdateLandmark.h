
class misGroupViewLandMark;
class    misPointSelctObserverUpdateLandmark :	public vtkCommand
{
private:
	misImageViewer::Pointer  m_pViewer;
	misLandmarkType   m_SeedMode;
	LandmarkStatus   m_seedtype;

public:

	static misPointSelctObserverUpdateLandmark* New()
	{return new misPointSelctObserverUpdateLandmark;}

	misGroupViewLandMark* m_pGroupView;

	void SetViewer(misImageViewer::Pointer val);
	void SetLandmarkType(misLandmarkType typr);
	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	misPointSelctObserverUpdateLandmark(void);
	~misPointSelctObserverUpdateLandmark(void);
};