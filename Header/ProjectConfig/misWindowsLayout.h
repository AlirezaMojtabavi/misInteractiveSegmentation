#pragma once
#include "misWindowLayout.h"
class misWindowsLayout : public Serializable
{
public:
	misWindowsLayout();
	~misWindowsLayout();
	void AddWindow(misWindowLayout window);

	virtual void serialize(XmlSerializer& s) const override;


	virtual void deserialize(XmlDeserializer& s) override;

	std::vector<misWindowLayout> GetWindows() const { return m_Windows; }
	void SetWindows(std::vector<misWindowLayout> val) { m_Windows = val; }
private:
	std::vector<misWindowLayout> m_Windows;
};

