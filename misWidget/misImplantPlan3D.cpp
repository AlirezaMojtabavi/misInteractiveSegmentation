#include "stdafx.h"
#include "misImplantPlan3D.h"

#include "misMathUtils.h"
#include "misSimpleLineImplant.h"

misImplantPlan3D::misImplantPlan3D(std::shared_ptr<IImplantSource> implantSource) :
	m_SimpleLineImplant(implantSource)
{
	m_LineSource->SetRadius(LineRadius);
	m_LineSource->SetHeight(LineHeight);
	m_LineSource->SetResolution(LineResolution);
	UpdateTransform();
	AppendMiddleLine();

}

vtkAlgorithmOutput* misImplantPlan3D::GetOutputPort()
{
	Update();
	return m_AppendFilter->GetOutputPort();
}

void misImplantPlan3D::UpdateTransform()
{
	m_Transform->RemoveAllInputs();
	const auto transform = m_SimpleLineImplant->GetTransform();
	m_Transform->SetTransform(transform);
	m_Transform->SetInputConnection(m_LineSource->GetOutputPort());
}

bool misImplantPlan3D::IsTransformChanged()
{
	auto const transform = vtkSmartPointer<vtkTransform>::New();
	m_Transform->GetTransform()->SafeDownCast(transform);
	return !misMathUtils::AreVtkTransformsClose(m_SimpleLineImplant->GetTransform(), transform, 1E-12);
}

void misImplantPlan3D::Update()
{
	if (IsTransformChanged())
	{
		UpdateTransform();
		AppendMiddleLine();
	}
}

void misImplantPlan3D::AppendMiddleLine()
{
	m_AppendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
	m_AppendFilter->AddInputConnection(m_SimpleLineImplant->GetOutputPort());
	m_AppendFilter->AddInputConnection(m_Transform->GetOutputPort());
	m_AppendFilter->Update();
}