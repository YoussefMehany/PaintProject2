#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}
void CFigure::SetID(int id) {
	ID = id;
}
int CFigure::GetID()const
{
	return ID;
}
void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	
	FigGfxInfo.DrawClr = Dclr; 
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
string CFigure::getColor(color clr)
{
	if (clr == BLUE)
	{
		return "BLUE";
	}

	if (clr == GREEN)
	{
		return "GREEN";
	}

	if (clr == WHITE)
	{
		return "WHITE";
	}

	if (clr == RED)
	{
		return "RED";
	}

	if (clr == BLACK)
	{
		return "BLACK";
	}

	if (clr == ORANGE)
	{
		return "ORANGE";
	}

	if (clr == YELLOW)
	{
		return "YELLOW";
	}
}
