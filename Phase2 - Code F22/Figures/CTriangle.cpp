#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corners[0] = P1; Corners[1] = P2; Corners[2] = P3;
	FigType = triangle;
	CalcCenter();
}
CTriangle::CTriangle()
{
	FigType = triangle;
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTrig(Corners[0], Corners[1], Corners[2], FigGfxInfo, Selected);
}
void CTriangle::CalcCenter()
{
	Center.x = (Corners[0].x + Corners[1].x + Corners[2].x) / 3;
	Center.y = (Corners[0].y + Corners[1].y + Corners[2].y) / 3;
}
void CTriangle::MoveTo(Point P)
{
	//getting the new corners
	for (int i = 0; i < 3; i++)
	{
		Corners[i].x += P.x - Center.x;
		Corners[i].y += P.y - Center.y;
	}
	Center = P;
}
void CTriangle::Resize(Point P)
{
	Corners[Index] = P;
}
bool CTriangle::IsCorner(Point P)
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(Corners[i].x - P.x) <= error && abs(Corners[i].y - P.y) <= error)
		{
			Index = i;
			return true;
		}
	}
	return false;
}
bool CTriangle::IsPointInside(Point P)
{
	double vectorsx[3];
	double vectorsy[3];
	double vectorsmag[3];
	for (int i = 0; i < 3; i++)
	{
		vectorsx[i] = Corners[i].x - P.x;
		vectorsy[i] = Corners[i].y - P.y;
	}
	for (int i = 0; i < 3; i++)
	{
		vectorsmag[i] = sqrt(pow(vectorsx[i], 2) + pow(vectorsy[i], 2));
	}
	double angle = 0;
	for (int i = 0; i < 3; i++)
	{
		int nextpoint = (i + 1) % 3;
		double dotproduct = vectorsx[i] * vectorsx[nextpoint] + vectorsy[i] * vectorsy[nextpoint];
		double magnitudeproduct = vectorsmag[i] * vectorsmag[nextpoint];
		angle += acos(dotproduct / magnitudeproduct);
	}
	if (abs(angle - 6.283) < 0.1) return true;
	return false;
}
void CTriangle::Save(ofstream& OutFile)
{
	string DrawClr = getColor(FigGfxInfo.DrawClr);
	string FillClr;
	OutFile << triangle << '\t' << ID << '\t';
	for (int i = 0; i < 3; i++)
	{
		OutFile << Corners[i].x << '\t' << Corners[i].y << '\t';
	}
	if (FigGfxInfo.isFilled == true)
	{
		FillClr = getColor(FigGfxInfo.FillClr);
	}
	else {
		FillClr = "NO_FILL";
	}
	OutFile << DrawClr << '\t' << FillClr << '\n';
}
void CTriangle::Load(ifstream& InFile)
{
	string Word;
	InFile >> Word;
	ID = stoi(Word);
	for (int i = 0; i < 3; i++)
	{
		InFile >> Word;
		Corners[i].x = stoi(Word);
		InFile >> Word;
		Corners[i].y = stoi(Word);
	}
	InFile >> Word;
	FigGfxInfo.DrawClr = getColorr(Word);
	InFile >> Word;
	if (Word != "NO_FILL")
	{
		FigGfxInfo.FillClr = getColorr(Word);
		FigGfxInfo.isFilled = true;
	}
}
CFigure* CTriangle::GetNewFigure()
{
	CTriangle* P = new CTriangle(Corners[0], Corners[1], Corners[2], FigGfxInfo);
	P->ID = ID;
	P->SetSelected(IsSelected());
	return P;
}
void CTriangle::ChngClr()
{
	UI.DrawColor = FigGfxInfo.DrawClr;
	UI.IsFilled = FigGfxInfo.isFilled;
	UI.FillColor = FigGfxInfo.FillClr;

}
void CTriangle::PrintInfo(Output* pOut)
{
	string info;
	info = "You selected a Triangle with ID: " + to_string(ID) + ", First Corner(" + to_string(Corners[0].x) + ", " + to_string(Corners[0].y) + ")";
	info += ", Second Corner(" + to_string(Corners[1].x) + ", " + to_string(Corners[1].y) + ")";
	info += ", Third Corner(" + to_string(Corners[2].x) + ", " + to_string(Corners[2].y) + ")";
	pOut->PrintMessage(info);
}