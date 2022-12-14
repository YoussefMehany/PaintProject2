#include "CSquare.h"

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Side = 200;
}


void CSquare::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawSquare(Center, FigGfxInfo, Selected);
}
void CSquare::MoveTo(Point P)
{
	Center = P;
}
bool CSquare::IsPointInside(Point P) {
	int right = Center.x + Side / 2;
	int left = Center.x - Side / 2;
	int up = Center.y + Side / 2;
	int down = Center.y - Side / 2;
	if (P.x <= right && P.x >= left && P.y <= up && P.y >= down) {
		return true;
	}
	return false;
}
