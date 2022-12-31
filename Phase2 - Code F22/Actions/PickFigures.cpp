#include "PickFigures.h"

PickFigures::PickFigures(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	
}
//Reads parameters required for action to execute (code depends on action type)
void PickFigures::ReadActionParameters()
{
	CCounter = 0;
	FCounter = 0;
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
bool PickFigures::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Pick_a_figure.wav"), NULL, SND_SYNC);
	}
	CFigure* select = NULL;
	int figcount = pManager->GetFigCount();
	if (figcount == 0)
	{
		pOut->PrintMessage("NO FIGURE");
		return true;
	}
	Random = rand() % figcount;
	FigType = pManager->GetRandomFig(Random);
	if (FigType == noshape)
	{
		pOut->PrintMessage("NO FIGURES");
		Reset();
		return true;
	}
	pManager->UpdateInterface();
	pOut->PrintMessage("Pick All " + TypetoString(FigType));
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		if (P.y >= 0 && P.y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			if (ClickedItemOrder == PLAYTYPE)
			{
				Reset();
				Execute();
				return true;
			}
		}
		select = pManager->GetFigure(P);
		if (!select)
		{
			i--;
			continue;
		}
		if (select->GetFigType() == FigType && !select->IsBlocked())
		{
			CCounter++;
		}
		else
		{
			if (select->IsBlocked()) i--;
			else FCounter++;
		}
		if (CCounter == pManager->GetRandFigCount())
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
bool PickFigures::CanBeRecorded() const
{
	return false;
}
string PickFigures::TypetoString(shape FigType) 
{
	if (FigType == hexagon) return "Hexagons";
	if (FigType == triangle) return "Triangles";
	if (FigType == square) return "Squares";
	if (FigType == rectangle) return "Rectangles";
	if (FigType == circle) return "Circles";
}
void PickFigures::Reset()
{
	pManager->SetRandFigCount(0);
	pManager->SetTypeClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}