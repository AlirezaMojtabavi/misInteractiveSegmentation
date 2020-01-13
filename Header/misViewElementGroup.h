#pragma once

#include "..\misNavigationFourView\misViewingWindowElement.h"

//Hold an n*n element of misViewingWindowElement - all viewers in a group have the same direction, for example all have Axial and
// the same misPlaneEnum (image plane visibility) direction. all viewers in a group have a constant distance relative to next or 
// previous viewer in group, and only have square number of elements example, 1, 4, 9, 16 ...
// 
class misViewElementGroup : public Serializable
{
public:
	misViewElementGroup();
	misViewElementGroup(int rowcolomn, misViewerTypeDirection direction, 
		std::map<misPlaneEnum, bool> planeImageVisibility = CreateDefaultPlaneVisibilyMap() , double distance = 0);


	~misViewElementGroup(void);
	
	// For each misViewingWindowElement a view port (a rectangle in normalized coordinate (0, 0, 1, 1)) is calculated for example
	// if number of misViewingWindowElement is 16 the first misViewPort is : (0, 0, 0.25 , 0.25)
	misViewPort GetViewPort(int index) const;
	misViewerTypeDirection GetTypeOfViewer() const;
	std::map<misPlaneEnum, bool> GetPlaneVisibilityStatus() const;
	int GetNumberOfViewer() const;
	const misViewingWindowElement& GetViewer(int index) const;
	static std::map<misPlaneEnum, bool> CreateDefaultPlaneVisibilyMap();
	virtual void serialize(XmlSerializer& s) const override;
	virtual void deserialize(XmlDeserializer& s) override;
	tgt::vec2 GetPosition() const { return m_Position; }
	void SetPosition(tgt::vec2 val) { m_Position = val; }
	tgt::vec2 GetSize() const { return m_Size; }
	void SetSize(tgt::vec2 val) { m_Size = val; }

	bool IsUpdateByVirtualTip() const;
	void SetUpdateByVirtualTip(bool val);
	bool GetIsObliq() const { return m_IsObliq; }
	void SetIsObliq(bool val) { m_IsObliq = val; }
	bool GetShowToolExtension() const;
	void SetShowToolExtension(bool val);
private:
	void CreateChilds();

	tgt::vec2 m_Position;
	tgt::vec2 m_Size;

	int m_NumberOfViewers = 1;
	std::vector<misViewingWindowElement> m_Elements;
	misViewerTypeDirection   m_ViewerTypeDirection;
	double m_Distance = 1.0;
	std::map<misPlaneEnum, bool>  m_PlaneVisibility;
	bool m_UpdateByVirtualTip = true;
	bool m_IsObliq = false;
	bool m_ShowToolExtension = false;
};

