#include "IToolShapeBuilder.h"
#include "misToolProperties.h"
#include "misEnums.h"
#include "vtkTransformPolyDataFilter.h"

// build a tool representation data represent a tracker tool  in rendering
class misToolShapeBuilder : public IToolShapeBuilder
{
public:
	misToolShapeBuilder(misApplicationType appType);
	~misToolShapeBuilder(void) = default;
	void SetToolRepresentationParam( misToolRepresentationType toolType, const misToolProperties& toolProp,
		bool measurementVirtualTipActivation) override;
	std::shared_ptr<IToolRepresentation> GetToolRepresentation() const override;
	void Clear() override;
private:
	static vtkSmartPointer<vtkPolyData> CreateGenericToolShape(misToolRepresentationType toolType, const misToolProperties& toolProp);
	void InitializeToolShapeColor(const misToolProperties& toolProp);
	void CreateToolRepresentation(const misToolProperties& toolProp, bool measurementVirtualTipEnabled);
	static vtkSmartPointer<vtkPolyData> CreateToolPolyData(const std::string& toolName);

private:
	std::shared_ptr<IToolRepresentation> m_ToolRepresentation;
	misApplicationType m_AppType;
};
