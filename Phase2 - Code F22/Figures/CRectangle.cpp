#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
void CRectangle::MoveTo(Point P)
{
	int length=0, width = 0;
	length = abs(Corner1.x - Corner2.x);
	width= abs(Corner1.y - Corner2.y);
	Corner1.x = P.x - .5 * length;
	Corner1.y = P.y - .5 * width;
	Corner2.x = P.x + .5 * length;
	Corner2.y = P.y + .5 * width;
}