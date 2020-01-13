#pragma once

using namespace System;
using namespace System::Speech::Synthesis;

public ref class misTextToSpeech
{
private:
	SpeechSynthesizer^ m_TextReader;

public:
	misTextToSpeech(void);
	void ReadText(System::String^ text);
};
