#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = P2;
	radius = (int)sqrt(pow((Radius.x - Center.x), 2) + pow((Radius.y - Center.y), 2));
	FigType = circle;
}
CCircle::CCircle()
{
	FigType = circle;
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
	OutFile << circle << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << Radius.x << '\t' << Radius.y << '\t' << DrawClr << '\t' << FillClr << '\n';
}
void CCircle::Load(ifstream& InFile) {
	string Word;
	InFile >> Word;
	ID = stoi(Word);
	InFile >> Word;
	Center.x = stoi(Word);
	InFile >> Word;
	Center.y = stoi(Word);
	InFile >> Word;
	Radius.x = stoi(Word);
	InFile >> Word;
	Radius.y = stoi(Word);
	radius = (int)sqrt(pow((Radius.x - Center.x), 2) + pow((Radius.y - Center.y), 2));
	InFile >> Word;
	FigGfxInfo.DrawClr = getColorr(Word);
	InFile >> Word;
	if (Word != "NO_FILL") {
		FigGfxInfo.FillClr = getColorr(Word);
		FigGfxInfo.isFilled = true;
	}
}
CFigure* CCircle::GetNewFigure()
{
	CCircle* P = new CCircle(Center, Radius, FigGfxInfo);
	P->ID = ID;
	P->SetSelected(IsSelected());
	return P;
}
void CCircle::ChngClr()
{
	UI.DrawColor = FigGfxInfo.DrawClr;
	UI.IsFilled = FigGfxInfo.isFilled;
	UI.FillColor = FigGfxInfo.FillClr;

}
void CCircle::PrintInfo(Output* pOut) {
	string info;
	info = "You selected a Circle with ID: " + to_string(ID) + ", Center Coordinates(" + to_string(Center.x) + ", " + to_string(Center.y) + ")";
	info += ", Point on Radius Coordinates(" + to_string(Radius.x) + ", " + to_string(Radius.y) + ")";
	info += ", Radius Length = " + to_string(radius);
	pOut->PrintMessage(info);
}