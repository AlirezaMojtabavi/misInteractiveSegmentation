#pragma once

#include "ITextFileWriter.h"
#include "IToolCorrelationLogRecorder.h"

class misToolCorrelationLogRecorder : public IToolCorrelationLogRecorder
{
public:
	misToolCorrelationLogRecorder(const std::string& logFilePath, std::shared_ptr<ITextFileWriter> textFileWriter);

	virtual void RecordLog( double timeInSeconds, const std::string& sourceTool, const std::string& destinationTool, 
		std::shared_ptr<const ITransform> correlationTransform ) override;

private:
	std::ostream& WriteTransformToStream(std::ostream& outStr, const ITransform& transform);

	const std::string m_LogFilePath;
	const std::shared_ptr<ITextFileWriter> m_TextFileWriter;
};

