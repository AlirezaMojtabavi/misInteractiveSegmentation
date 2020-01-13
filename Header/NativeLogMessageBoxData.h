#pragma once

typedef enum
{
	MUSTFLUSH=0,
	FATAL,
	CRITICAL,
	WARNING,
	INFO,
	DEBUGLOGGING,
	NOTSET
} misPriorityLevelType;

struct NativeLogMessageBoxData
{
	std::string message;
	misPriorityLevelType  level;
};