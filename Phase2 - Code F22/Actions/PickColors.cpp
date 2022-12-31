#include "PickColors.h"

PickColors::PickColors(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	
}
//Reads parameters required for action to execute (code depends on action type)
void PickColors::ReadActionParameters()
{
	CCounter = 0;
	FCounter = 0;
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
bool PickColors::Execute(bool ReadParams)
{
	if (ReadParams) 
	{
		ReadActionParameters();
	}
	if (pManager->IsSoundOn()) 
	{
		PlaySound(TEXT("Sound/Pick_a_color.wav"), NULL, SND_SYNC);
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
	int ColorCount = pManager->GetClrCount(Random);
	if (color == "NO COLORED FIG")
	{
		pOut->PrintMessage("NO COLORED FIGURE");
		Reset();
		return true;
	}
	pManager->UpdateInterface();
	pOut->PrintMessage("Pick All " + color + " Figures");
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		if (P.y >= 0 && P.y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			if (ClickedItemOrder == PLAYCLR)
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
		if (select->getColor() == color && !select->IsBlocked())
		{
			CCounter++;
		}
		else
		{
			if (select->IsBlocked()) i--;
			else FCounter++;
		}
		if (CCounter == ColorCount)
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
bool PickColors::CanBeRecorded() const
{
	return false;
}
void PickColors::Reset()
{
	pManager->SetClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}