#include "StdAfx.h"

#include "misColorStruct.h"
#include "misException.h"
#include "misPanoramicMapper.h"
#include "misTransFunctionBuilder.h"

misPanoramicMapper* misPanoramicMapper::New()
{
	return new misPanoramicMapper;
}

misPanoramicMapper::misPanoramicMapper()
	: m_Width(1.0), 
	m_Height(1.0), 
	m_Slice(0.0), 
	m_Transferfunction(0), 
	m_ImageTexture(0), 
	m_PanoramicTextureID(0), 
	m_Program(Singleton<tgt::ShaderManager>::GetInstance()->loadSeparate("panoramic.vert", "panoramic.frag","",false))
{
	if (!m_Program)
		throw misException("Failed to load shader: eep_simple.vert, eep_simple.frag");
	m_Range[0] = m_Range[1] = 0;
}

misPanoramicMapper::~misPanoramicMapper()
{

}

void misPanoramicMapper::SetPanoramicTextureData(float *pixelData, int width, int height)
{
	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, pixelData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	m_PanoramicTextureID = textureId;

}

void misPanoramicMapper::SetImage( GLuint imageTexture )
{
	m_ImageTexture = imageTexture;
}


void misPanoramicMapper::SetWindowLevel(const misWindowLevelStr& windowLevel)
{
	m_WindowLevel = windowLevel;
	// Normalize windowLevel

	m_WindowLevel.SetWindowParams(windowLevel.GetWindowCenter() / windowLevel.GetWindowWidth() + 0.5, 1);
	
	misTransFunctionBuilder builder;
	misColorStruct	colorstr;
	m_Transferfunction = builder.GenerateTransferFunction(windowLevel, false, m_Range , colorstr);
}

misWindowLevelStr misPanoramicMapper::GetWindowLevel() const
{
	return m_WindowLevel;
}

void misPanoramicMapper::SetTransferFunctionID( std::shared_ptr<TransFuncIntensity> colorTransferFunc )
{
	m_Transferfunction = colorTransferFunc;
}

double misPanoramicMapper::GetWidth() const
{
	return m_Width;
}

void misPanoramicMapper::SetWidth( double val )
{
	m_Width = val;
}

double misPanoramicMapper::GetHeight() const
{
	return m_Height;
}

void misPanoramicMapper::SetHeight( double val )
{
	m_Height = val;
}

void misPanoramicMapper::SetSlice( double slice )
{
	m_Slice = slice;
}

void misPanoramicMapper::Render( vtkRenderer *ren, vtkActor *a )
{
	if (m_ImageTexture == 0 || m_Transferfunction == 0 || m_PanoramicTextureID == 0)
		return;
	glEnable(GL_TEXTURE_3D);
	m_Program->activate();
	SetUniformVariables();
	DrawQuad();
	m_Program->deactivate();
	glDisable(GL_TEXTURE_3D);
}

void misPanoramicMapper::DrawQuad()
{
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, m_Slice);

	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0, m_Height, m_Slice);

	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(m_Width, m_Height, m_Slice);

	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(m_Width, 0, m_Slice);
	glEnd();
}

void misPanoramicMapper::SetUniformVariables()
{
	const int ExpansionDirection = 2;
	m_Program->setUniform(std::string("slice"), static_cast<float>((m_Slice + m_Depth / ExpansionDirection ) / m_Depth));

	tgt::TextureUnit textureUintImage;
	textureUintImage.activate();
	glBindTexture(GL_TEXTURE_3D, m_ImageTexture);
	m_Program->setUniform(std::string("image"), (GLint)textureUintImage.getUnitNumber());



	tgt::TextureUnit textureUintCurve;
	textureUintCurve.activate();
	glBindTexture(GL_TEXTURE_2D, m_PanoramicTextureID);
	bool founded = m_Program->setUniform(std::string("curveTexture"), (GLint)textureUintCurve.getUnitNumber());


	tgt::TextureUnit textureUintTransfer;
	textureUintTransfer.activate();
	glBindTexture(GL_TEXTURE_1D, m_Transferfunction->getTexture()->getId() );
	m_Program->setUniform("transferFuncofWindowLevel", static_cast<GLint>(textureUintTransfer.getUnitNumber()));
}

void misPanoramicMapper::GetBounds( double bounds[6] )
{
	bounds[0] = 0;
	bounds[1] = m_Width;
	bounds[2] = 0;
	bounds[3] = m_Height;
	bounds[4] = 0;
	bounds[5] = m_Depth;
}

void misPanoramicMapper::SetDepth( double depth )
{
	m_Depth = depth;
}

void misPanoramicMapper::SetRange( double *range )
{
	m_Range[0] = range[0];
	m_Range[1] = range[1];
}
