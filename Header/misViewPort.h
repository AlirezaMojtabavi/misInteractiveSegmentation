#pragma once

//view port: start and end point of rectangle in normalized 2d coordinate like 0,0,0.5,0.5
struct misViewPort
{

public:
	// default start :0,0 default end :(1,1)
	misViewPort();
	misViewPort(tgt::Vector2d start, tgt::Vector2d end);
	tgt::vec2 GetStart();
	tgt::vec2 GetEnd();
 	double Width();
	double Height();
private:
	tgt::Vector2d m_Start;
	tgt::Vector2d m_End;
};

