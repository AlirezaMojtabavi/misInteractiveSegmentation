#include "misrepresentation.h"
#include "misSeconderyNeededHeader.h"
#include "misTrackingManagerExports.h"

class  misAuroraTrackingVolumeRep : public misRepresentation
{
 
private:
	void Init();
	void InitPlanesCoordinateds();

	misItkListPointType m_PlanesCoordinateds;

public:
	misAuroraTrackingVolumeRep(std::string name);
	~misAuroraTrackingVolumeRep(void);
};

