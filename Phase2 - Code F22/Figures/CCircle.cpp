#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = P2;
	radius = (int)sqrt(pow((Radius.x - Center.x), 2) + pow((Radius.y - Center.y), 2));
}


void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCircle to draw a Circle on the screen	
	pOut->DrawCir(Center, Radius, FigGfxInfo, Selected);
}
void CCircle::MoveTo(Point P)
{
	Center = P;
	Radius.x = radius + P.x;
	Radius.y = P.y;
}
bool CCircle::IsPointInside(Point P) {
	int distance = (int)sqrt(pow((P.x - Center.x), 2) + pow((P.y - Center.y), 2));
	if (distance <= radius) return true;
	return false;
}
void CCircle::Save(ofstream& OutFile)
{
	string DrawClr = getColor(FigGfxInfo.DrawClr);
	string FillClr;
	if (FigGfxInfo.isFilled == true)
	{
		FillClr = getColor(FigGfxInfo.FillClr);
	}
	else {
		FillClr = "NO_FILL";
	}
	OutFile << circle << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << radius << '\t' << DrawClr << '\t' << FillClr << '\n';
}