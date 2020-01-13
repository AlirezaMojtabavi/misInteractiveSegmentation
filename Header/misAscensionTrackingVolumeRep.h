
#include "misrepresentation.h"
#include "misSeconderyNeededHeader.h"
#include "misTrackingManagerExports.h"

class  misAscensionTrackingVolumeRep : public misRepresentation
{
public:
	igstkStandardClassBasicTraitsMacro(misAscensionTrackingVolumeRep, misRepresentation);
	static Pointer New(std::string name);
	misAscensionTrackingVolumeRep(std::string name);
	~misAscensionTrackingVolumeRep(void);
private:
	void Init();
	void InitPlanesCoordinateds();
 
	misItkListPointType m_PlanesCoordinateds;

public:

};


