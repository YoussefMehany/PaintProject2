#include "CSquare.h"

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Side = 200;
}
void CSquare::Draw(Output* pOut) const
{
	//Call Output::DrawSquare to draw a Square on the screen	
	pOut->DrawSquare(Center, Side, FigGfxInfo, Selected);
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
void CSquare::Save(ofstream& OutFile)
{
	//<< '\t' 
	string DrawClr = getColorName(FigGfxInfo.DrawClr);
	OutFile << square << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << Side << '\t' << DrawClr << '\t';


	if (FigGfxInfo.isFilled == true)
	{
		string FillClr = getColorName(FigGfxInfo.FillClr);
		OutFile << FillClr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}