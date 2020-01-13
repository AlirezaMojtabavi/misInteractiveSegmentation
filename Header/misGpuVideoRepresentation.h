#pragma once

#include "misPlanarRepresentation.h"
#include "misVideoTextureCreator.h"

class misGpuVideoRepresentation : public misPlanarRepresentation
{
private:
	misVideoTextureCreator::Pointer m_VideoTextureCreator;
public:
	
	igstkStandardClassBasicTraitsMacro(misGpuVideoRepresentation,misPlanarRepresentation);
	static Pointer New(std::string name);
	
	void RenderVideoTexture();
	void InitializeVideoCreator(misTexturePropertyStruct Texture);
	void StartVideo();
	void TerminateVideo();

private:
	
	misGpuVideoRepresentation(std::string name);
	~misGpuVideoRepresentation(void);

	void SetVideoTextureProperties(misVideoTextureProperties videoProp);
	std::wstring s2ws(const std::string& s);

	
};

