#pragma once

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center;
	Point Corners[6];
	int Side;	
public:
	CHexagon(Point, GfxInfo FigureGfxInfo);
	CHexagon();
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	void CalcCorners(Point* Corners);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ChngClr();
	virtual CFigure* GetNewFigure();
	virtual void PrintInfo(Output* pOut);
};
