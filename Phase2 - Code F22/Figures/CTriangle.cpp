#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}


void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTrig(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}
void CTriangle::MoveTo(Point P)
{
	Point Center1;
	Center1.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Center1.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	//getting the new first corner
	Corner1.x = P.x +Corner1.x - Center1.x ;
	Corner1.y = P.y + Corner1.y - Center1.y;
	//getting the new second corner
	Corner2.x = P.x + Corner2.x - Center1.x;
	Corner2.y = P.y + Corner2.y - Center1.y;
	//getting the new third corner
	Corner3.x = P.x + Corner3.x - Center1.x;
	Corner3.y = P.y + Corner3.y - Center1.y;
}
bool CTriangle::IsPointInside(Point P) {
	double vectorsx[3];
	double vectorsy[3];
	double vectorsmag[3];
	Point V[3];
	V[0] = Corner1; V[1] = Corner2; V[2] = Corner3;
	for (int i = 0; i < 3; i++) {
		vectorsx[i] = V[i].x - P.x;
		vectorsy[i] = V[i].y - P.y;
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