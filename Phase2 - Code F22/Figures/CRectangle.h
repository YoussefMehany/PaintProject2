#pragma once
#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Center;
	int Length, Width;
public:
	CRectangle(Point, Point, GfxInfo FigureGfxInfo);
	CRectangle();
	void Calc_Length_Width();
	virtual void Draw(Output* pOut) const;
	virtual void MoveTo(Point P);
	virtual bool IsPointInside(Point P);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual void ChngClr();
	virtual CFigure* GetNewFigure();
	virtual void PrintInfo(Output* pOut);
	virtual void Resize(Point P);
	virtual bool IsCorner(Point P);
	void CalcCenter();
};