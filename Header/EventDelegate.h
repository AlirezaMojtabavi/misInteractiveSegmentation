#pragma once

#include "misGuiEvent.h"

using namespace System;
#pragma   make_public(misGUIEvent)
namespace WrapperGUIBase {
	public delegate void ExternalEventDelegate(System::IntPtr event);
}