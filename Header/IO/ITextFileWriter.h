#pragma once

// The ITextFileWriter class provides an abstract interface for opening text files and writing data to it. Principal data type
// that does not require specific formatting before writing is std::string.
class ITextFileWriter
{
public:
	enum FileMode 
	{
		// Opening a file that already exists in Append mode does not erase existing file contents and appends to it. If the file
		// does not exist, it will be created.
		Append,	
	};

	// Open the file in either Append or Truncate mode.
	virtual void Open(const std::string& filePath, FileMode mode) = 0;

	// Writes the specified piece of data to the currently open file.
	virtual void Write(const std::string& data) = 0;

	// Closes the file handle flushing any underlying buffers.
	virtual void Close() = 0;

	// Gets whether a file has been opened
	virtual bool IsOpen() const = 0;

	virtual ~ITextFileWriter() { };
};