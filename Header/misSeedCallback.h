#ifndef __MISSEEDCALLBACK__
#define __MISSEEDCALLBACK__


#include "misSeedSTRCT.h"

class misSeedViewer;

#define SeedAdded 1000

class misSeedCallback : public vtkCommand
{
private:

	misSeedViewer* m_Viewer;
public:

	misSeedViewer* GetViewer() const { return m_Viewer; }
	void SetViewer(misSeedViewer* val) { m_Viewer = val; }

	//store  real position index
	typedef itk::Image< float , 3 > ImageType;

	misLandmarkType seedtype;
	vector<misSeedSTRCT>   m_FGSeedList;
	vector<misSeedSTRCT>   m_BGSeedList;



	static misSeedCallback  *New() 
	{ return new misSeedCallback ; }
	virtual void Execute(vtkObject*, unsigned long, void*);
	misSeedCallback () : m_SeedRepresentation(0) {}
	vtkSeedRepresentation *m_SeedRepresentation;
	vtkSeedWidget* m_Widget;


};

#endif