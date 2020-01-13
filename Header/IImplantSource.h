
#pragma once
#include "BusinessEntities\Point.h"

// The misSimpleLineImplant class creates implant
class IImplantSource
{
public:
	virtual ~IImplantSource() = default;
	virtual void SetEntry(const parcast::PointD3& point) = 0;
	virtual parcast::PointD3 GetEntry() const  = 0;
	virtual void SetTarget(const parcast::PointD3& point) = 0;
	virtual parcast::PointD3 GetTarget() const = 0;
	virtual void SetRadius(double radius) = 0;
	virtual double GetRadius() const  = 0;
	virtual void SetTargetRadius(double radius) = 0;
	virtual vtkSmartPointer<vtkMapper> GetMapper() const  = 0;
	virtual void SetCurrentPoint(const parcast::PointD3& point) = 0;
	virtual void SetInterSectionPoint(const parcast::PointD3& point) = 0;
	virtual void SetNormalPlane(const parcast::VectorD3& vector) = 0;
};

