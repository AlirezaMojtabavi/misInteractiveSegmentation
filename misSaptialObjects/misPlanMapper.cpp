#include "..\Header\misPlanMapper.h"
#include "StdAfx.h"
#include "misPlanMapper.h"

#include "misException.h"

misPlanMapper::misPlanMapper(std::weak_ptr<ICornerProperties> cornerProperties, std::string shaderFileName, parcast::PlanSettingParam biopsyPlanParam, bool displayCross) :
	m_program(nullptr), m_CornerProperties(cornerProperties), m_ShaderFileName(shaderFileName),
	planParam(biopsyPlanParam), m_DisplayCross(displayCross)
{
}

misPlanMapper::~misPlanMapper(void)
{
	delete m_program;
}

void misPlanMapper::CreateGLSLObjects()
{
	auto shdrmgr = Singleton<tgt::ShaderManager>::GetInstance();
	if(m_program)
		delete m_program;
	m_program = shdrmgr->loadSeparate("NewMultiTextureVertex.vert", m_ShaderFileName, "", false);
	if (!m_program)
		throw misException("Failed to load shaders: passthrough.vert, fragment.frag");
}

void misPlanMapper::SetShaderVariables(vtkRenderer *ren, vtkActor *a)
{
	if (!m_program)
	{
		CreateGLSLObjects();
	}
	auto isOblique = misMathUtils::IsPerpendicular(parcast::VectorD3(m_NormalPlane[0], m_NormalPlane[1], m_NormalPlane[2]),
		parcast::PointD3(m_PlanStart[0], m_PlanStart[1], m_PlanStart[2]),
		parcast::PointD3(m_PlanEnd[0], m_PlanEnd[1], m_PlanEnd[2]));
	m_program->activate();
	m_program->setIgnoreUniformLocationError(true);
	m_program->setUniform("startPoint", m_PlanStart[0], m_PlanStart[1], m_PlanStart[2]);
	m_program->setUniform("endPoint", m_PlanEnd[0], m_PlanEnd[1], m_PlanEnd[2]);
	m_program->setUniform("planRadius", planParam.planDiameter/2);
	m_program->setUniform("targetRadius", m_TargetRadius);
	m_program->setUniform("screwColor", m_Color);
	m_program->setUniform("borderInlineOpacity", planParam.borderInlineOpacity);
	m_program->setUniform("borderOpacity", planParam.borderOpacity);
	m_program->setUniform("displayCrossSection", planParam.displayCrossSection);
	m_program->setUniform("displayProjection", planParam.displayProjection);
	m_program->setUniform("currentPoint", m_CurrentPoint[0], m_CurrentPoint[1], m_CurrentPoint[2]);
	m_program->setUniform("interSectionPoint", m_InterSectionPoint[0], m_InterSectionPoint[1], m_InterSectionPoint[2]);
	m_program->setUniform("normalPlane", m_NormalPlane[0], m_NormalPlane[1], m_NormalPlane[2]);
	m_program->setUniform("dashlineSize", planParam.dashLineSize);
	m_program->setUniform("intersectionColor", planParam.intersectionColor.r, planParam.intersectionColor.g, planParam.intersectionColor.b, planParam.intersectionColor.opacity);
	m_program->setUniform("intersectionRadius", planParam.intersectionRadius);
	m_program->setUniform("isOblique", isOblique);
	m_program->setUniform("isCrossSectionVisible", m_DisplayCross);
	

	const auto cornerProperties = m_CornerProperties.lock();
	if (cornerProperties)
	{
		const auto planCenter = cornerProperties->GetPlaneCenter();
		m_program->setUniform("imageExtent", static_cast<float>(planCenter.data[0]) * 2,
			static_cast<float>(planCenter.data[1]) * 2, static_cast<float>(planCenter.data[2]) * 2);

		auto planeNormal = cornerProperties->GetPlaneNormal();
		double planeNormalMat[3];
		planeNormal.GetPoint(planeNormalMat);
		m_program->setUniform("planeNormal",
			static_cast<float>(planeNormalMat[0]), static_cast<float>(planeNormalMat[1]), static_cast<float>(planeNormalMat[2]));
	}

	BuildPlane();
	m_program->deactivate();
}

void misPlanMapper::Render(vtkRenderer *ren, vtkActor *a)
{
	SetShaderVariables(ren, a);
	glDisable(GL_TEXTURE_3D);
	glActiveTexture(GL_TEXTURE0);
}

void misPlanMapper::SetColor(const tgt::vec3& color)
{
	m_Color = color;
}

void misPlanMapper::SetTargetRadius(double radius)
{
	m_TargetRadius = radius;
}

void misPlanMapper::BuildPlane()
{
	const auto cornerProperties = m_CornerProperties.lock();
	if (!cornerProperties)
	{
		return;
	}

	auto planePoints = cornerProperties->GetPlanePoints(AXIAL);
	auto textureCoords = cornerProperties->GetTexturePoints(AXIAL);
	if (planePoints.empty() || textureCoords.empty())
	{
		return;
	}

	glBegin(GL_QUADS);
	glTexCoord3f(textureCoords[0][0], textureCoords[0][1], textureCoords[0][2]);
	glVertex3f(planePoints[0][0], planePoints[0][1], planePoints[0][2]);

	glTexCoord3f(textureCoords[1][0], textureCoords[1][1], textureCoords[1][2]);
	glVertex3f(planePoints[1][0], planePoints[1][1], planePoints[1][2]);

	glTexCoord3f(textureCoords[2][0], textureCoords[2][1], textureCoords[2][2]);
	glVertex3f(planePoints[2][0], planePoints[2][1], planePoints[2][2]);

	glTexCoord3f(textureCoords[3][0], textureCoords[3][1], textureCoords[3][2]);
	glVertex3f(planePoints[3][0], planePoints[3][1], planePoints[3][2]);
	glEnd();
}

void misPlanMapper::SetStartPoint(parcast::Point<float, 3> point)
{
	m_PlanStart = point;
}

void misPlanMapper::SetEndPoint(parcast::Point<float, 3> point)
{
	m_PlanEnd = point;
}

void misPlanMapper::SetRadius(double radius)
{
	planParam.planDiameter = radius;
}

void misPlanMapper::SetCurrentPoint(parcast::Point<float, 3> point)
{
	m_CurrentPoint = point;
}

void misPlanMapper::SetInterSectionPoint(parcast::Point<float, 3> point)
{
	m_InterSectionPoint = point;
}

void misPlanMapper::SetNormalPlane(parcast::Vector<float,3> vector)
{
	m_NormalPlane = vector;
}

double* misPlanMapper::GetBounds()
{
	Bounds[0] = m_PlanStart[0];
	Bounds[1] = m_PlanEnd[0];
	Bounds[2] = m_PlanStart[1];
	Bounds[3] = m_PlanEnd[1];
	Bounds[4] = m_PlanStart[2];
	Bounds[5] = m_PlanEnd[2];
	return Bounds;
}

void misPlanMapper::GetBounds(double bounds[6])
{
	bounds[0] = m_PlanStart[0];
	bounds[1] = m_PlanEnd[0];
	bounds[2] = m_PlanStart[1];
	bounds[3] = m_PlanEnd[1];
	bounds[4] = m_PlanStart[2];
	bounds[5] = m_PlanEnd[2];
}

