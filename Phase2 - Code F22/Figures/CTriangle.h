#pragma once
#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corners[3];
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	CTriangle();
	virtual CFigure* GetNewFigure();
	virtual bool IsPointInside(Point P);
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void PrintInfo(Output* pOut);
	virtual void ChngClr();
	bool Resize(Point);
};
