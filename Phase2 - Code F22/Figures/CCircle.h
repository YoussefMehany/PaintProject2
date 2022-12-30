#pragma once
#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	Point Radius;
	int radius;
public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	CCircle();
	virtual CFigure* GetNewFigure();
	virtual bool IsPointInside(Point P);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ChngClr();
	virtual void PrintInfo(Output* pOut);
	bool Resize(Point);
};
