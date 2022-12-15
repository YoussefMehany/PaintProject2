#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	Point Radius;
	int radius;
public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	virtual void Save(ofstream& OutFile);
};

#endif