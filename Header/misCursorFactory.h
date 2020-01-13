#pragma once

class misCursor;
enum misCursorType;

class misCursorFactory
{
public :
	static vtkSmartPointer<misCursor> MakeNewCursor(misCursorType cursorType);
};
