#pragma once

#include "misCommonHeader.h"

class MISCOMMONEXPORT misIOCheckUtilities
{
public:
	misIOCheckUtilities(void);
	~misIOCheckUtilities(void);

	static void  PrepareStringToBeAFileName(std::string& path);
	static bool        CreateFolder(std::string folderpath);
};
