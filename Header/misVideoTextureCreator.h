#pragma once

#include "misCornerProperties.h"
#include "misObject.h"
#include "misTexturePropertyStruct.h"
class misVideoStarter;

class misVideoTextureCreator: public misOldObject
{
private:

	misVideoStarter* m_pVideoStarter;
	tgt::Texture* m_ErrorText;

	std::vector<misSimplePointType> m_VideoPlanePointVector;
	std::vector<misSimplePointType> m_VideoTexturePointVector;
	IMAGEORIENTATION m_Orientation;
	misCornerProperties::Pointer m_CornerProperties;

	GLuint	m_VideoTextureTransferFunctionID;
public:

	void Initialize(misTexturePropertyStruct PlaneProp ,std::wstring deviceName , IMAGEORIENTATION orientation);
	void Initialize(std::wstring deviceName , IMAGEORIENTATION orientation);
	misVideoTextureProperties GetVideoTextureProperties();
	void TerminateVideoCapture();
	void UpdateCurrentPosition(double pos[3]);
	void UpdateTransform(vtkMatrix4x4* currentMatrix);
	void CreateVideo( std::wstring deviceName );

private:

	misVideoTextureCreator(void);
	~misVideoTextureCreator(void);

	GLuint GenerateVideoTexture();
	void UpdatePlaneTexturePoints();

	BYTE* CutSonoBuffer(BYTE* buffer);

public:
	typedef misVideoTextureCreator		Self;  
	typedef misOldObject				Superclass; 
	typedef ::itk::SmartPointer< Self >			Pointer; 
	typedef ::itk::SmartPointer< const Self >   ConstPointer; 
	static Pointer New(void);


};