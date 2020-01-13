#pragma once

#include "misCommonHeader.h"

class MISCOMMONEXPORT misCopyFile
{
public:
	misCopyFile(void);
	~misCopyFile(void);
	bool	CopyDirectoryFileByFile( std::string source, std::string destination );
	void	RequestStop();	
	void	SetProgressbarValue(double val);
	void	ResetProgressbarValue();
	double	GetProgressbarValue();

private:
	bool	StopRequested();
	void	ResetRequestStop();	

	bool	m_CancelReadingFolders;
	double	m_ProgressbarValue;	//IMPORTANTNOTE: To access this value, it's set and get method must used.
};
