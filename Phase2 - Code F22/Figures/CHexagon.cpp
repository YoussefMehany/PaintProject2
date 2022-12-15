#include "CHexagon.h"

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Side = 100;
	CalcCorners(Corners);
}


void CHexagon::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawHex(Center, Side, FigGfxInfo, Selected);
}
void CHexagon::MoveTo(Point P) {
	Center = P;
	CalcCorners(Corners);
}
void CHexagon::CalcCorners(Point* Corners)
{
	Corners[0].x = Center.x - Side * sqrt(3) / 2, Corners[1].x = Center.x, Corners[2].x = Center.x + Side * sqrt(3) / 2,
	Corners[3].x = Center.x + Side * sqrt(3) / 2, Corners[4].x = Center.x, Corners[5].x = Center.x - Side * sqrt(3) / 2;
	Corners[0].y = Center.y - Side / 2, Corners[1].y = Center.y - Side, Corners[2].y = Center.y - Side / 2,
	Corners[3].y = Center.y + Side / 2, Corners[4].y = Center.y + Side, Corners[5].y = Center.y + Side / 2;
}

bool CHexagon::IsPointInside(Point P) {
	double vectorsx[6];
	double vectorsy[6];
	double vectorsmag[6];
	for (int i = 0; i < 6; i++) {
		vectorsx[i] = Corners[i].x - P.x;
		vectorsy[i] = Corners[i].y - P.y;
	}
	for (int i = 0; i < 6; i++) {
		vectorsmag[i] = sqrt(pow(vectorsx[i], 2) + pow(vectorsy[i], 2));
	}
	double angle = 0;
	for (int i = 0; i < 6; i++) {
		int nextpoint = (i + 1) % 6;
		double dotproduct = vectorsx[i] * vectorsx[nextpoint] + vectorsy[i] * vectorsy[nextpoint];
		double magnitudeproduct = vectorsmag[i] * vectorsmag[nextpoint];
		angle += acos(dotproduct / magnitudeproduct);
	}
	if (abs(angle - 6.283) < 0.1) return true;
	return false;
}
void CHexagon::Save(ofstream& OutFile)
{
	
	string DrawClr = getColor(FigGfxInfo.DrawClr);
	string FillClr;
	OutFile << hexagon << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t'; 
	for (int i = 0; i < 6; i++) {
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