#pragma once

#ifndef misColorTable_H
#define misColorTable_H

#include "misColorStruct.h"
#include "misMacros.h"
#include "misSeconderyNeededHeader.h"

// todo: check and add Inline
class  misColorTable
{
	misCreateVariableWithSetGetMacro(DefaultColor,misColorStruct);

private:

	misColorStruct*                    m_ColorArray;
	bool*                              m_ColorUpdatedStatusArray;
	bool                               m_UpdatedColorTable;
	int                                m_ArraySize;
	int                                m_MaxInt    ;

	misColorVector					   m_ColorArrayeVector;
	int								   m_NumberOfSegmentedImage;

protected:
	void        MakeDefaultColor(void);
	void        InitilazeColorArray(void);
	void	    CreateLookUpTableForSegmentedImage(void);
	void		CreateLookUpTableForSpecificImage(misColorStruct color);

public:
	 static	misColorTable* New(void)
	 {
		 return new misColorTable;
	 };

	 void                SetColorOfElement        (int elemetIndex,misColorStruct color );
	 void				 SetColorOfEmptyElement (unsigned int elemetIndex,misColorStruct color );
	 void                RemoveColorOfElemet      (int elemetIndex);
	 void                Clear(void);

	misColorStruct*               GetColorTable(void);
	misColorVector				  GetColortableVectorForSegmentedImage(void);
	misColorVector				  GetColortableVectorForSpecificImage(misColorStruct objectColor, bool showMargin = true); // it is ranged between	[ 0 255]
	void SetNumberOfSegmentedImage(int val);

	misColorTable(void);
   ~misColorTable(void);
};

#endif 