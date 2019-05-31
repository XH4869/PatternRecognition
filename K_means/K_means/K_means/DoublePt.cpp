#include "stdafx.h"
#include "DoublePt.h"


CDoublePt::CDoublePt()
	: x(0)
	, y(0)
{
}


CDoublePt::~CDoublePt()
{
}


BOOL CDoublePt::operator!=(CDoublePt Point)
{
	return (x != Point.x || y != Point.y);
}


BOOL CDoublePt::operator==(CDoublePt Point)
{
	return (x == Point.x&&y == Point.y);
}


void CDoublePt::operator=(CPoint Point)
{
	x = (double)Point.x;
	y = (double)Point.y;
}