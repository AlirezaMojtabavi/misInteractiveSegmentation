#pragma once

#include "misEventProxy.h"
#include "misGuiProxy.h"

using  namespace  System;
#pragma make_public(misEventProxy)

public ref class misGuiDispathcer
{
private:
	misEventProxy* m_Core;
public:

	misGuiDispathcer( misEventProxy* pCore );
	void CaptureEvent(System::IntPtr event);
};
