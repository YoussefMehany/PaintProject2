#ifndef CHEX_H
#define CHEX_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center;
	Point Corners[6];
	int Side;	
public:
	CHexagon(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	void CalcCorners(Point* Corners);
	virtual void Save(ofstream& OutFile);
};

#endif