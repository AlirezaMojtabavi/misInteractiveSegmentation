#ifndef __misSeedSelectCallback__
#define __misSeedSelectCallback__
#include "misSeedSTRCT.h"
class misSegmentationView;
class misImageSegmentationSubSeq ;
class vtkSeedRepresentation;

class misSeedSelectCallback : public vtkCommand
{
private:

public:

	typedef itk::Image< float , 3 > ImageType;
	typedef ImageType::IndexType     SeedType;
	TypeOfSeed seedtype;
	vector<misSeedSTRCT>   m_FGSeedList;
	vector<misSeedSTRCT>   m_BGSeedList;
	misImageSegmentationSubSeq* m_ImageSubSeq;
	static misSeedSelectCallback  *New() 
	{ return new misSeedSelectCallback ; }
	virtual void Execute(vtkObject*, unsigned long, void*);
	misSeedSelectCallback () : m_SeedRepresentation(0) {}
	vtkSeedRepresentation *m_SeedRepresentation;
 
};

#endif