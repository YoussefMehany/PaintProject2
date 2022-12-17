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
bool CRectangle::IsPointInside(Point P) {
	int minimumx = (Corner1.x <= Corner2.x ? Corner1.x : Corner2.x);
	int maximumx = (minimumx == Corner1.x ? Corner2.x : Corner1.x);
	int minimumy = (Corner1.y <= Corner2.y ? Corner1.y : Corner2.y);
	int maximumy = (minimumy == Corner1.y ? Corner2.y : Corner1.y);
	if (P.x >= minimumx && P.x <= maximumx && P.y >= minimumy && P.y <= maximumy) {
		return true;
	}
	return false;
}
void CRectangle::Save(ofstream& OutFile)
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
	OutFile << rectangle << '\t' << ID << '\t' << Corner1.x << '\t' << Corner1.y << '\t' << Corner2.x << '\t' << Corner2.y << '\t' << DrawClr << '\t' << FillClr << '\n';
}