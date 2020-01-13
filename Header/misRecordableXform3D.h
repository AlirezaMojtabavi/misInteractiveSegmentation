#pragma once

#include "IRecordableData.h"


class misRecordableXform3D : public IRecordableData
{
public:
	// Note: Xform3D copy constructor MUST NOT be called.
	misRecordableXform3D(Xform3D* xformData);

private:
	virtual std::ostream& WriteToStream( std::ostream& os ) const;

	Xform3D *m_XformData;
};

