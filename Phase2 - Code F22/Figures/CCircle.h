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
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ChngClr();
	virtual CFigure* GetNewFigure();
	virtual void Resize(Point P);
	virtual bool IsCorner(Point P);
	virtual void PrintInfo(Output* pOut);
	void CalcRadius();
};
