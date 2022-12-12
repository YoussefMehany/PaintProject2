#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = P2;
}


void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCircle to draw a Circle on the screen	
	pOut->DrawCir(Center, Radius, FigGfxInfo, Selected);
}
 void CCircle::MoveTo(Point P)
 {
	 int radius = sqrt(pow((Radius.x - Center.x), 2) + pow((Radius.y - Center.y), 2));
	 Center = P;
	 Radius.x = radius + P.x;
	 Radius.y = P.y;
 }