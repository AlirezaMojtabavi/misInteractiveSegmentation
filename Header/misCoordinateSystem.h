#pragma once

#include "ICoordinateSystem.h"
#include "misLibraryMacroes.h"

// The misCoordinateSystem class is the default implementation of the supposedly abstract ICoordinateSystem. No particular behaviour
// is currently attached to this implementation.
class MISLIBRARYEXPORT misCoordinateSystem : public ICoordinateSystem
{
public:
	misCoordinateSystem(const std::string& uid);
	~misCoordinateSystem(void);

	 std::string GetUID() const override;


	 virtual void SetUID(const std::string& id) override;

private:
	std::string m_UID;
};