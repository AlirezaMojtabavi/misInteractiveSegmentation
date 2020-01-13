#include "StdAfx.h"
#include "misDepthIndicatorRepresentation.h"

misDepthIndicatorRepresentation::misDepthIndicatorRepresentation(void):misSurfaceRepresentation("DepthIndicator")
{
	double offfset[2];
	offfset[0]=100;
	offfset[1]=100;

	m_StickerMapper = misStickerMapper::New();
	m_Sticker = vtkActor::New();//misStickerModelActor::New(1500,offfset);
	m_Sticker->SetMapper(m_StickerMapper);
	m_Actors.push_back(m_Sticker);
}


misDepthIndicatorRepresentation::~misDepthIndicatorRepresentation(void)
{
}

 
void misDepthIndicatorRepresentation::SetRenderer( vtkRenderer* renderer )
{
	//m_Sticker->SetRenderer(renderer);
}

misStickerMapper * misDepthIndicatorRepresentation::GetStickerMapper()
{
	return this->m_StickerMapper;
}
