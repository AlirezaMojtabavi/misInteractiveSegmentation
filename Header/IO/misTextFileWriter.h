#pragma once

#include "ITextFileWriter.h"

class misTextFileWriter : public ITextFileWriter
{
public:
	virtual void Open( const std::string& filePath, FileMode mode ) override;
	virtual void Write( const std::string& data ) override;
	virtual void Close() override;
	virtual bool IsOpen() const override;

private:
	std::ofstream m_FileStream;
};

