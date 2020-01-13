/*
 *  
 *  $Id: globals.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 */
#pragma once

#if 0
	#if defined (_GINKGO_DEBUG)

		#include <iostream>
		#if defined(_WINDOWS)
		#include <windows.h>
		#endif
		
		#define GDEBUG(expr) std::cout << "D: " << expr << "   @ " << __FILE__ << ":" << __LINE__ << std::endl;

	#else // !defined (_GINKGO_DEBUG)
		 #define GDEBUG(expr) /* nada */
	#endif

	#if defined (_GINKGO_TRACE)
		 #define GTRACE(expr) std::cout << "T: " << expr << "   @ " << __FILE__ << ":" << __LINE__ << std::endl;

	#else // !defined (_GINKGO_DEBUG)
		 #define GTRACE(expr) /* nada */
	#endif
#else
	#define GTRACE(expr) /* nada */
#endif

///#if defined(__WXGTK__) || defined(__WXMAC__) || defined(__WXMSW__)

//#if defined (_WIN32)
	#define TOPATH(stringwx) (stringwx.To8BitData()==NULL)?"":stringwx.To8BitData()
	#define FROMPATH(stringstd) wxString::From8BitData(stringstd.c_str())
//#else
//	#define TOPATH(stringwx) stringwx.ToUTF8()
//	#define FROMPATH(stringstd) wxString::FromUTF8(stringstd.c_str())
//#endif

#ifndef AUI_NAMESPACE
//#define AUI_NAMESPACE TEST::
#endif

#ifndef AUI_NAMESPACE
#define AUI_NAMESPACE
#define GINKGO_AUI_DECLARE(clase) class clase;
#define AUI_USE_NAMESPACE()
#else
#define GINKGO_AUI_DECLARE(clase) namespace AUI_NAMESPACE { class clase; }
#define AUI_USE_NAMESPACE() using namespace AUI_NAMESPACE;
#endif

//#endif
