#include "StdAfx.h"
#include "misImageSlicerMapper.h"

#include "misApplicationSetting.h"
#include "misException.h"
#include "misImageContainedDataType.h"
#include "misVTKMattoTgtMatConvertor.h"
#include "misPlaneContrast.h"


char *textFileRead(char *fn);

misImageSlicerMapper::misImageSlicerMapper(IMAGEORIENTATION imageOrientation)
	:m_program(nullptr), m_UseContrastShader(true), m_maskTextureID(0), m_useMaskFlag(0), m_shiftInDirectionValue(0.0)

{
	m_pTimer = vtkTimerLog::New();
	m_Orientation = imageOrientation;
	m_GroupImageContainedTFs.resize(2);
	for (int i = 0; i < 2; i++)
		m_GroupImageContainedTFs[i].resize(6);
	m_GroupTextureViewingProperties.resize(4);
	for (int i = 0; i < m_GroupTextureViewingProperties.size(); i++)
		InitialTextureColorValue(i);

	m_planeNames.resize(4);
	m_OrientationTransform = tgt::Matrix::createIdentity();
	InitializeCoorinatePoints();
	m_ShaderHeaderGenerator =
		std::make_shared<misShaderHeaderGeneratorforImageViewer>(m_planeNames, m_GroupTextureViewingProperties,
			m_GroupImageContainedTFs);

}

misImageSlicerMapper::~misImageSlicerMapper(void)
{
	delete m_program;
}

void misImageSlicerMapper::CreateGLSLObjects()
{
	m_ShaderHeaderGenerator->setOldShaderIsUsed(false);
	m_ShaderHeaderGenerator->ComposeHeader();
	tgt::ShaderManager* shdrmgr = Singleton<tgt::ShaderManager>::GetInstance();
	if (m_program)
		delete m_program;
	m_program = shdrmgr->loadSeparate("NewMultiTextureVertex.vert", "NewMultiTextureFragment.frag",
		m_ShaderHeaderGenerator->GetHeader(), false);
	if (!m_program)
		throw misException("Failed to load shaders: passthrough.vert, fragment.frag");
}

std::string misImageSlicerMapper::ConvertPlaneIndexToString(int id)
{
	if (id < 0)
		return "";
	std::ostringstream planeNum;
	planeNum << "grProp_" << id + 1  << "_";
	return planeNum.str();
}

std::string misImageSlicerMapper::ConvertSegmentedObjectIndexToString(int groupIndex, int objectIndex)
{
	if (groupIndex < 0 || objectIndex < 0)
		return "";

	std::ostringstream planeNum;
	planeNum << "GroupContainedColorMap_" << groupIndex + 1 << "_" << objectIndex + 1 << "_";
	return planeNum.str();
}

void misImageSlicerMapper::SetShaderVariables(vtkRenderer *ren, vtkActor *a)
{
	//We define TextureUnits locally and due to consideration of unit numbers order.
	//The most important point: shader just works by units and only knows the units. it doesn't matter what is textureID. In shader, we can assign more than one textureID to a unique Unit.
	//As we found, the priority of Texture_3D is higher than priority of Texture_2D, and priority of Texture_1D is the lowest. 
	//So, if  we assign a Texture_3D and a Texture_1D or Texture_2D to one unit at the same time, only Texture_3D is showed, and other textures are ignored.
	//And if we assign several Texture to one unit, the last one is showed and the others are ignored.
	//Therefore,in the case of Texture_3Ds, we always active the unit at first and then if the visibility of that is false, we disable it. 
	//i.e. mainImageTextureUnit and segmentedImageTextureUnit.
	//We don't have any Texture_2D in this case. but if we do, it must be activated and disabled in correct conditions.
	if (!m_program)
		CreateGLSLObjects();
	int loopVarient = 0;
	if (sizeof(ImageContainedDataType) == sizeof(unsigned short))
		loopVarient = 6;

	typedef std::vector<tgt::TextureUnit> unitArray;

	unitArray  mainImageTextureUnit;
	unitArray  segmentedImageTextureUnit;
	unitArray  fmriImageTextureUnit;
	unitArray  segmentedImageTransFuncTextureUnit;
	unitArray  colorMapTransFuncTextureUnit;
	unitArray  windowLevelTransFuncTextureUnit;
	std::vector<unitArray>  segmentedObjectTFUnit;
	unitArray  fmriTransFuncTextureUnit;

	tgt::TextureUnit  videoTextureUnit;
	tgt::TextureUnit  videoTransferFuncUnit;

	mainImageTextureUnit.resize(m_planeNames.size());
	segmentedImageTextureUnit.resize(m_planeNames.size());
	fmriImageTextureUnit.resize(m_planeNames.size());
	segmentedImageTransFuncTextureUnit.resize(m_planeNames.size());
	colorMapTransFuncTextureUnit.resize(m_planeNames.size());
	windowLevelTransFuncTextureUnit.resize(m_planeNames.size());
	fmriTransFuncTextureUnit.resize(m_planeNames.size());
	GLuint videoID = 0;
	segmentedObjectTFUnit.resize(m_planeNames.size());
	for (int k = 0; k < m_planeNames.size(); k++)
	{
		segmentedObjectTFUnit[k].resize(loopVarient); //assumption: just for 4 segmented objects
	}


	m_program->activate();
	m_program->setIgnoreUniformLocationError(true);

	for (int i = 0; i < m_planeNames.size(); i++)
	{
		if (m_planeNames[i] != "")
		{
			if (!m_GroupTextureViewingProperties[i].GetVisiblityOfMT() &&
				!m_GroupTextureViewingProperties[i].GetVisiblityofSegmentedImage() &&
				!m_GroupTextureViewingProperties[i].GetVisiblityOfColorMap())
				continue;
			if ((m_GroupTextureViewingProperties[i].MainImageID > 0) &&
				(m_GroupTextureViewingProperties[i].GetVisiblityOfMT()))
			{
				GLboolean istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].MainImageID);
				_ASSERT(istexturecheck == 1);
				_ASSERT(m_GroupTextureViewingProperties[i].MainImageID < 1000);
				if (istexturecheck)
				{
					m_program->setUniform(m_planeNames[i] + "UseColorForMT", m_GroupTextureViewingProperties[i].UseColorForMT);
					m_program->setUniform(m_planeNames[i] + "UseAlphaForMainBlending", m_GroupTextureViewingProperties[i].UseAlphaForMainBlending);
					auto color = m_GroupTextureViewingProperties[i].GetColorValueOfMainTexture();
					m_program->setUniform(m_planeNames[i] + "TexColorRedPart", static_cast<GLfloat>(color.Red));
					m_program->setUniform(m_planeNames[i] + "TexColorGreenPart", static_cast<GLfloat>(color.Green));
					m_program->setUniform(m_planeNames[i] + "TexColorBluePart", static_cast<GLfloat>(color.Blue));
					m_program->setUniform(m_planeNames[i] + "OpacityOfMT", m_GroupTextureViewingProperties[i].GetOpacityOfMT());
					m_program->setUniform(m_planeNames[i] + "CurrentWindowCenterOfMT", m_GroupTextureViewingProperties[i].CurrentWindowCenterOfMT);
					m_program->setUniform(m_planeNames[i] + "CurrentWindowWidthOfMT", m_GroupTextureViewingProperties[i].CurrentWindowWidthOfMT);
				}




				mainImageTextureUnit[i].activate();
				glBindTexture(GL_TEXTURE_3D, m_GroupTextureViewingProperties[i].MainImageID);
				m_program->setUniform(m_planeNames[i] + "baseTexture", mainImageTextureUnit[i].getUnitNumber());
				bool imageIsColored = m_GroupTextureViewingProperties[i].GetMainImageIsColored();
				m_program->setUniform(m_planeNames[i] + "mainImageIsColored", imageIsColored);
				if (!imageIsColored)
				{
					istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].GetWindowLevelTransferFuncID());
					_ASSERT(istexturecheck == 1);
					if (istexturecheck)
					{
						windowLevelTransFuncTextureUnit[i].activate();
						glBindTexture(GL_TEXTURE_1D, m_GroupTextureViewingProperties[i].GetWindowLevelTransferFuncID());
						m_program->setUniform(m_planeNames[i] + "TransferFuncofWindowLevel", windowLevelTransFuncTextureUnit[i].getUnitNumber());

					}
				}
			}

			if ((m_GroupTextureViewingProperties[i].GetSegmentedImageID() > 0) && (m_GroupTextureViewingProperties[i].GetVisiblityofSegmentedImage()))
			{
				GLboolean istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].GetSegmentedImageID());
				_ASSERT(istexturecheck == 1);
				_ASSERT(m_GroupTextureViewingProperties[i].GetSegmentedImageID() < 1000);
				if (istexturecheck)
				{
					segmentedImageTextureUnit[i].activate();
					glBindTexture(GL_TEXTURE_3D, m_GroupTextureViewingProperties[i].GetSegmentedImageID());
					m_program->setUniform(m_planeNames[i] + "segmentedTexture", segmentedImageTextureUnit[i].getUnitNumber());

					auto imageContainedTFs = m_GroupImageContainedTFs[i];
					for (int j = 0; j < loopVarient/*imageContainedTFs.size()*/; j++)
					{
						if (j < m_GroupImageContainedTFs[i].size() && imageContainedTFs[j].GetAssigned())
						{
							GLboolean ispolydataTexturecheck = glIsTexture(imageContainedTFs[j].GetTfId());
							_ASSERT(ispolydataTexturecheck == 1);
							_ASSERT(imageContainedTFs[j].GetTfId() < 1000);

							if (ispolydataTexturecheck)
							{
								segmentedObjectTFUnit[i][j].activate();
								glBindTexture(GL_TEXTURE_1D, imageContainedTFs[j].GetTfId());
								//m_program->setUniform(ConvertSegmentedObjectIndexToString(i , j)+"isActive", true);
								m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "TransferFunction", segmentedObjectTFUnit[i][j].getUnitNumber());
								m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "startBit", imageContainedTFs[j].allocatedByte[0]);
								int byteSize = imageContainedTFs[j].allocatedByte.size();
								m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "numberOfBits", byteSize);
							}
						}
						else
						{
							//m_program->setUniform(ConvertSegmentedObjectIndexToString(i , j)+"isActive", false);
							m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "TransferFunction", 0);
							m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "startBit", 0);
							m_program->setUniform(ConvertSegmentedObjectIndexToString(i, j) + "numberOfBits", 0);
						}
					}
				}

			}
			SetSkinBoneRenderingUniforms(m_GroupTextureViewingProperties[i], colorMapTransFuncTextureUnit[i], m_planeNames[i]);

			// Set FMRI Shader Variables
			if ((m_GroupTextureViewingProperties[i].GetfMRIImageID() > 0) && (m_GroupTextureViewingProperties[i].GetVisiblityofFmriImage()))
			{
				GLboolean istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].GetfMRIImageID());
				_ASSERT(istexturecheck == 1);
				_ASSERT(m_GroupTextureViewingProperties[i].GetfMRIImageID() < 1000);
				if (istexturecheck)
				{

					fmriImageTextureUnit[i].activate();
					glBindTexture(GL_TEXTURE_3D, m_GroupTextureViewingProperties[i].GetfMRIImageID());
					m_program->setUniform(m_planeNames[i] + ".fmriTexture", fmriImageTextureUnit[i].getUnitNumber());
				}
				if (m_GroupTextureViewingProperties[i].FmriImageTransferFuncID > 0)
				{
					istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].FmriImageTransferFuncID);
					_ASSERT(istexturecheck == 1);
					_ASSERT(m_GroupTextureViewingProperties[i].GetfMRIImageID() < 1000);
					if (istexturecheck)
					{
						fmriTransFuncTextureUnit[i].activate();
						glBindTexture(GL_TEXTURE_1D, m_GroupTextureViewingProperties[i].FmriImageTransferFuncID);
						m_program->setUniform(m_planeNames[i] + "TransferFuncofFmri", fmriTransFuncTextureUnit[i].getUnitNumber());
					}
				}
			}
		}
	}

	UpdatePlaneAndTexturePoints();
	//the position of VTKActor must be set after points are updated
	a->SetPosition(m_P1[0], m_P1[1], m_P1[2]);


	glBegin(GL_QUADS);
	BuildPlane();
	glEnd();




	m_program->deactivate();

}


void misImageSlicerMapper::SetSkinBoneRenderingUniforms(const misTextureViewingProperties& texureProp,
	tgt::TextureUnit& colorMapTransFuncTextureUnit,
	std::string planeName)
{
	if (!texureProp.GetColorMap() || (!texureProp.GetVisiblityOfColorMap()))
		return;
	auto IsTexture = glIsTexture(texureProp.GetColorMap()->getTexture()->getId());
	GLboolean istexturecheck = IsTexture;
	_ASSERT(istexturecheck == 1);
	_ASSERT(texureProp.GetColorMap()->getTexture()->getId() < 1000);
	if (!istexturecheck)
		return;
	colorMapTransFuncTextureUnit.activate();
	glBindTexture(GL_TEXTURE_1D, texureProp.GetColorMap()->getTexture()->getId());
	m_program->setUniform(planeName + "TransferFuncofColorMap", colorMapTransFuncTextureUnit.getUnitNumber());
}

void misImageSlicerMapper::SetWindowLevel(misWindowLevelStr normalizedWinLevStr, int groupIndex)
{
	m_GroupTextureViewingProperties[groupIndex].CurrentWindowCenterOfMT = normalizedWinLevStr.GetWindowCenter();
	m_GroupTextureViewingProperties[groupIndex].CurrentWindowWidthOfMT = normalizedWinLevStr.GetWindowWidth();
}

void misImageSlicerMapper::SetUsingTransferFunctionForMainImage(bool usingColored, int groupIndex)
{
	m_GroupTextureViewingProperties[groupIndex].SetMainImageIsColored(usingColored);

}

void misImageSlicerMapper::InitializeGrid()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				m_Grid[i][j][k].x = i * 0.5;
				m_Grid[i][j][k].y = j * 0.5;
				m_Grid[i][j][k].z = k * 0.5;

			}
		}
	}
}

void misImageSlicerMapper::SetColorValueToTexture(misDoubleColorStruct colorVal, int groupIndex)
{
	m_GroupTextureViewingProperties[groupIndex].SetColorValueOfMainTexture(colorVal);
}

void misImageSlicerMapper::InitialTextureColorValue(int groupIndex)
{
	const auto whiteColor = misDoubleColorStruct(1.0, 1.0, 1.0, 1.0);
	m_GroupTextureViewingProperties[groupIndex].SetColorValueOfMainTexture(whiteColor);
 }

void misImageSlicerMapper::SetOpacityValueToTexture(float opacityValue, int groupIndex)
{
	if (opacityValue != m_GroupTextureViewingProperties[groupIndex].GetOpacityOfMT())
	{
		m_GroupTextureViewingProperties[groupIndex].SetOpacityOfMT(opacityValue);
		ChangeOpacities(groupIndex);
	}
}

void misImageSlicerMapper::SetMaskTextureID(GLuint MaskTexID)
{
	m_maskTextureID = MaskTexID;
}

void misImageSlicerMapper::SetUseMaskFlag(int UseMaskFlag)
{
	m_useMaskFlag = UseMaskFlag;
}

void misImageSlicerMapper::SetShiftInDirectionValue(float ShiftValue)
{
	m_shiftInDirectionValue = ShiftValue;
}

void misImageSlicerMapper::SetVisibilityOfSegmentedImage(int groupIndex, bool val) //image contained polydata
{
	m_GroupTextureViewingProperties[groupIndex].SetVisiblityofSegmentedImage(val);
	CreateGLSLObjects();
}

void misImageSlicerMapper::SetVisibilityOfFmriImage(int groupIndex, bool val)
{
	m_GroupTextureViewingProperties[groupIndex].SetVisiblityofFmriImage(val);
	CreateGLSLObjects();
}

void misImageSlicerMapper::SetSegmentedImageTransFunc(std::shared_ptr<TransFuncIntensity> tf, int groupIndex)
{
	m_GroupTextureViewingProperties[groupIndex].SetSegmentedImageTransferFunc(tf);
}

void misImageSlicerMapper::SetFmriImageTransFuncID(int val, int groupIndex)
{
	bool notRepeated = (m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID != val);
	if (notRepeated)
	{
		if (glIsTexture(m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID))
			glDeleteTextures(1, (GLuint*)&m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID);
	}

	m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID = val;
}

void misImageSlicerMapper::UpdateCoordinatePoints(int groupIndex)
{
 	const auto transposed = transpose(m_GroupCoordinateProperties[groupIndex].Transform);
	for (int i = 0; i < 4; i++)
	{
		const auto temp = m_InitialPoints[i] * transposed;
		m_GroupCoordinateProperties[groupIndex].TransformedPoints[i] = temp;
	}
}

void misImageSlicerMapper::SetMainImageTextureID(int val, int groupIndex)
{

	glBindTexture(GL_TEXTURE_3D, val);
	m_GroupTextureViewingProperties[groupIndex].MainImageID = val;
	glBindTexture(GL_TEXTURE_3D, 0);
}

void misImageSlicerMapper::SetSegmentedImageTextureID(int val, int groupIndex)
{
	if ((m_GroupTextureViewingProperties[groupIndex].GetSegmentedImageID() > 0) && (m_GroupTextureViewingProperties[groupIndex].GetSegmentedImageID() != val))
	{
		GLuint textures[1];
		textures[0] = m_GroupTextureViewingProperties[groupIndex].GetSegmentedImageID();
		glDeleteTextures(1, textures);
	}

	m_GroupTextureViewingProperties[groupIndex].SetSegmentedImageID(val);
}

void misImageSlicerMapper::SetFmriImageTextureID(int val, int groupIndex)
{
	int prevFmriImageUid = m_GroupTextureViewingProperties[groupIndex].GetfMRIImageID();
	if (prevFmriImageUid > 0 && prevFmriImageUid != val)
	{
		GLuint textures[1];
		textures[0] = m_GroupTextureViewingProperties[groupIndex].GetfMRIImageID();
		glDeleteTextures(1, textures);
	}
	m_GroupTextureViewingProperties[groupIndex].SetfMRIImageID(val);
}

void misImageSlicerMapper::InitializeCoorinatePoints()
{
	UpdateCoordinatePoints(0);
	UpdateCoordinatePoints(1);
}

void misImageSlicerMapper::AddTextureGroup(int index)
{
	if (m_planeNames[index] == "")
	{
		m_planeNames[index] = ConvertPlaneIndexToString(index);
	}
}

void misImageSlicerMapper::RemoveTextureGroup(int index)
{
	if (m_planeNames[index] == ConvertPlaneIndexToString(index))
	{
		m_planeNames[index] = "";
	}
}

void misImageSlicerMapper::GeneratePlaneMesh(misTexturePropertyStruct prop)
{
	misQuadMapperBase::GeneratePlaneMesh(prop);
}

void misImageSlicerMapper::SetVisibilityOfMainTexture(int groupIndex, bool val)
{
	m_GroupTextureViewingProperties[groupIndex].SetVisiblityOfMT(val);
	CreateGLSLObjects();
}

void misImageSlicerMapper::SetColorMapTransFuncID(int groupIndex, std::shared_ptr<TransFuncIntensity> val)
{
	m_GroupTextureViewingProperties[groupIndex].SetColorMap(val);
}

void misImageSlicerMapper::SetVisiblityOfColorMap(int groupIndex, bool val) //volume data
{
	m_GroupTextureViewingProperties[groupIndex].SetVisiblityOfColorMap(val);
	CreateGLSLObjects();
}

void misImageSlicerMapper::ChangeOpacities(int groupIndex)
{
	float op0 = double(m_GroupTextureViewingProperties[0].GetOpacityOfMT());
	float op1 = double(m_GroupTextureViewingProperties[1].GetOpacityOfMT());

	double MAX = std::max(op1, op0);
	if (MAX == 0)
	{
		m_GroupTextureViewingProperties[groupIndex].SetOpacityOfMT(0.0);
	}
	else
	{
		double NorMalizedOpacity = m_GroupTextureViewingProperties[groupIndex].GetOpacityOfMT() / MAX;
		float newOpacity = pow(NorMalizedOpacity, double(0.33));
		m_GroupTextureViewingProperties[groupIndex].SetOpacityOfMT(newOpacity);


	}
}

void misImageSlicerMapper::AddDeformitytoGrid()  // deformation test
{
	m_Grid[1][1][1].x = 0.0;
	m_Grid[1][1][1].y = 0.0;
	m_Grid[1][1][1].z = 0.0;
	m_Grid[1][1][0].x = 0.0;
	m_Grid[1][1][0].y = 0.0;
	m_Grid[1][1][0].z = 0.0;

}

void misImageSlicerMapper::SetWindowLevelTransferFunctionTextureID(int layerIndex, int textureId)  // window level transfer function
{

	m_GroupTextureViewingProperties[layerIndex].SetWindowLevelTransferFuncID(textureId);
}

void misImageSlicerMapper::SetMatrixTransform(tgt::mat4 transformMatrix, int groupIndex)
{
	m_GroupCoordinateProperties[groupIndex].Transform = transformMatrix;
	UpdateCoordinatePoints(groupIndex);
}

void misImageSlicerMapper::Render(vtkRenderer *ren, vtkActor *a)
{
	if (GetIsContrastShaderUsed())
	{
		SetShaderVariables(ren, a);
	}

	glDisable(GL_TEXTURE_3D);

	glActiveTexture(GL_TEXTURE0);
}

void misImageSlicerMapper::BuildPlane()
{
	_ASSERT(m_shiftInDirectionValue >= 0);

	glMultiTexCoord3f(GL_TEXTURE0,
		m_GroupCoordinateProperties[0].TransformedPoints[0].x,
		m_GroupCoordinateProperties[0].TransformedPoints[0].y,
		m_GroupCoordinateProperties[0].TransformedPoints[0].z);
	glMultiTexCoord3f(GL_TEXTURE1,
		m_GroupCoordinateProperties[1].TransformedPoints[0].x,
		m_GroupCoordinateProperties[1].TransformedPoints[0].y,
		m_GroupCoordinateProperties[1].TransformedPoints[0].z);


	glVertex3f(m_P1[0], m_P1[1], m_P1[2]);


	glMultiTexCoord3f(GL_TEXTURE0,
		m_GroupCoordinateProperties[0].TransformedPoints[1].x,
		m_GroupCoordinateProperties[0].TransformedPoints[1].y,
		m_GroupCoordinateProperties[0].TransformedPoints[1].z);
	glMultiTexCoord3f(GL_TEXTURE1,
		m_GroupCoordinateProperties[1].TransformedPoints[1].x,
		m_GroupCoordinateProperties[1].TransformedPoints[1].y,
		m_GroupCoordinateProperties[1].TransformedPoints[1].z);


	glVertex3f(m_P2[0], m_P2[1], m_P2[2]);

	glMultiTexCoord3f(GL_TEXTURE0, m_GroupCoordinateProperties[0].TransformedPoints[2].x, m_GroupCoordinateProperties[0].TransformedPoints[2].y, m_GroupCoordinateProperties[0].TransformedPoints[2].z);
	glMultiTexCoord3f(GL_TEXTURE1, m_GroupCoordinateProperties[1].TransformedPoints[2].x, m_GroupCoordinateProperties[1].TransformedPoints[2].y, m_GroupCoordinateProperties[1].TransformedPoints[2].z);

	glVertex3f(m_P3[0], m_P3[1], m_P3[2]);

	glMultiTexCoord3f(GL_TEXTURE0, m_GroupCoordinateProperties[0].TransformedPoints[3].x, m_GroupCoordinateProperties[0].TransformedPoints[3].y, m_GroupCoordinateProperties[0].TransformedPoints[3].z);
	glMultiTexCoord3f(GL_TEXTURE1, m_GroupCoordinateProperties[1].TransformedPoints[3].x, m_GroupCoordinateProperties[1].TransformedPoints[3].y, m_GroupCoordinateProperties[1].TransformedPoints[3].z);


	glVertex3f(m_P4[0], m_P4[1], m_P4[2]);
}


void misImageSlicerMapper::SetImageContainedTF(ImageContainedTransferFuncs ImgCntTF, int groupIndex)
{
	m_GroupImageContainedTFs[groupIndex] = ImgCntTF;
	CreateGLSLObjects();

}


void misImageSlicerMapper::ClearFmriTransferFunctionIDs(int groupIndex)
{
	if (glIsTexture(m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID))
	{
		GLuint textures[1];
		textures[0] = m_GroupTextureViewingProperties[groupIndex].FmriImageTransferFuncID;
		glDeleteTextures(1, textures);
	}
}

void misImageSlicerMapper::SetOrientation(IMAGEORIENTATION newOrientatio)
{
	m_Orientation = newOrientatio;
	SetInitialSetting();
}

void misImageSlicerMapper::SetUseColorForTexture(bool val, int groupIndex)
{
	this->m_GroupTextureViewingProperties[groupIndex].UseColorForMT = val;
}

bool misImageSlicerMapper::GetUseColorForTexture(int groupIndex)
{
	return this->m_GroupTextureViewingProperties[groupIndex].UseColorForMT;
}

double* misImageSlicerMapper::GetDimention()
{
	misSimplePointType  p1, p2, p3, pt1, pt2, vec, final;
	p1 = m_P1;
	p2 = m_P2;
	p3 = m_P3;
	vec = p2;
	vec.Minus(p1);
	vec.Sum(p3);
	final = vec;
	vec.Multiply(m_OrintationDir);
	double*  elem = new double[2];
	for (int i = 0; i < 3; i++)
	{
		if (vec[i] == 0)
			elem[i] = final[i];
	}
	return  elem;
}

void misImageSlicerMapper::SetInitialSetting()
{

	m_OrintationDir = m_CornerProperties->GetPlaneNormal();
	switch (m_Orientation)
	{
	case AXIAL:
	{
		m_InitialPoints[0] = tgt::vec4(0, 0, 0, 1);
		m_InitialPoints[1] = tgt::vec4(1, 0, 0, 1);
		m_InitialPoints[2] = tgt::vec4(1, 1, 0, 1);
		m_InitialPoints[3] = tgt::vec4(0, 1, 0, 1);
		break;
	}
	case CORONAL:
	{
		m_InitialPoints[0] = tgt::vec4(0, 0, 0, 1);
		m_InitialPoints[1] = tgt::vec4(1, 0, 0, 1);
		m_InitialPoints[2] = tgt::vec4(1, 0, 1, 1);
		m_InitialPoints[3] = tgt::vec4(0, 0, 1, 1);
		break;
	}
	case SAGITTAL:
	{
		m_InitialPoints[0] = tgt::vec4(0, 0, 0, 1);
		m_InitialPoints[1] = tgt::vec4(0, 1, 0, 1);
		m_InitialPoints[2] = tgt::vec4(0, 1, 1, 1);
		m_InitialPoints[3] = tgt::vec4(0, 0, 1, 1);
		break;
	}
	case UNKnownDirection:
	{
		_ASSERT(0 == 1);
		break;
	}
	default:
		_ASSERT(0 == 1);
	}

}

void misImageSlicerMapper::UpdatePlaneAndTexturePoints()
{
	if (!m_CornerProperties)
		return;
	auto planePoints = m_CornerProperties->GetPlanePoints(m_Orientation);
	if (planePoints.size() == 4)
	{
		m_P1 = planePoints[0];
		m_P2 = planePoints[1];
		m_P3 = planePoints[2];
		m_P4 = planePoints[3];

		auto texturePoints = m_CornerProperties->GetTexturePoints(m_Orientation);
		for (int i = 0; i < 4; i++)
		{
			double tempPoint[3];
			texturePoints[i].GetPoint(tempPoint);
			m_InitialPoints[i] = tgt::vec4(tempPoint[0], tempPoint[1], tempPoint[2], 1);
		}
		InitializeCoorinatePoints();
	}

}


 

vtkMapper* misImageSlicerMapper::GetMapper()
{
	return  static_cast<vtkMapper*>(this);
}

void misImageSlicerMapper::SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProp)
{
	misQuadMapperBase::SetCornerProperties(pCornerProp);
}

float misImageSlicerMapper::GetOpacityValueOfTexture(int groupIndex)
{
	return m_GroupTextureViewingProperties[groupIndex].GetOpacityOfMT();
}

bool misImageSlicerMapper::GetVisibilityOfMainTexture(int groupIndex)const
{
	return m_GroupTextureViewingProperties[groupIndex].GetVisiblityOfMT();

}

void misImageSlicerMapper::SetIsContrastShaderUsed(bool val)
{
	m_UseContrastShader = val;

}

bool misImageSlicerMapper::GetIsContrastShaderUsed()
{
	return m_UseContrastShader;
}

void misImageSlicerMapper::UseAlphaForBlending(bool val, int groupIndex)
{
	this->m_GroupTextureViewingProperties[groupIndex].UseAlphaForMainBlending = val;
}

bool misImageSlicerMapper::GetUseAlphaForBlending(int groupIndex)
{
	return this->m_GroupTextureViewingProperties[groupIndex].UseAlphaForMainBlending;
}
