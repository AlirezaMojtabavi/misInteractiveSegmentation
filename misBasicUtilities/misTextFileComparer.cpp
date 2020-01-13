#include "StdAfx.h"
#include "misTextFileComparer.h"

misTextFileComparer::misTextFileComparer(void)
	: m_TrimWhiteSpace(false)
{
}

misTextFileComparer::~misTextFileComparer(void)
{
}

void misTextFileComparer::SetSourceFilePath( const std::string& path )
{
	m_SourceFilePath = path;
}

void misTextFileComparer::SetDestinationFilePath( const std::string& path )
{
	m_DestinationFilePath = path;
}

ITextFileComparer::Differences misTextFileComparer::GetAllDifferences() const
{
	auto sourceLines = ReadFileToLines(m_SourceFilePath);
	auto destinationLines = ReadFileToLines(m_DestinationFilePath);
	if (m_TrimWhiteSpace)
	{
		TrimWhiteSpaceOnLines(sourceLines);
		TrimWhiteSpaceOnLines(destinationLines);
	}
	auto lineMatches = MatchLines(sourceLines, destinationLines);
	Differences diffList;
	int prevSourceLine = 0, prevDestLine = 0;
	for (auto matchItr = lineMatches.cbegin(); matchItr != lineMatches.cend(); ++matchItr)
	{
		if (matchItr->first - prevSourceLine > 1 || matchItr->second - prevDestLine > 1)
		{
			DifferenceInstance diff;
			// Each number is added to one to convert zero-based line numbers to one-based.
			diff.SourceFirstLineNumber = prevSourceLine + 2;
			diff.SourceLastLineNumber = matchItr->first + 1;
			diff.DestinationFirstLineNumber = prevSourceLine + 2;
			diff.SourceLastLineNumber = matchItr->first + 1;
			std::ostringstream sourceContents, destinationContents;
			for (int i = diff.SourceFirstLineNumber - 1; i < diff.SourceLastLineNumber; ++i)
				sourceContents << sourceLines[i] << std::endl;
			for (int i = diff.DestinationFirstLineNumber - 1; i < diff.DestinationLastLineNumber; ++i)
				destinationContents << destinationLines[i] << std::endl;
			diff.SourceContents = sourceContents.str();
			diff.DestinationContents = destinationContents.str();
			if (m_TrimWhiteSpace)
			{
				TrimWhiteSpace(diff.DestinationContents);
				TrimWhiteSpace(diff.SourceContents);
			}
			if (diff.SourceContents != diff.DestinationContents)
				diffList.push_back(diff);
		}
		prevSourceLine = matchItr->first;
		prevDestLine = matchItr->second;
	}
	return diffList;
}

std::vector<std::string> misTextFileComparer::ReadFileToLines( const std::string& path ) const
{
	std::ifstream file(path);
	std::vector<std::string> lines;
	while (file.good())
	{
		std::string line;
		std::getline(file, line);
		lines.push_back(line);
	}
	return lines;
}

misTextFileComparer::MatchSet misTextFileComparer::MatchLines(
	const TextLines& srcLines, const TextLines& destLines, int srcStartLine, int destStartLine) const
{
	MatchSet matchSet;
	for (int i = srcStartLine, j = destStartLine; i < srcLines.size() && j < destLines.size(); ++i, ++j)
	{
		if (srcLines[i] != destLines[j])
		{
			auto extraLineInSourceMatch = MatchLines(srcLines, destLines, i + 1, j);
			auto extraLineInDestinationMatch = MatchLines(srcLines, destLines, i, j + 1);
			if (extraLineInSourceMatch.size() < extraLineInDestinationMatch.size())
				matchSet.insert(matchSet.end(), extraLineInSourceMatch.cbegin(), extraLineInSourceMatch.cend());
			else
				matchSet.insert(matchSet.end(), extraLineInDestinationMatch.cbegin(), extraLineInDestinationMatch.cend());
			return matchSet;
		}
		matchSet.push_back(std::make_pair(i, j));
	}
	return matchSet;
}

misTextFileComparer::MatchSet misTextFileComparer::MatchLines( const TextLines& srcLines, const TextLines& destLines ) const
{
	throw std::exception("Implementation not completed!");
	std::vector<RecursionParams> recursionStack;
	recursionStack.emplace_back(RecursionParams(0, 0, 0));
	while (recursionStack.size() > 1)
	{
		auto& recNodeChild1 = recursionStack.back();
		auto childRecId = recNodeChild1.RecursionId;
		auto recNodeChild2RItr = std::find_if(recursionStack.rend() + 2, recursionStack.rbegin(), 
			[&childRecId](const RecursionParams& recNode) -> bool { return recNode.RecursionId == childRecId; } );
		auto recNodeParentRItr = std::find_if(recNodeChild2RItr + 1, recursionStack.rbegin(), 
			[&childRecId](const RecursionParams& recNode) -> bool { return recNode.RecursionId == childRecId - 1; } );
		auto& recNodeChild2 = *recNodeChild2RItr, recNodeParent = *recNodeParentRItr;

		if (recNodeChild1.IsProcessed && recNodeChild2.IsProcessed)
		{
			auto& secondMatchSet = recNodeChild1.ResMatchSet, firstMatchSet = recNodeChild2.ResMatchSet, 
				matchSet = recNodeParent.ResMatchSet;
			if (firstMatchSet.size() < secondMatchSet.size())
				matchSet.insert(matchSet.end(), secondMatchSet.cbegin(), secondMatchSet.cend());
			else
				matchSet.insert(matchSet.end(), firstMatchSet.cbegin(), firstMatchSet.cend());
			recNodeParent.IsProcessed = true;
		}
		else
		{
			for (int i = recNodeChild1.SourceStartLine, j = recNodeChild1.DestinationStartLine; i < srcLines.size() && j < destLines.size(); ++i, ++j)
			{
				if (srcLines[i] != destLines[j])
				{
					recursionStack.emplace_back(RecursionParams(i + 1, j, recNodeChild1.RecursionId + 1));
					recursionStack.emplace_back(RecursionParams(i, j + 1, recNodeChild1.RecursionId + 1));
					break;
				}
				recNodeChild1.ResMatchSet.push_back(std::make_pair(i, j));
			}
			recNodeChild1.IsProcessed = true;
		}
		auto extraLineInDestMatch = recursionStack.back().ResMatchSet;
		recursionStack.pop_back();
		auto extraLineInSrcMatch = recursionStack.back().ResMatchSet;
		recursionStack.pop_back();
		auto& matchSet = recursionStack.back().ResMatchSet;
		if (extraLineInSrcMatch.size() < extraLineInDestMatch.size())
			matchSet.insert(matchSet.end(), extraLineInDestMatch.cbegin(), extraLineInDestMatch.cend());
		else
			matchSet.insert(matchSet.end(), extraLineInSrcMatch.cbegin(), extraLineInSrcMatch.cend());
	}
	return recursionStack.back().ResMatchSet;
}

void misTextFileComparer::TrimWhiteSpace( std::string& str ) const
{
	auto first = std::find_if(str.cbegin(), str.cend(), [] (char ch) -> bool { return !std::isspace(ch); } );
	str.erase(str.begin(), first);
	auto last = std::find_if(str.crbegin(), str.crend(), [] (char ch) -> bool { return !std::isspace(ch); } ).base();
	str.erase(last, str.end());
}

void misTextFileComparer::TrimWhiteSpaceOnLines( std::vector<std::string>& lines ) const
{
	for (auto lineItr = lines.begin(); lineItr != lines.end(); ++lineItr)
		TrimWhiteSpace(*lineItr);
	auto newEnd = std::remove_if( lines.begin(), lines.end(), [](const std::string& line) { return line.empty(); } );
	lines.resize(newEnd - lines.begin());
}

bool misTextFileComparer::AreIdentical() const
{
	auto sourceLines = ReadFileToLines(m_SourceFilePath);
	auto destinationLines = ReadFileToLines(m_DestinationFilePath);

	if (m_TrimWhiteSpace)
	{
		TrimWhiteSpaceOnLines(sourceLines);
		TrimWhiteSpaceOnLines(destinationLines);
	}

	if (sourceLines.size() != destinationLines.size())
		return false;

	for (int i = 0; i < sourceLines.size(); ++i)
	{
		if (sourceLines[i] != destinationLines[i])
			return false;
	}

	return true;
}

void misTextFileComparer::SetWhitespaceTrimming( bool enabled )
{
	m_TrimWhiteSpace = enabled;
}
