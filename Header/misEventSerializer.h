#pragma once

class  misGUIEvent;

class misEventSerializer:public  Serializable
{
private:
	std::string m_type;
	misGUIEvent*  m_element;
public:
	misEventSerializer(void);
	misEventSerializer(misGUIEvent* elemnt,std::string  type);
	~misEventSerializer(void);
	misGUIEvent* GetElement();
	void SetElement(misGUIEvent* elem);
	std::string GetType();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};
