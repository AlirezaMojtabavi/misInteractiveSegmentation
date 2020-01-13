#pragma once
#include "ISubSequenceUIAdapter.h"
class misSubSequenceUIAdapter : public ISubSequenceUIAdapter
{
public:
	misSubSequenceUIAdapter(itk::Object::Pointer parent);

	virtual void WriteMessageBox(itk::LoggerBase::PriorityLevelType level, std::string const& message) override;

private:
	itk::LoggerBase::PriorityLevelType ToEnum(std::string enumstring);

	itk::Object::Pointer m_ParentObject;
};
