#pragma once

class TestObserver : public itk::Command
{
public:
	TestObserver()
		: m_ReceivedEvent(false)
	{
	}

	virtual void Execute( Object *caller, const itk::EventObject & event )
	{
		m_ReceivedEvent = true;
		m_ReceivedEventNames.push_back(event.GetEventName());
	}

	virtual void Execute( const Object *caller, const itk::EventObject & event )
	{
		m_ReceivedEvent = true;
		m_ReceivedEventNames.push_back(event.GetEventName());
	}

	void Reset()
	{
		m_ReceivedEvent = false;
		m_ReceivedEventNames.clear();
	}

	bool hasReceivedEvent() const { return m_ReceivedEvent; }
	std::vector<std::string> GetReceivedEventNames() const { return m_ReceivedEventNames; }
private:
	bool m_ReceivedEvent;
	std::vector<std::string> m_ReceivedEventNames;
};
