#pragma once
#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	int Length, Width;
public:
	CRectangle(Point, Point, GfxInfo FigureGfxInfo);
	CRectangle();
	virtual CFigure* GetNewFigure();
	virtual bool IsPointInside(Point P);
	void Calc_Length_Width();
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void PrintInfo(Output* pOut);
	virtual void ChngClr();
	bool Resize(Point);
};