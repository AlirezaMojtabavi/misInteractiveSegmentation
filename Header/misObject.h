#ifndef MISOBJECT_H_HEADER_INCLUDED_B843A19F
#define MISOBJECT_H_HEADER_INCLUDED_B843A19F
#pragma once

#include "misEvent.h"
#include "misLibraryMacroes.h"
#include "misLogger.h"
#include "misMacros.h"
#include "misTypes.h"

// The base for nearly all MIS classes. It builds over the itk::Object base and adds logging functionality in a per-object fashion.
// The very much older version of misObject (which is now obsolete) is still available, but has been renamed to misOldObject.
// Older classes deriving misObject have all been updated to derive misOldObject. In time, old classes should be migrated to 
// derive misObject instead.
class MISLIBRARYEXPORT misObject : public itk::Object
{
	misObjectMacro(misObject, itk::Object);

public:
	typedef itk::SmartPointer<misLogger> LoggerType;
	virtual ~misObject();
	// Gets/sets the logger object used by this misObject. Default value is NULL.
	misPrivateVariableWithPublicAccessorsMacro(LoggerType, m_Logger, Logger)

protected:
	misObject();
};

class MISLIBRARYEXPORT misOldObject : public itk::Object
{
public:
	typedef misLogger LoggerType;
	mutable LoggerType*	m_Logger;
	typedef misOldObject  Self;
	virtual ::itk::LightObject::Pointer CreateAnother(void) const;
	virtual ~misOldObject();
	misOldObject();
	misOldObject(const misOldObject &);
	misOldObject& operator =(const misOldObject &);
	misLogger*						GetLogger() const;
	virtual void SetLogger(LoggerType* logger);
	static Pointer New(void);
};

#endif /* MISOBJECT_H_HEADER_INCLUDED_B843A19F */