#include "CSquare.h"

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Side = 200;
}
CSquare::CSquare()
{
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
	string DrawClr = getColor(FigGfxInfo.DrawClr);
	string FillClr;
	if (FigGfxInfo.isFilled == true)
	{
		FillClr = getColor(FigGfxInfo.FillClr);
	}
	else {
		FillClr = "NO_FILL";
	}
	OutFile << square << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << DrawClr << '\t' << FillClr << '\n';
}
void CSquare::Load(ifstream& InFile) {
	string Word;
	InFile >> Word;
	ID = stoi(Word);
	InFile >> Word;
	Center.x = stoi(Word);
	InFile >> Word;
	Center.y = stoi(Word);
	InFile >> Word;
	FigGfxInfo.DrawClr = getColorr(Word);
	InFile >> Word;
	if (Word != "NO_FILL") {
		FigGfxInfo.FillClr = getColorr(Word);
		FigGfxInfo.isFilled = true;
	}
}
CFigure* CSquare::GetNewFigure()
{
	CSquare* P = new CSquare(Center, FigGfxInfo);
	P->ID = ID;
	P->SetSelected(IsSelected());
	return P;
}
void CSquare::ChngClr()
{
	UI.DrawColor = FigGfxInfo.DrawClr;
	UI.IsFilled = FigGfxInfo.isFilled;
	UI.FillColor = FigGfxInfo.FillClr;

}
void CSquare::PrintInfo(Output* pOut) {
	string info;
	info = "You selected a Square with ID: " + to_string(ID) + ", Center Coordinates(" + to_string(Center.x) + ", " + to_string(Center.y) + ")" + ", Side Length = " + to_string(Side);
	pOut->PrintMessage(info);
}