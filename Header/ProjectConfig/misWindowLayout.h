#pragma once
#include "misenums.h"
#include "misobjectProperitiesEnums.h"
#include "misViewerTypeDirection.h"

class misWindowLayout : public Serializable
{
public:
	misWindowLayout();
	misWindowLayout(tgt::vec2 position , 	tgt::vec2 size, std::string typedirection);
	~misWindowLayout();

	virtual void serialize(XmlSerializer& s) const override;


	virtual void deserialize(XmlDeserializer& s) override;
	tgt::vec2 GetPosition() const { return m_Position; }
	void SetPosition(tgt::vec2 val) { m_Position = val; }
	tgt::vec2 GetSize() const { return m_Size; }
	void SetSize(tgt::vec2 val) { m_Size = val; }
	bool GetIs2D() const { return m_Is2D; }
	void SetIs2D(bool val) { m_Is2D = val; }
	std::string GetViewerTypeDirection() const;
	void SetViewerTypeDirection(std::string val);
	bool IsOblique() const;
	void SetIsOblique(bool val);
private:
	tgt::vec2 m_Position;
	tgt::vec2 m_Size;
	std::string m_ViewerTypeDirection;
	bool m_IsOblique = false;
	
	bool m_Is2D;

};

