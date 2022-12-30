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
	virtual CFigure* GetNewFigure();
	virtual bool IsPointInside(Point P);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ChngClr();
	virtual void PrintInfo(Output* pOut);
	void CalcCorners(Point* Corners);
	bool Resize(Point);
};
