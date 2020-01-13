#pragma  once

#include "misROI.h"
#include "misSimpleDataPackage.h"
#include "IWindows.h"
#include "misInteractorSTyleImageExtend.h"

class IMedicalImageViewer
{
public:
	virtual void Render() const = 0;
	virtual bool ProcessRequest(const itk::EventObject* event) = 0;
	virtual void SetWindow(const std::shared_ptr<Iwindows> pWindow) = 0;
	virtual void SetPackageData(const std::shared_ptr<misSimpleDataPackage> pPackage) = 0;
	virtual void SetTransform(const std::shared_ptr<vtkMatrix4x4> pTrans) = 0;
	virtual void SetROI(const misROI data) = 0;
	virtual void SetInteractorStyle(InteractionState interactionStyle) = 0;
};
