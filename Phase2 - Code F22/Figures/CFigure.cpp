#include "CFigure.h"

int CFigure::ID_Num = 0;
CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Blocked = false;
	ID = ++ID_Num;
}

CFigure::CFigure()
{
	FigGfxInfo.isFilled = false;
	Selected = false;
}
void CFigure::SetBlock(bool B)
{
	Blocked = B;
}
bool CFigure::IsBlocked() const
{
	return Blocked;
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
	if (clr == BISQUE) 
	{
		if (FigGfxInfo.isFilled == false) 
			return "NO FILL CLR";
		return getColor(FigGfxInfo.FillClr);
	}
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
color CFigure::getColorr(string clr)
{
	if (clr == "BISQUE") 
	{
		return FigGfxInfo.FillClr;
	}
	if (clr == "BLUE")
	{
		return BLUE;
	}
	if (clr == "GREEN")
	{
		return GREEN;
	}
	if (clr == "WHITE")
	{
		return WHITE;
	}
	if (clr == "RED")
	{
		return RED;
	}
	if (clr == "BLACK")
	{
		return BLACK;
	}
	if (clr == "ORANGE")
	{
		return ORANGE;
	}
	if (clr == "YELLOW")
	{
		return YELLOW;
	}
}
