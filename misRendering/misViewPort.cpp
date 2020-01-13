#include "StdAfx.h"
#include "misViewPort.h"

 
misViewPort::misViewPort( tgt::Vector2d start, tgt::Vector2d end)
	:m_Start(start), m_End(end)
{
}

misViewPort::misViewPort()
	:m_Start(tgt::Vector2d(0, 0)), m_End(tgt::Vector2d(1, 1))
{

}

tgt::vec2 misViewPort::GetStart()
{
	return m_Start;
}

tgt::vec2 misViewPort::GetEnd()
{
	return m_End;
}

double misViewPort::Width()
{
	return (m_End - m_Start).x;
}

double misViewPort::Height()
{
	return (m_End- m_Start).y;
}
