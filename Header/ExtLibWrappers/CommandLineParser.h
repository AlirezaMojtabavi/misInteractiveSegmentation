#pragma once

class CommandLineParser
{

public:
struct CommandLineArgs
{
	bool Help = false;
	boost::optional<bool> ShowSplash;
	boost::optional<bool> ShowConsole;
	boost::optional<std::string> TrackerType;
};
	CommandLineParser(int argc, char* argv[]);
	CommandLineArgs Get();
	~CommandLineParser();
private:
	CommandLineArgs m_Args;

};

