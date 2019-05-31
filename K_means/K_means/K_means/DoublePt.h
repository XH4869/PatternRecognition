#pragma once
class CDoublePt
{
public:
	CDoublePt();
	virtual ~CDoublePt();
	BOOL operator != (CDoublePt Point);
	BOOL operator ==(CDoublePt Point);
	void operator = (CPoint Point);
	double x;
	double y;
};

