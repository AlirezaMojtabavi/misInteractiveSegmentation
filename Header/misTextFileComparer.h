#pragma once

#include "ITextFileComparer.h"

class misTextFileComparer : ITextFileComparer
{
public:
	misTextFileComparer();
	~misTextFileComparer();

	virtual void SetSourceFilePath( const std::string& path );
	virtual void SetDestinationFilePath( const std::string& path );
	virtual Differences GetAllDifferences() const;
	virtual bool AreIdentical() const;
	virtual void SetWhitespaceTrimming( bool enabled );

	// Reads the contents of the text file specified by its path and stores the sequence of lines in the file in a vector of 
	// strings with each line an element of the vector.
	std::vector<std::string> ReadFileToLines(const std::string& path) const;

private:
	// Used to describe lines of text as a vector of strings
	typedef std::vector< std::string > TextLines; 

	// Used to describe how two different sets of lines can be matched. The MatchSet is a list of pairs each of which represents
	// a single match associating a line number in source line set with a line number in destination line set.
	typedef std::vector< std::pair<int, int> > MatchSet; 

	// This was supposed to be used in the iterative implementation of MatchLines which was left half done.
	struct RecursionParams
	{
		RecursionParams(int sourceStartLine, int destStartLine, int recursionLevel) 
			: SourceStartLine(sourceStartLine), DestinationStartLine(destStartLine), RecursionId(recursionLevel), 
			IsProcessed(false)
		{ }
		int SourceStartLine;
		int DestinationStartLine;
		bool IsProcessed;
		int RecursionId;
		MatchSet ResMatchSet;
	};

	// Matches two different sets of lines by finding the most number of matching lines between the two line sets. It starts 
	// matching of line from the specified starting line in both source and destination line sets. 
	// It performs the matching recursively such that it tries to match lines from the specified starting lines in source and
	// destination line sets. If a differing line is encountered, it recalls itself twice, each time incrementing either source or
	// destination start line and discarding the one yielding less matching number of lines. It then appends the secondary matches
	// to the initial direct matches and stores and retrieves the result in a MatchSet.
	MatchSet MatchLines(const TextLines& srcLines, const TextLines& destLines, int srcStartLine, int destStartLine) const;

	// This was supposed to be an iterative implementation of the recursive overload, but was left half done.
	MatchSet MatchLines(const TextLines& srcLines, const TextLines& destLines) const;

	// Trims all the leading and trailing whitespace characters from the specified string.
	void TrimWhiteSpace(std::string& str) const;
	
	// Trims all the leading and trailing whitespace characters from all the strings within the specified set. It also removes 
	// empty lines afterwards.
	void TrimWhiteSpaceOnLines( std::vector<std::string>& lines ) const;


	std::string m_SourceFilePath;
	std::string m_DestinationFilePath;
	bool m_TrimWhiteSpace;
};