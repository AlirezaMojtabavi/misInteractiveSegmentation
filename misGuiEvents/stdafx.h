// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <memory>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <ObjIdl.h>
#include "targetver.h"

#include <GdiPlus.h>


#include "itkPoint.h"
#include "itkVector.h"

#include "tgt/matrix.h"
#include "tgt/vector.h"

#include "tinyxml/tinyxml.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
