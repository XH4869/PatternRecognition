#include "stdafx.h"
#include "DoublePt.h"


CDoublePt::CDoublePt()
	: m_x(0)
	, m_y(0)
{
}


CDoublePt::~CDoublePt()
{
}


void CDoublePt::operator=(CPoint point)
{
	m_x = (double)point.x;
	m_y = (double)point.y;
}