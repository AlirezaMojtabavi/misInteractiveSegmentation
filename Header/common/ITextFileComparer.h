#pragma once

// The ITextFileComparer is an abstract interface to classes that allow comparison of two text files. A source and a destination
// file are specified and then the differences are retrieved as a list of difference instances.
class ITextFileComparer
{
public:
	// The DifferenceInstance struct defines a single occurrence of difference encountered during the comparison of two files.
	// The struct indicates two blocks of text from each of the source and destination files. Each block within each of the files
	// is identified by a starting and ending line number. The contents of the difference block within each of the files is
	// also kept in this structure. The first line in each file is numbered 1 as usual.
	struct DifferenceInstance
	{
		// The line number, within the source file, marking the start of the difference block
		int SourceFirstLineNumber;

		// The line number, within the source file, marking the end of the difference block
		int SourceLastLineNumber;

		// The contents of the block according to the source file version
		std::string SourceContents;
		
		// The line number, within the destination file, marking the start of the difference block
		int DestinationFirstLineNumber;

		// The line number, within the destination file, marking the end of the difference block
		int DestinationLastLineNumber;

		// The contents of the block according to the destination file version
		std::string DestinationContents;
	};

	typedef std::vector<DifferenceInstance> Differences;

	// Set the file name and complete or relative path to the source and destination files.
	virtual void SetSourceFilePath(const std::string& path) = 0;
	virtual void SetDestinationFilePath(const std::string& path) = 0;
	
	// Performs the comparison if necessary and gets the list of encountered differences between the two files.
	virtual Differences GetAllDifferences() const = 0;

	// Checks whether the specified source and destination text files have the same text. This should be equivalent to 
	// GetAllDifferences().empty().
	virtual bool AreIdentical() const = 0;

	// Sets whether whitespace trimming should be done on each line before performing the line by line comparison.
	virtual void SetWhitespaceTrimming(bool enabled) = 0;

	virtual ~ITextFileComparer(void) { }
};

