#ifndef CTRINAGLE_H
#define CTRIANGLE_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corners[3];
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	virtual void Save(ofstream& OutFile);
};

#endif