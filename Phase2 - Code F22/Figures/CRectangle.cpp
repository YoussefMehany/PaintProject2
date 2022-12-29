#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Calc_Length_Width();
	FigType = rectangle;
}
CRectangle::CRectangle()
{
	FigType = rectangle;
}
void CRectangle::Calc_Length_Width()
{
	Length = abs(Corner1.x - Corner2.x);
	Width = abs(Corner1.y - Corner2.y);
}
void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
void CRectangle::MoveTo(Point P)
{
	Corner1.x = P.x - .5 * Length;
	Corner1.y = P.y - .5 * Width;
	Corner2.x = P.x + .5 * Length;
	Corner2.y = P.y + .5 * Width;
}
bool CRectangle::IsPointInside(Point P) 
{
	int minimumx = (Corner1.x <= Corner2.x ? Corner1.x : Corner2.x);
	int maximumx = (minimumx == Corner1.x ? Corner2.x : Corner1.x);
	int minimumy = (Corner1.y <= Corner2.y ? Corner1.y : Corner2.y);
	int maximumy = (minimumy == Corner1.y ? Corner2.y : Corner1.y);
	if (P.x >= minimumx && P.x <= maximumx && P.y >= minimumy && P.y <= maximumy) 
	{
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
void CRectangle::Load(ifstream& InFile) 
{
	string Word;
	InFile >> Word;
	ID = stoi(Word);
	InFile >> Word;
	Corner1.x = stoi(Word);
	InFile >> Word;
	Corner1.y = stoi(Word);
	InFile >> Word;
	Corner2.x = stoi(Word);
	InFile >> Word;
	Corner2.y = stoi(Word);
	Calc_Length_Width();
	InFile >> Word;
	FigGfxInfo.DrawClr = getColorr(Word);
	InFile >> Word;
	if (Word != "NO_FILL") 
	{
		FigGfxInfo.FillClr = getColorr(Word);
		FigGfxInfo.isFilled = true;
	}
}
CFigure* CRectangle::GetNewFigure()
{
	CRectangle* P = new CRectangle(Corner1, Corner2, FigGfxInfo);
	P->ID = ID;
	P->SetSelected(IsSelected());
	return P;
}
void CRectangle::ChngClr()
{
	UI.DrawColor = FigGfxInfo.DrawClr;
	UI.IsFilled = FigGfxInfo.isFilled;
	UI.FillColor = FigGfxInfo.FillClr;

}
void CRectangle::PrintInfo(Output* pOut) 
{
	string info;
	info = "You selected a Rectangle with ID: " + to_string(ID) + ", First Corner(" + to_string(Corner1.x) + ", " + to_string(Corner1.y) + ")";
	info += ", Second Corner(" + to_string(Corner2.x) + ", " + to_string(Corner2.y) + ")" + ", Length = " + to_string(Length) + ", Width = " + to_string(Width);
	pOut->PrintMessage(info);
}