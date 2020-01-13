#pragma  once

class mis3DModelObjectOpacityPropertiesStrct
{
public:


	void Reset();;

	mis3DModelObjectOpacityPropertiesStrct(void);

	void operator =(mis3DModelObjectOpacityPropertiesStrct right);

	bool operator==(const mis3DModelObjectOpacityPropertiesStrct &right) const;

	bool operator != (mis3DModelObjectOpacityPropertiesStrct right) const;

	void SetAllInvisible();

	void SetAllVisible();

	double GetOpacityIn2DScene() const;

	void SetOpacityIn2DScene(double val);

	bool GetVisibilityIn2DScene() const;
	bool GetVisibilityIn3DScene() const;
	void SetVisibilityIn3DScene(bool val);

	bool   visibilityIn2DScene;
	double OpacityIn3DScene;

private:
	bool m_VisibilityIn3DScene;
	double m_OpacityIn2DScene;
};

typedef std::string misUID;
typedef std::map<misUID , mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityMap;
typedef std::pair<misUID , mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityPair;