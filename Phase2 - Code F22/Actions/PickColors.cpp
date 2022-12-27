#include "PickColors.h"

PickColors::PickColors(ApplicationManager* pApp) :Action(pApp)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	CCounter = 0;
	FCounter = 0;
}
//Reads parameters required for action to execute (code depends on action type)
void PickColors::ReadActionParameters()
{
	pManager->SetKEY(true);
	pOut->CreatePlayToolBar();
}

//Execute action (code depends on action type)
void PickColors::Execute()
{
	ReadActionParameters();
	if (pManager->IsSoundOn()) {
		PlaySound(TEXT("Sound/Pick_a_color.wav"), NULL, SND_SYNC);
	}
	CFigure* select = NULL;
	int figcount = pManager->getFigCount();
	color = pManager->GetRandomClr(Random);
	if (color == "NO COLORED FIG")
	{
		pOut->PrintMessage("NO COLORED FIGURE");
		pManager->SetClrCount(0);
		pManager->UnBlock();
		pManager->SetKEY(false);
		return;
	}
	pManager->UpdateInterface();
	pOut->PrintMessage("Pick All " + color + " Figures");
	for (int i = 0; i < figcount; i++)
	{
		pIn->GetPointClicked(P.x, P.y);
		select = pManager->GetFigure(P);
		if(!select)
		{
			i--;
			continue;
		}
		if (select->getColor() == color)
		{
			CCounter++;
		}
		else
		{
			FCounter++;
		}
		pOut->PrintMessage("Correct : " + to_string(CCounter) + "      Incorrect : " + to_string(FCounter));

		if (CCounter == pManager->GetClrCount())
			break;
		pManager->BlockFig(select);
		pManager->UpdateInterface();
	}
	pManager->SetClrCount(0);
	pManager->UnBlock();
	pManager->SetKEY(false);
}