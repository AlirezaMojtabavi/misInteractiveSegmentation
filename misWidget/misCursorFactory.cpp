#include "stdafx.h"
#include "misCursorFactory.h"

#include "misCompleteCursor.h"
#include "misEnums.h"
#include "misPreciseCursor.h"
#include "misSimpleCursor.h"
#include "misThickCursor.h"

vtkSmartPointer<misCursor> misCursorFactory::MakeNewCursor(misCursorType cursorType)
{
	switch (cursorType)
	{
	case CompleteCursor:
	{
		auto cursor = vtkSmartPointer<misCompleteCursor>::New();
		return cursor;
	}

	case PreciseCursor:
	{
		auto cursor = vtkSmartPointer<misPreciseCursor>::New();
		return cursor;
	}

	case SimpleCursor:
	{
		auto cursor = vtkSmartPointer<misSimpleCursor>::New();
		return cursor;
	}
	case ThickCursorSize1:
	case ThickCursorSize2:
	case ThickCursorSize3:
		return vtkSmartPointer<misThickCursor>::New();
	}
	return nullptr;
}
