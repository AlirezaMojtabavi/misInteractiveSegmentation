#pragma once
class ISubSequenceUIAdapter
{
public:
	virtual void WriteMessageBox(itk::LoggerBase::PriorityLevelType level, std::string const& message) = 0;

	~ISubSequenceUIAdapter()
	{

	}
};
