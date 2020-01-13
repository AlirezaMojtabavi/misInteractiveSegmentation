#pragma once

class misGeoActor : public vtkOpenGLActor
{
protected 	:
	bool  m_DisbaleDepthDest;
		misGeoActor(void);
public:

	~misGeoActor(void);
	static misGeoActor* New();

	bool GetDisbaleDepthDest() const;
	void SetDisbaleDepthDest(bool val);
};
