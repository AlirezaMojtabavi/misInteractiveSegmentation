// XFolderSize.h  Version 1.0 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XFOLDERSIZE_H
#define XFOLDERSIZE_H

class CXFolderSize
{
// Constructor
public:
	CXFolderSize() {};

// Attributes
public:
	BOOL GetFileSize64(LPCTSTR lpszPath, PLARGE_INTEGER lpFileSize);
	BOOL GetFolderSize(LPCTSTR lpszStartFolder, 
					   BOOL bRecurse, 
	   				   BOOL bQuickSize,
					   PLARGE_INTEGER lpFolderSize,
					   LPDWORD lpFolderCount = NULL,
					   LPDWORD lpFileCount = NULL);
};


#endif //XFOLDERSIZE_H
