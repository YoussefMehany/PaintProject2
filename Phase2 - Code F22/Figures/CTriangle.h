#pragma once
#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corners[3];
	Point Center;
	int Index;
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	CTriangle();
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
