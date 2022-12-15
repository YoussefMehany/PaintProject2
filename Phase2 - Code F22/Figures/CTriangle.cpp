#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corners[0] = P1; Corners[1] = P2; Corners[2] = P3;
}


void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTrig(Corners[0], Corners[1], Corners[2], FigGfxInfo, Selected);
}
void CTriangle::MoveTo(Point P)
{
	Point Center1;
	Center1.x = (Corners[0].x + Corners[1].x + Corners[2].x) / 3;
	Center1.y = (Corners[0].y + Corners[1].y + Corners[2].y) / 3;
	//getting the new corners
	for (int i = 0; i < 3; i++) {
		Corners[i].x += P.x - Center1.x;
		Corners[i].y += P.y - Center1.y;
	}
}
bool CTriangle::IsPointInside(Point P) {
	double vectorsx[3];
	double vectorsy[3];
	double vectorsmag[3];
	for (int i = 0; i < 3; i++) {
		vectorsx[i] = Corners[i].x - P.x;
		vectorsy[i] = Corners[i].y - P.y;
	}
	for (int i = 0; i < 3; i++) {
		vectorsmag[i] = sqrt(pow(vectorsx[i], 2) + pow(vectorsy[i], 2));
	}
	double angle = 0;
	for (int i = 0; i < 3; i++) {
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
	string DrawClr = getColorName(FigGfxInfo.DrawClr);
	OutFile << triangle << '\t' << ID << '\t' ;
	for (int i = 0; i < 3; i++) {
		OutFile << Corners[i].x << '\t' << Corners[i].y << '\t';
	}
	OutFile << DrawClr << '\t';
	if (FigGfxInfo.isFilled == true)
	{
		string FillClr = getColorName(FigGfxInfo.FillClr);
		OutFile << FillClr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}