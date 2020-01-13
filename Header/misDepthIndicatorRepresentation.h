#pragma once

#include "misRepresentation.h"
#include "misStickerMapper.h"
#include "misStickerModelActor.h"
#include "misSurfaceRepresentation.h"

class misDepthIndicatorRepresentation :
	public misSurfaceRepresentation
{
private:
	//misStickerModelActor* m_Sticker;
	vtkActor* m_Sticker;

	misStickerMapper* m_StickerMapper;

	misDepthIndicatorRepresentation(void);
	~misDepthIndicatorRepresentation(void);

public:
	igstkStandardClassBasicTraitsMacro( misDepthIndicatorRepresentation, misSurfaceRepresentation ) 
	static Pointer New();
	void SetRenderer(vtkRenderer* renderer);

	misStickerMapper * GetStickerMapper();

};

