#include "CHexagon.h"

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Side = 100;
}


void CHexagon::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawHex(Center, FigGfxInfo, Selected);
}
void CHexagon::MoveTo(Point P) {
	Center = P;
}
bool CHexagon::IsPointInside(Point P) {
	double vectorsx[6];
	double vectorsy[6];
	double vectorsmag[6];
	Point V[6];
	V[0].x = Center.x - Side * sqrt(3) / 2, V[1].x = Center.x, V[2].x = Center.x + Side * sqrt(3) / 2,
	V[3].x = Center.x + Side * sqrt(3) / 2, V[4].x = Center.x, V[5].x = Center.x - Side * sqrt(3) / 2;
	V[0].y = Center.y - Side / 2, V[1].y = Center.y - Side, V[2].y = Center.y - Side / 2,
	V[3].y = Center.y + Side / 2, V[4].y = Center.y + Side, V[5].y = Center.y + Side / 2;
	for (int i = 0; i < 6; i++) {
		vectorsx[i] = V[i].x - P.x;
		vectorsy[i] = V[i].y - P.y;
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