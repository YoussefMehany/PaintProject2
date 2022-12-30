#pragma once
#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point Center;
	int Side;
public:
	CSquare(Point, GfxInfo FigureGfxInfo);
	CSquare();
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
