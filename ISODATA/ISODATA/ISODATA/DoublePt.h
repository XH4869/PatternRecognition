#pragma once
#include "atltypes.h"
class CDoublePt :
	public CPoint
{
public:
	CDoublePt();
	virtual ~CDoublePt();
	void operator=(CPoint point);
	double m_x;
	double m_y;
};

