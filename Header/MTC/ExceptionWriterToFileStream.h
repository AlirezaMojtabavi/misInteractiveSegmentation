#pragma once

class ExceptionWriterToFileStream
{
	std::ofstream * m_Fout;
public:
	ExceptionWriterToFileStream(void);
	~ExceptionWriterToFileStream(void);
};

