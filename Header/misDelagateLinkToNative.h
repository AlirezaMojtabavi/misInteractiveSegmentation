#pragma once

#include "misEventProxy.h"

using namespace System;
#pragma make_public(misEventProxy)

public ref class misDelagateLinkToNative
{
private:
	misEventProxy*  m_Proxy;

public:
	misDelagateLinkToNative(misEventProxy* proxy);
	void CaptureEvent(System::IntPtr event);
	void SetProxy(misEventProxy* val);
};
