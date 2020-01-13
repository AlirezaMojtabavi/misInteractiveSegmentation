#pragma once

// Needed property to add 3 axis to renderer
class  misAxisProperty
{
public:
	enum  GeoType
	{
		cylinder=0,line
	};


	misAxisProperty();
	misAxisProperty::GeoType GetGeoType() const { return m_GeoType; }
	void SetGeoType(misAxisProperty::GeoType val) { m_GeoType = val; }
	misAxisProperty(double xLenghth, double yLenghth, double zLength);
	float GetCylinderRadius() const { return m_CylinderRadius; }
	void SetCylinderRadius(float val) { m_CylinderRadius = val; }
	float GetConeRadius() const { return m_ConeRadius; }
	void SetConeRadius(float val) { m_ConeRadius = val; }
	float GetSpherRadius() const { return m_spherRadius; }
	void SetSpherRadius(float val) { m_spherRadius = val; }
	float GetScaleFactor() const { return m_ScaleFactor; }
	void SetScaleFactor(float val) { m_ScaleFactor = val; }
	float GetXLenght() const { return x_Lenght; }
	void SetXLenght(float val) { x_Lenght = val; }
	float GetYLenght() const { return y_Lenght; }
	void SetYLenght(float val) { y_Lenght = val; }
	float GetZLenght() const { return z_Lenght; }
	void SetZLenght(float val) { z_Lenght = val; }
private:
	
	GeoType  m_GeoType;

	float m_CylinderRadius;
	float m_ConeRadius;
	float m_spherRadius;
	float m_ScaleFactor;
	float x_Lenght;
	float y_Lenght;
	float z_Lenght;

};
