#ifndef misCineInformation_H
#define misCineInformation_H

#include "misSeconderyNeededHeader.h"
#include "misDataProdecureEnum.h"

class  misCineInformation
{
public:
	misCineInformation();
	void SetPosition(double pos);
	int SetInterval() const;
	void SetInterval(int val);
	double  GetNextImageIndex(double speed);
	void SetCineInformation(double ImageExtent,misCineDirection cineDirection = forwardDirection);
	void ResetCineInformation();
	void SetCurrentImagePosZ(double val);
	bool ReachedTheEnd(void);
private :
	double m_CurrentImagePosZ;
	bool m_LoopActivation;
	misCineDirection m_Direction;
	float  m_ImageLEngthInOrientation;
	int m_interval;
	
};

#endif
