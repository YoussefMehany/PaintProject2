#include "PickTypeandColor.h"


PickTypeandColor::PickTypeandColor(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();

}
//Reads parameters required for action to execute (code depends on action type)
void PickTypeandColor::ReadActionParameters()
{
	CCounter = 0;
	FCounter = 0;
	Random = 0;
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
bool PickTypeandColor::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Pick_a_figure_with_a_color.wav"), NULL, SND_SYNC);
	}
	CFigure* select = NULL;
	int figcount = pManager->GetFigCount();
	if (figcount == 0) 
	{
		pOut->PrintMessage("NO FIGURE");
		return true;
	}
	Random = rand() % figcount;
	color = pManager->GetRandomClr(Random);
	if (color == "NO COLORED FIG")
	{
		pOut->PrintMessage("NO COLORED FIGURE");
		Reset();
		return false;
	}
	pManager->UpdateInterface();
	FigType = pManager->GetRandomFig(Random);
	pOut->PrintMessage("Pick All " + TypetoString(FigType) + " with " + color + " color");
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		if (P.y >= 0 && P.y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			if (ClickedItemOrder == PLAYTYPECLR)
			{
				Reset();
				Execute();
				return false;
			}
		}
		select = pManager->GetFigure(P);
		if (!select)
		{
			i--;
			continue;
		}
		if (select->GetFigType() == FigType && select->getColor() == color)
		{
			CCounter++;
		}
		else
		{
			FCounter++;
		}
		if (CCounter == pManager->GetTypeClrCount())
		{
			pOut->PrintMessage("Correct : " + to_string(CCounter) + "      Incorrect : " + to_string(FCounter));
			break;
		}

		pManager->BlockFig(select);
		pManager->UpdateInterface();
	}
	Reset();
	return true;
}
bool PickTypeandColor::CanBeRecorded() const
{
	return false;
}
string PickTypeandColor::TypetoString(shape FigType) 
{
	if (FigType == hexagon) return "Hexagons";
	if (FigType == triangle) return "Triangles";
	if (FigType == square) return "Squares";
	if (FigType == rectangle) return "Rectangles";
	if (FigType == circle) return "Circles";
}
void PickTypeandColor::Reset()
{
	pManager->SetRandFigCount(0);
	pManager->SetClrCount(0);
	pManager->SetTypeClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}